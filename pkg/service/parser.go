package service

import (
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
	"go/ast"
	"slices"
	"strings"
)

func (node *ServiceNode) ParseImports() {
	logger.Logger.Debugf("inspecting imports for service %s\n", node.Name)

	for _, imp := range node.File.Imports {
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

		importSpec := &ParsedImportSpec{
			Ast:   imp,
			Alias: alias,
			Path:  path,
			// FIXME: package can sometimes be different than path when it is replaced by the go.mod
			// but this is VERY rare, especially between services
			// still, we need to later cover this edge case
			Package: path,
		}
		// FIXME: this can be different if replaced in the Go.mod file
		if path == "github.com/blueprint-uservices/blueprint/runtime/core/backend" {
			importSpec.IsBlueprintBackend = true
		}
		node.Imports[alias] = importSpec
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
				if ident, ok := recv.X.(*ast.Ident); ok && ident.Name == node.Impl {
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

func (node *ServiceNode) parseFuncDeclParams(funcDecl *ast.FuncDecl) []*types.FunctionParameter {
	return node.ParseFieldList(funcDecl.Type.Params)
}

func (node *ServiceNode) ParseFieldList(params *ast.FieldList) []*types.FunctionParameter {
	var funcParams []*types.FunctionParameter 
	for _, field := range params.List {
		paramType := types.ComputeType(field.Type, node.Package, node.GetImportsMap())
		for _, ident := range field.Names {
			param := &types.FunctionParameter{
				FieldInfo: types.FieldInfo{
					Ast:  field,
					Type: paramType,
					Name: ident.Name,
				},
			}
			funcParams = append(funcParams, param)
		}
	}
	return funcParams
}

func (node *ServiceNode) ParseMethods() {
	logger.Logger.Debugf("inspecting exposed methods for service implementation %s\n", node.Impl)

	ast.Inspect(node.File, func(n ast.Node) bool {
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

func (node *ServiceNode) ParseMethodsBody() {
	for name, method := range node.ExposedMethods {
		logger.Logger.Debugf(">> EXPOSED >> %s", name)
		node.findMethodBodyCalls(method)
	}
	for name, method := range node.QueueHandlerMethods {
		logger.Logger.Debugf(">> QUEUE HANDLER >> %s", name)
		node.findMethodBodyCalls(method)
	}
	//FIXME: move to package methods
	for name, method := range node.InternalMethods {
		logger.Logger.Debugf(">> INTERNAL >> %s", name)
		node.findMethodBodyCalls(method)
	}
}

func (node *ServiceNode) ParseFields() {
	logger.Logger.Debugf("inspecting fields for service %s\n", node.Name)

	ast.Inspect(node.File, func(n ast.Node) bool {
		// a struct type is first a spec type
		// we want to make sure that we found the service type
		// otherwise, we return true to keep recursition to next ast node
		if ts, ok := n.(*ast.TypeSpec); ok {
			if ts.Name.Name != node.Impl {
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

func (node *ServiceNode) RegisterConstructor(constructorName string) {
	ast.Inspect(node.File, func(n ast.Node) bool {
		hasReceiver, funcDecl := node.methodHasReceiver(n)
		if !hasReceiver && funcDecl != nil && funcDecl.Name.Name == constructorName {
			node.Constructor = &ParsedFuncDecl{
				Ast:     funcDecl,
				Name:    funcDecl.Name.Name,
				Service: node.Name,
			}
			logger.Logger.Debugf("[PARSER] registered constructor %s for service %s", constructorName, node.Name)
		}
		return true
	})
}

func (node *ServiceNode) RegisterStructure() {
	var exposedMethodsNames []string
	for name := range node.ExposedMethods {
		exposedMethodsNames = append(exposedMethodsNames, name)
	}
	ast.Inspect(node.File, func(n ast.Node) bool {
		if node.Impl != "" {
			return false
		}
		if funcDecl, ok := n.(*ast.FuncDecl); ok && slices.Contains(exposedMethodsNames, funcDecl.Name.Name) {
			if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
				if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
					if ident, ok := recv.X.(*ast.Ident); ok {
						node.Impl = ident.Name
						logger.Logger.Debugf("[PARSER] registered structure %s for service %s", node.Impl, node.Name)
						return false
					}
				}
			}
		}
		return true
	})
}

// saveFieldWithType saves the service or database fields defined in the structure
func (node *ServiceNode) saveFieldWithType(field *ast.Field, paramName string, idx int) {
	switch t := field.Type.(type) {

	// if the type is from the current package, then it is probably a service import
	// so we need to check the type and if the type correponds to an existing service
	case *ast.Ident:
		// the field indeed corresponds to another service
		// so the package of the variable is the same
		if _, ok := node.Services[t.Name]; ok {
			node.Fields[paramName] = &types.ServiceField{
				FieldInfo: types.FieldInfo{
					Ast:  field,
					Name: paramName,
					Type: &types.UserType{
						Name:    t.Name,
						Package: node.Package,
					},
				},
				Idx: idx,
			}
		}

	// probably selecting from a specific package
	case *ast.SelectorExpr:
		// e.g. backend.Queue
		//      ^ ident ^ selector
		if ident, ok := t.X.(*ast.Ident); ok {
			if impt, ok := node.Imports[ident.Name]; ok {
				// check if the matched package is a database package imported from blueprint
				if impt.IsBlueprintBackend && frameworks.IsBlueprintBackend(t.Sel.Name) {
					newField := &types.DatabaseField{
						FieldInfo: types.FieldInfo{
							Ast:  field,
							Name: paramName,
							Type: &types.UserType{
								Name:    t.Sel.Name,
								Package: impt.Package,
							},
						},
						IsQueue: frameworks.IsBlueprintBackendQueue(t.Sel.Name),
						Idx:     idx,
					}
					if frameworks.IsBlueprintBackendQueue(t.Sel.Name) {
						newField.IsQueue = true
						node.ImplementsQueue = true
					}
					node.Fields[paramName] = newField
				}
				// check if the import matches the path of any of existing services
				for _, s := range node.Services {
					if s.Package == impt.Package {
						node.Fields[paramName] = &types.ServiceField{
							FieldInfo: types.FieldInfo{
								Ast:  field,
								Name: paramName,
								Type: &types.UserType{
									Name:    t.Sel.Name,
									Package: s.Package,
								},
							},
						}
					}
				}
			}
		}
	default:
		logger.Logger.Warnf("unknown field type %s for service %s", field.Type, node.Name)
	}
}

func (node *ServiceNode) funcImplementsQueue(funcDecl *ast.FuncDecl, recvIdent *ast.Ident) (implements bool, dbInstance types.DatabaseInstance) {
	// inspect methods
	ast.Inspect(funcDecl, func(n ast.Node) bool {
		ok, _, methodIdent, fieldIdent, _ := selectedFieldOrInternalFuncInCall(n, recvIdent)
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

func (node *ServiceNode) addQueueHandlerMethod(funcDecl *ast.FuncDecl, recvIdent *ast.Ident, dbInstance types.DatabaseInstance) {
	params := node.parseFuncDeclParams(funcDecl)
	parsedFuncDecl := &ParsedFuncDecl{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Recv:    recvIdent,
		Params:  params,
		Service: node.Name,
	}
	parsedFuncDecl.DbInstances = append(parsedFuncDecl.DbInstances, dbInstance)
	node.QueueHandlerMethods[parsedFuncDecl.Name] = parsedFuncDecl
	logger.Logger.Debugf("[PARSER] added worker method %s for service %s: %v (field=%s)", parsedFuncDecl.String(), node.Name, parsedFuncDecl.DbInstances, dbInstance)
}

func (node *ServiceNode) addInternalMethod(funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) {
	params := node.parseFuncDeclParams(funcDecl)
	parsedFuncDecl := &ParsedFuncDecl{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Params:  params,
		Recv:    rcvIdent,
		Service: node.Name,
	}
	node.InternalMethods[parsedFuncDecl.Name] = parsedFuncDecl
	logger.Logger.Debugf("[PARSER] added internal method %s to service %s", parsedFuncDecl.String(), node.Name)
}

func (node *ServiceNode) addExposedMethod(funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) {
	params := node.parseFuncDeclParams(funcDecl)
	parsedFuncDecl := &ParsedFuncDecl{
		Ast:     funcDecl,
		Name:    funcDecl.Name.Name,
		Recv:    rcvIdent,
		Params:  params,
		Service: node.Name,
	}
	node.ExposedMethods[parsedFuncDecl.Name] = parsedFuncDecl
	logger.Logger.Debugf("[PARSER] added exposed method %s to service %s", parsedFuncDecl.String(), node.Name)
}

func hasCurrentServiceRecvIdent(selectorExpr *ast.SelectorExpr, expectedRecvIdent *ast.Ident) (bool, *ast.Ident) {
	if serviceRecvIdent, ok := selectorExpr.X.(*ast.Ident); ok {
		if serviceRecvIdent.Name == expectedRecvIdent.Name {
			return true, serviceRecvIdent
		}
	}
	return false, nil
}

func selectedFieldOrInternalFuncInCall(node ast.Node, expectedRecvIdent *ast.Ident) (ok bool, funcCall *ast.CallExpr, methodIdent *ast.Ident, fieldIdent *ast.Ident, serviceRecvIdent *ast.Ident) {
	// e.g. f.queue.Push
	//    ^ident2 ^ident ^method
	// e.g. f.storageService.StorePost
	//      ^ident2  ^ident    ^method
	if funcCall, ok := node.(*ast.CallExpr); ok {
		if methodSel, ok := funcCall.Fun.(*ast.SelectorExpr); ok {
			// get first selector (e.g. storageService)
			if fieldSel, ok := methodSel.X.(*ast.SelectorExpr); ok {
				if ok, serviceRecvIdent := hasCurrentServiceRecvIdent(fieldSel, expectedRecvIdent); ok {
					return true, funcCall, methodSel.Sel, fieldSel.Sel, serviceRecvIdent
				}
			} else if ok, serviceRecvIdent := hasCurrentServiceRecvIdent(methodSel, expectedRecvIdent); ok {
				return true, funcCall, methodSel.Sel, nil, serviceRecvIdent
			}
		}
	}
	return false, nil, nil, nil, nil
}

func (node *ServiceNode) findMethodBodyCalls(parsedFuncDecl *ParsedFuncDecl) {
	logger.Logger.Debugf("[AST PARSER] visiting method %s", parsedFuncDecl.Name)

	ast.Inspect(parsedFuncDecl.GetAst(), func(n ast.Node) bool {
		// beware that functions migh have nil receivers
		ok, funcCall, methodIdent, fieldIdent, serviceRecvIdent := selectedFieldOrInternalFuncInCall(n, parsedFuncDecl.Recv)
		if !ok {
			return true
		}
		if fieldIdent != nil {
			// if the targeted variable corresponds to a service field
			if field, ok := node.Fields[fieldIdent.Name]; ok {
				// store function call either as service call or database call
				// if the field corresponds to a service field
				if serviceField, ok := field.(*types.ServiceField); ok {
					// 1. extract the service field from the current service
					// 2. get the target node service for the type
					// 3. add the targeted method of the other service for the current call expression
					targetServiceType := serviceField.GetTypeName()
					targetServiceNode := node.Services[targetServiceType]
					targetMethod := targetServiceNode.ExposedMethods[methodIdent.Name]
					svcParsedCallExpr := &ServiceParsedCallExpr{
						ParsedCallExpr: ParsedCallExpr{
							Ast:         funcCall,
							Receiver:    serviceRecvIdent.Name,
							TargetField: fieldIdent.Name,
							Name:        methodIdent.Name,
							Pos:         funcCall.Pos(),
							Method:      targetMethod,
						},
						CallerTypeName: &types.Service{Name: node.Name, Package: node.Package},
						CalleeTypeName: serviceField.GetType(),
					}
					parsedFuncDecl.Calls = append(parsedFuncDecl.Calls, svcParsedCallExpr)
					logger.Logger.Debugf("[PARSER] found new service call %s (params: %v)", svcParsedCallExpr.String(), svcParsedCallExpr.Params)
				}
				// if the field corresponds to a database field
				if databaseField, ok := field.(*types.DatabaseField); ok {
					// 1. extract the service field from the current service
					// 2. get the target database node
					// 3. add the target method for the current call expression
					targetDatabaseType := databaseField.GetTypeName()
					dbCall := &DatabaseParsedCallExpr{
						ParsedCallExpr: ParsedCallExpr{
							Ast:         funcCall,
							Receiver:    serviceRecvIdent.Name,
							TargetField: fieldIdent.Name,
							Name:        methodIdent.Name,
							Pos:         funcCall.Pos(),
							Method:      frameworks.GetBackendMethod(fmt.Sprintf("%s.%s", targetDatabaseType, methodIdent.Name)),
						},
						CallerTypeName: &types.Service{Name: node.Name, Package: node.Package},
						DbInstance:     databaseField.DbInstance,
					}
					parsedFuncDecl.Calls = append(parsedFuncDecl.Calls, dbCall)
					logger.Logger.Debugf("[PARSER] found new database call %s (params: %v)", dbCall.String(), dbCall.Params)
				}
			}
		} else if funcDecl, ok := node.InternalMethods[methodIdent.Name]; ok {
			internalCall := &InternalTempParsedCallExpr{
				ParsedCallExpr: ParsedCallExpr{
					Ast:      funcCall,
					Receiver: serviceRecvIdent.Name,
					Name:     methodIdent.Name,
					Method:   funcDecl,
					Pos:      funcCall.Pos(),
				},
				ServiceTypeName: &types.Service{Name: node.Name, Package: node.Package},
			}
			parsedFuncDecl.Calls = append(parsedFuncDecl.Calls, internalCall)
			logger.Logger.Debugf("[PARSER] found new internal call %s (params: %v)", internalCall.String(), internalCall.Params)
		}
		return true
	})
}

func (node *ServiceNode) ParseConstructor(constructorArgs []string, dbInstancesConstructorIdx map[int]types.DatabaseInstance) {
	constructor := node.Constructor
	ast.Inspect(constructor.GetBody(), func(n ast.Node) bool {
		compositeLit, ok := n.(*ast.CompositeLit)
		if !ok {
			return true
		}
		if ident, ok := compositeLit.Type.(*ast.Ident); ok && ident.Name == node.Impl {
			// iterate all key value pairs passed during the service definition
			for _, elt := range compositeLit.Elts {
				if kv, ok := elt.(*ast.KeyValueExpr); ok {
					keyIdent, ok1 := kv.Key.(*ast.Ident)
					keyValue, ok2 := kv.Value.(*ast.Ident)
					if ok1 && ok2 {
						field := node.Fields[keyIdent.Name]
						// check if the field being defined in a database field
						if dbField, ok := field.(*types.DatabaseField); ok {
							// find the value that was passed to the structure
							// implementation in the constructor arguments
							for idx, arg := range constructorArgs {
								if arg == keyValue.Name {
									if dbInstance, ok := dbInstancesConstructorIdx[idx]; ok {
										dbField.DbInstance = dbInstance
										logger.Logger.Debugf("[PARSER] [%s] linked database field '%s' to instance '%s'", node.Name, dbField.GetName(), dbInstance.GetName())
										break
									}
								}
							}
						}
					}
				}
			}
		}
		return true
	})
}
