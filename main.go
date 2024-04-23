package main

import (
	"detection_tool/logger"
	"detection_tool/parser"
	"detection_tool/visitor"
	"fmt"
	goparser "go/parser"
	"go/token"
	"sort"
)

var appdir = "./apps/postnotification/workflow/postnotification"

func main() {
	uploadServiceNode, err := genServiceNode("UploadService.go", "UploadService", "UploadServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "UploadService")
		return
	}
	notifyServiceNode, err := genServiceNode("NotifyService.go", "NotifyService", "NotifyServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "NotifyService")
		return
	}
	storageServiceNode, err := genServiceNode("StorageService.go", "StorageService", "StorageServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "StorageService")
		return
	}
	// FIXME: this should be automated with the help of the blueprint IR technique even before we parse and generate CFGs
	uploadServiceNode.Services["StorageService"] = storageServiceNode
	uploadServiceNode.Services["NotifyService"] = notifyServiceNode
	notifyServiceNode.Services["StorageService"] = storageServiceNode
	
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

	targetMethod := uploadServiceNode.Methods["UploadPost"]

	abstractGraph := parser.AbstractGraph {
		Nodes: make([]*parser.AbstractNode, 0),
	}
	logger.Logger.Info(abstractGraph)

	linenos := make([]token.Pos, 0, len(targetMethod.DatabaseCalls))
	for k := range targetMethod.DatabaseCalls {
		linenos = append(linenos, k)
	}
	for k := range targetMethod.ServiceCalls {
		linenos = append(linenos, k)
	}
	// order by lineno
	sort.Slice(linenos, func(i, j int) bool {
		return linenos[i] < linenos[j]
	})

	for _, lineno := range linenos {
		if targetMethod.DatabaseCalls[lineno] != nil {
			abstractGraph.Nodes = append(abstractGraph.Nodes, &parser.AbstractNode{
				ParsedCall: targetMethod.DatabaseCalls[lineno],
				NodeType: 	parser.DATABASE_CALL,
			})
		} else if targetMethod.ServiceCalls[lineno] != nil {
			abstractGraph.Nodes = append(abstractGraph.Nodes, &parser.AbstractNode{
				ParsedCall: targetMethod.ServiceCalls[lineno],
				NodeType: 	parser.SERVICE_CALL,
			})
		}
	}

}

func genServiceNode(filename string, name string, impl string) (*parser.ServiceNode, error) {
	fset := token.NewFileSet()
	filepath := fmt.Sprintf("%s/%s", appdir, filename)
	file, err := goparser.ParseFile(fset, filepath, nil, goparser.ParseComments)
	if err != nil {
		logger.Logger.Errorf("error parsing file %s: %s", filepath, err.Error())
		return nil, err
	}
	return &parser.ServiceNode{
		Name:      name,
		Impl:      impl,
		Filepath:  filepath,
		File:      file,
		Imports:   make(map[string]*parser.ParsedImportSpec),
		Databases: make(map[string]*parser.DatabaseField),
		Services:  make(map[string]*parser.ServiceNode),
		Methods:   make(map[string]*parser.ParsedFuncDecl),
	}, nil
}

func parseServiceNode(node *parser.ServiceNode) {
	parser.InspectServiceImports(node)
	parser.InspectServiceStructFields(node)
	parser.InspectServiceMethods(node)
}

func visitServiceMethodCFG(serviceNode *parser.ServiceNode, targetMethodName string) {
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
