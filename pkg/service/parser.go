package service

import (
	"go/ast"
	"slices"
	"strings"

	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

func (service *Service) ParseImports() {
	logger.Logger.Debugf("inspecting imports for service %s\n", service.Name)

	for _, imp := range service.File.Ast.Imports {
		path := imp.Path.Value
		// remove quotes
		path = path[1 : len(path)-1]

		// get alias
		// e.g. blueprintbackend in "github.com/blueprint-uservices/blueprint/runtime/core/backend"
		var alias string
		if imp.Name != nil {
			alias = imp.Name.Name
		} else {
			// if alias is not define then we extract it as the last "member"
			items := strings.Split(path, "/")
			alias = items[len(items)-1]
		}

		impt := &types.Import{
			Alias:      alias,
			ImportPath: path,
			//FIXME
			PackagePath: path,
			PackageName: "",
		}
		service.File.Imports[alias] = impt
		logger.Logger.Debugf("> %s for %s\n", alias, path)
	}
	logger.Logger.Debugln()
}

// ParseMethods:
//  1. inspects the service service
//  2. finds the function declarations that implement the
//     service struct along with the name of the function, the receiver, and the parameters
//  3. stores the function delc as parsed func decls in the methods of the service service

func (service *Service) methodImplementsService(n ast.Node) (ok bool, funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) {
	// check if service is a function declaration
	if funcDecl, ok = n.(*ast.FuncDecl); ok {
		// check if the function has any receivers (i.e. structure(s) implemented by the function)
		if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
			// get the function's receiver (i.e. i.e. structure(s) implemented by the function)
			if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
				// check if the data type (e.g. StorageService) of the receiver (i.e. structure(s) implemented by the function)
				// matches the one we are looking for (i.e. StorageService)
				if ident, ok := recv.X.(*ast.Ident); ok && ident.Name == service.ImplName {
					rcvIdent = funcDecl.Recv.List[0].Names[0]
					return true, funcDecl, rcvIdent
				}
			}
		}
	}
	return false, funcDecl, nil
}

func (service *Service) methodHasReceiver(n ast.Node) (ok bool, funcDecl *ast.FuncDecl) {
	// check if service is a function declaration
	if funcDecl, ok = n.(*ast.FuncDecl); ok {
		// check if the function has any receivers (i.e. structure(s) implemented by the function)
		if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
			return true, funcDecl
		}
	}
	return false, funcDecl
}

func (service *Service) isMethodExposedByService(funcDecl *ast.FuncDecl) bool {
	// check if the function declaration being implemented by the Service structure
	// is actually an exposed method to other services
	_, ok := service.ExposedMethods[funcDecl.Name.Name]
	return ok
}

func (service *Service) parseFuncDeclParameters(funcDecl *ast.FuncDecl) ([]*types.MethodField, []*types.MethodField) {
	parser := func(fieldsList []*ast.Field) []*types.MethodField {
		var params []*types.MethodField
		for _, field := range fieldsList {
			paramType := service.File.ComputeTypeForAstExpr(field.Type)
			// returns with types only, which is usually the most frequent scenario
			if len(field.Names) == 0 {
				param := &types.MethodField{
					FieldInfo: types.FieldInfo{
						Ast:  field,
						Type: paramType,
					},
				}
				params = append(params, param)
			}
			for _, ident := range field.Names {
				param := &types.MethodField{
					FieldInfo: types.FieldInfo{
						Ast:  field,
						Type: paramType,
						Name: ident.Name,
					},
				}
				params = append(params, param)
			}
		}
		return params
	}
	return parser(funcDecl.Type.Params.List), parser(funcDecl.Type.Results.List)

}

func (service *Service) ParseMethods() {
	logger.Logger.Debugf("inspecting exposed methods for service implementation %s\n", service.ImplName)

	ast.Inspect(service.File.Ast, func(n ast.Node) bool {
		implementsService, funcDecl, rcvIdent := service.methodImplementsService(n)
		if implementsService {
			if service.isMethodExposedByService(funcDecl) {
				service.addExposedMethod(funcDecl, rcvIdent)
				return true
			} else if service.ImplementsQueue {
				if funcImplementsQueue, dbInstance := service.funcImplementsQueue(funcDecl, rcvIdent); funcImplementsQueue {
					service.addQueueHandlerMethod(funcDecl, rcvIdent, dbInstance)
					service.addInternalMethod(funcDecl, rcvIdent)
					return true
				}
			}
			service.addInternalMethod(funcDecl, rcvIdent)
		} else if funcDecl != nil && funcDecl.Name.Name != service.Constructor.Name {
			// be aware that there can be internal methods with the same name of the instructor
			// we distinguish them since the constructor usually does not implement the service
			// so we need to make sure that the name of this function (that does not implement the service) is not equal to the constructor
			service.addInternalMethod(funcDecl, nil)
		}
		return true
	})
}

func (service *Service) ParseFields() {
	logger.Logger.Debugf("inspecting fields for service %s\n", service.Name)

	ast.Inspect(service.File.Ast, func(n ast.Node) bool {
		// a struct type is first a spec type
		// we want to make sure that we found the service type
		// otherwise, we return true to keep recursition to next ast service
		if ts, ok := n.(*ast.TypeSpec); ok {
			if ts.Name.Name != service.ImplName {
				return true
			}
		}
		//FIXME: should only be service fields
		if str, ok := n.(*ast.StructType); ok {
			for idx, field := range str.Fields.List {
				service.saveFieldWithType(field, field.Names[0].Name, idx)
				logger.Logger.Debugf("%s: saved field %s\n", service.Name, service.Fields[field.Names[0].Name])
			}
		}
		return true
	})
	logger.Logger.Debugln()
}

func (service *Service) saveFieldWithType(field *ast.Field, paramName string, idx int) {
	fieldType := service.File.ComputeTypeForAstExpr(field.Type)
	switch t := fieldType.(type) {
	case *blueprint.BackendType:
		dbField := &types.DatabaseField{
			FieldInfo: types.FieldInfo{
				Ast:  field,
				Name: paramName,
				Type: t,
			},
			IsQueue: t.IsQueue(),
			Idx:     idx,
		}
		if dbField.IsQueue {
			service.ImplementsQueue = true
		}
		service.Fields[paramName] = dbField
	case *gotypes.ServiceType:
		service.Fields[paramName] = &types.ServiceField{
			FieldInfo: types.FieldInfo{
				Ast:  field,
				Name: paramName,
				Type: t,
			},
		}
	default:
		genericField := &types.GenericField{
			FieldInfo: types.FieldInfo{
				Ast:  field,
				Name: paramName,
				Type: fieldType,
			},
		}
		logger.Logger.Warnf("saved generic field for %s (type = %s): %s", paramName, utils.GetType(fieldType), fieldType.String())
		service.Fields[paramName] = genericField
	}
}

func (service *Service) RegisterConstructor() {
	ast.Inspect(service.File.Ast, func(n ast.Node) bool {
		hasReceiver, funcDecl := service.methodHasReceiver(n)
		if !hasReceiver && funcDecl != nil && funcDecl.Name.Name == service.ConstructorName {
			service.Constructor = &types.ParsedMethod{
				Ast:     funcDecl,
				Name:    funcDecl.Name.Name,
				Service: service.Name,
			}
			logger.Logger.Infof("[PARSER] registered constructor %s for service %s", service.ConstructorName, service.Name)
		}
		return true
	})
}

func (service *Service) RegisterStructure() {
	var exposedMethodsNames []string
	for name := range service.ExposedMethods {
		exposedMethodsNames = append(exposedMethodsNames, name)
	}
	ast.Inspect(service.File.Ast, func(n ast.Node) bool {
		if service.ImplName != "" {
			return false
		}
		if funcDecl, ok := n.(*ast.FuncDecl); ok && slices.Contains(exposedMethodsNames, funcDecl.Name.Name) {
			if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
				if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
					if ident, ok := recv.X.(*ast.Ident); ok {
						service.ImplName = ident.Name
						logger.Logger.Debugf("[PARSER] registered structure %s for service %s", service.ImplName, service.Name)
						return false
					}
				}
			}
		}
		return true
	})
}

func (service *Service) funcImplementsQueue(funcDecl *ast.FuncDecl, recvIdent *ast.Ident) (implements bool, dbInstance datastores.DatabaseInstance) {
	// inspect methods
	ast.Inspect(funcDecl, func(n ast.Node) bool {
		ok, methodIdent, fieldIdent := getFuncCallIfSelectedServiceField(n, recvIdent)
		if !ok || fieldIdent == nil {
			return true
		}
		if field, isField := service.Fields[fieldIdent.Name]; isField {
			if dbField, isDbField := field.(*types.DatabaseField); isDbField {
				if dbField.IsQueue && methodIdent.Name == "Pop" {
					implements = true
					dbInstance = dbField.DbInstance
					return false
				}
			}
		}
		return true
	})
	return implements, dbInstance
}

func getFuncCallIfSelectedServiceField(service ast.Node, expectedRecvIdent *ast.Ident) (ok bool, methodIdent *ast.Ident, fieldIdent *ast.Ident) {
	hasCurrentServiceRecvIdent := func(selectorExpr *ast.SelectorExpr, expectedRecvIdent *ast.Ident) bool {
		if serviceRecvIdent, ok := selectorExpr.X.(*ast.Ident); ok {
			if serviceRecvIdent.Name == expectedRecvIdent.Name {
				return true
			}
		}
		return false
	}

	// e.g. f.queue.Push
	//    ^ident2 ^ident ^method
	// e.g. f.storageService.StorePost
	//      ^ident2  ^ident    ^method
	if funcCall, ok := service.(*ast.CallExpr); ok {
		if methodSel, ok := funcCall.Fun.(*ast.SelectorExpr); ok {
			// get first selector (e.g. storageService)
			if fieldSel, ok := methodSel.X.(*ast.SelectorExpr); ok && hasCurrentServiceRecvIdent(fieldSel, expectedRecvIdent) {
				return true, methodSel.Sel, fieldSel.Sel
			} else if hasCurrentServiceRecvIdent(methodSel, expectedRecvIdent) {
				return true, methodSel.Sel, nil
			}
		}
	}
	return false, nil, nil
}

func (service *Service) addQueueHandlerMethod(funcDecl *ast.FuncDecl, recvIdent *ast.Ident, dbInstance datastores.DatabaseInstance) {
	params, returns := service.parseFuncDeclParameters(funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Recv:    &types.MethodReceiver{Name: recvIdent.Name},
		Params:  params,
		Returns: returns,
		Service: service.Name,
	}
	parsedMethod.DbInstances = append(parsedMethod.DbInstances, dbInstance)
	service.QueueHandlerMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Debugf("[PARSER] added worker method %s for service %s: %v (field=%s)", parsedMethod.String(), service.Name, parsedMethod.DbInstances, dbInstance)
}

func (service *Service) addInternalMethod(funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) {
	params, returns := service.parseFuncDeclParameters(funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Params:  params,
		Returns: returns,
		Recv:    &types.MethodReceiver{Name: rcvIdent.Name},
		Service: service.Name,
	}
	service.InternalMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Infof("[PARSER] added internal method %s to service %s", parsedMethod.String(), service.Name)
}

func (service *Service) addExposedMethod(funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) {
	params, returns := service.parseFuncDeclParameters(funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Recv:    &types.MethodReceiver{Name: rcvIdent.Name},
		Params:  params,
		Returns: returns,
		Service: service.Name,
	}
	service.ExposedMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Debugf("[PARSER] added exposed method %s to service %s", parsedMethod.String(), service.Name)
}

func (service *Service) ParseConstructorAndLoadFields(paramDBs map[string]datastores.DatabaseInstance) {
	constructor := service.Constructor
	ast.Inspect(constructor.GetBody(), func(n ast.Node) bool {
		compositeLit, ok := n.(*ast.CompositeLit)
		if !ok {
			return true
		}
		if ident, ok := compositeLit.Type.(*ast.Ident); ok && ident.Name == service.ImplName {
			// iterate all key value pairs passed during the service definition
			for _, elt := range compositeLit.Elts {
				if kv, ok := elt.(*ast.KeyValueExpr); ok {
					keyIdent := kv.Key.(*ast.Ident)
					if keyIdent == nil {
						logger.Logger.Fatalf("unexpected key type %s", utils.GetType(kv.Key))
					}
					field := service.Fields[keyIdent.Name]
					if field == nil {
						logger.Logger.Fatalf("field %s unexpectedly not found", keyIdent.Name)
					}
					if dbField, ok := field.(*types.DatabaseField); ok {
						valueIdent := kv.Value.(*ast.Ident)
						if valueIdent == nil {
							logger.Logger.Fatalf("unexpected ident type %s", utils.GetType(kv.Value))
						}
						dbInstance := paramDBs[valueIdent.Name]
						if dbInstance == nil {
							logger.Logger.Fatalf("could not find database instance for constructor parameter %s in %s", valueIdent.Name, service.Name)
						}
						dbField.DbInstance = dbInstance
						logger.Logger.Infof("[PARSER] [%s] linked database field '%s' to instance '%s'", service.Name, dbField.GetName(), dbField.DbInstance.GetName())
					} else if _, ok := field.(*types.ServiceField); ok {
						// ignore service
						continue
					} else if field, ok := field.(*types.GenericField); ok {
						if basicLit, ok := kv.Value.(*ast.BasicLit); ok {
							field.GetType().AddValue(basicLit.Value)
						} else {
							logger.Logger.Fatalf("ignoring value %v", kv.Value)
						}
					} else {
						logger.Logger.Fatalf("ignoring composite element (%s, %s)", keyIdent.Name, utils.GetType(kv.Value))
					}
				}
			}
		}
		return true
	})
}
