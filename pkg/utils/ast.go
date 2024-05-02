package utils

import (
	"analyzer/pkg/logger"
	"go/ast"
	"reflect"

	/* "github.com/blueprint-uservices/blueprint/plugins/golang/gocode" */
)

/* func ConvertExprTypes(expr ast.Expr) (gocode.TypeName) {
	switch e := expr.(type) {
	case *ast.Ident:
		expr = append(args, e.Name)
		
		// e.g. &post
	case *ast.UnaryExpr:
		logger.Logger.Warnf("HEREEEEEEEEE %v", e.X)

	// e.g. post.ReqID
	//       ^ ident ^ selector
	case *ast.SelectorExpr:
		if ident, ok := e.X.(*ast.Ident); ok {
			ident.
		}
	}
} */

func TransverseExprIdentifiers(expr ast.Expr) (string, []string) {
	var identifiers []string
	var varType string

	switch e := expr.(type) {
	case *ast.Ident:
		identifiers = append(identifiers, e.Name)
	case *ast.BasicLit:
	case *ast.CallExpr:
		//FIXME: get type of func call
		for _, arg := range e.Args {
			_, r := TransverseExprIdentifiers(arg)
			identifiers = append(identifiers, r...)
		}
	case *ast.CompositeLit:
		varType = getExprType(e.Type)
		for _, elt := range e.Elts {
			if kv, ok := elt.(*ast.KeyValueExpr); ok {
				if _, ok := kv.Key.(*ast.Ident); ok {
					_, r := TransverseExprIdentifiers(kv.Value)
					identifiers = append(identifiers, r...)
				}
			}
		}
	case *ast.SelectorExpr:
		if ident, ok := e.X.(*ast.Ident); ok {
			identifiers = append(identifiers, ident.Name)
		}
	case *ast.BinaryExpr:
		_, rX := TransverseExprIdentifiers(e.X)
		identifiers = append(identifiers, rX...)
		_, rY := TransverseExprIdentifiers(e.Y)
		identifiers = append(identifiers, rY...)
	default:
		nodeType := reflect.TypeOf(e).Elem().Name()
		logger.Logger.Warnf("unknown type in TransverseExprIdentifiers: %s", nodeType)
	}
	return varType, identifiers
}

func getExprType(expr ast.Expr) string {
	switch e := expr.(type) {
	case *ast.Ident:
		return e.Name
	case *ast.UnaryExpr:
		return e.Op.String()
	default:
		nodeType := reflect.TypeOf(e).Elem().Name()
		logger.Logger.Warnf("unknown type in getExprType: %s", nodeType)
	}
	// FIXME: cover more use cases e.g.
	// 1. type from other package using selector
	// 2. type from current package
	return "unknown"
}
