package main

import (
	"detection_tool/parser"
	"detection_tool/visitor"
	"fmt"
	goparser "go/parser"
	"go/token"
	"detection_tool/logger"
)

var appdir = "./apps/postnotification/workflow/postnotification"

func main() {
	
	fmt.Println()
	fmt.Println("###########################")
	fmt.Println("UPLOAD SERVICE (UploadPost)")
	fmt.Println("###########################")
	fmt.Println()
	computeServiceNode("UploadService.go", "UploadService", "UploadServiceImpl", "UploadPost")
	
	fmt.Println()
	fmt.Println("#######################")
	fmt.Println("NOTIFY SERVICE (Notify)")
	fmt.Println("#######################")
	fmt.Println()
	computeServiceNode("NotifyService.go", "NotifyService", "NotifyServiceImpl", "Notify")
	
	fmt.Println()
	fmt.Println("###########################")
	fmt.Println("STORAGE SERVICE (StorePost)")
	fmt.Println("###########################")
	fmt.Println()
	computeServiceNode("StorageService.go", "StorageService", "StorageServiceImpl", "StorePost")
	
	fmt.Println()
	fmt.Println("##########################")
	fmt.Println("STORAGE SERVICE (ReadPost)")
	fmt.Println("##########################")
	fmt.Println()
	computeServiceNode("StorageService.go", "StorageService", "StorageServiceImpl", "ReadPost")

}

func parseServiceNode(filename string, name string, impl string) (*parser.ServiceNode, error) {
	fset := token.NewFileSet()
	filepath := fmt.Sprintf("%s/%s", appdir, filename)
	file, err := goparser.ParseFile(fset, filepath, nil, goparser.ParseComments)
	if err != nil {
		logger.Logger.Errorf("error parsing file %s: %s", filepath, err.Error())
		return nil, err
	}
	node := &parser.ServiceNode{
		Name:      name,
		Impl:      impl,
		Filepath:  filepath,
		File:      file,
		Imports:   make(map[string]*parser.ParsedImportSpec),
		Databases: make(map[string]*parser.DatabaseField),
		Services:  make(map[string]*parser.ServiceNode),
		Methods:   nil,
	}
	parser.InspectServiceImports(node)
	parser.InspectServiceStructFields(node)
	parser.InspectServiceMethods(node)
	return node, nil
}

func computeServiceNode(serviceFilename string, serviceName string, serviceImplName string, targetMethodName string) {
	serviceNode, err := parseServiceNode(serviceFilename, serviceName, serviceImplName)
	if err != nil {
		return
	}
	var targetMethod *parser.ParsedFuncDecl
	for _, m := range serviceNode.Methods {
		if m.Name == targetMethodName {
			targetMethod = m
			break
		}
	}

	if targetMethod == nil {
		logger.Logger.Infoln("[ERROR] could not find target method with name ", targetMethodName)
		return
	}
	// spew.Dump(serviceNode)

	for _, m := range serviceNode.Methods {
		if m.Name == targetMethod.Name {
			visitor.VisitServiceMethod(m, serviceNode)
		}
	}

	/* storageServiceNode, err := parseServiceNode("StorageService.go", "StorageService", "StorageServiceImpl")
	if err != nil {
		return
	}
	for _, m := range storageServiceNode.Methods {
		if m.Name == "StorePost" {
			visitor.VisitServiceMethod(m, storageServiceNode)
		}
	} */

	basic_cfg, err := parser.GenerateMethodCFG(targetMethod, serviceNode.Filepath)
	if err != nil {
		logger.Logger.Infof("error generating CFG for target method %s in %s: %s\n", targetMethod.Name, serviceNode.Filepath, err.Error())
		return
	}
	if basic_cfg == nil {
		logger.Logger.Infof("basic cfg is nil for target method %s in %s\n", targetMethod.Name, serviceNode.Filepath)
		return
	}

	/* fset := token.NewFileSet()
	dot := basic_cfg.Dot(fset)
	filename := "cfg.dot"
	err = os.WriteFile(filename, []byte(dot), 0644)
	if err != nil {
		logger.Logger.Infoln("Error writing DOT to file:", err)
		return
	}
	logger.Logger.Infof("cfg dot file saved to %s\n", filename) */

	parsedCfg := parser.GenParsedCfg(basic_cfg, targetMethod)
	fmt.Println()

	parser.VisitBasicBlockAssignments(parsedCfg)
	fmt.Println()

	parser.VisitBasicBlockFuncCalls(parsedCfg, targetMethod)
	fmt.Println()

	logger.Logger.Infof("visiting database calls for service node target method %s -> %s", targetMethod.Name, targetMethod.Params)
	visitCalls(targetMethod.DatabaseCalls)
	fmt.Println()
	
	logger.Logger.Infof("visiting service calls for service node target method %s -> %s", targetMethod.Name, targetMethod.Params)
	visitCalls(targetMethod.ServiceCalls)
	fmt.Println()

}

func visitCalls(parsedCalls map[token.Pos]*parser.ParsedCallExpr) {
	for pos, call := range parsedCalls {
		logger.Logger.Infof("call %s.%s [%d]\n", call.Selected, call.MethodName, pos)
		logger.Logger.Info("> deps: ")
		for _, dep := range call.Deps {
			r := visitDeps(dep)
			logger.Logger.Infof("\t%s [%d], %s", dep.Name, dep.Lineno, r)
		}
	}
}

func visitDeps(v *parser.Variable) string {
	s := ""
	for _, dep := range v.Deps {
		visitDeps(dep)
		return s + fmt.Sprintf("-> %s [%d] ", dep.Name, dep.Lineno)
	}
	return ""
}
