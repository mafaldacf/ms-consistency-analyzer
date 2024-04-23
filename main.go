package main

import (
	"detection_tool/logger"
	"detection_tool/parser"
	"detection_tool/visitor"
	"encoding/json"
	"fmt"
	goparser "go/parser"
	"go/token"
	"os"
	"sort"
)

var appdir = "./apps/postnotification/workflow/postnotification"

var allServiceNodes map[string]*parser.ServiceNode

func main() {
	allServiceNodes = make(map[string]*parser.ServiceNode)

	uploadServiceNode, err := genServiceNode("UploadService.go", "UploadService", "UploadServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "UploadService")
		return
	}
	allServiceNodes["UploadService"] = uploadServiceNode

	notifyServiceNode, err := genServiceNode("NotifyService.go", "NotifyService", "NotifyServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "NotifyService")
		return
	}
	allServiceNodes["NotifyService"] = notifyServiceNode

	storageServiceNode, err := genServiceNode("StorageService.go", "StorageService", "StorageServiceImpl")
	if err != nil {
		logger.Logger.Error("error generating node for service", "StorageService")
		return
	}
	allServiceNodes["StorageService"] = storageServiceNode
	
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

	abstractGraph := start(uploadServiceNode, "UploadPost")

	// print in JSON format
	// https://omute.net/editor
	file, err := os.Create("abstract_graph.json")
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()
	for _, node := range abstractGraph.Nodes {
		data, err := json.MarshalIndent(node, "", "  ")
		if err != nil {
			logger.Logger.Error("error marshaling json:", err)
			return
		}
		file.Write(data)
		fmt.Println(string(data))
	}
}

func start(serviceNode *parser.ServiceNode, targetMethodName string) (*parser.AbstractGraph) {
	targetMethod := serviceNode.Methods[targetMethodName]

	abstractGraph := parser.AbstractGraph {
		Nodes: make([]*parser.AbstractNode, 0),
	}

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
	
	abstractGraph.Nodes = append(abstractGraph.Nodes, &parser.AbstractNode{
		NodeType: parser.KIND_ROOT,
		Repr: fmt.Sprintf("%s.%s", serviceNode.Name, targetMethodName),
	})
	
	for _, lineno := range linenos {
		if targetMethod.DatabaseCalls[lineno] != nil {
			dbCall := targetMethod.DatabaseCalls[lineno]
			repr := fmt.Sprintf("%s.%s", dbCall.Type, dbCall.MethodName)
			abstractGraph.Nodes[0].Children = append(abstractGraph.Nodes[0].Children, &parser.AbstractNode{
				ParsedCall: 	dbCall,
				CallerParams: 	dbCall.Deps,
				NodeType: 		parser.KIND_DATABASE_CALL,
				Repr: 			repr,
			})
		} else if targetMethod.ServiceCalls[lineno] != nil {
			svcCall := targetMethod.ServiceCalls[lineno]
			//svcFuncDecl := allServiceNodes[svcCall.Type].ParsedCFGs[svcCall.MethodName].Vars
			repr := fmt.Sprintf("%s.%s", svcCall.Type, svcCall.MethodName)
			abstractGraph.Nodes[0].Children = append(abstractGraph.Nodes[0].Children, &parser.AbstractNode{
				ParsedCall: 	svcCall,
				CallerParams: 	svcCall.Deps,
				//CalleeParams: 	svcFuncDecl,
				NodeType: 		parser.KIND_SERVICE_CALL,
				Repr: 			repr,
			})
		}
	}
	recurse(abstractGraph.Nodes[0])
	return &abstractGraph
}

func recurse (parentNode *parser.AbstractNode) {
	for _, node := range parentNode.Children {
		// we need to unfold the service blocks from each service call
		if node.NodeType == parser.KIND_SERVICE_CALL {
			serviceNode := allServiceNodes[node.ParsedCall.Type]
			methodName := node.ParsedCall.MethodName
			targetMethod := serviceNode.Methods[methodName]

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
					dbCall := targetMethod.DatabaseCalls[lineno]
					repr := fmt.Sprintf("%s.%s", dbCall.Type, dbCall.MethodName)
					node.Children = append(node.Children, &parser.AbstractNode{
						ParsedCall: 	dbCall,
						CallerParams: 	dbCall.Deps,
						NodeType: 		parser.KIND_DATABASE_CALL,
						Repr:       	repr,
					})
				} else if targetMethod.ServiceCalls[lineno] != nil {
					svcCall := targetMethod.ServiceCalls[lineno]
					repr := fmt.Sprintf("%s.%s", svcCall.Type, svcCall.MethodName)
					node.Children = append(node.Children, &parser.AbstractNode{
						ParsedCall: 	svcCall,
						CallerParams: 	svcCall.Deps,
						NodeType: 		parser.KIND_SERVICE_CALL,
						Repr:       	repr,
					})
				}
			}
			recurse(node)
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
		ParsedCFGs: make(map[string]*parser.ParsedCFG),
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
	serviceNode.ParsedCFGs[targetMethodName] = parsedCfg

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
		logger.Logger.Info("> params: ")
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
