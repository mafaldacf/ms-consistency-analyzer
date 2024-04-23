package main

import (
	"detection_tool/parser"
	"detection_tool/visitor"
	"fmt"
	goparser "go/parser"
	"go/token"
)

var appdir = "./apps/post-notification/workflow/postnotification"

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
	frontendNode, err := parseServiceNode("Frontend.go", "Frontend", "FrontendImpl")
	if err != nil {
		return
	}
	// spew.Dump(frontendNode)

	for _, m := range frontendNode.Methods {
		if m.Name == "UploadPost" {
			visitor.VisitServiceMethod(m, frontendNode)
			for _, c := range m.ServiceCalls {
				fmt.Println("sv call:", c.Ast)
			}
			for _, c := range m.DatabaseCalls {
				fmt.Println("db call:", c.Ast)
			}
		}
	}

	fmt.Println("-----------------------")
	fmt.Println("-----------------------")

	/* storageServiceNode, err := parseServiceNode("StorageService.go", "StorageService", "StorageServiceImpl")
	if err != nil {
		return
	}
	for _, m := range storageServiceNode.Methods {
		if m.Name == "StorePost" {
			visitor.VisitServiceMethod(m, storageServiceNode)
		}
	} */

	basic_cfg, err := parser.GenerateMethodCFG("Test", frontendNode.Filepath)
	if err != nil {
		fmt.Printf("error generating CFG for target method %s in %s: %s", "UploadPost", frontendNode.Filepath, err.Error())
		return
	}

	for _, b := range basic_cfg.Blocks {
		parser.VisitBasicBlock(b, frontendNode)
	}

	/* _, err = parser.GenerateMethodCFG("StorePost", storageServiceNode.Filepath)
	if err != nil {
		fmt.Printf("error generating CFG for target method %s in %s: %s", "StorePost", storageServiceNode.Filepath, err.Error())
		return
	} */

}
