package service

import (
	"go/ast"
	"slices"

	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/lookup"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

// ParseMethods:
//  1. inspects the service service
//  2. finds the function declarations that implement the
//     service struct along with the name of the function, the receiver, and the parameters
//  3. stores the function delc as parsed func decls in the methods of the service service

func (service *Service) methodImplementsService(n ast.Node) (bool, *ast.FuncDecl) {
	// check if service is a function declaration
	if funcDecl, ok := n.(*ast.FuncDecl); ok {
		// check if the function has any receivers (i.e. structure(s) implemented by the function)
		if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
			// get the function's receiver (i.e. i.e. structure(s) implemented by the function)
			if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
				// check if the data type (e.g. StorageService) of the receiver (i.e. structure(s) implemented by the function)
				// matches the one we are looking for (i.e. StorageService)
				if ident, ok := recv.X.(*ast.Ident); ok && ident.Name == service.ImplName {
					return true, funcDecl
				}
			}
		}
	}
	return false, nil
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
	_, ok := service.ExportedMethods[funcDecl.Name.Name]
	return ok
}

func (service *Service) ParseMethods() {
	logger.Logger.Tracef("[SERVICE] inspecting exposed methods for service implementation %s\n", service.ImplName)

	ast.Inspect(service.File.Ast, func(n ast.Node) bool {
		implementsService, funcDecl := service.methodImplementsService(n)

		if implementsService {
			if service.isMethodExposedByService(funcDecl) {
				service.addExportedMethod(funcDecl)
				return true
			} else if service.ImplementsQueue {
				if funcImplementsQueue, dbInstance := service.funcImplementsQueue(funcDecl); funcImplementsQueue {
					service.addQueueHandlerMethod(funcDecl, dbInstance)
					service.addInternalMethod(funcDecl)
					return true
				}
			}
			service.addInternalMethod(funcDecl)
		} else if funcDecl != nil && funcDecl.Name.Name != service.Constructor.Name {
			// be aware that there can be internal methods with the same name of the instructor
			// we distinguish them since the constructor usually does not implement the service
			// so we need to make sure that the name of this function (that does not implement the service) is not equal to the constructor
			service.addInternalMethod(funcDecl)
		}
		return true
	})
}

func (service *Service) ParseFields() {
	logger.Logger.Tracef("[SERVICE] inspecting fields for service %s\n", service.Name)

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
				name := field.Names[0].Name
				field := service.computeFieldFromType(field, name, idx)
				service.Fields[name] = field
				logger.Logger.Debugf("[SERVICE] %s: saved field %s\n", service.Name, service.Fields[name])
			}
		}
		return true
	})
}

func (service *Service) computeFieldFromType(field *ast.Field, paramName string, idx int) types.Field {
	fieldType := lookup.ComputeTypeForAstExpr(service.File, field.Type)
	switch t := fieldType.(type) {
	case *blueprint.BlueprintBackendType:
		dbField := &types.DatabaseField{
			FieldInfo: types.FieldInfo{
				Ast:  field,
				Name: paramName,
				Type: t.DeepCopy(),
			},
			IsQueue: t.IsQueue(),
			Idx:     idx,
		}
		if dbField.IsQueue {
			service.ImplementsQueue = true
		}
		return dbField
	case *gotypes.ServiceType:
		return &types.ServiceField{
			FieldInfo: types.FieldInfo{
				Ast:  field,
				Name: paramName,
				Type: t,
			},
		}
	}
	return &types.GenericField{
		FieldInfo: types.FieldInfo{
			Ast:  field,
			Name: paramName,
			Type: fieldType,
		},
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

func (service *Service) RegisterImplStructure() {
	var ExportedMethodsNames []string
	for name := range service.ExportedMethods {
		ExportedMethodsNames = append(ExportedMethodsNames, name)
	}
	// get impl name
	ast.Inspect(service.File.Ast, func(n ast.Node) bool {
		if service.ImplName != "" {
			return false
		}
		if funcDecl, ok := n.(*ast.FuncDecl); ok && slices.Contains(ExportedMethodsNames, funcDecl.Name.Name) {
			if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
				if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
					if ident, ok := recv.X.(*ast.Ident); ok {
						service.ImplName = ident.Name
						return false
					}
				}
			}
		}
		return true
	})
}

func (service *Service) funcImplementsQueue(funcDecl *ast.FuncDecl) (implements bool, dbInstance datastores.DatabaseInstance) {
	// inspect methods
	ast.Inspect(funcDecl, func(n ast.Node) bool {
		ok, methodIdent, fieldIdent := getFuncCallIfSelectedServiceField(n, funcDecl.Recv.List[0].Names[0])
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

func (service *Service) addQueueHandlerMethod(funcDecl *ast.FuncDecl, dbInstance datastores.DatabaseInstance) {
	params, returns, receiver := lookup.ComputeFuncDeclFields(service.File, funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:      funcDecl,
		Name:     funcDecl.Name.Name,
		Receiver: receiver,
		Params:   params,
		Returns:  returns,
		Service:  service.Name,
	}
	parsedMethod.DbInstances = append(parsedMethod.DbInstances, dbInstance)
	service.QueueHandlerMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Tracef("[PARSER] added worker method %s for service %s: %v (field=%s)", parsedMethod.String(), service.Name, parsedMethod.DbInstances, dbInstance)
}

func (service *Service) addInternalMethod(funcDecl *ast.FuncDecl) {
	params, returns, receiver := lookup.ComputeFuncDeclFields(service.File, funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:      funcDecl,
		Name:     funcDecl.Name.Name,
		Params:   params,
		Returns:  returns,
		Receiver: receiver,
		Service:  service.Name,
	}
	service.InternalMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Infof("[PARSER] added internal method %s to service %s", parsedMethod.String(), service.Name)
}

func (service *Service) addExportedMethod(funcDecl *ast.FuncDecl) {
	params, returns, receiver := lookup.ComputeFuncDeclFields(service.File, funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:      funcDecl,
		Name:     funcDecl.Name.Name,
		Receiver: receiver,
		Params:   params,
		Returns:  returns,
		Service:  service.Name,
	}
	service.ExportedMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Tracef("[PARSER] added exposed method %s to service %s", parsedMethod.String(), service.Name)
}

func (service *Service) ParseConstructorAndLoadImplFields(paramDBs map[string]datastores.DatabaseInstance) {
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
						logger.Logger.Fatalf("[PARSER] [%s] unexpected key type (%s)", service.Name, utils.GetType(kv.Key))
					}
					field := service.Fields[keyIdent.Name]
					if field == nil {
						logger.Logger.Fatalf("[PARSER] [%s] field (%s) unexpectedly not found", service.Name, keyIdent.Name)
					}
					if dbField, ok := field.(*types.DatabaseField); ok {
						valueIdent := kv.Value.(*ast.Ident)
						if valueIdent == nil {
							logger.Logger.Fatalf("[PARSER] [%s] unexpected ident type (%s)", service.Name, utils.GetType(kv.Value))
						}
						dbInstance := paramDBs[valueIdent.Name]
						if dbInstance == nil {
							logger.Logger.Fatalf("[PARSER] [%s] could not find database instance for constructor parameter (%s)", service.Name, valueIdent.Name)
						}
						dbField.DbInstance = dbInstance
						dbField.GetType().(*blueprint.BlueprintBackendType).DbInstance = dbInstance
						//logger.Logger.Debugf("[PARSER] [%s] linked datastore instance (%s) to service field (%s)", service.Name, dbField.DbInstance.GetName(), dbField.String())
					} else if _, ok := field.(*types.ServiceField); ok {
						// ignore service
						continue
					} else if field, ok := field.(*types.GenericField); ok {
						if basicLit, ok := kv.Value.(*ast.BasicLit); ok {
							field.GetType().AddValue(basicLit.Value)
						} else {
							logger.Logger.Fatalf("[PARSER] [%s] ignoring value (%v)", service.Name, kv.Value)
						}
					} else {
						logger.Logger.Fatalf("[PARSER] [%s] ignoring composite element (%s, %s)", service.Name, keyIdent.Name, utils.GetType(kv.Value))
					}
				}
			}
		}
		return true
	})

	impl := service.GetPackage().GetDeclaredType(service.ImplName).(*gotypes.UserType).UserType.(*gotypes.StructType)
	for name, field := range service.Fields {
		if implFieldType, ok := impl.GetFieldTypeByName(name).SubType.(*blueprint.BlueprintBackendType); ok {
			if serviceFieldType, ok := field.GetType().(*blueprint.BlueprintBackendType); ok {
				impl.UpdateFieldSubTypeByName(name, serviceFieldType)
				logger.Logger.Infof("[PARSER] [%s] matched service field type (%s) to impl type (%s)", service.Name, serviceFieldType.StringWithInstance(), implFieldType.StringWithInstance())
			} else {
				logger.Logger.Fatalf("[PARSER] [%s] service field type (%s) does not match impl type (%s) for BlueprintBackendType", service.Name, serviceFieldType.StringWithInstance(), implFieldType.StringWithInstance())
			}
		}
	}
}
