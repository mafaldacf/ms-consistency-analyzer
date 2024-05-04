package service

import (
	"analyzer/pkg/analyzer"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/logger"
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

func (node *ServiceNode) methodImplementsServiceStructure(n ast.Node) (ok bool, funcDecl *ast.FuncDecl, ident *ast.Ident, rcvIdent *ast.Ident) {
	// check if node is a function declaration
	if funcDecl, ok = n.(*ast.FuncDecl); ok {
		// check if the function has any receivers (i.e. structure(s) implemented by the function)
		if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
			// get the function's receiver (i.e. i.e. structure(s) implemented by the function)
			if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
				// check if the data type (e.g. StorageService) of the receiver (i.e. structure(s) implemented by the function)
				// matches the one we are looking for (i.e. StorageService)
				if ident, ok = recv.X.(*ast.Ident); ok && ident.Name == node.Impl {
					// check if the function declaration being implemented by the Service structure
					// is actually an exposed method to other services
					if _, ok := node.ExposedMethods[funcDecl.Name.Name]; ok {
						rcvIdent = funcDecl.Recv.List[0].Names[0]
						return true, funcDecl, ident, rcvIdent
					}
				}
			}
		}
	}
	return false, nil, nil, nil
}

func (node *ServiceNode) parseFuncDeclParams(funcDecl *ast.FuncDecl) []*analyzer.FunctionField {
	var params []*analyzer.FunctionField
	for _, field := range funcDecl.Type.Params.List {
		// TODO: any types with selector! e.g. model.Message (careful with context.Context)
		switch t := field.Type.(type) {
			case *ast.Ident:
				for _, fieldIdent := range field.Names {
					newParam := &analyzer.FunctionField{
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
							Name: t.Name,
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
						newParam := &analyzer.FunctionField{
							Variable: gocode.Variable{
								Name: fieldIdent.Name,
								Type:  &gocode.UserType{
									Name: t.Sel.Name,
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
	logger.Logger.Warnf("HEREEEEEEEEEE appending for %s: %v\n", funcDecl.Name, params)
	return params
}

func (node *ServiceNode) ParseMethods() {
	logger.Logger.Debugf("inspecting exposed methods for service implementation %s\n", node.Impl)

	ast.Inspect(node.File, func(n ast.Node) bool {
		ok, funcDecl, ident, rcvIdent := node.methodImplementsServiceStructure(n)
		if ok {
			logger.Logger.Debugf("> (%s *%s) %s [:%d]\n", rcvIdent, ident.Name, funcDecl.Name.Name, funcDecl.Pos())
			params := node.parseFuncDeclParams(funcDecl)
			parsedFuncDecl := ParsedFuncDecl{
				Ast:           funcDecl,
				Name:          funcDecl.Name.Name,
				Recv:          rcvIdent,
				Params:        params,
				DatabaseCalls: make(map[token.Pos]*ParsedCallExpr),
				ServiceCalls:  make(map[token.Pos]*ParsedCallExpr),
				Service: 	   node.Name,
			}
			node.ExposedMethods[parsedFuncDecl.Name] = &parsedFuncDecl
		}
		return true
	})
	logger.Logger.Debugln()
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

func (node *ServiceNode) ParseStructFields() {
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
			node.Fields[paramName] = &analyzer.ServiceField{
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
					newField := &analyzer.DatabaseField{
						Variable: gocode.Variable{
							Name: paramName,
							Type: &gocode.UserType{
								Package: impt.Package,
								Name:    t.Sel.Name,
							},
						},
						Lineno: 	field.Pos(),
						Ast:    	field,
						IsQueue: 	frameworks.IsBlueprintBackendQueue(t.Sel.Name),
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
						node.Fields[paramName] = &analyzer.ServiceField{
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

func (node *ServiceNode) ParseQueueImplementation() {
	queues := []*analyzer.DatabaseField{}
	// get all implemented queues
	for _, field := range node.Fields {
		if dbField, ok := field.(*analyzer.DatabaseField); ok && dbField.IsQueue {
			queues = append(queues, dbField)
		}
	}

	// search for the method that implements the queues
}

func hasFieldCallInMethodBody(node ast.Node, parsedFuncDecl *ParsedFuncDecl) (bool, *ast.CallExpr, *ast.SelectorExpr, *ast.SelectorExpr, *ast.Ident)  {
	// e.g. f.queue.Push
	//    ^ident2 ^ident ^method
	// e.g. f.storageService.StorePost
	//      ^ident2  ^ident    ^method
	if funcCall, ok := node.(*ast.CallExpr); ok {
		if method, ok := funcCall.Fun.(*ast.SelectorExpr); ok {
			// get first selector (e.g. storageService)
			if ident, ok := method.X.(*ast.SelectorExpr); ok {
				// get second selector (e.g. f)
				if ident2, ok := ident.X.(*ast.Ident); ok {
					// check if ident2 (e.g. f) is the current service receiver being implemented by the method
					if ident2.Name == parsedFuncDecl.Recv.Name {
						return true, funcCall, method, ident, ident2
					}
				}
			}
		}
	}
	return false, nil, nil, nil, nil
}

func (node *ServiceNode) ParseMethodBodyCalls(parsedFuncDecl *ParsedFuncDecl) {
	logger.Logger.Debugf("visiting method %s\n", parsedFuncDecl.Name)

	ast.Inspect(parsedFuncDecl.Ast, func(n ast.Node) bool {
		ok, funcCall, method, ident, ident2 := hasFieldCallInMethodBody(n, parsedFuncDecl)
		if ok {
			// store function call either as service call or database call
			parsedCallExpr := &ParsedCallExpr{
				Ast:         funcCall,
				Receiver:    ident2.Name,
				TargetField: ident.Sel.Name,
				Name:        method.Sel.Name,
				Pos:         funcCall.Pos(),
			}
			// if the targeted variable corresponds to a service field
			if field, ok := node.Fields[parsedCallExpr.TargetField]; ok {
				// if the field corresponds to a service field
				if serviceField, ok := field.(*analyzer.ServiceField); ok {
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
				if databaseField, ok := field.(*analyzer.DatabaseField); ok {
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
