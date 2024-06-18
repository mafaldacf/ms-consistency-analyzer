package app

import (
	golangtypes "go/types"
	"path/filepath"
	"strings"

	"golang.org/x/tools/go/packages"

	"analyzer/pkg/frameworks"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

const (
	PACKAGE_PATH_POST_NOTIFICATION string = "github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification"
	PACKAGE_PATH_FOOBAR            string = "github.com/blueprint-uservices/blueprint/examples/foobar/workflow/foobar"
	PACKAGE_PATH_BLUEPRINT         string = "github.com/blueprint-uservices/blueprint/runtime/core/backend"
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
		DeclaredTypes:     make(map[string]gotypes.Type),
		ServiceTypes:      make(map[string]*gotypes.ServiceType),
		DatastoreTypes:    make(map[string]gotypes.Type),
		DeclaredVariables: make(map[string]types.Variable),
		ImportedTypes:     make(map[string]gotypes.Type),
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
		if _, isInterface := def.Type().Underlying().(*golangtypes.Interface); isInterface {
			if namedGoType, ok := def.Type().(*golangtypes.Named); ok {
				if visitedNamedTypes[namedGoType.String()] {
					continue
				}
				visitedNamedTypes[namedGoType.String()] = true

				typeName := namedGoType.Obj().Name()
				objectPackage := namedGoType.Obj().Pkg()
				if objectPackage == nil || objectPackage.Path() != bpPackage.PackagePath {
					continue
				}

				if blueprint.IsBackendComponent(typeName) {
					backendType := &blueprint.BackendType{
						Name:    typeName,
						Package: objectPackage.Path(),
					}
					backendType.Methods = blueprint.BuildBackendComponentMethods(backendType.Name)
					bpPackage.AddDeclaredType(backendType)
					logger.Logger.Infof("[BLUEPRINT] added blueprint backend %s", backendType.String())

				} else {
					logger.Logger.Warnf("[BLUEPRINT] ignoring type %s (%s): %v", utils.GetType(def.Type()), utils.GetType(def.Type().Underlying()), def.Type().String())
				}
			}
		}
	}
}

func (app *App) ParsePackages(servicesInfo []*frameworks.ServiceInfo) {
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

	servicesPkgPath := make(map[string]string)
	for _, info := range servicesInfo {
		servicesPkgPath[info.Name] = info.PackagePath
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

		underlyingTypes := make(map[string]golangtypes.Type)
		visitedNamedTypes := make(map[string]bool)

		for _, def := range goPkg.TypesInfo.Defs {
			if def == nil {
				continue
			}
			/* if namedGoType, ok := def.Type().(*golangtypes.Named); ok {
				if structGoType, ok := namedGoType.Underlying().(*golangtypes.Struct); ok {
					logger.Logger.Infof("visiting %s: %s", utils.GetType(structGoType.Underlying()), structGoType.Underlying().String())
					for i := 0; i < structGoType.NumFields(); i++ {
						typeParam := structGoType.Field(i)
						logger.Logger.Infof("\t\tvisiting %s: %s", utils.GetType(typeParam), typeParam.String())
					}
				}
			} */
			if namedGoType, ok := def.Type().(*golangtypes.Named); ok {
				logger.Logger.Debugf("visiting %s: %s", utils.GetType(namedGoType), namedGoType.String())
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
					} else if servicePkgPath, ok := servicesPkgPath[typeName]; ok && servicePkgPath == objectPackagePath {
						serviceType := &gotypes.ServiceType{
							Name:    typeName,
							Package: objectPackagePath,
						}
						pkg.AddImportedType(serviceType)
						pkg.AddServiceType(serviceType)
						logger.Logger.Debugf("added imported service type %s", serviceType.String())
					} else {
						importedType := &gotypes.UserType{
							Name:    typeName,
							Package: objectPackagePath, // this is the real package name
						}
						pkg.AddImportedType(importedType)
						logger.Logger.Debugf("added imported type %s", importedType.String())
					}
				} else if servicePkgPath, ok := servicesPkgPath[typeName]; ok && servicePkgPath == objectPackagePath {
					serviceType := &gotypes.ServiceType{
						Name:    typeName,
						Package: objectPackagePath,
					}
					logger.Logger.Debugf("added declared service type %s", serviceType.String())
					pkg.AddDeclaredType(serviceType)
					pkg.AddServiceType(serviceType)
				} else {
					// new type defined in the current package
					namedType := &gotypes.UserType{
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
			if userType, ok := declaredType.(*gotypes.UserType); ok {
				userType.UserType = pkg.ComputeTypesForGoTypes(underlyingTypes[n])
			}
		}
		for n, importedType := range pkg.ImportedTypes {
			if userType, ok := importedType.(*gotypes.UserType); ok {
				userType.UserType = pkg.ComputeTypesForGoTypes(underlyingTypes[n])
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
