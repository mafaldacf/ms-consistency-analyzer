package visitor

import (
	"fmt"
	"go/ast"
	"static_analyzer/logger"
	"static_analyzer/models"
)

func VisitServiceMethod(parsedFuncDecl *models.ParsedFuncDecl, node *models.ServiceNode) {
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
						parsedCallExpr := &models.ParsedCallExpr{
							Ast:        funcCall,
							Selected:   ident.Sel.Name,
							MethodName: method.Sel.Name,
							Pos:        funcCall.Pos(),
						}

						// check if ident2 is the current service receiver being implemented by the method
						if ident2.Name == parsedFuncDecl.Recv.Name {
							funcCallStr := fmt.Sprintf("%s.%s.%s(", ident2.Name, parsedCallExpr.Selected, parsedCallExpr.MethodName)
							for _, arg := range funcCall.Args {
								if ident, ok := arg.(*ast.Ident); ok {
									funcCallStr += fmt.Sprintf("%s, ", ident.Name)
								}
							}
							funcCallStr += ")"

							if n, exists := node.Services[parsedCallExpr.Selected]; exists {
								parsedFuncDecl.ServiceCalls[parsedCallExpr.Pos] = parsedCallExpr
								parsedCallExpr.Type = n.Name
								parsedCallExpr.Kind = models.KIND_SERVICE_CALL
								logger.Logger.Infof("> found service call [%d]: %s \t", funcCall.Pos(), funcCallStr)

								// TODO: store the func decl in the call expr
								// maybe not necessary ????
								/* childServiceName := parsedCallExpr.Selected
								service, found := node.Services[childServiceName]
								if found {
									service.Methods
								} else {
									logger.Logger.Warnf("child service (%s) not found in service dependencies for current node (%s)", childServiceName, node.Name)
								} */

							}
							if n, exists := node.Databases[parsedCallExpr.Selected]; exists {
								parsedFuncDecl.DatabaseCalls[parsedCallExpr.Pos] = parsedCallExpr
								parsedCallExpr.Type = n.Type
								parsedCallExpr.Kind = models.KIND_DATABASE_CALL
								logger.Logger.Infof("> found database call [%d]: %s \t", funcCall.Pos(), funcCallStr)

							}
						}

					}
				}
			}
		}
		return true
	})
	fmt.Println()
}
