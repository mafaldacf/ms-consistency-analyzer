package parser

import (
	"fmt"
	"go/ast"
	"go/token"
	"strings"
	"detection_tool/logger"
)

func InspectServiceImports(node *ServiceNode) {
	logger.Logger.Infof("inspecting imports for service %s\n", node.Name)

	for _, imp := range node.File.Imports {
		path := imp.Path.Value
		// remove quotes
		path = path[1 : len(path)-1]

		if path == "github.com/blueprint-uservices/blueprint/runtime/core/backend" {
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
			node.Imports[alias] = &ParsedImportSpec{imp, alias, path, BLUEPRINT_RUNTIME_CORE_BACKEND}
			logger.Logger.Debugf("> %s for %s\n", alias, path)
		}
	}
	fmt.Println()
}

// InspectServiceMethods:
// 1. inspects the service node
// 2. finds the function declarations that implement the 
// 	  service struct along with the name of the function, the receiver, and the parameters
// 3. stores the function delc as parsed func decls in the methods of the service node
func InspectServiceMethods(node *ServiceNode) {
	logger.Logger.Infof("inspecting exposed methods for service implementation %s\n", node.Impl)

	ast.Inspect(node.File, func(n ast.Node) bool {
		// check if node is a function declaration
		if funcDecl, ok := n.(*ast.FuncDecl); ok {
			// check if the function has any receivers (i.e. structure(s) implemented by the function)
			if funcDecl.Recv != nil && len(funcDecl.Recv.List) > 0 {
				// get the function's receiver (i.e. structure implemented by the function)
				if recv, ok := funcDecl.Recv.List[0].Type.(*ast.StarExpr); ok {
					// get the identifier (i.e. data type) of the receiver (i.e., implemented structure name) matches the one we are looking for
					if ident, ok := recv.X.(*ast.Ident); ok && ident.Name == node.Impl {
						// get the name (i.e. variable name) of the receiver
						if len(funcDecl.Recv.List[0].Names) > 0 {
							receiverName := funcDecl.Recv.List[0].Names[0]
							// e.g. (f *FrontendImpl) UploadPost
							logger.Logger.Debugf("> (%s *%s) %s\n", receiverName, ident.Name, funcDecl.Name.Name)
							
							// get name of the params for function declaration
							var params []string
							for _, field := range funcDecl.Type.Params.List {
								// TODO: any types with selector! e.g. model.Message
								if _, ok := field.Type.(*ast.Ident); ok {
									for _, ident := range field.Names {
										params = append(params, ident.Name)
									}
								}
								if _, ok := field.Type.(*ast.SelectorExpr); ok {
									continue
									// TODO: any types with selector! e.g. model.Message
									// except any 'ctx' parameter
									// FIXME: this cannot be hard coded
									// we need to check if Context actually corresponds
									// to context.Context from the Go library
								}
							}

							// store parsed func decl in the methods of the service node
							ParsedFuncDecl := ParsedFuncDecl{
								Ast:  	funcDecl,
								Name: 	funcDecl.Name.Name,
								Recv: 	receiverName,
								Params: params,
								DatabaseCalls: make(map[token.Pos]*ParsedCallExpr),
								ServiceCalls: make(map[token.Pos]*ParsedCallExpr),
							}
							node.Methods = append(node.Methods, &ParsedFuncDecl)
						}
					}
				}
			}
		}
		return true
	})
	fmt.Println()
}

func InspectServiceInterfaceMethods(file *ast.File) {
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

func InspectServiceStructFields(node *ServiceNode) {
	logger.Logger.Infof("inspecting fields for service %s\n", node.Name)

	ast.Inspect(node.File, func(n ast.Node) bool {
		if str, ok := n.(*ast.StructType); ok {
			for _, field := range str.Fields.List {
				for _, ident := range field.Names {
					logger.Logger.Debugf("> %s: %s\n", ident.Name, getFieldType(field))
					saveFieldIfServiceOrDb(node, field, ident.Name)
				}
			}
		}
		return true
	})
	fmt.Println()
}

func saveFieldIfServiceOrDb(node *ServiceNode, field *ast.Field, paramName string) {
	switch t := field.Type.(type) {
	case *ast.Ident:
		//FIXME: this is hard coded, can be in differente package and therefore be an ast.SelectorExpr
		if t.Name == "StorageService" || t.Name == "NotifyService" || t.Name == "Frontend" || t.Name == "Notify" {
			// TODO: get the service node from the graph and add here
			node.Services[paramName] = &ServiceNode{Name: t.Name}
		}

	case *ast.SelectorExpr:
		// e.g. backend.Queue
		//      ^ ident ^ selector
		if ident, ok := t.X.(*ast.Ident); ok {
			// check if package (e.g. backend) is in the imports
			imp, found := node.Imports[ident.Name]
			// check if the matched package is a package imported from blueprint
			//FIXME: this should be more automated and we are still missing some types
			if found && imp.Type == BLUEPRINT_RUNTIME_CORE_BACKEND {
				if t.Sel.Name == "Queue" {
					parsedField := &DatabaseField{Kind: BLUEPRINT_DB_QUEUE}
					node.Databases[paramName] = parsedField
				} else if t.Sel.Name == "NoSQLDatabase" {
					parsedField := &DatabaseField{Kind: BLUEPRINT_DB_NO_SQL_DATABASE}
					node.Databases[paramName] = parsedField
				} else if t.Sel.Name == "Cache" {
					parsedField := &DatabaseField{Kind: BLUEPRINT_DB_CACHE}
					node.Databases[paramName] = parsedField
				}
			}
		}
	}
}

func getFieldType(field *ast.Field) string {
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
