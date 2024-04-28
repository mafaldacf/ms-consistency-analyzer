package service

import (
	"analyzer/pkg/logger"
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
func (node *ServiceNode) ParseMethods() {
	logger.Logger.Debugf("inspecting exposed methods for service implementation %s\n", node.Impl)

	ast.Inspect(node.File, func(n ast.Node) bool {
		// check if node is a function declaration
		if funcDecl, ok := n.(*ast.FuncDecl); ok {
			// check if the function has any receivers (i.e. structure(s) implemented by the function)
			if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
				// get the function's receiver (i.e. i.e. structure(s) implemented by the function)
				if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
					// check if the data type (e.g. StorageService) of the receiver (i.e. structure(s) implemented by the function)
					// matches the one we are looking for (i.e. StorageService)
					if ident, ok := recv.X.(*ast.Ident); ok && ident.Name == node.Impl {
						// check if the function declaration being implDebugfemented by the Service structure
						// is actually an exposed method to other services
						if _, ok := node.ExposedMethods[funcDecl.Name.Name]; ok {
							// get the variable name of the receiver
							receiverName := funcDecl.Recv.List[0].Names[0]
							// e.g. (f *FrontendImpl) UploadPost
							logger.Logger.Debugf("> (%s *%s) %s [:%d]\n", receiverName, ident.Name, funcDecl.Name.Name, funcDecl.Pos())

							// get name of the params for function declaration
							var params []string
							for _, field := range funcDecl.Type.Params.List {
								// TODO: any types with selector! e.g. model.Message
								if _, ok := field.Type.(*ast.Ident); ok {
									for _, ident := range field.Names {
										params = append(params, ident.Name)
									}
								}
								/* if _, ok := field.Type.(*ast.SelectorExpr); ok {
									// TODO: any types with selector! e.g. model.Message
									// except any 'ctx' parameter
									// FIXME: this cannot be hard coded
									// we need to check if Context actually corresponds
									// to context.Context from the Go library
								} */
							}

							// store parsed func decl in the methods of the service node
							parsedFuncDecl := ParsedFuncDecl{
								Ast:           funcDecl,
								Name:          funcDecl.Name.Name,
								Recv:          receiverName,
								Params:        params,
								DatabaseCalls: make(map[token.Pos]*ParsedCallExpr),
								ServiceCalls:  make(map[token.Pos]*ParsedCallExpr),
							}
							node.ExposedMethods[parsedFuncDecl.Name] = &parsedFuncDecl
						}
					}
				}
			}
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
					logger.Logger.Debugf("> %s: %s\n", ident.Name, field.Type)
					node.saveFieldWithType(field, ident.Name)
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
			node.Fields[paramName] = &ServiceField{
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
				if impt.IsBlueprintBackend {
					switch t.Sel.Name {
					//TODO: include other types from BLUEPRINT
					case "Queue", "NoSQLDatabase", "Cache":
						node.Fields[paramName] = &DatabaseField{
							Variable: gocode.Variable{
								Name: paramName,
								Type: &gocode.UserType{
									Package: node.Package,
									Name:    t.Sel.Name,
								},
							},
							Lineno: field.Pos(),
							Ast:    field,
						}
					default:
						logger.Logger.Warnf("unknown database type field %s for service %s", t.Sel.Name, node.Name)
					}
				}
				// check if the import matches the path of any of existing services
				for _, s := range node.Services {
					if s.Package == impt.Package {
						node.Fields[paramName] = &ServiceField{
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

func (node *ServiceNode) ParseMethodBodyCalls(parsedFuncDecl *ParsedFuncDecl) {
	logger.Logger.Debugf("visiting method %s\n", parsedFuncDecl.Ast.Name.Name)

	// e.g. f.queue.Push
	//    ^ident2 ^ident ^method
	// e.g. f.storageService.StorePost
	//      ^ident2  ^ident    ^method
	ast.Inspect(parsedFuncDecl.Ast, func(n ast.Node) bool {
		if funcCall, ok := n.(*ast.CallExpr); ok {
			if method, ok := funcCall.Fun.(*ast.SelectorExpr); ok {
				// get first selector (e.g. storageService)
				if ident, ok := method.X.(*ast.SelectorExpr); ok {
					// get second selector (e.g. f)
					if ident2, ok := ident.X.(*ast.Ident); ok {
						// store function call either as service call or database call
						parsedCallExpr := &ParsedCallExpr{
							Ast:         funcCall,
							Receiver:    ident2.Name,
							TargetField: ident.Sel.Name,
							MethodName:  method.Sel.Name,
							Pos:         funcCall.Pos(),
						}

						// check if ident2 (e.g. f) is the current service receiver being implemented by the method
						if ident2.Name == parsedFuncDecl.Recv.Name {
							// if the targeted variable corresponds to a service field
							if field, ok := node.Fields[parsedCallExpr.TargetField]; ok {
								// if the field corresponds to a service field
								if serviceField, ok := field.(*ServiceField); ok {
									serviceNode := node.Services[serviceField.Variable.Type.(*gocode.UserType).Name]
									parsedFuncDecl.ServiceCalls[parsedCallExpr.Pos] = parsedCallExpr
									parsedCallExpr.SrcType = node.Name
									parsedCallExpr.DestType = serviceNode.Name
									parsedCallExpr.Kind = KIND_SERVICE_CALL
								}
								// if the field corresponds to a database field
								if databaseField, ok := field.(*DatabaseField); ok {
									databaseType := databaseField.Variable.Type.(*gocode.UserType).Name
									parsedFuncDecl.DatabaseCalls[parsedCallExpr.Pos] = parsedCallExpr
									parsedCallExpr.SrcType = node.Name
									parsedCallExpr.DestType = databaseType
									parsedCallExpr.Kind = KIND_DATABASE_CALL
								}
							}
						}

					}
				}
			}
		}
		return true
	})
	logger.Logger.Debugln()
}

// NOT USED!!
/* func getFieldType(field *ast.Field) string {
	switch t := field.Type.(type) {
	case *ast.Ident:
		return t.Name
	case *ast.ArrayType:
		if ident, ok := t.Elt.(*ast.Ident); ok {
			return "[]" + ident.Name
		}
	case *ast.StarExpr:
		if ident, ok := t.X.(*ast.Ident); ok {
			return "*" + ident.Name
		}
	case *ast.SelectorExpr:
		return fmt.Sprintf("%s.%s", t.X.(*ast.Ident).Name, t.Sel.Name)
	}
	return "unknown"
}
*/
