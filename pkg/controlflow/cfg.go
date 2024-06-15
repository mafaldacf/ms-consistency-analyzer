package controlflow

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"go/ast"

	"golang.org/x/tools/go/cfg"
)

func GenerateMethodCFG(parsedFuncDecl *service.ParsedFuncDecl) {
	cfg := cfg.New(parsedFuncDecl.GetBody(), mayReturn)
	parsedCfg := types.InitParsedCFG(cfg, parsedFuncDecl.Name)
	parsedFuncDecl.SetParsedCFG(parsedCfg)
	entryBlock := parsedCfg.GetEntryParsedBlock()
	for i, param := range parsedFuncDecl.Params {
		if u, ok := param.GetType().(*types.UserType); ok {
			if s, ok := u.UserType.(*types.StructType); ok {
				logger.Logger.Debugf("param %s: %v", param.String(), s.FieldTypes)
			}
		}
		v := getOrCreateVariableFromType(param.GetName(), param.GetType())
		if u, ok := v.GetVariableInfo().GetType().(*types.UserType); ok {
			if s, ok := u.UserType.(*types.StructType); ok {
				logger.Logger.Debugf("param %s: %v", param.String(), s.FieldTypes)
			}
		}
		v.GetVariableInfo().IsBlockParam = true
		v.GetVariableInfo().BlockParamIdx = i
		entryBlock.Vars = append(entryBlock.Vars, v)
	}
	logger.Logger.Infof("[CFG] parsed CFG %s with block variables %v", parsedCfg.FullMethod, entryBlock.Vars)
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
