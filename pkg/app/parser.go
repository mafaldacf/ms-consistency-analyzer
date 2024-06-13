package app

import (
	bp "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
	gotypes "go/types"
	"os"
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

	repr := "---\n\n"
	for _, goPkg := range pkgs {
		logger.Logger.Infof("[APP] found new package %s", goPkg)

		pkg := &types.Package{
			Name:              goPkg.Name,        // e.g. models
			PackagePath:       goPkg.PkgPath,     // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification/models
			Module:            goPkg.Module.Path, // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow
			DeclaredTypes:     make(map[string]*types.UserType),
			ServiceTypes:      make(map[string]*types.ServiceType),
			DatastoreTypes:    make(map[string]*types.DatastoreType),
			DeclaredVariables: make(map[string]types.Variable),
			ImportedTypes:     make(map[string]*types.UserType),
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
				objPkg := namedGoType.Obj().Pkg()

				if visitedNamedTypes[typeName] {
					continue
				}
				visitedNamedTypes[typeName] = true

				// sanity check, e.g. 'error' is an interface type with no package path
				pkgPath := ""
				pkgName := ""
				if objPkg != nil {
					pkgName = objPkg.Name()
					pkgPath = objPkg.Path()
				}

				if _, isInterface := namedGoType.Underlying().(*gotypes.Interface); isInterface && pkgPath != "" {
					packageName := namedGoType.Obj().Pkg().Path()
					if slices.Contains(services, typeName) {
						serviceType := &types.ServiceType{
							Name: 		typeName,
							Package: 	packageName,
						}
						pkg.ServiceTypes[typeName] = serviceType
						logger.Logger.Debugf("added service type for interface %s @ %s", typeName, packageName)
						continue
					} else if bp.IsBlueprintPackage(packageName) && bp.IsBlueprintBackend(typeName) {
						datastoreType := &types.DatastoreType{
							Name: typeName,
							Package: packageName,
						}
						pkg.DatastoreTypes[typeName] = datastoreType
						logger.Logger.Debugf("added datastore type for interface %s @ %s", typeName, packageName)
						continue
					}
				}

				if pkgPath == pkg.PackagePath {
					// new type defined in the current package
					namedType := &types.UserType{
						Name:    typeName,
						Package: pkg.Name,
					}
					// since we can have nested structures with definitions out of order
					// there, here we only add an entry and latter we generate the subtypes
					pkg.DeclaredTypes[typeName] = namedType
					underlyingTypes[typeName] = namedGoType.Underlying()
					logger.Logger.Infof("\t [APP] added named type %s", namedType.String())
				} else {
					importedType := &types.UserType{
						Name: typeName,
						Package: pkgName,
					}
					pkg.ImportedTypes[typeName] = importedType
				}
			}
		}
		for n, namedType := range pkg.DeclaredTypes {
			namedType.UserType = types.GenerateUnderlyingTypesFromGoType(pkg, underlyingTypes[n])
		}

		for i, fileAst := range goPkg.Syntax {
			file := &types.File{
				Ast:     fileAst,
				AbsPath: goPkg.GoFiles[i],
				Package: pkg,
				Imports: make(map[string]*types.Import),
			}
			pkg.Files = append(pkg.Files, file)
		}
		str := pkg.FullString()
		logger.Logger.Infof("[APP] added new package %s", str)
		repr += str + "---\n\n"
		fmt.Println("----")
	}


	path := fmt.Sprintf("assets/%s/metadata.yaml", app.Name)
	file, err := os.Create(path)
	if err != nil {
		logger.Logger.Fatalf("error creating file %s: %s", path, err.Error())
	}
	defer file.Close()
	file.WriteString(repr)
}
