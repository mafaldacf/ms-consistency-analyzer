package visitor

import (
	"detection_tool/parser"
	"fmt"
	"go/ast"
)

func VisitServiceMethod(parsedFuncDecl *parser.ParsedFuncDecl, node *parser.ServiceNode) {
	fmt.Printf("[INFO] Visiting method %s\n", parsedFuncDecl.Ast.Name.Name)

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
						parsedCallExpr := &parser.ParsedCallExpr{
							Ast:        funcCall,
							Selected:   ident.Sel.Name,
							MethodName: method.Sel.Name,
							Pos: 		funcCall.Pos(),
						}

						// check if ident2 is the current service receiver being implemented by the method
						if ident2.Name == parsedFuncDecl.Recv.Name {
							if _, exists := node.Services[ident.Sel.Name]; exists {
								parsedFuncDecl.ServiceCalls[parsedCallExpr.Pos] = parsedCallExpr
								fmt.Printf("> found service call:\t")

							}
							if _, exists := node.Databases[ident.Sel.Name]; exists {
								parsedFuncDecl.DatabaseCalls[parsedCallExpr.Pos] = parsedCallExpr
								fmt.Printf("> found database call:\t")

							}

							fmt.Printf("%s.%s.%s(", ident2.Name, parsedCallExpr.Selected, parsedCallExpr.MethodName)
							for _, arg := range funcCall.Args {
								if ident, ok := arg.(*ast.Ident); ok {
									fmt.Printf("%s, ", ident.Name)
								}
							}
							fmt.Printf(")\n")
						}

					}
				}
			}
		}
		return true
	})
	fmt.Println()
}
