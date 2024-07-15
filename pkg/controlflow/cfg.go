package controlflow

import (
	"go/ast"

	"golang.org/x/tools/go/cfg"

	"analyzer/pkg/logger"
	"analyzer/pkg/lookup"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

func GenerateMethodCFG(service *service.Service, parsedMethod *types.ParsedMethod) {
	cfg := cfg.New(parsedMethod.GetBody(), mayReturn)
	parsedCfg := types.InitParsedCFG(cfg, parsedMethod.Name)
	parsedMethod.SetParsedCFG(parsedCfg)
	entryBlock := parsedCfg.GetEntryParsedBlock()

	receiver := lookup.CreateVariableFromType(parsedMethod.Receiver.GetName(), parsedMethod.Receiver.GetType())
	entryBlock.AddVariable(receiver)
	
	variable := receiver
	if pointerVar, ok := variable.(*variables.PointerVariable); ok {
		variable = pointerVar.PointerTo
	}
	if structVar, ok := variable.(*variables.StructVariable); ok {
		for name, f := range service.Fields {
			structVar.Fields[name] = lookup.CreateVariableFromType(name, f.GetType())
		}
	}
	logger.Logger.Tracef("[CFG] added receiver %s (%s) (%s)", receiver.String(), utils.GetType(receiver.(*variables.PointerVariable).PointerTo), utils.GetType(receiver.(*variables.PointerVariable).PointerTo.GetType()))

	for i, param := range parsedMethod.Params {
		v := lookup.CreateVariableFromType(param.GetName(), param.GetType())
		v.GetVariableInfo().IsBlockParam = true
		v.GetVariableInfo().BlockParamIdx = i
		entryBlock.Vars = append(entryBlock.Vars, v)
	}
	logger.Logger.Tracef("[CFG] parsed CFG %s with block variables %v", parsedCfg.FullMethod, entryBlock.Vars)
	//logger.Logger.Debugf("[CFG] parsed CFG: %s", parsedCfg.LongString())
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
