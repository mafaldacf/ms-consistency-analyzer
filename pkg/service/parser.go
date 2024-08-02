package service

import (
	"go/ast"
	"slices"

	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

func (service *Service) isMethodExposedByService(methodName string) bool {
	// check if the function declaration being implemented by the Service structure
	// is actually an exposed method to other services
	_, ok := service.ExposedMethods[methodName]
	return ok
}

func (service *Service) methodReceiverImplementsService(parsedMethod *types.ParsedMethod) bool {
	methodReceiver := parsedMethod.GetReceiverIfExists()
	if methodReceiver == nil {
		return false
	}
	return service.Type.IsCurrentServiceType(methodReceiver.GetType())
}

func (service *Service) methodIsServiceConstructor(parsedMethod *types.ParsedMethod) bool {
	return parsedMethod.Name == service.ConstructorName
}

func (service *Service) attachConstructor(parsedMethod *types.ParsedMethod) {
	service.Constructor = parsedMethod
}

func (service *Service) AttachParsedMethods() []*types.ParsedMethod {
	var serviceImplementedMethods []*types.ParsedMethod
	logger.Logger.Tracef("[SERVICE] inspecting exposed methods for service implementation %s\n", service.ImplName)

	for _, parsedMethod := range service.GetPackage().GetAllParsedMethods() {
		if service.methodReceiverImplementsService(parsedMethod) {
			if service.isMethodExposedByService(parsedMethod.Name) {
				service.attachExportedMethod(parsedMethod)
			} else if service.ImplementsQueue {
				if instance := service.getQueueInstanceIfMethodHandlesQueue(parsedMethod); instance != nil {
					//logger.Logger.Fatalf("FOUND: METHOD (%s) HANDLES QUEUE? INSTANCE = %v", parsedMethod.Name, instance.GetName())
					service.attachQueueHandlerMethod(parsedMethod, instance)
					service.attachInternalMethod(parsedMethod)
				} else {
					service.attachInternalMethod(parsedMethod)
				}
			} else {
				service.attachInternalMethod(parsedMethod)
			}
			serviceImplementedMethods = append(serviceImplementedMethods, parsedMethod)
		} else if service.methodIsServiceConstructor(parsedMethod) {
			service.attachConstructor(parsedMethod)
		} else {
			logger.Logger.Warnf("[SERVICE] [%s] ignoring attachment parsed method (%s)", service.GetName(), parsedMethod.String())
		}
	}
	return serviceImplementedMethods
}

func (service *Service) AttachAllPackageMethods() {
	for _, parsedMethod := range service.GetPackage().GetAllParsedMethods() {
		if !parsedMethod.HasAttachedService() {
			service.PackageMethods[parsedMethod.Name] = parsedMethod
			logger.Logger.Warnf("[PARSER] [%s] attached package method: %s", service.Name, parsedMethod.String())
			//logger.Logger.Warnf("[PARSER] [%s] package methods list: %v", service.Name, service.PackageMethods)
		}
	}
}

// RegisterFields parses the service's fields from the previously parsed impl user type declared in the package
func (service *Service) RegisterFields() {
	logger.Logger.Tracef("[PARSER] [%s] inspecting fields...\n", service.Name)

	serviceImplType := service.GetPackage().GetDeclaredType(service.ImplName)
	userType, ok := serviceImplType.(*gotypes.UserType)
	if !ok {
		logger.Logger.Fatalf("[PARSER] [%s] service impl is not user type: (%s) %s", service.GetName(), utils.GetType(serviceImplType), serviceImplType.String())
	}

	structType, ok := userType.UserType.(*gotypes.StructType)
	if !ok {
		logger.Logger.Fatalf("[PARSER] [%s] service impl underlying user type is not struct or interface type: (%s) %s", service.GetName(), utils.GetType(userType.UserType), userType.UserType.String())
	}

	for i, fieldType := range structType.GetFieldTypes() {
		service.Fields[fieldType.GetName()] = service.computeServiceFieldFromFieldWrappedType(fieldType.GetWrappedType(), fieldType.GetName(), i)
	}
	logger.Logger.Infof("[PARSER] [%s] registered %d fields: %v", service.GetName(), len(service.Fields), service.Fields)
}

func (service *Service) computeServiceFieldFromFieldWrappedType(wrappedType gotypes.Type, paramName string, idx int) types.Field {
	switch t := wrappedType.(type) {
	case *blueprint.BlueprintBackendType:
		dbField := &types.DatabaseField{
			FieldInfo: types.FieldInfo{
				Name: paramName,
				Type: t.Copy(true),
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
				Name: paramName,
				Type: wrappedType,
			},
		}
	}
	return &types.GenericField{
		FieldInfo: types.FieldInfo{
			Name: paramName,
			Type: wrappedType,
		},
	}
}

func (service *Service) RegisterConstructor() {
	method := service.GetPackage().GetParsedMethod(service.ConstructorName, "")
	method.SetConstructor()
	service.Constructor = method
	logger.Logger.Infof("[PARSER] [%s] registered constructor (%s)", service.GetName(), service.ConstructorName)
}

func (service *Service) FindAndRegisterImplStructure() {
	var exportedMethods []string
	for name := range service.ExposedMethods {
		exportedMethods = append(exportedMethods, name)
	}
	// get impl name
	ast.Inspect(service.File.Ast, func(n ast.Node) bool {
		if service.ImplName != "" {
			return false
		}
		if funcDecl, ok := n.(*ast.FuncDecl); ok && slices.Contains(exportedMethods, funcDecl.Name.Name) {
			if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
				if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
					if ident, ok := recv.X.(*ast.Ident); ok {
						service.ImplName = ident.Name
						service.Type.ImplName = ident.Name
						return false
					}
				}
			}
		}
		return true
	})
}

func (service *Service) getQueueInstanceIfMethodHandlesQueue(parsedMethod *types.ParsedMethod) datastores.DatabaseInstance {
	var dbInstance datastores.DatabaseInstance

	// inspect methods
	ast.Inspect(parsedMethod.Ast, func(n ast.Node) bool {
		ok, methodIdent, fieldIdent := getFuncCallIfSelectedServiceField(n, parsedMethod.Ast.Recv.List[0].Names[0])
		if !ok || fieldIdent == nil {
			return true
		}
		if field, isField := service.Fields[fieldIdent.Name]; isField {
			if dbField, isDbField := field.(*types.DatabaseField); isDbField {
				if dbField.IsQueue && methodIdent.Name == "Pop" {
					dbInstance = dbField.DbInstance
					return false
				}
			}
		}
		return true
	})
	return dbInstance
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

func (service *Service) attachQueueHandlerMethod(parsedMethod *types.ParsedMethod, dbInstance datastores.DatabaseInstance) {
	parsedMethod.DbInstances = append(parsedMethod.DbInstances, dbInstance)
	service.QueueHandlerMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Infof("[PARSER] [%s] attached queue handler method method for instance (%s): %s", service.Name, dbInstance.String(), parsedMethod.String())
	//logger.Logger.Warnf("[PARSER] [%s] queue handler methods list: %v", service.Name, service.QueueHandlerMethods)
}

func (service *Service) attachInternalMethod(parsedMethod *types.ParsedMethod) {
	service.InternalMethods[parsedMethod.Name] = parsedMethod
	parsedMethod.AttachService(service.GetName())
	logger.Logger.Infof("[PARSER] [%s] attached internal method: %s", service.Name, parsedMethod.String())
	//logger.Logger.Warnf("[PARSER] [%s] internal methods list: %v", service.Name, service.InternalMethods)
}

func (service *Service) attachExportedMethod(parsedMethod *types.ParsedMethod) {
	service.ExposedMethods[parsedMethod.Name] = parsedMethod
	parsedMethod.AttachService(service.GetName())
	logger.Logger.Infof("[PARSER] [%s] attached exposed method: %s", service.Name, parsedMethod.String())
	//logger.Logger.Warnf("[PARSER] [%s] exposed methods list: %v", service.Name, service.ExposedMethods)
}

// LoadServiceFieldsValues loads generic fields and datastore instances
func (service *Service) LoadServiceFieldsValues(paramDBs map[string]datastores.DatabaseInstance) {
	logger.Logger.Infof("[PARSER] [%s] attaching datastore instances to service fields...", service.Name)

	ast.Inspect(service.Constructor.GetBody(), func(n ast.Node) bool {
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
						logger.Logger.Fatalf("[PARSER] [%s] field (%s) unexpectedly not found for fields list: %v", service.Name, keyIdent.Name, service.Fields)
					}
					if dbField, ok := field.(*types.DatabaseField); ok {
						valueIdent := kv.Value.(*ast.Ident)
						if valueIdent == nil {
							logger.Logger.Fatalf("[PARSER] [%s] unexpected ident type (%s)", service.Name, utils.GetType(kv.Value))
						}
						dbInstance := paramDBs[valueIdent.Name]
						if dbInstance == nil {
							logger.Logger.Fatalf("[PARSER] [%s] could not find database instance for constructor parameter (%s) for paramDBs list: %v", service.Name, valueIdent.Name, paramDBs)
						}
						dbField.DbInstance = dbInstance
						dbField.GetType().(*blueprint.BlueprintBackendType).DbInstance = dbInstance
						logger.Logger.Debugf("[PARSER] [%s] linked datastore instance (%s) to service field (%s)", service.Name, dbField.DbInstance.GetName(), dbField.String())
					} else if _, ok := field.(*types.ServiceField); ok {
						// ignore service
						continue
					} else if field, ok := field.(*types.GenericField); ok {
						if basicLit, ok := kv.Value.(*ast.BasicLit); ok {
							field.GetType().AddValue(basicLit.Value)
						} else if _, ok := kv.Value.(*ast.CallExpr); ok {
							logger.Logger.Warnf("[PARSER - TODOOOOOOO!!!!] [%s] ignoring value (%s) (%v)", service.Name, utils.GetType(kv.Value), kv.Value)
						} else if _, ok := kv.Value.(*ast.UnaryExpr); ok {
							logger.Logger.Warnf("[PARSER - TODOOOOOOO!!!!] [%s] ignoring value (%s) (%v)", service.Name, utils.GetType(kv.Value), kv.Value)
						} else if _, ok := kv.Value.(*ast.Ident); ok {
							logger.Logger.Warnf("[PARSER - TODOOOOOOO!!!!] [%s] ignoring value (%s) (%v)", service.Name, utils.GetType(kv.Value), kv.Value)
						} else {
							logger.Logger.Warnf("[PARSER] [%s] ignoring value (%s) (%v)", service.Name, utils.GetType(kv.Value), kv.Value)
						}
					} else {
						logger.Logger.Fatalf("[PARSER] [%s] ignoring composite element (%s, %s)", service.Name, keyIdent.Name, utils.GetType(kv.Value))
					}
				}
			}
		}
		return true
	})

	logger.Logger.Infof("[PARSER] [%s] updating datastore instances in declared service impl user type: FIELDS = %v", service.Name, service.Fields)
	impl := service.GetPackage().GetDeclaredType(service.ImplName).(*gotypes.UserType).UserType.(*gotypes.StructType)
	for name, field := range service.Fields {
		logger.Logger.Debugf("[PARSER] [%s] updating datastore instances in declared service impl user type: %s // %s", service.Name, name, field)
		if implFieldType, ok := impl.GetFieldTypeByName(name).WrappedType.(*blueprint.BlueprintBackendType); ok {
			if serviceFieldType, ok := field.GetType().(*blueprint.BlueprintBackendType); ok {
				impl.UpdateFieldSubTypeByName(name, serviceFieldType)
				logger.Logger.Debugf("[PARSER] [%s] loaded impl type (%s)", service.Name, serviceFieldType.StringWithInstance())
			} else {
				logger.Logger.Fatalf("[PARSER] [%s] impl type (%s) does not match service field type (%s) for BlueprintBackendType", service.Name, serviceFieldType.StringWithInstance(), implFieldType.StringWithInstance())
			}
		}
	}
}
