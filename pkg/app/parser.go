package app

import (
	"go/ast"
	golangtypes "go/types"
	"path/filepath"
	"slices"
	"strings"

	"golang.org/x/tools/go/packages"

	"analyzer/pkg/controlflow"
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
	PACKAGE_PATH_SOCKSHOP2         string = "github.com/blueprint-uservices/blueprint/examples/sockshop2/workflow"
	PACKAGE_PATH_TRAIN_TICKET      string = "github.com/blueprint-uservices/blueprint/examples/train_ticket/workflow"
	PACKAGE_PATH_SHOPPING_APP      string = "github.com/blueprint-uservices/blueprint/examples/shopping_app/workflow"
	PACKAGE_PATH_DSB_HOTEL         string = "github.com/blueprint-uservices/blueprint/examples/dsb_hotel/workflow/hotelreservation"
	PACKAGE_PATH_DSB_SN            string = "github.com/blueprint-uservices/blueprint/examples/dsb_sn/workflow/socialnetwork"
	PACKAGE_PATH_BLUEPRINT         string = "github.com/blueprint-uservices/blueprint/runtime/core/backend"
)

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
		logger.Logger.Infof("[APP PACKAGE FINDER] found internal package %s", goPackage.String())
		newPackage.Type = types.APP
		app.AddAppPackage(newPackage.Name, newPackage)
	} else if goPackage.PkgPath == PACKAGE_PATH_BLUEPRINT {
		logger.Logger.Infof("[APP PACKAGE FINDER] found blueprint package %s", goPackage.String())
		newPackage.Type = types.BLUEPRINT
		app.AddBlueprintPackage(newPackage.Name, newPackage)
	} else {
		logger.Logger.Infof("[APP PACKAGE FINDER] found external package %s", goPackage.String())
		newPackage.Type = types.EXTERNAL
		app.AddExternalPackage(newPackage.Name, newPackage)
	}

	return newPackage
}

func parseBlueprintPackage(bpPackage *types.Package) {
	packagesPattern := bpPackage.PackagePath
	pkgs, err := packages.Load(&packages.Config{Mode: packages.NeedName | packages.NeedModule | packages.NeedFiles | packages.NeedTypes | packages.NeedTypesInfo | packages.NeedSyntax | packages.NeedImports}, packagesPattern)
	if err != nil {
		logger.Logger.Fatalf("[APP PACKAGE BLUEPRINT] error loading packages from %s: %s", bpPackage.PackagePath, err.Error())
	}
	// should be only one package
	if len(pkgs) != 1 {
		logger.Logger.Fatalf("[APP PACKAGE BLUEPRINT] unexpected number of packages (%d) in blueprint backend %s", len(pkgs), bpPackage.PackagePath)
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
					logger.Logger.Infof("[APP PACKAGE BLUEPRINT] added blueprint backend %s", backendType.String())

				} else {
					logger.Logger.Tracef("[APP PACKAGE BLUEPRINT] ignoring type %s (%s): %v", utils.GetType(def.Type()), utils.GetType(def.Type().Underlying()), def.Type().String())
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
	case "sockshop2":
		basePackagePath = PACKAGE_PATH_SOCKSHOP2
	case "trainticket":
		basePackagePath = PACKAGE_PATH_TRAIN_TICKET
	case "shopping_app":
		basePackagePath = PACKAGE_PATH_SHOPPING_APP
	case "dsb_hotel":
		basePackagePath = PACKAGE_PATH_DSB_HOTEL
	case "dsb_sn":
		basePackagePath = PACKAGE_PATH_DSB_SN
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
		parseBlueprintPackage(pkg)
	}

	for _, pkg := range app.ExternalPackages {
		app.parsePackage(pkg, servicesPkgPath, allGoPackages)
	}

	for _, pkg := range app.Packages {
		app.parsePackage(pkg, servicesPkgPath, allGoPackages)
	}

	for _, pkg := range app.Packages {
		for _, m := range pkg.GetAllParsedMethods() {
			controlflow.GenerateMethodCFG(m)
		}
	}

	app.dumpYamlPackages()
}

func parseGolangFuncTypes(pkg *types.Package, def golangtypes.Object, typeNameToFuncs map[string][]*golangtypes.Func) []*golangtypes.Func {
	var funcs []*golangtypes.Func
	if funcGoType, ok := def.(*golangtypes.Func); ok && funcGoType.Pkg().Path() == pkg.PackagePath {
		//logger.Logger.Debugf("FUNC TYPE %v", funcGoType)
		if signatureGoType, ok := funcGoType.Type().Underlying().(*golangtypes.Signature); ok {
			//logger.Logger.Debugf("\t\t SIGNATURE TYPE %v", signatureGoType)
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
	return funcs
}

func (app *App) parsePackage(pkg *types.Package, servicesPkgPath map[string]string, allGoPackages map[*types.Package]*packages.Package) {
	goPkg := allGoPackages[pkg]

	if goPkg == nil {
		logger.Logger.Fatalf("[APP PACKAGE PARSER] cannot find go package (%s) in list: %v", pkg.Name, allGoPackages)
	}

	// we are currently not able to get the types info defs for any external packages
	if goPkg.TypesInfo == nil {
		logger.Logger.Warnf("[APP PACKAGE PARSER] skipping package (%s)", goPkg)
		return
	}

	if pkg.IsAppPackage() {
		logger.Logger.Infof("[APP PACKAGE PARSER] parsing app package (%s)", goPkg)
	} else {
		logger.Logger.Infof("[APP PACKAGE PARSER] parsing external package (%s)", goPkg)
	}

	visitedNamedTypes := make(map[*golangtypes.Named]bool)
	typeNameToFuncs := make(map[string][]*golangtypes.Func)
	var funcs []*golangtypes.Func

	for _, def := range goPkg.TypesInfo.Defs {
		if def == nil {
			continue
		}
		funcs = append(funcs, parseGolangFuncTypes(pkg, def, typeNameToFuncs)...)
		lookup.FindDefTypesAndAddToPackage(pkg, def.Type(), visitedNamedTypes, typeNameToFuncs, servicesPkgPath)
	}

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

					if recvTypeIdent != nil {
						if structTypeFuncs, ok := typeNameToFuncs[recvTypeIdent.Name]; ok {
							createAndSaveMethodForFuncDecl(pkg, file, funcDecl, structTypeFuncs)
						} else {
							logger.Logger.Fatalf("[APP PACKAGE PARSER] cannot find func for type name (%s)", recvTypeIdent.Name)
						}
					} else {
						createAndSaveMethodForFuncDecl(pkg, file, funcDecl, funcs)
					}
				}
				return true
			})
		}
	}
	logger.Logger.Tracef("[APP PACKAGE PARSER] added new package %s", pkg.Name)
}

func createAndSaveMethodForFuncDecl(pkg *types.Package, file *types.File, funcDecl *ast.FuncDecl, funcGoTypes []*golangtypes.Func) {
	for _, f := range funcGoTypes {
		if f.Name() == funcDecl.Name.Name {
			params, returns, receiver := lookup.ComputeFuncDeclFields(file, funcDecl)
			if receiver != nil {
				logger.Logger.Warnf("COMPUTED RECEIVER (%s)", receiver.GetName())
			}
			parsedMethod := &types.ParsedMethod{
				Ast:      funcDecl,
				Name:     funcDecl.Name.Name,
				Package:  pkg,
				Exported: f.Exported(),
				Params:   params,
				Returns:  returns,
				Receiver: receiver,
			}
			pkg.RegisterMethodToParse(parsedMethod)
			logger.Logger.Warnf("[APP] registered method (%s) to be parsed in package (%s)", parsedMethod.Name, pkg.Name)
		}
	}
}
