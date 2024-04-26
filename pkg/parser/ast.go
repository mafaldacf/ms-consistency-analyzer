package parser

import (
	"analyzer/pkg/models"
	"go/ast"
	"go/token"
	"analyzer/pkg/logger"
	"strings"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
	"github.com/blueprint-uservices/blueprint/plugins/golang/goparser"
)

func ParseImports(node *models.ServiceNode) {
	log.Logger.Debugf("inspecting imports for service %s\n", node.Name)

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

		importSpec := &models.ParsedImportSpec{
			Ast:   		imp,
			Alias: 		alias,
			Path:  		path,
			// FIXME: package can sometimes be different than path when it is replaced by the go.mod
			// but this is VERY rare, especially between services
			// still, we need to later cover this edge case
			Package:  	path,
		}
		// FIXME: this can be different if replaced in the Go.mod file
		if path == "github.com/blueprint-uservices/blueprint/runtime/core/backend" {
			importSpec.IsBlueprintBackend = true
		}
		node.Imports[alias] = importSpec
		log.Logger.Debugf("> %s for %s\n", alias, path)
	}
	log.Logger.Debugln()
}

// ParseMethods:
//  1. inspects the service node
//  2. finds the function declarations that implement the
//     service struct along with the name of the function, the receiver, and the parameters
//  3. stores the function delc as parsed func decls in the methods of the service node
func ParseMethods(node *models.ServiceNode) {
	log.Logger.Debugf("inspecting exposed methods for service implementation %s\n", node.Impl)

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
							log.Logger.Debugf("> (%s *%s) %s [:%d]\n", receiverName, ident.Name, funcDecl.Name.Name, funcDecl.Pos())

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
							parsedFuncDecl := models.ParsedFuncDecl{
								Ast:           funcDecl,
								Name:          funcDecl.Name.Name,
								Recv:          receiverName,
								Params:        params,
								DatabaseCalls: make(map[token.Pos]*models.ParsedCallExpr),
								ServiceCalls:  make(map[token.Pos]*models.ParsedCallExpr),
							}
							node.Methods[parsedFuncDecl.Name] = &parsedFuncDecl
						}
					}
				}
			}
		}
		return true
	})
	log.Logger.Debugln()
}

func ParseInterfaceMethods(file *ast.File) {
	log.Logger.Debug("inspecting service interface and methods \n")

	serviceMethods := []string{}
	ast.Inspect(file, func(n ast.Node) bool {
		if iface, ok := n.(*ast.InterfaceType); ok {
			for _, field := range iface.Methods.List {
				if methodName, ok := field.Names[0].Name, ok; ok {
					serviceMethods = append(serviceMethods, methodName)
					log.Logger.Debugf("> %s\n", methodName)
				}
			}
		}
		return true
	})
}

func ParseStructFields(node *models.ServiceNode) {
	log.Logger.Debugf("inspecting fields for service %s\n", node.Name)

	ast.Inspect(node.File, func(n ast.Node) bool {
		if str, ok := n.(*ast.StructType); ok {
			for _, field := range str.Fields.List {
				for _, ident := range field.Names {
					log.Logger.Debugf("> %s: %s\n", ident.Name, field.Type)
					saveFieldWithType(node, field, ident.Name)
				}
			}
		}
		return true
	})
	log.Logger.Debugln()
}

// saveFieldWithType saves the service or database fields defined in the structure
func saveFieldWithType(node *models.ServiceNode, field *ast.Field, paramName string) {
	switch t := field.Type.(type) {

	// if the type is from the current package, then it is probably a service import
	// so we need to check the type and if the type correponds to an existing service
	case *ast.Ident:
		// the field indeed corresponds to another service
		// so the package of the variable is the same
		if _, ok := node.Services[t.Name]; ok {
			node.Fields[paramName] = &goparser.ParsedField{
				Variable: gocode.Variable{
					// param is the name of the field e.g. storageService in 'storageService StorageService'
					Name: paramName,
					Type: &gocode.UserType{
						Package: node.Package,
						// t.Name is the type of the field e.g. StorageService in 'storageService StorageService'
						Name: t.Name,
					},
				},
				Struct:    nil,
				Position:  int(field.Pos()),
				Ast:       field,
				IsService: true,
			}
		}

		/* if t.Name == "StorageService" || t.Name == "NotifyService" || t.Name == "Frontend" || t.Name == "Notify" {
			// TODO: get the service node from the graph and add here
			node.Services[paramName] = &models.ServiceNode{Name: t.Name}
		} */

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
							parsedField := &models.DatabaseField{Type: t.Sel.Name}
							node.Databases[paramName] = parsedField
						default:
							log.Logger.Warnf("unknown database type field %s for service %s", t.Sel.Name, node.Name)
						}
					}
				// check if the import matches the path of any of existing services
				for _, s := range node.Services {
					if s.Package == impt.Package {
						node.Fields[paramName] = &goparser.ParsedField{
							Variable: gocode.Variable{
								// param is the name of the field e.g. storageService in 'storageService StorageService'
								Name: paramName,
								Type: &gocode.UserType{
									Package: s.Package,
									// t.Sel.Name is the type of the field e.g. StorageService in 'storageService StorageService'
									Name: t.Sel.Name,
								},
							},
							Struct:    nil,
							Position:  int(field.Pos()),
							Ast:       field,
							IsService: true,
						}
					}
				}
			}
		}
	default:
		log.Logger.Warnf("unknown field type %s for service %s", field.Type, node.Name)
	}
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
