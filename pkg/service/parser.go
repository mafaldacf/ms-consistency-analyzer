package service

import (
	"analyzer/pkg/datastores"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"go/ast"
	"slices"
	"strings"
)

func (node *ServiceNode) ParseImports() {
	logger.Logger.Debugf("inspecting imports for service %s\n", node.Name)

	for _, imp := range node.File.Ast.Imports {
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
		node.File.Imports[alias] = impt
		logger.Logger.Debugf("> %s for %s\n", alias, path)
	}
	logger.Logger.Debugln()
}

// ParseMethods:
//  1. inspects the service node
//  2. finds the function declarations that implement the
//     service struct along with the name of the function, the receiver, and the parameters
//  3. stores the function delc as parsed func decls in the methods of the service node

func (node *ServiceNode) methodImplementsService(n ast.Node) (ok bool, funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) {
	// check if node is a function declaration
	if funcDecl, ok = n.(*ast.FuncDecl); ok {
		// check if the function has any receivers (i.e. structure(s) implemented by the function)
		if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
			// get the function's receiver (i.e. i.e. structure(s) implemented by the function)
			if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
				// check if the data type (e.g. StorageService) of the receiver (i.e. structure(s) implemented by the function)
				// matches the one we are looking for (i.e. StorageService)
				if ident, ok := recv.X.(*ast.Ident); ok && ident.Name == node.ImplName {
					rcvIdent = funcDecl.Recv.List[0].Names[0]
					return true, funcDecl, rcvIdent
				}
			}
		}
	}
	return false, funcDecl, nil
}

func (node *ServiceNode) methodHasReceiver(n ast.Node) (ok bool, funcDecl *ast.FuncDecl) {
	// check if node is a function declaration
	if funcDecl, ok = n.(*ast.FuncDecl); ok {
		// check if the function has any receivers (i.e. structure(s) implemented by the function)
		if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
			return true, funcDecl
		}
	}
	return false, funcDecl
}

func (node *ServiceNode) isMethodExposedByService(funcDecl *ast.FuncDecl) bool {
	// check if the function declaration being implemented by the Service structure
	// is actually an exposed method to other services
	_, ok := node.ExposedMethods[funcDecl.Name.Name]
	return ok
}

func (node *ServiceNode) parseFuncDeclParameters(funcDecl *ast.FuncDecl) ([]*types.FunctionField, []*types.FunctionField) {
	parser := func(fieldsList []*ast.Field) []*types.FunctionField {
		var params []*types.FunctionField
		for _, field := range fieldsList {
			paramType := types.ComputeType(field.Type, node.File)
			// returns with types only, which is usually the most frequent scenario
			if len(field.Names) == 0 {
				param := &types.FunctionField{
					FieldInfo: types.FieldInfo{
						Ast:  field,
						Type: paramType,
					},
				}
				params = append(params, param)
			}
			for _, ident := range field.Names {
				param := &types.FunctionField{
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

func (node *ServiceNode) ParseMethods() {
	logger.Logger.Debugf("inspecting exposed methods for service implementation %s\n", node.ImplName)

	ast.Inspect(node.File.Ast, func(n ast.Node) bool {
		implementsService, funcDecl, rcvIdent := node.methodImplementsService(n)
		if implementsService {
			if node.isMethodExposedByService(funcDecl) {
				node.addExposedMethod(funcDecl, rcvIdent)
				return true
			} else if node.ImplementsQueue {
				if funcImplementsQueue, dbInstance := node.funcImplementsQueue(funcDecl, rcvIdent); funcImplementsQueue {
					node.addQueueHandlerMethod(funcDecl, rcvIdent, dbInstance)
					return true
				}
			}
			node.addInternalMethod(funcDecl, rcvIdent)
		} else if funcDecl != nil && funcDecl.Name.Name != node.Constructor.Name {
			// be aware that there can be internal methods with the same name of the instructor
			// we distinguish them since the constructor usually does not implement the service
			// so we need to make sure that the name of this function (that does not implement the service) is not equal to the constructor
			node.addInternalMethod(funcDecl, nil)
		}
		return true
	})
}

func (node *ServiceNode) ParseFields() {
	logger.Logger.Debugf("inspecting fields for service %s\n", node.Name)

	ast.Inspect(node.File.Ast, func(n ast.Node) bool {
		// a struct type is first a spec type
		// we want to make sure that we found the service type
		// otherwise, we return true to keep recursition to next ast node
		if ts, ok := n.(*ast.TypeSpec); ok {
			if ts.Name.Name != node.ImplName {
				return true
			}
		}
		if str, ok := n.(*ast.StructType); ok {
			for idx, field := range str.Fields.List {
				node.saveFieldWithType(field, field.Names[0].Name, idx)
				logger.Logger.Debugf("%s: saved field %s\n", node.Name, node.Fields[field.Names[0].Name])
			}
		}
		return true
	})
	logger.Logger.Debugln()
}

func (node *ServiceNode) RegisterConstructor() {
	ast.Inspect(node.File.Ast, func(n ast.Node) bool {
		hasReceiver, funcDecl := node.methodHasReceiver(n)
		if !hasReceiver && funcDecl != nil && funcDecl.Name.Name == node.ConstructorName {
			node.Constructor = &ParsedFuncDecl{
				Ast:     funcDecl,
				Name:    funcDecl.Name.Name,
				Service: node.Name,
			}
			logger.Logger.Debugf("[PARSER] registered constructor %s for service %s", node.ConstructorName, node.Name)
		}
		return true
	})
}

func (node *ServiceNode) RegisterStructure() {
	var exposedMethodsNames []string
	for name := range node.ExposedMethods {
		exposedMethodsNames = append(exposedMethodsNames, name)
	}
	ast.Inspect(node.File.Ast, func(n ast.Node) bool {
		if node.ImplName != "" {
			return false
		}
		if funcDecl, ok := n.(*ast.FuncDecl); ok && slices.Contains(exposedMethodsNames, funcDecl.Name.Name) {
			if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
				if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
					if ident, ok := recv.X.(*ast.Ident); ok {
						node.ImplName = ident.Name
						logger.Logger.Debugf("[PARSER] registered structure %s for service %s", node.ImplName, node.Name)
						return false
					}
				}
			}
		}
		return true
	})
}

func (node *ServiceNode) saveFieldWithType(field *ast.Field, paramName string, idx int) {
	fieldType := types.ComputeType(field.Type, node.File)
	switch t := fieldType.(type) {
	case *types.DatastoreType:
		dbField := &types.DatabaseField{
			FieldInfo: types.FieldInfo{
				Ast:  field,
				Name: paramName,
				Type: t,
			},
			IsQueue: frameworks.IsBlueprintBackendQueue(t.Name),
			Idx:     idx,
		}
		if dbField.IsQueue {
			node.ImplementsQueue = true
		}
		node.Fields[paramName] = dbField
	case *types.ServiceType:
		node.Fields[paramName] = &types.ServiceField{
			FieldInfo: types.FieldInfo{
				Ast:  field,
				Name: paramName,
				Type: t,
			},
		}
	default:
		logger.Logger.Warnf("SAVED GENERIC FIELD for %s", paramName)
		node.Fields[paramName] = &types.GenericField{
			FieldInfo: types.FieldInfo{
				Ast:  field,
				Name: paramName,
				Type: fieldType,
			},
		}
	}
}

func (node *ServiceNode) funcImplementsQueue(funcDecl *ast.FuncDecl, recvIdent *ast.Ident) (implements bool, dbInstance datastores.DatabaseInstance) {
	// inspect methods
	ast.Inspect(funcDecl, func(n ast.Node) bool {
		ok, methodIdent, fieldIdent := getFuncCallIfSelectedServiceField(n, recvIdent)
		if !ok || fieldIdent == nil {
			return true
		}
		if field, isField := node.Fields[fieldIdent.Name]; isField {
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

func getFuncCallIfSelectedServiceField(node ast.Node, expectedRecvIdent *ast.Ident) (ok bool, methodIdent *ast.Ident, fieldIdent *ast.Ident) {
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
	if funcCall, ok := node.(*ast.CallExpr); ok {
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

func (node *ServiceNode) addQueueHandlerMethod(funcDecl *ast.FuncDecl, recvIdent *ast.Ident, dbInstance datastores.DatabaseInstance) {
	params, returns := node.parseFuncDeclParameters(funcDecl)
	parsedFuncDecl := &ParsedFuncDecl{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Recv:    recvIdent,
		Params:  params,
		Returns: returns,
		Service: node.Name,
	}
	parsedFuncDecl.DbInstances = append(parsedFuncDecl.DbInstances, dbInstance)
	node.QueueHandlerMethods[parsedFuncDecl.Name] = parsedFuncDecl
	logger.Logger.Debugf("[PARSER] added worker method %s for service %s: %v (field=%s)", parsedFuncDecl.String(), node.Name, parsedFuncDecl.DbInstances, dbInstance)
}

func (node *ServiceNode) addInternalMethod(funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) {
	params, returns := node.parseFuncDeclParameters(funcDecl)
	parsedFuncDecl := &ParsedFuncDecl{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Params:  params,
		Returns: returns,
		Recv:    rcvIdent,
		Service: node.Name,
	}
	node.InternalMethods[parsedFuncDecl.Name] = parsedFuncDecl
	logger.Logger.Debugf("[PARSER] added internal method %s to service %s", parsedFuncDecl.String(), node.Name)
}

func (node *ServiceNode) addExposedMethod(funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) {
	params, returns := node.parseFuncDeclParameters(funcDecl)
	parsedFuncDecl := &ParsedFuncDecl{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Recv:    rcvIdent,
		Params:  params,
		Returns: returns,
		Service: node.Name,
	}
	node.ExposedMethods[parsedFuncDecl.Name] = parsedFuncDecl
	logger.Logger.Debugf("[PARSER] added exposed method %s to service %s", parsedFuncDecl.String(), node.Name)
}

func (node *ServiceNode) ParseConstructor(paramDBs map[string]datastores.DatabaseInstance) {
	constructor := node.Constructor
	ast.Inspect(constructor.GetBody(), func(n ast.Node) bool {
		compositeLit, ok := n.(*ast.CompositeLit)
		if !ok {
			return true
		}
		if ident, ok := compositeLit.Type.(*ast.Ident); ok && ident.Name == node.ImplName {
			// iterate all key value pairs passed during the service definition
			for _, elt := range compositeLit.Elts {
				if kv, ok := elt.(*ast.KeyValueExpr); ok {
					keyIdent, ok1 := kv.Key.(*ast.Ident)
					valueIdent, ok2 := kv.Value.(*ast.Ident)
					if ok1 && ok2 {
						field := node.Fields[keyIdent.Name]
						// check if the field being defined in a database field
						if dbField, ok := field.(*types.DatabaseField); ok {
							dbInstance := paramDBs[valueIdent.Name]
							if dbInstance == nil {
								logger.Logger.Fatalf("could not find database instance for constructor parameter %s in %s", valueIdent.Name, node.Name)
							}
							dbField.DbInstance = dbInstance
							logger.Logger.Debugf("[PARSER] [%s] linked database field '%s' to instance '%s'", node.Name, dbField.GetName(), dbField.DbInstance.GetName())
						}
					}
				}
			}
		}
		return true
	})
}
