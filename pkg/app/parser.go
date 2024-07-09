package app

import (
	"go/ast"
	golangtypes "go/types"
	"path/filepath"
	"slices"
	"strings"

	"golang.org/x/tools/go/packages"

	"analyzer/pkg/frameworks"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/lookup"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

const (
	PACKAGE_PATH_POST_NOTIFICATION string = "github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification"
	PACKAGE_PATH_FOOBAR            string = "github.com/blueprint-uservices/blueprint/examples/foobar/workflow/foobar"
	PACKAGE_PATH_SOCKSHOP          string = "github.com/blueprint-uservices/blueprint/examples/sockshop/workflow"
	PACKAGE_PATH_TRAIN_TICKET      string = "github.com/blueprint-uservices/blueprint/examples/train_ticket/workflow"
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
		DeclaredVariables: make(map[string]variables.Variable),
		ImportedTypes:     make(map[string]gotypes.Type),
		TypesInfo:         goPackage.TypesInfo,
	}

	//TODO ADD FLAG FOR BLUEPRINT PACKAGE
	if strings.HasPrefix(goPackage.PkgPath, basePackagePath) {
		logger.Logger.Infof("[APP] found internal package %s", goPackage.String())
		newPackage.Type = types.APP
		app.AddAppPackage(newPackage.Name, newPackage)
	} else if goPackage.PkgPath == PACKAGE_PATH_BLUEPRINT {
		logger.Logger.Infof("[APP] found blueprint package %s", goPackage.String())
		newPackage.Type = types.BLUEPRINT
		app.AddBlueprintPackage(newPackage.Name, newPackage)
	} else {
		logger.Logger.Infof("[APP] found external package %s", goPackage.String())
		newPackage.Type = types.EXTERNAL
		app.AddExternalPackage(newPackage.Name, newPackage)
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
					backendType := &blueprint.BlueprintBackendType{
						Name:    typeName,
						Package: objectPackage.Path(),
					}
					backendType.Methods = blueprint.BuildBackendComponentMethods(backendType.Name)
					bpPackage.AddDeclaredType(backendType)
					bpPackage.AddDatastoreType(backendType)
					logger.Logger.Infof("[APP BLUEPRINT] added blueprint backend %s with methods %v", backendType.String(), backendType.Methods)

				} else {
					logger.Logger.Warnf("[APP BLUEPRINT] ignoring type %s (%s): %v", utils.GetType(def.Type()), utils.GetType(def.Type().Underlying()), def.Type().String())
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
	case "sockshop":
		basePackagePath = PACKAGE_PATH_SOCKSHOP
	case "trainticket":
		basePackagePath = PACKAGE_PATH_TRAIN_TICKET
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
		logger.Logger.Debugf("pkg: %s", pkg.Name)
	}

	for _, pkg := range app.Packages {
		app.parsePackage(pkg, servicesPkgPath, allGoPackages)
	}

	for _, pkg := range app.ExternalPackages {
		app.parsePackage(pkg, servicesPkgPath, allGoPackages)
	}
}

func (app *App) parsePackage(pkg *types.Package, servicesPkgPath map[string]string, allGoPackages map[*types.Package]*packages.Package) {
	goPkg := allGoPackages[pkg]

	if goPkg == nil {
		logger.Logger.Fatalf("[APP] cannot find go package (%s) in list: %v", pkg.Name, allGoPackages)
	}

	if pkg.IsAppPackage() {
		logger.Logger.Infof("[APP] parsing app package (%s)\n----------", goPkg)
	} else {
		logger.Logger.Infof("[APP] parsing external package (%s)\n----------", goPkg)
	}

	// we are currently not able to get the types info defs for any external packages
	if goPkg.TypesInfo == nil {
		logger.Logger.Warnf("[APP] ignoring package (%s)", goPkg)
		return
	}

	underlyingTypes := make(map[string]golangtypes.Type)
	visitedNamedTypes := make(map[string]bool)
	typeNameToFuncs := make(map[string][]*golangtypes.Func)
	funcs := []*golangtypes.Func{}

	for _, def := range goPkg.TypesInfo.Defs {
		if def == nil {
			continue
		}
		//logger.Logger.Warnf("[APP] [%s] visiting %s: %s", utils.GetType(def), def.Name(), def.String())

		//logger.Logger.Infof("[%s] visiting %s\n", utils.GetType(def), def.Name())
		if funcGoType, ok := def.(*golangtypes.Func); ok && funcGoType.Pkg().Path() == pkg.PackagePath {
			if signatureGoType, ok := funcGoType.Type().Underlying().(*golangtypes.Signature); ok {
				if signatureGoType.Recv() != nil {
					recv := signatureGoType.Recv().Type()
					if pointerGoType, ok := signatureGoType.Recv().Type().(*golangtypes.Pointer); ok {
						recv = pointerGoType.Elem()
					}
					if namedGoType, ok := recv.(*golangtypes.Named); ok {
						var recvTypeName string
						_, isStruct := recv.Underlying().(*golangtypes.Struct)
						_, isInterface := recv.Underlying().(*golangtypes.Interface)
						if !isStruct && !isInterface {
							logger.Logger.Fatalf("[APP] unexpected type (%s) for recv underlying (%s)", utils.GetType(recv.Underlying()), recv.Underlying())
						}
						recvTypeName = namedGoType.Obj().Name()
						if !slices.Contains(typeNameToFuncs[recvTypeName], funcGoType) {
							typeNameToFuncs[recvTypeName] = append(typeNameToFuncs[recvTypeName], funcGoType)
						}
					} else {
						logger.Logger.Fatalf("[APP] unexpected type (%s) for recv (%s)", utils.GetType(namedGoType), recv.String())
					}
				} else {
					if !slices.Contains(funcs, funcGoType) {
						funcs = append(funcs, funcGoType)
					}
				}
			}
		}
		/* if signatureGoType, ok := def.Type().(*golangtypes.Signature); ok {
			if signatureGoType.Recv() != nil {
				logger.Logger.Infof("[%s] visiting %s: %v\n", utils.GetType(signatureGoType), def.Name(), utils.GetType(signatureGoType.Recv().Type()))
			}
		}
		if namedGoType, ok := def.Type().(*golangtypes.Named); ok {
			if structGoType, ok := namedGoType.Underlying().(*golangtypes.Struct); ok {
				logger.Logger.Warnf("[%s] visiting %s with %d fields: %s", utils.GetType(structGoType), def.Name(), structGoType.NumFields(), structGoType.String())
				for i := 0; i < structGoType.NumFields(); i++ {
					typeParam := structGoType.Field(i)
					logger.Logger.Warnf("\t\t[%s] visiting struct field %s", utils.GetType(typeParam), typeParam.String())
				}
				logger.Logger.Warn()
			}
			if interfaceGoType, ok := namedGoType.Underlying().(*golangtypes.Interface); ok {
				logger.Logger.Warnf("[%s] visiting %s: %s\n", utils.GetType(interfaceGoType), def.Name(), interfaceGoType.String())
			}
		} */

		goType := def.Type()
		namedGoType, ok := goType.(*golangtypes.Named)
		stop := false
		for !stop {
			switch e := goType.(type) {
			case *golangtypes.Slice:
				goType = e.Elem()
			case *golangtypes.Pointer:
				goType = e.Elem()
			case *golangtypes.Chan:
				goType = e.Elem()
			case *golangtypes.Named:
				namedGoType = e
				ok = true
				stop = true
			case *golangtypes.Signature, *golangtypes.Struct, *golangtypes.Basic, *golangtypes.Map:
				// ignore
				stop = true
			default:
				logger.Logger.Fatalf("unknown go type (%s) for (%v)", utils.GetType(goType), goType)
			}
		}

		if ok {
			logger.Logger.Tracef("[APP] [%s] visiting %s: %s", utils.GetType(namedGoType), def.Name(), namedGoType.String())
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

			if pkg.IsAppPackage() {
				// different package implies imported object
				if !pkg.HasPath(objectPackagePath) {
					if isBlueprintPackagePath(objectPackagePath) {
						bpPackage := pkg.GetImportedPackage(objectPackagePath)
						declaredType := bpPackage.GetDeclaredType(typeName)
						pkg.AddImportedType(declaredType)
						pkg.AddDatastoreType(declaredType)
						logger.Logger.Debugf("[APP] added imported blueprint type %s", declaredType.String())
					} else if servicePkgPath, ok := servicesPkgPath[typeName]; ok && servicePkgPath == objectPackagePath {
						serviceType := &gotypes.ServiceType{
							Name:    typeName,
							Package: objectPackagePath,
						}
						pkg.AddImportedType(serviceType)
						pkg.AddServiceType(serviceType)
						logger.Logger.Debugf("[APP] added imported service type %s", serviceType.String())
					} else {
						importedType := &gotypes.UserType{
							Name:    typeName,
							Package: objectPackagePath, // this is the real package name
						}
						pkg.AddImportedType(importedType)
						logger.Logger.Debugf("[APP] added imported type %s", importedType.String())
					}
				} else if servicePkgPath, ok := servicesPkgPath[typeName]; ok && servicePkgPath == objectPackagePath {
					serviceType := &gotypes.ServiceType{
						Name:    typeName,
						Package: objectPackagePath,
					}
					logger.Logger.Debugf("[APP] added declared service type %s", serviceType.String())
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
					logger.Logger.Debugf("[APP] added declared named type %s", namedType.String())
					pkg.AddDeclaredType(namedType)
					underlyingTypes[typeName] = namedGoType.Underlying()
				}
			} else {
				if pkg.HasPath(objectPackagePath) {
					// new type defined in the current package
					namedType := &gotypes.UserType{
						Name:    typeName,
						Package: pkg.Name,
					}
					// since we can have nested structures with definitions out of order
					// there, here we only add an entry and latter we generate the subtypes
					pkg.AddDeclaredType(namedType)
					underlyingTypes[typeName] = namedGoType.Underlying()
				}
			}
		} else {
			logger.Logger.Warnf("skipping %v with type %s", goType, utils.GetType(goType))
		}
	}

	for n, importedType := range pkg.ImportedTypes {
		if userType, ok := importedType.(*gotypes.UserType); ok {
			userType.UserType = lookup.ComputeTypesForGoTypes(pkg, underlyingTypes[n])
		}
	}

	for n, declaredType := range pkg.DeclaredTypes {
		if userType, ok := declaredType.(*gotypes.UserType); ok {
			userType.UserType = lookup.ComputeTypesForGoTypes(pkg, underlyingTypes[n])

			if structType, ok := userType.UserType.(*gotypes.StructType); ok {
				for _, funcGoType := range typeNameToFuncs[userType.Name] {
					structType.AddMethod(funcGoType.Name(), pkg.GetPackagePath())
					logger.Logger.Infof("[APP] saved struct (%s) function (%s) in package (%s)", userType.GetName(), funcGoType.Name(), pkg.GetName())
				}
			} else if interfaceType, ok := userType.UserType.(*gotypes.InterfaceType); ok {
				for _, funcGoType := range typeNameToFuncs[userType.Name] {
					interfaceType.AddMethod(funcGoType.Name(), pkg.GetPackagePath())
					logger.Logger.Infof("[APP] saved interface (%s) function (%s) in package (%s)", userType.GetName(), funcGoType.Name(), pkg.GetName())
				}
			}
		}
	}

	app.dumpYamlPackages()

	if pkg.IsAppPackage() {
		for i, fileAst := range goPkg.Syntax {
			file := &types.File{
				Ast:     fileAst,
				Name:    filepath.Base(goPkg.GoFiles[i]),
				AbsPath: goPkg.GoFiles[i],
				Package: pkg,
				Imports: make(map[string]*types.Import),
			}
			lookup.ParseImports(file)
			pkg.LinkFile(file)

			ast.Inspect(fileAst, func(n ast.Node) bool {
				if funcDecl, ok := n.(*ast.FuncDecl); ok {
					var recvTypeIdent *ast.Ident
					if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
						recvField := funcDecl.Recv.List[0]
						if startExpr, ok := recvField.Type.(*ast.StarExpr); ok {
							if ident, ok := startExpr.X.(*ast.Ident); ok {
								recvTypeIdent = ident
							}
						} else if ident, ok := recvField.Type.(*ast.Ident); ok {
							recvTypeIdent = ident
						}
					}

					var funcGoTypes []*golangtypes.Func
					if recvTypeIdent != nil {
						if structTypeFuncs, ok := typeNameToFuncs[recvTypeIdent.Name]; ok {
							funcGoTypes = structTypeFuncs
						} else {
							logger.Logger.Fatalf("[APP] cannot find func for type name (%s)", recvTypeIdent.Name)
						}
					} else {
						funcGoTypes = funcs
					}
					for _, f := range funcGoTypes {
						if f.Name() == funcDecl.Name.Name {
							params, returns, receiver := lookup.ComputeFuncDeclFields(file, funcDecl)
							parsedMethod := &types.ParsedMethod{
								Ast:      funcDecl,
								Name:     funcDecl.Name.Name,
								Package:  pkg,
								Exported: f.Exported(),
								Params:   params,
								Returns:  returns,
								Receiver: receiver,
							}
							pkg.AddParsedMethod(parsedMethod)
							logger.Logger.Infof("[APP] added parsed method (%s) to package (%s)", parsedMethod.Name, pkg.Name)
						}
					}
				}
				return true
			})
		}
	}

	logger.Logger.Tracef("[APP] added new package %s", pkg.Name)
}
