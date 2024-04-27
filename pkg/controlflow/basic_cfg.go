package controlflow

import (
	log "analyzer/pkg/logger"
	"analyzer/pkg/service"
	"go/ast"
	"go/parser"
	"go/token"

	"golang.org/x/tools/go/cfg"
)

func GenerateMethodCFG(method *service.ParsedFuncDecl, filepath string) (*cfg.CFG, error) {
	fset := token.NewFileSet()
	file, err := parser.ParseFile(fset, filepath, nil, 0)
	if err != nil {
		log.Logger.Error(err)
		return nil, err
	}

	for _, decl := range file.Decls {
		if funcDecl, ok := decl.(*ast.FuncDecl); ok {
			if funcDecl.Name.Name == method.Name && funcDecl.Body != nil {
				return cfg.New(funcDecl.Body, mayReturn), nil
			}
		}
	}
	return nil, nil
}

// https://github.com/coder/go-tools/blob/master/go/analysis/passes/ctrlflow/ctrlflow_test.go
func mayReturn(call *ast.CallExpr) bool {
	switch fun := call.Fun.(type) {
	case *ast.Ident:
		return fun.Name != "panic"
	case *ast.SelectorExpr:
		return fun.Sel.Name != "Fatal"
	}
	return true
}
