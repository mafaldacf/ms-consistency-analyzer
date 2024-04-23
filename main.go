package main

import (
	"detection_tool/parser"
	"detection_tool/visitor"
	"fmt"
	goparser "go/parser"
	"go/token"
)

var appdir = "./apps/postnotification/workflow/postnotification"

func parseServiceNode(filename string, name string, impl string) (*parser.ServiceNode, error) {
	fset := token.NewFileSet()
	filepath := fmt.Sprintf("%s/%s", appdir, filename)
	file, err := goparser.ParseFile(fset, filepath, nil, goparser.ParseComments)
	if err != nil {
		fmt.Printf("error parsing file %s: %s", filepath, err.Error())
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

func main() {
	fmt.Print("\n--------------\nUPLOAD SERVICE\n--------------\n\n")
	computeServiceNode("UploadService.go", "UploadService", "UploadServiceImpl")
	fmt.Print("\n--------------\nNOTIFY SERVICE\n--------------\n\n")
	computeServiceNode("NotifyService.go", "NotifyService", "NotifyServiceImpl")

}

func computeServiceNode(serviceFilename string, serviceName string, serviceImplName string) {
	serviceNode, err := parseServiceNode(serviceFilename, serviceName, serviceImplName)
	if err != nil {
		return
	}

	targetMethod := serviceNode.Methods[0]
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
		fmt.Printf("error generating CFG for target method %s in %s: %s\n", targetMethod.Name, serviceNode.Filepath, err.Error())
		return
	}
	if basic_cfg == nil {
		fmt.Printf("basic cfg is nil for target method %s in %s\n", targetMethod.Name, serviceNode.Filepath)
		return
	}

	/* fset := token.NewFileSet()
	dot := basic_cfg.Dot(fset)
	filename := "cfg.dot"
	err = os.WriteFile(filename, []byte(dot), 0644)
	if err != nil {
		fmt.Println("Error writing DOT to file:", err)
		return
	}
	fmt.Printf("[INFO] cfg dot file saved to %s\n", filename) */

	parsedCfg := parser.GenParsedCfg(basic_cfg, targetMethod)
	fmt.Println("\n----------------------------------------------")
	parser.VisitBasicBlockAssignments(parsedCfg)
	fmt.Println("----------------------------------------------")
	parser.VisitBasicBlockFuncCalls(parsedCfg, serviceNode.Methods[0])
	fmt.Println("----------------------------------------------\n")
	fmt.Println("[INFO] visiting database calls for service node target method")
	visitCalls(serviceNode.Methods[0].DatabaseCalls)
	fmt.Println("[INFO] visiting service calls for service node target method")
	visitCalls(serviceNode.Methods[0].ServiceCalls)

}

func visitCalls(parsedCalls map[token.Pos]*parser.ParsedCallExpr) {
	for pos, call := range parsedCalls {
		fmt.Printf("call %s [%d]\n", call.MethodName, pos)
		fmt.Print("deps: ")
		for _, dep := range call.Deps {
			fmt.Printf("%s [%d], ", dep.Name, dep.Lineno)
			visitDeps(dep)
		}
		fmt.Printf("\n")
	}
}

func visitDeps(v *parser.Variable) {
	for _, dep := range v.Deps {
		fmt.Printf("-> %s [%d] ", dep.Name, dep.Lineno)
		visitDeps(dep)
	}
}
