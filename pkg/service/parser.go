package service

import (
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	"fmt"
	"go/ast"
	"go/token"
	"strings"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
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
	return false, nil, nil
}

func (node *ServiceNode) methodExposedByService(funcDecl *ast.FuncDecl) bool {
	// check if the function declaration being implemented by the Service structure
	// is actually an exposed method to other services
	_, ok := node.ExposedMethods[funcDecl.Name.Name]
	return ok
}

func (node *ServiceNode) parseFuncDeclParams(funcDecl *ast.FuncDecl) []*types.FunctionField {
	var params []*types.FunctionField
	for _, field := range funcDecl.Type.Params.List {
		// TODO: any types with selector! e.g. model.Message (careful with context.Context)
		switch t := field.Type.(type) {
		case *ast.Ident:
			for _, fieldIdent := range field.Names {
				newParam := &types.FunctionField{
					Variable: gocode.Variable{
						Name: fieldIdent.Name,
					},
					Lineno: field.Pos(),
					Ast:    field,
				}
				if utils.IsBasicType(t.Name) {
					newParam.Type = &gocode.BasicType{
						Name: t.Name,
					}
				} else {
					newParam.Type = &gocode.UserType{
						Name:    t.Name,
						Package: node.Package,
					}
				}
				params = append(params, newParam)
			}
		case *ast.SelectorExpr:
			if pkgIdent, ok := t.X.(*ast.Ident); ok {
				for _, fieldIdent := range field.Names {
					importPathAlias := pkgIdent.Name
					importPath := node.Imports[importPathAlias]
					newParam := &types.FunctionField{
						Variable: gocode.Variable{
							Name: fieldIdent.Name,
							Type: &gocode.UserType{
								Name:    t.Sel.Name,
								Package: importPath.Package,
							},
						},
						Lineno: field.Pos(),
						Ast:    field,
					}
					params = append(params, newParam)
				}
			}
		}
	}
	return params
}

func (node *ServiceNode) ParseMethods() {
	logger.Logger.Debugf("inspecting exposed methods for service implementation %s\n", node.Impl)

	ast.Inspect(node.File, func(n ast.Node) bool {
		ok, funcDecl, rcvIdent := node.methodImplementsService(n)
		if ok {
			if node.methodExposedByService(funcDecl) {
				parsedFuncDecl := node.addExposedMethod(funcDecl, rcvIdent)
				logger.Logger.Debugf("Found exposed method: %s", parsedFuncDecl.String())
			} else {
				parsedFuncDecl := node.addInternalMethod(funcDecl, rcvIdent)
				logger.Logger.Debugf("Found internal method: %s", parsedFuncDecl.String())
				if node.ImplementsQueue {
					node.parseQueueImplementationIfWorker(parsedFuncDecl)
				}
			}
		}
		return true
	})
}

func (node *ServiceNode) ParseMethodsBody() {
	for _, method := range node.ExposedMethods {
		node.parseMethodBodyCalls(method)
	}
	for _, method := range node.InternalMethods {
		node.parseMethodBodyCalls(method)
	}
	for _, method := range node.WorkerMethods {
		node.parseMethodBodyCalls(method)
	}
}

func ParseInterfaceMethods(file *ast.File) {
	logger.Logger.Debug("inspecting service interface and methods \n")

	serviceMethods := []string{}
	ast.Inspect(file, func(n ast.Node) bool {
		if iface, ok := n.(*ast.InterfaceType); ok {
			for _, field := range iface.Methods.List {
				if methodName, ok := field.Names[0].Name, ok; ok {
					serviceMethods = append(serviceMethods, methodName)
					logger.Logger.Debugf("> %s\n", methodName)
				}
			}
		}
		return true
	})
}

func (node *ServiceNode) ParseServiceFields() {
	logger.Logger.Debugf("inspecting fields for service %s\n", node.Name)

	ast.Inspect(node.File, func(n ast.Node) bool {
		if str, ok := n.(*ast.StructType); ok {
			for _, field := range str.Fields.List {
				for _, ident := range field.Names {
					node.saveFieldWithType(field, ident.Name)
					logger.Logger.Debugf("%s: saved field %s\n", node.Name, node.Fields[ident.Name])
				}
			}
		}
		return true
	})
	logger.Logger.Debugln()
}

// saveFieldWithType saves the service or database fields defined in the structure
func (node *ServiceNode) saveFieldWithType(field *ast.Field, paramName string) {
	switch t := field.Type.(type) {

	// if the type is from the current package, then it is probably a service import
	// so we need to check the type and if the type correponds to an existing service
	case *ast.Ident:
		// the field indeed corresponds to another service
		// so the package of the variable is the same
		if _, ok := node.Services[t.Name]; ok {
			node.Fields[paramName] = &types.ServiceField{
				Variable: gocode.Variable{
					Name: paramName,
					Type: &gocode.UserType{
						Package: node.Package,
						Name:    t.Name,
					},
				},
				Lineno: field.Pos(),
				Ast:    field,
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
						Variable: gocode.Variable{
							Name: paramName,
							Type: &gocode.UserType{
								Package: impt.Package,
								Name:    t.Sel.Name,
							},
						},
						Lineno:  field.Pos(),
						Ast:     field,
						IsQueue: frameworks.IsBlueprintBackendQueue(t.Sel.Name),
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
							Variable: gocode.Variable{
								Name: paramName,
								Type: &gocode.UserType{
									Package: s.Package,
									Name:    t.Sel.Name,
								},
							},
							Lineno: field.Pos(),
							Ast:    field,
						}
					}
				}
			}
		}
	default:
		logger.Logger.Warnf("unknown field type %s for service %s", field.Type, node.Name)
	}
}

func (node *ServiceNode) parseQueueImplementationIfWorker(parsedFuncDecl *ParsedFuncDecl) {
	/* queues := []*types.DatabaseField{}
	// get all implemented queues
	for _, field := range node.Fields {
		if dbField, ok := field.(*types.DatabaseField); ok && dbField.IsQueue {
			queues = append(queues, dbField)
		}
	} */

	// inspect methods
	ast.Inspect(parsedFuncDecl.Ast, func(n ast.Node) bool {
		ok, _, methodIdent, fieldIdent, _ := fieldCallInMethodBody(n, parsedFuncDecl)
		if !ok {
			return true
		}
		if field, isField := node.Fields[fieldIdent.Name]; isField {
			if dbField, isDbField := field.(*types.DatabaseField); isDbField {
				if dbField.IsQueue && methodIdent.Name == "Pop" {
					logger.Logger.Debugf("Found internal (worker) method: %s", parsedFuncDecl.String())
					// move from internal to worker methods (althought theoretically they are still internal)
					delete(node.InternalMethods, parsedFuncDecl.Name)
					node.WorkerMethods[parsedFuncDecl.Name] = parsedFuncDecl
				}
			}
		}
		return true
	})
}

func (node *ServiceNode) addInternalMethod(funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) *ParsedFuncDecl {
	params := node.parseFuncDeclParams(funcDecl)
	parsedFuncDecl := &ParsedFuncDecl{
		Ast:           funcDecl,
		Name:          funcDecl.Name.Name,
		Recv:          rcvIdent,
		Params:        params,
		DatabaseCalls: make(map[token.Pos]*ParsedCallExpr),
		ServiceCalls:  make(map[token.Pos]*ParsedCallExpr),
		Service:       node.Name,
	}
	node.InternalMethods[parsedFuncDecl.Name] = parsedFuncDecl
	return parsedFuncDecl
}

func (node *ServiceNode) addExposedMethod(funcDecl *ast.FuncDecl, rcvIdent *ast.Ident) *ParsedFuncDecl {
	params := node.parseFuncDeclParams(funcDecl)
	parsedFuncDecl := &ParsedFuncDecl{
		Ast:           funcDecl,
		Name:          funcDecl.Name.Name,
		Recv:          rcvIdent,
		Params:        params,
		DatabaseCalls: make(map[token.Pos]*ParsedCallExpr),
		ServiceCalls:  make(map[token.Pos]*ParsedCallExpr),
		Service:       node.Name,
	}
	node.ExposedMethods[parsedFuncDecl.Name] = parsedFuncDecl
	return parsedFuncDecl
}

func fieldCallInMethodBody(node ast.Node, parsedFuncDecl *ParsedFuncDecl) (bool, *ast.CallExpr, *ast.Ident, *ast.Ident, *ast.Ident) {
	// e.g. f.queue.Push
	//    ^ident2 ^ident ^method
	// e.g. f.storageService.StorePost
	//      ^ident2  ^ident    ^method
	if funcCall, ok := node.(*ast.CallExpr); ok {
		if methodSel, ok := funcCall.Fun.(*ast.SelectorExpr); ok {
			// get first selector (e.g. storageService)
			if fieldSel, ok := methodSel.X.(*ast.SelectorExpr); ok {
				// get second selector (e.g. f)
				if serviceRcvIdent, ok := fieldSel.X.(*ast.Ident); ok {
					// check if ident2 (e.g. f) is the current service receiver being implemented by the method
					if serviceRcvIdent.Name == parsedFuncDecl.Recv.Name {
						return true, funcCall, methodSel.Sel, fieldSel.Sel, serviceRcvIdent
					}
				}
			}
		}
	}
	return false, nil, nil, nil, nil
}

func (node *ServiceNode) parseMethodBodyCalls(parsedFuncDecl *ParsedFuncDecl) {
	logger.Logger.Debugf("visiting method %s\n", parsedFuncDecl.Name)

	ast.Inspect(parsedFuncDecl.Ast, func(n ast.Node) bool {
		ok, funcCall, methodIdent, fieldIdent, serviceRcvIdent := fieldCallInMethodBody(n, parsedFuncDecl)
		if ok {
			// store function call either as service call or database call
			parsedCallExpr := &ParsedCallExpr{
				Ast:         funcCall,
				Receiver:    serviceRcvIdent.Name,
				TargetField: fieldIdent.Name,
				Name:        methodIdent.Name,
				Pos:         funcCall.Pos(),
			}
			// if the targeted variable corresponds to a service field
			if field, ok := node.Fields[parsedCallExpr.TargetField]; ok {
				// if the field corresponds to a service field
				if serviceField, ok := field.(*types.ServiceField); ok {
					// 1. extract the service field from the current service
					// 2. get the target node service for the type
					// 3. add the targeted method of the other service for the current call expression
					targetServiceType := GetShortServiceTypeStr(serviceField.Type)
					targetServiceNode := node.Services[targetServiceType]
					targetMethod := targetServiceNode.ExposedMethods[parsedCallExpr.Name]
					parsedCallExpr.Method = targetMethod
					// set the source (caller service) and destination (callee service) types
					parsedCallExpr.SrcType = &ServiceType{Name: node.Name, Package: node.Package}
					parsedCallExpr.DestType = serviceField.Variable.Type
					// add the call expr to the existing calls of the current service
					parsedFuncDecl.ServiceCalls[parsedCallExpr.Pos] = parsedCallExpr
				}
				// if the field corresponds to a database field
				if databaseField, ok := field.(*types.DatabaseField); ok {
					// 1. extract the service field from the current service
					// 2. get the target database node
					// 3. add the target method for the current call expression
					targetDatabaseType := GetShortServiceTypeStr(databaseField.Type)
					parsedCallExpr.Method = frameworks.GetBackendMethod(fmt.Sprintf("%s.%s", targetDatabaseType, parsedCallExpr.Name))

					// set the source (caller service) and destination (callee database) types
					parsedCallExpr.SrcType = &ServiceType{Name: node.Name, Package: node.Package}
					parsedCallExpr.DestType = databaseField.Variable.Type
					// add the call expr to the existing calls of the current service
					parsedFuncDecl.DatabaseCalls[parsedCallExpr.Pos] = parsedCallExpr
				}
			}
		}
		return true
	})
	logger.Logger.Debugln()
}
