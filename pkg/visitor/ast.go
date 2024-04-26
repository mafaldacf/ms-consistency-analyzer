package visitor

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/models"
	"fmt"
	"go/ast"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

func VisitServiceMethod(parsedFuncDecl *models.ParsedFuncDecl, node *models.ServiceNode) {
	log.Logger.Debugf("visiting method %s\n", parsedFuncDecl.Ast.Name.Name)

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
						parsedCallExpr := &models.ParsedCallExpr{
							Ast:        funcCall,
							Selected:   ident.Sel.Name,
							MethodName: method.Sel.Name,
							Pos:        funcCall.Pos(),
						}

						// check if ident2 (e.g. f) is the current service receiver being implemented by the method
						if ident2.Name == parsedFuncDecl.Recv.Name {
							funcCallStr := fmt.Sprintf("%s.%s.%s(", ident2.Name, parsedCallExpr.Selected, parsedCallExpr.MethodName)
							for _, arg := range funcCall.Args {
								if ident, ok := arg.(*ast.Ident); ok {
									funcCallStr += fmt.Sprintf("%s, ", ident.Name)
								}
							}
							funcCallStr += ")"
							
							// if the function call target corresponds to a service
							if field, ok := node.Fields[parsedCallExpr.Selected]; ok {
								// retrieve the targeted service node
								if targetServiceNode, ok := node.Services[field.Variable.Type.(*gocode.UserType).Name]; ok {
									log.Logger.Debugf("> found service call %s", funcCallStr)
									parsedFuncDecl.ServiceCalls[parsedCallExpr.Pos] = parsedCallExpr
									parsedCallExpr.TargetType = targetServiceNode.Name
									parsedCallExpr.Kind = models.KIND_SERVICE_CALL
								}
							}
							// if the function call target in a database
							//FIXME: use the same logic for service fields and use interface with different 
							// structure types similar to blueprint in *gocode.UserType for TypeName
							if n, exists := node.Databases[parsedCallExpr.Selected]; exists {
								log.Logger.Debugf("> found database call %s", funcCallStr)
								parsedFuncDecl.DatabaseCalls[parsedCallExpr.Pos] = parsedCallExpr
								parsedCallExpr.TargetType = n.Type
								parsedCallExpr.Kind = models.KIND_DATABASE_CALL

							}
						}

					}
				}
			}
		}
		return true
	})
	log.Logger.Debugln()
}
