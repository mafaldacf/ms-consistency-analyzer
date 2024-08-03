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

func GenerateMethodCFG(parsedMethod *types.ParsedMethod) {
	cfg := cfg.New(parsedMethod.GetBody(), mayReturn)
	parsedCfg := types.InitParsedCFG(cfg, parsedMethod.Name)
	parsedMethod.SetParsedCFG(parsedCfg)
	entryBlock := parsedCfg.GetEntryParsedBlock()

	receiver := parsedMethod.GetReceiverIfExists()
	if receiver != nil {
		receiver := lookup.CreateVariableFromType(parsedMethod.Receiver.GetName(), parsedMethod.Receiver.GetType())
		entryBlock.AddVariable(receiver)
		parsedCfg.HasReceiver = true
		parsedCfg.ReceiverType = receiver.GetType()
		logger.Logger.Tracef("[CFG] added receiver (%s) %s", variables.VariableTypeName(receiver), receiver.String())
	}

	for i, param := range parsedMethod.Params {
		v := lookup.CreateVariableFromType(param.GetName(), param.GetType())
		v.GetVariableInfo().IsBlockParam = true
		v.GetVariableInfo().BlockParamIdx = i
		entryBlock.Vars = append(entryBlock.Vars, v)
	}

	// note that parameters also include receiver
	logger.Logger.Infof("[CFG] parsed CFG with receiver (%v) and (%d) initial variables for method (%s)", receiver, len(entryBlock.Vars), parsedMethod.String())
}

func InitServiceReceiverFieldsForParsedCFG(service *service.Service, parsedMethod *types.ParsedMethod) {
	logger.Logger.Debugf("[CFG] [%s] updating service receiver for method: %s", service.GetName(), parsedMethod.String())

	parsedCfg := parsedMethod.GetParsedCfg()
	receiver := parsedCfg.GetEntryParsedBlock().GetReceiver()
	implVariable := service.GetImplVariable()

	if ptrReceiver, ok := receiver.(*variables.PointerVariable); ok {
		ptrReceiver.PointerTo = implVariable
	} else {
		logger.Logger.Fatalf("[CFG] TODO!!!!")
	}

	logger.Logger.Warnf("[CFG] [%s] updated service receiver for method (%s):\n\t\t\t\t\t - %s", service.GetName(), parsedMethod.GetName(), implVariable.LongString())

}

func GenerateMethodCFGForService(service *service.Service, parsedMethod *types.ParsedMethod) {
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
	logger.Logger.Tracef("[CFG] added service receiver %s (%s) (%s)", receiver.String(), utils.GetType(receiver.(*variables.PointerVariable).PointerTo), utils.GetType(receiver.(*variables.PointerVariable).PointerTo.GetType()))

	for i, param := range parsedMethod.Params {
		v := lookup.CreateVariableFromType(param.GetName(), param.GetType())
		v.GetVariableInfo().IsBlockParam = true
		v.GetVariableInfo().BlockParamIdx = i
		entryBlock.Vars = append(entryBlock.Vars, v)
	}

	// note that parameters also include receiver
	logger.Logger.Infof("[CFG] parsed CFG with (%d) initial variables for method (%s) in service (%s)", len(entryBlock.Vars), parsedCfg.FullMethod, service.GetName())
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
