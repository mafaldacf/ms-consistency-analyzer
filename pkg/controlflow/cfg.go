package controlflow

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"go/ast"

	"golang.org/x/tools/go/cfg"
)

func GenerateMethodCFGs(node *service.ServiceNode, parsedFuncDecl *service.ParsedFuncDecl) {
	cfg := cfg.New(parsedFuncDecl.Ast.Body, mayReturn)
	parsedCfg := types.InitParsedCFG(cfg, parsedFuncDecl.Name)
	parsedFuncDecl.SetParsedCFG(parsedCfg)
	entryBlock := parsedCfg.GetEntryParsedBlock()
	for i, param := range parsedFuncDecl.Params {
		entryBlock.Vars = append(entryBlock.Vars, &types.Variable{
			Id:            types.VARIABLE_UNASSIGNED_ID,
			Lineno:        entryBlock.GetPosition(),
			Name:          param.Name,
			Type:          param.Type,
			IsBlockParam:  true,
			BlockParamIdx: i,
		})
	}
	logger.Logger.Infof("parsed %s", parsedCfg.String())
	//logger.Logger.Info(parsedCfg.FullString())
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
