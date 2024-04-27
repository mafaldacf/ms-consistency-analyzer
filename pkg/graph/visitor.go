package graph

import (
	"analyzer/pkg/abstree"
	"analyzer/pkg/controlflow"
	log "analyzer/pkg/logger"
	"analyzer/pkg/models"
	"fmt"
	"go/token"
)

func VisitServiceMethodCFG(node *abstree.ServiceNode, targetMethodName string) {
	targetMethod := node.ExposedMethods[targetMethodName]
	if targetMethod == nil {
		log.Logger.Error("could not find target method with name ", targetMethodName)
		return
	}
	node.ParseMethodBodyCalls(targetMethod)

	basic_cfg, err := controlflow.GenerateMethodCFG(targetMethod, node.Filepath)
	if err != nil {
		log.Logger.Errorf("error generating CFG for target method %s in %s: %s\n", targetMethod.Name, node.Filepath, err.Error())
		return
	}
	if basic_cfg == nil {
		log.Logger.Errorf("basic cfg is nil for target method %s in %s\n", targetMethod.Name, node.Filepath)
		return
	}

	parsedCfg := controlflow.GenParsedCfg(basic_cfg, targetMethod, node.Filepath)
	node.ParsedCFGs[targetMethodName] = parsedCfg

	controlflow.VisitBasicBlockAssignments(parsedCfg)
	controlflow.VisitBasicBlockFuncCalls(parsedCfg, targetMethod)

	VisitCalls(targetMethod.DatabaseCalls)
	VisitCalls(targetMethod.ServiceCalls)
}

func VisitCalls(parsedCalls map[token.Pos]*abstree.ParsedCallExpr) {
	log.Logger.Info("visiting database/service calls for service node target method")
	for pos, call := range parsedCalls {
		log.Logger.Debugf("call %s.%s [%d]\n", call.TargetField, call.MethodName, pos)
		log.Logger.Debug("> deps: ")
		for _, dep := range call.Deps {
			r := visitDeps(dep)
			log.Logger.Debugf("\t%s [%d], %s", dep.Name, dep.Lineno, r)
		}
	}
	log.Logger.Debugln()
}

func visitDeps(v *models.Variable) string {
	s := ""
	for _, dep := range v.Deps {
		visitDeps(dep)
		return s + fmt.Sprintf("-> %s [%d] ", dep.Name, dep.Lineno)
	}
	return ""
}
