package app

import (
	bp "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	gotypes "go/types"
	"path/filepath"
	"slices"

	"golang.org/x/tools/go/packages"
)

var postnotification_package_path string = "github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification"
var foobar_package_path string = "github.com/blueprint-uservices/blueprint/examples/foobar/workflow/foobar"

func (app *App) ParsePackages(servicesInfo []*types.ServiceInfo) {
	var pkgName string
	switch app.Name {
	case "postnotification":
		pkgName = postnotification_package_path
	case "foobar":
		pkgName = foobar_package_path
	default:
		logger.Logger.Fatalf("unknown application name %s", app.Name)
	}

	pkgPattern := pkgName + "/..."
	pkgs, err := packages.Load(&packages.Config{Mode: packages.NeedName | packages.NeedModule | packages.NeedFiles | packages.NeedTypes | packages.NeedTypesInfo | packages.NeedSyntax}, pkgPattern)
	if err != nil {
		logger.Logger.Fatalf("error loading packages from %s: %s", pkgName, err.Error())
	}

	var services []string
	for _, info := range servicesInfo {
		services = append(services, info.Name)
	}

	for _, goPkg := range pkgs {
		logger.Logger.Infof("[APP] found new package %s", goPkg)

		pkg := &types.Package{
			Name:              goPkg.Name,        // e.g. models
			PackagePath:       goPkg.PkgPath,     // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification/models
			Module:            goPkg.Module.Path, // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow
			DeclaredTypes:     make(map[string]types.Type),
			ServiceTypes:      make(map[string]*types.ServiceType),
			DatastoreTypes:    make(map[string]*types.DatastoreType),
			DeclaredVariables: make(map[string]types.Variable),
			ImportedTypes:     make(map[string]types.Type),
		}
		app.Packages[pkg.Name] = pkg

		underlyingTypes := make(map[string]gotypes.Type)
		visitedNamedTypes := make(map[string]bool)
		for _, def := range goPkg.TypesInfo.Defs {
			if def == nil {
				continue
			}
			if namedGoType, ok := def.Type().(*gotypes.Named); ok {
				typeName := namedGoType.Obj().Name()
				objectPackage := namedGoType.Obj().Pkg()

				if visitedNamedTypes[typeName] {
					continue
				}
				visitedNamedTypes[typeName] = true

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
					logger.Logger.Warnf("added datastore type for interface %s @ %s", typeName, objectPackagePath)
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
					logger.Logger.Infof("\t [APP] added named type %s", namedType.String())
				} else {
					importedType := &types.UserType{
						Name: typeName,
						Package: objectPackagePath, // this is the real package name
					}
					pkg.AddImportedType(importedType)
				}
			}
		}
		for n, declaredType := range pkg.DeclaredTypes {
			if userType, ok := declaredType.(*types.UserType); ok {
				userType.UserType = pkg.GenerateUnderlyingTypesFromGoType(underlyingTypes[n])
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

	yamlData := app.Yaml()
	utils.SaveToYamlFile(yamlData, app.Name, "metadata")
}
