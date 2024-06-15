package app

import (
	bp "analyzer/pkg/frameworks/blueprint"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	gotypes "go/types"
	"path/filepath"
	"slices"
	"strings"

	"golang.org/x/tools/go/packages"
)

const (
	PACKAGE_PATH_POST_NOTIFICATION string = "github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification"
	PACKAGE_PATH_FOOBAR            string = "github.com/blueprint-uservices/blueprint/examples/foobar/workflow/foobar"
	// blueprint backend package
	PACKAGE_PATH_BLUEPRINT string = "github.com/blueprint-uservices/blueprint/runtime/core/backend"
)

func isBlueprintPackagePath(name string) bool {
	return name == PACKAGE_PATH_BLUEPRINT
}

func createPackage(app *App, goPackage *packages.Package, basePackagePath string) *types.Package {
	modulePath := ""
	if goPackage.Module != nil {
		modulePath = goPackage.Module.Path
	}

	newPackage := &types.Package{
		Name:              goPackage.Name,    // e.g. models
		PackagePath:       goPackage.PkgPath, // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification/models
		Module:            modulePath,        // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow
		ImportedPackages:  make(map[string]*types.Package),
		DeclaredTypes:     make(map[string]types.Type),
		ServiceTypes:      make(map[string]*types.ServiceType),
		DatastoreTypes:    make(map[string]types.Type),
		DeclaredVariables: make(map[string]types.Variable),
		ImportedTypes:     make(map[string]types.Type),
		TypesInfo:         goPackage.TypesInfo,
	}

	//TODO ADD FLAG FOR BLUEPRINT PACKAGE
	if strings.HasPrefix(goPackage.PkgPath, basePackagePath) {
		logger.Logger.Debugf("[APP] found internal package %s", goPackage.String())
		newPackage.Type = types.APP
		app.Packages[newPackage.Name] = newPackage
	} else if goPackage.PkgPath == PACKAGE_PATH_BLUEPRINT {
		logger.Logger.Debugf("[APP] found blueprint package %s", goPackage.String())
		newPackage.Type = types.BLUEPRINT
		app.BlueprintPackages[newPackage.Name] = newPackage
	} else {
		logger.Logger.Debugf("[APP] found external package %s", goPackage.String())
		newPackage.Type = types.EXTERNAL
	}

	return newPackage
}

func parseBlueprintPackage(bpPackage *types.Package) {
	packagesPattern := bpPackage.PackagePath
	pkgs, err := packages.Load(&packages.Config{Mode: packages.NeedName | packages.NeedModule | packages.NeedFiles | packages.NeedTypes | packages.NeedTypesInfo | packages.NeedSyntax | packages.NeedImports}, packagesPattern)
	if err != nil {
		logger.Logger.Fatalf("error loading packages from %s: %s", bpPackage.PackagePath, err.Error())
	}
	// should be only one package
	if len(pkgs) != 1 {
		logger.Logger.Fatalf("unexpected number of packages (%d) in blueprint backend %s", len(pkgs), bpPackage.PackagePath)
	}
	goPkg := pkgs[0]
	visitedNamedTypes := make(map[string]bool)
	for _, def := range goPkg.TypesInfo.Defs {
		if def == nil {
			continue
		}
		if _, isInterface := def.Type().Underlying().(*gotypes.Interface); isInterface {
			if namedGoType, ok := def.Type().(*gotypes.Named); ok {
				if visitedNamedTypes[namedGoType.String()] {
					continue
				}
				visitedNamedTypes[namedGoType.String()] = true

				typeName := namedGoType.Obj().Name()
				objectPackage := namedGoType.Obj().Pkg()
				if objectPackage == nil || objectPackage.Path() != bpPackage.PackagePath {
					continue
				}

				if bp.IsBlueprintBackendComponent(typeName) {
					backendType := &frameworks.BlueprintBackendType{
						Name:           typeName,
						Package:        objectPackage.Path(),
						NoSQLComponent: bp.IsBlueprintNoSQLComponent(typeName),
					}
					backendType.Methods = frameworks.BuildBackendComponentMethods(backendType.Name)
					bpPackage.AddDeclaredType(backendType)
					logger.Logger.Debugf("[BLUEPRINT] added blueprint backend %s", backendType.String())

				} else {
					logger.Logger.Debugf("[BLUEPRINT] ignoring type %s (%s): %v", utils.GetType(def.Type()), utils.GetType(def.Type().Underlying()), def.Type().String())
				}
			}
		}
	}
}

func (app *App) ParsePackages(servicesInfo []*types.ServiceInfo) {
	var basePackagePath string
	switch app.Name {
	case "postnotification":
		basePackagePath = PACKAGE_PATH_POST_NOTIFICATION
	case "foobar":
		basePackagePath = PACKAGE_PATH_FOOBAR
	default:
		logger.Logger.Fatalf("unknown application name %s", app.Name)
	}

	packagesPattern := basePackagePath + "/..."
	pkgs, err := packages.Load(&packages.Config{Mode: packages.NeedName | packages.NeedModule | packages.NeedFiles | packages.NeedTypes | packages.NeedTypesInfo | packages.NeedSyntax | packages.NeedImports}, packagesPattern)
	if err != nil {
		logger.Logger.Fatalf("error loading packages from %s: %s", basePackagePath, err.Error())
	}

	var services []string
	for _, info := range servicesInfo {
		services = append(services, info.Name)
	}

	allPackages := make(map[string]*types.Package)
	allGoPackages := make(map[*types.Package]*packages.Package)
	for _, goPkg := range pkgs {
		if _, exists := allPackages[goPkg.PkgPath]; !exists {
			newPackage := createPackage(app, goPkg, basePackagePath)
			allPackages[goPkg.PkgPath] = newPackage
			allGoPackages[newPackage] = goPkg

			for k, imptGoPkg := range goPkg.Imports {
				importedPackage, exists := allPackages[imptGoPkg.PkgPath]
				if !exists {
					importedPackage = createPackage(app, imptGoPkg, basePackagePath)
					allPackages[imptGoPkg.PkgPath] = importedPackage
					allGoPackages[importedPackage] = imptGoPkg
				}
				newPackage.ImportedPackages[k] = importedPackage
			}
		}
	}

	for _, pkg := range app.BlueprintPackages {
		logger.Logger.Infof("[APP] parsing blueprint package %s", pkg.PackagePath)
		parseBlueprintPackage(pkg)
	}

	for _, pkg := range app.Packages {
		goPkg := allGoPackages[pkg]
		logger.Logger.Infof("[APP] parsing app package %s", goPkg)

		underlyingTypes := make(map[string]gotypes.Type)
		visitedNamedTypes := make(map[string]bool)

		for _, def := range goPkg.TypesInfo.Defs {
			if def == nil {
				continue
			}
			if namedGoType, ok := def.Type().(*gotypes.Named); ok {
				if visitedNamedTypes[namedGoType.String()] {
					continue
				}
				visitedNamedTypes[namedGoType.String()] = true

				typeName := namedGoType.Obj().Name()
				objectPackage := namedGoType.Obj().Pkg()
				objectPackagePath := ""
				if objectPackage != nil { // e.g. 'error' is an interface type with no package path TODO: ignore it
					objectPackagePath = objectPackage.Path()
				}

				// different package implies imported object
				if !pkg.HasPath(objectPackagePath) {
					if isBlueprintPackagePath(objectPackagePath) {
						bpPackage := pkg.GetImportedPackage(objectPackagePath)
						declaredType := bpPackage.GetDeclaredType(typeName)
						pkg.AddImportedType(declaredType)
						pkg.AddDatastoreType(declaredType)
						logger.Logger.Debugf("added imported blueprint type %s", declaredType.String())
					} else if slices.Contains(services, typeName) {
						//FIXME: verify is service is also in the same package
						serviceType := &types.ServiceType{
							Name:    typeName,
							Package: objectPackagePath,
						}
						pkg.AddImportedType(serviceType)
						pkg.AddServiceType(serviceType)
						logger.Logger.Debugf("added imported service type %s", serviceType.String())
					} else {
						importedType := &types.UserType{
							Name:    typeName,
							Package: objectPackagePath, // this is the real package name
						}
						pkg.AddImportedType(importedType)
						logger.Logger.Debugf("added imported type %s", importedType.String())
					}
				} else if slices.Contains(services, typeName) {
					//FIXME: verify is service is also in the same package
					serviceType := &types.ServiceType{
						Name:    typeName,
						Package: objectPackagePath,
					}
					logger.Logger.Debugf("added declared service type %s", serviceType.String())
					pkg.AddDeclaredType(serviceType)
					pkg.AddServiceType(serviceType)
				} else {
					// new type defined in the current package
					namedType := &types.UserType{
						Name:    typeName,
						Package: pkg.Name,
					}
					// since we can have nested structures with definitions out of order
					// there, here we only add an entry and latter we generate the subtypes
					pkg.AddDeclaredType(namedType)
					logger.Logger.Debugf("added declared type %s", namedType.String())
					underlyingTypes[typeName] = namedGoType.Underlying()
				}
			}
		}
		for n, declaredType := range pkg.DeclaredTypes {
			if userType, ok := declaredType.(*types.UserType); ok {
				userType.UserType = pkg.GenerateUnderlyingTypesFromGoType(underlyingTypes[n])
			}
		}
		for n, importedType := range pkg.ImportedTypes {
			if userType, ok := importedType.(*types.UserType); ok {
				userType.UserType = pkg.GenerateUnderlyingTypesFromGoType(underlyingTypes[n])
			}
		}

		for i, fileAst := range goPkg.Syntax {
			file := &types.File{
				Ast:     fileAst,
				Name:    filepath.Base(goPkg.GoFiles[i]),
				AbsPath: goPkg.GoFiles[i],
				Package: pkg,
				Imports: make(map[string]*types.Import),
			}
			pkg.LinkFile(file)
		}
		logger.Logger.Debugf("[APP] added new package %s", pkg.Name)
	}
}
