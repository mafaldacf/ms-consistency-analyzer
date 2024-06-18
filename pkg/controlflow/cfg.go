package controlflow

import (
	"go/ast"

	"golang.org/x/tools/go/cfg"

	"analyzer/pkg/logger"
	"analyzer/pkg/types"
)

func GenerateMethodCFG(parsedMethod *types.ParsedMethod) {
	cfg := cfg.New(parsedMethod.GetBody(), mayReturn)
	parsedCfg := types.InitParsedCFG(cfg, parsedMethod.Name)
	parsedMethod.SetParsedCFG(parsedCfg)
	entryBlock := parsedCfg.GetEntryParsedBlock()
	for i, param := range parsedMethod.Params {
		v := lookupVariableFromType(param.GetName(), param.GetType())
		v.GetVariableInfo().IsBlockParam = true
		v.GetVariableInfo().BlockParamIdx = i
		entryBlock.Vars = append(entryBlock.Vars, v)
	}
	logger.Logger.Infof("[CFG] parsed CFG %s with block variables %v", parsedCfg.FullMethod, entryBlock.Vars)
	logger.Logger.Debugf("[CFG] parsed CFG: %s", parsedCfg.FullString())
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
