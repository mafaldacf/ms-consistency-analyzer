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

func (service *Service) ParseFields() {
	logger.Logger.Tracef("[PARSER] [%s] inspecting fields\n", service.Name)

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
				logger.Logger.Debugf("[PARSER] [%s] saved field (%s)\n", service.Name, service.Fields[name])
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
				Ast:             funcDecl,
				Name:            funcDecl.Name.Name,
				AttachedService: service.Name,
			}
			service.Constructor.SetConstructor()
			logger.Logger.Infof("[PARSER] registered constructor %s for service %s", service.ConstructorName, service.Name)
		}
		return true
	})
}

func (service *Service) RegisterImplStructure() {
	var ExportedMethodsNames []string
	for name := range service.ExposedMethods {
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

func (service *Service) buildAndAddQueueHandlerMethod(funcDecl *ast.FuncDecl, dbInstance datastores.DatabaseInstance) {
	params, returns, receiver := lookup.ComputeFuncDeclFields(service.File, funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:             funcDecl,
		Name:            funcDecl.Name.Name,
		Receiver:        receiver,
		Params:          params,
		Returns:         returns,
		AttachedService: service.Name,
	}
	parsedMethod.DbInstances = append(parsedMethod.DbInstances, dbInstance)
	service.QueueHandlerMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Tracef("[PARSER] added worker method %s for service %s: %v (field=%s)", parsedMethod.String(), service.Name, parsedMethod.DbInstances, dbInstance)
}

func (service *Service) attachQueueHandlerMethod(parsedMethod *types.ParsedMethod, dbInstance datastores.DatabaseInstance) {
	parsedMethod.DbInstances = append(parsedMethod.DbInstances, dbInstance)
	service.QueueHandlerMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Infof("[PARSER] [%s] attached queue handler method method for instance (%s): %s", service.Name, dbInstance.String(), parsedMethod.String())
	//logger.Logger.Warnf("[PARSER] [%s] queue handler methods list: %v", service.Name, service.QueueHandlerMethods)
}

func (service *Service) buildAndAddInternalMethod(funcDecl *ast.FuncDecl) {
	params, returns, receiver := lookup.ComputeFuncDeclFields(service.File, funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:             funcDecl,
		Name:            funcDecl.Name.Name,
		Params:          params,
		Returns:         returns,
		Receiver:        receiver,
		AttachedService: service.Name,
	}
	service.InternalMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Infof("[PARSER] added internal method %s to service %s", parsedMethod.String(), service.Name)
}

func (service *Service) attachInternalMethod(parsedMethod *types.ParsedMethod) {
	service.InternalMethods[parsedMethod.Name] = parsedMethod
	parsedMethod.AttachService(service.GetName())
	logger.Logger.Infof("[PARSER] [%s] attached internal method: %s", service.Name, parsedMethod.String())
	//logger.Logger.Warnf("[PARSER] [%s] internal methods list: %v", service.Name, service.InternalMethods)
}

func (service *Service) buildAndAddExportedMethod(funcDecl *ast.FuncDecl) {
	params, returns, receiver := lookup.ComputeFuncDeclFields(service.File, funcDecl)
	parsedMethod := &types.ParsedMethod{
		Ast:             funcDecl,
		Name:            funcDecl.Name.Name,
		Receiver:        receiver,
		Params:          params,
		Returns:         returns,
		AttachedService: service.Name,
	}
	service.ExposedMethods[parsedMethod.Name] = parsedMethod
	logger.Logger.Tracef("[PARSER] added exposed method %s to service %s", parsedMethod.String(), service.Name)
}

func (service *Service) attachExportedMethod(parsedMethod *types.ParsedMethod) {
	service.ExposedMethods[parsedMethod.Name] = parsedMethod
	parsedMethod.AttachService(service.GetName())
	logger.Logger.Infof("[PARSER] [%s] attached exposed method: %s", service.Name, parsedMethod.String())
	//logger.Logger.Warnf("[PARSER] [%s] exposed methods list: %v", service.Name, service.ExposedMethods)
}

func (service *Service) AttachDatastoreInstances(paramDBs map[string]datastores.DatabaseInstance) {
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
						logger.Logger.Debugf("[PARSER] [%s] linked datastore instance (%s) to service field (%s)", service.Name, dbField.DbInstance.GetName(), dbField.String())
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

	logger.Logger.Infof("[PARSER] [%s] updating datastore instances in declared service impl user type...", service.Name)
	impl := service.GetPackage().GetDeclaredType(service.ImplName).(*gotypes.UserType).UserType.(*gotypes.StructType)
	for name, field := range service.Fields {
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
