package app

import (
	bp "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	gotypes "go/types"
	"path/filepath"
	"slices"
	"strings"

	"golang.org/x/tools/go/packages"
)

var postnotification_package_path string = "github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification"
var foobar_package_path string = "github.com/blueprint-uservices/blueprint/examples/foobar/workflow/foobar"

func createPackage(goPackage *packages.Package, basePackagePath string) *types.Package {
	modulePath := ""
	if goPackage.Module != nil {
		modulePath = goPackage.Module.Path
	}

	external := true
	if strings.HasPrefix(goPackage.PkgPath, basePackagePath) {
		logger.Logger.Infof("[APP] found internal package %s", goPackage.String())
		external = false
	} else {
		logger.Logger.Infof("[APP] found external package %s", goPackage.String())
	}

	return &types.Package{
		Name:              goPackage.Name,	// e.g. models
		PackagePath:       goPackage.PkgPath,    // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification/models
		Module:            modulePath, 		// e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow
		ExternalPackage:   external,
		Imports:   		   make(map[string]*types.Package),
		DeclaredTypes:     make(map[string]types.Type),
		ServiceTypes:      make(map[string]*types.ServiceType),
		DatastoreTypes:    make(map[string]*types.DatastoreType),
		DeclaredVariables: make(map[string]types.Variable),
		ImportedTypes:     make(map[string]types.Type),
		TypesInfo: 		   goPackage.TypesInfo,
	}
}

func (app *App) ParsePackages(servicesInfo []*types.ServiceInfo) {
	var basePackagePath string
	switch app.Name {
	case "postnotification":
		basePackagePath = postnotification_package_path
	case "foobar":
		basePackagePath = foobar_package_path
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
			newPackage := createPackage(goPkg, basePackagePath)
			allPackages[goPkg.PkgPath] = newPackage
			allGoPackages[newPackage] = goPkg

			for k, p := range goPkg.Imports {
				importedPackage, exists := allPackages[p.PkgPath]
				if !exists {
					importedPackage = createPackage(p, basePackagePath)
					allPackages[p.PkgPath] = importedPackage
					allGoPackages[importedPackage] = goPkg
				}
				newPackage.Imports[k] = importedPackage
			}
		}
	}

	for pkg, goPkg := range allGoPackages {
		if pkg.ExternalPackage {
			continue // skip parsing of external packages
		}

		logger.Logger.Infof("[APP] parsing package package %s", goPkg)
		app.Packages[pkg.Name] = pkg

		underlyingTypes := make(map[string]gotypes.Type)
		visitedNamedTypes := make(map[string]bool)

		for key, t := range goPkg.TypesInfo.Types {
			logger.Logger.Debugf("- TYPES %s: %v", key, t.Type)
		}

		for name, def := range goPkg.TypesInfo.Defs {
			logger.Logger.Debugf("- DEFS %s: %v", name, def)
			if def == nil {
				continue
			}
			if namedGoType, ok := def.Type().(*gotypes.Named); ok {
				typeName := namedGoType.Obj().Name()
				objectPackage := namedGoType.Obj().Pkg()
				if visitedNamedTypes[namedGoType.String()] {
					continue
				}
				visitedNamedTypes[namedGoType.String()] = true
				// sanity check, e.g. 'error' is an interface type with no package path
				objectPackagePath := ""
				if objectPackage != nil {
					objectPackagePath = objectPackage.Path()
				}

				_, isInterface := namedGoType.Underlying().(*gotypes.Interface)
				if isInterface && bp.IsBlueprintPackage(objectPackagePath) && bp.IsBlueprintBackend(typeName) {
					datastoreType := &types.DatastoreType{
						Name: typeName,
						Package: objectPackagePath,
					}
					pkg.AddDatastoreType(datastoreType)
					pkg.AddImportedType(datastoreType)
					logger.Logger.Debugf("added datastore type for interface %s @ %s", typeName, objectPackagePath)
				} else if isInterface && objectPackagePath != "" && slices.Contains(services, typeName) {
					//TODO confirm that service package is the same of the object package
					serviceType := &types.ServiceType{
						Name: 		typeName,
						Package: 	objectPackagePath,
					}
					pkg.AddServiceType(serviceType)
					if pkg.HasPath(objectPackagePath) {
						pkg.AddDeclaredType(serviceType)
					} else {
						pkg.AddImportedType(serviceType)
					}
					logger.Logger.Debugf("added service type for interface %s @ %s", typeName, objectPackagePath)
				} else if pkg.HasPath(objectPackagePath) {
					// new type defined in the current package
					namedType := &types.UserType{
						Name:    typeName,
						Package: pkg.Name,
					}
					// since we can have nested structures with definitions out of order
					// there, here we only add an entry and latter we generate the subtypes
					pkg.AddDeclaredType(namedType)
					underlyingTypes[typeName] = namedGoType.Underlying()
					logger.Logger.Debugf("\t [APP] added named type %s", namedType.String())
				} else if objectPackagePath == "" {
					// edge case for .error
					userType := &types.UserType{
						Name: typeName,
						Package: objectPackagePath, // this is the real package name
					}
					pkg.AddDeclaredType(userType)
					logger.Logger.Debugf("added imported type %s for package %s", typeName, objectPackagePath)
				} else {
					importedType := &types.UserType{
						Name: typeName,
						Package: objectPackagePath, // this is the real package name
					}
					pkg.AddImportedType(importedType)
					logger.Logger.Debugf("added imported type %s for package %s", typeName, objectPackagePath)
				}
			} else if funcGoType, ok := def.(*gotypes.Func); ok {
				funcName := funcGoType.Name()
				funcPackage := funcGoType.Pkg()
				// use Type() because we can have func ptrs (in impl interfaces) and func only (in calls)
				if visitedNamedTypes[funcGoType.Type().String()] {
					continue
				}
				visitedNamedTypes[funcGoType.Type().String()] = true
				objectPackagePath := ""
				if funcPackage != nil {
					objectPackagePath = funcPackage.Path()
				}
				funcType := &types.FuncType{
					Name: 	 funcGoType.Name(),
					Package: objectPackagePath,
				}
				if pkg.HasPath(objectPackagePath) {
					pkg.AddDeclaredType(funcType)
				} else {
					pkg.AddImportedType(funcType)
				}
				underlyingTypes[funcName] = def.Type()
			}
		}
		for n, declaredType := range pkg.DeclaredTypes {
			if userType, ok := declaredType.(*types.UserType); ok {
				userType.UserType = pkg.GenerateUnderlyingTypesFromGoType(underlyingTypes[n])
			} else if funcType, ok := declaredType.(*types.FuncType); ok {
				funcType.SignatureType = pkg.GenerateUnderlyingTypesFromGoType(underlyingTypes[n]).(*types.SignatureType)
			}
		}
		for n, importedType := range pkg.ImportedTypes {
			if userType, ok := importedType.(*types.UserType); ok {
				userType.UserType = pkg.GenerateUnderlyingTypesFromGoType(underlyingTypes[n])
			} else if funcType, ok := importedType.(*types.FuncType); ok {
				funcType.SignatureType = pkg.GenerateUnderlyingTypesFromGoType(underlyingTypes[n]).(*types.SignatureType)
			}
		}

		for i, fileAst := range goPkg.Syntax {
			file := &types.File{
				Ast:     fileAst,
				Name: 	 filepath.Base(goPkg.GoFiles[i]),
				AbsPath: goPkg.GoFiles[i],
				Package: pkg,
				Imports: make(map[string]*types.Import),
			}
			pkg.LinkFile(file)
		}
		logger.Logger.Debugf("[APP] added new package %s", pkg.Name)
	}
}
