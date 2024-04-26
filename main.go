package main

import (
	"analyzer/pkg/app"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/graph"
	"analyzer/pkg/models"
	"analyzer/pkg/parser"
	"analyzer/pkg/visitor"
	"fmt"
	"go/token"
	"analyzer/pkg/logger"

	// this needs to target the root of the app otherwise (and then replace the path in the go.mod file)
	// otherwise the blueprint workflow plugin won't be able to locate the package
	// more specifically, this occurs at
	// blueprint/plugins/workflow/workflowspec/cache.go GetService() -> cached.get()
	// blueprint/plugins/workflow/workflowspec/spec.go  get() -> pkg, pkgExists := mod.Packages[pkgName]
	// the pkgName used as argument is the package name imported here '
	// 		analyzer/apps/postnotification/workflow/postnotification'
	// but the existing packages in the mod.Package represents the root of the app
	// 		'postnotification/workflow/postnotification'
	/* "postnotification/wiring/specs" */
	"postnotification/workflow/postnotification"
	"postnotification/workflow/postnotification/dummy"
)

type BlueprintType interface {
}

func main() {
	dummyServiceSpec, err0 := frameworks.GetBlueprintServiceSpec[dummy.DummyService]()
	storageServiceSpec, err1 := frameworks.GetBlueprintServiceSpec[postnotification.StorageService]()
	notifyServiceSpec, err2 := frameworks.GetBlueprintServiceSpec[postnotification.NotifyService]()
	uploadServiceSpec, err3 := frameworks.GetBlueprintServiceSpec[postnotification.UploadService]()
	if err0 != nil|| err1 != nil || err2 != nil || err3 != nil {
		return
	}
	app, err := app.Init("examples/postnotification/workflow/postnotification")
	if err != nil {
		return
	}
	err = app.AddServiceNode(dummyServiceSpec)
	if err != nil {
		return
	}
	err = app.AddServiceNode(storageServiceSpec, dummyServiceSpec)
	if err != nil {
		return
	}
	err = app.AddServiceNode(notifyServiceSpec, storageServiceSpec)
	if err != nil {
		return
	}
	err = app.AddServiceNode(uploadServiceSpec, storageServiceSpec, notifyServiceSpec)
	if err != nil {
		return
	}

	for _, node := range app.Services {
		fmt.Printf("\n######################## %s ########################\n", node.Name)
		parseServiceNode(node)
		for method := range node.Methods {
			fmt.Printf("\n------------------------ %s ------------------------\n", method)
			visitServiceMethodCFG(node, method)
		}
	}
	entryPoints := map[string][]string {
		"UploadService":  {"UploadPost"},
	}
	abstractGraph := graph.Build(app, entryPoints)
	abstractGraph.Save()
}

func parseServiceNode(node *models.ServiceNode) {
	parser.ParseImports(node)
	parser.ParseStructFields(node)
	parser.ParseMethods(node)
}

func visitServiceMethodCFG(serviceNode *models.ServiceNode, targetMethodName string) {
	targetMethod := serviceNode.Methods[targetMethodName]
	if targetMethod == nil {
		log.Logger.Error("could not find target method with name ", targetMethodName)
		return
	}
	visitor.VisitServiceMethod(targetMethod, serviceNode)

	basic_cfg, err := parser.GenerateMethodCFG(targetMethod, serviceNode.Filepath)
	if err != nil {
		log.Logger.Errorf("error generating CFG for target method %s in %s: %s\n", targetMethod.Name, serviceNode.Filepath, err.Error())
		return
	}
	if basic_cfg == nil {
		log.Logger.Errorf("basic cfg is nil for target method %s in %s\n", targetMethod.Name, serviceNode.Filepath)
		return
	}

	parsedCfg := parser.GenParsedCfg(basic_cfg, targetMethod, serviceNode.Filepath)
	serviceNode.ParsedCFGs[targetMethodName] = parsedCfg

	visitor.VisitBasicBlockAssignments(parsedCfg)
	visitor.VisitBasicBlockFuncCalls(parsedCfg, targetMethod)

	visitCalls(targetMethod.DatabaseCalls)
	visitCalls(targetMethod.ServiceCalls)
}

func visitCalls(parsedCalls map[token.Pos]*models.ParsedCallExpr) {
	log.Logger.Info("visiting database/service calls for service node target method")
	for pos, call := range parsedCalls {
		log.Logger.Debugf("call %s.%s [%d]\n", call.Selected, call.MethodName, pos)
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
