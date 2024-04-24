package main

import (
	"fmt"
	goparser "go/parser"
	"go/token"
	"static_analyzer/logger"
	"static_analyzer/models"
	"static_analyzer/parser"
	"static_analyzer/visitor"
	"static_analyzer/graph"
)

var appdir = "./apps/postnotification/workflow/postnotification"

var appServiceNodes map[string]*models.ServiceNode

func main() {
	appServiceNodes = make(map[string]*models.ServiceNode)

	uploadServiceNode, err := genServiceNode("UploadService.go", "UploadService", "UploadServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "UploadService")
		return
	}
	appServiceNodes["UploadService"] = uploadServiceNode

	notifyServiceNode, err := genServiceNode("NotifyService.go", "NotifyService", "NotifyServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "NotifyService")
		return
	}
	appServiceNodes["NotifyService"] = notifyServiceNode

	storageServiceNode, err := genServiceNode("StorageService.go", "StorageService", "StorageServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "StorageService")
		return
	}
	appServiceNodes["StorageService"] = storageServiceNode

	fmt.Println()
	fmt.Println("##############")
	fmt.Println("UPLOAD SERVICE")
	fmt.Println("##############")
	fmt.Println()
	parseServiceNode(uploadServiceNode)
	visitServiceMethodCFG(uploadServiceNode, "UploadPost")

	fmt.Println()
	fmt.Println("##############")
	fmt.Println("NOTIFY SERVICE")
	fmt.Println("##############")
	fmt.Println()
	parseServiceNode(notifyServiceNode)
	visitServiceMethodCFG(notifyServiceNode, "Notify")

	fmt.Println()
	fmt.Println("###############")
	fmt.Println("STORAGE SERVICE")
	fmt.Println("################")
	fmt.Println()
	parseServiceNode(storageServiceNode)
	fmt.Println("--------- Store Post -----------")
	fmt.Println()
	visitServiceMethodCFG(storageServiceNode, "StorePost")
	fmt.Println("---------- Read Post -----------")
	fmt.Println()
	visitServiceMethodCFG(storageServiceNode, "ReadPost")

	// FIXME: this should be automated
	// BUT we can need to be caferul between storageService and StorageService
	delete(uploadServiceNode.Services, "storageService")
	delete(uploadServiceNode.Services, "notifyService")
	uploadServiceNode.Services["storageService"] = storageServiceNode
	uploadServiceNode.Services["notifyService"] = notifyServiceNode
	delete(notifyServiceNode.Services, "storageService")
	notifyServiceNode.Services["storageService"] = storageServiceNode

	abstractGraph := graph.Build(uploadServiceNode, "UploadPost", appServiceNodes)
	abstractGraph.Save()
}

func genServiceNode(filename string, name string, impl string) (*models.ServiceNode, error) {
	fset := token.NewFileSet()
	filepath := fmt.Sprintf("%s/%s", appdir, filename)
	file, err := goparser.ParseFile(fset, filepath, nil, goparser.ParseComments)
	if err != nil {
		logger.Logger.Errorf("error parsing file %s: %s", filepath, err.Error())
		return nil, err
	}
	return &models.ServiceNode{
		Name:       name,
		Impl:       impl,
		Filepath:   filepath,
		File:       file,
		Imports:    make(map[string]*models.ParsedImportSpec),
		Databases:  make(map[string]*models.DatabaseField),
		Services:   make(map[string]*models.ServiceNode),
		Methods:    make(map[string]*models.ParsedFuncDecl),
		ParsedCFGs: make(map[string]*models.ParsedCFG),
	}, nil
}

func parseServiceNode(node *models.ServiceNode) {
	parser.InspectServiceImports(node)
	parser.InspectServiceStructFields(node)
	parser.InspectServiceMethods(node)
}

func visitServiceMethodCFG(serviceNode *models.ServiceNode, targetMethodName string) {
	targetMethod := serviceNode.Methods[targetMethodName]
	if targetMethod == nil {
		logger.Logger.Error("could not find target method with name ", targetMethodName)
		return
	}
	visitor.VisitServiceMethod(targetMethod, serviceNode)

	basic_cfg, err := parser.GenerateMethodCFG(targetMethod, serviceNode.Filepath)
	if err != nil {
		logger.Logger.Errorf("error generating CFG for target method %s in %s: %s\n", targetMethod.Name, serviceNode.Filepath, err.Error())
		return
	}
	if basic_cfg == nil {
		logger.Logger.Errorf("basic cfg is nil for target method %s in %s\n", targetMethod.Name, serviceNode.Filepath)
		return
	}

	parsedCfg := parser.GenParsedCfg(basic_cfg, targetMethod)
	fmt.Println()
	serviceNode.ParsedCFGs[targetMethodName] = parsedCfg

	visitor.VisitBasicBlockAssignments(parsedCfg)
	fmt.Println()

	visitor.VisitBasicBlockFuncCalls(parsedCfg, targetMethod)
	fmt.Println()

	logger.Logger.Infof("visiting database calls for service node target method %s -> %s", targetMethod.Name, targetMethod.Params)
	visitCalls(targetMethod.DatabaseCalls)
	fmt.Println()

	logger.Logger.Infof("visiting service calls for service node target method %s -> %s", targetMethod.Name, targetMethod.Params)
	visitCalls(targetMethod.ServiceCalls)
	fmt.Println()
}

func visitCalls(parsedCalls map[token.Pos]*models.ParsedCallExpr) {
	for pos, call := range parsedCalls {
		logger.Logger.Infof("call %s.%s [%d]\n", call.Selected, call.MethodName, pos)
		logger.Logger.Info("> params: ")
		for _, dep := range call.Deps {
			r := visitDeps(dep)
			logger.Logger.Infof("\t%s [%d], %s", dep.Name, dep.Lineno, r)
		}
	}
}

func visitDeps(v *models.Variable) string {
	s := ""
	for _, dep := range v.Deps {
		visitDeps(dep)
		return s + fmt.Sprintf("-> %s [%d] ", dep.Name, dep.Lineno)
	}
	return ""
}
