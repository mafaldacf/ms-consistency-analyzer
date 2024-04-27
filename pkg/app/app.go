package app

import (
	log "analyzer/pkg/logger"
	"analyzer/pkg/models"
	"analyzer/pkg/service"
	"fmt"
	goparser "go/parser"
	"go/token"
	"path/filepath"

	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"
)

type App struct {
	Path     string
	Services map[string]*service.ServiceNode
}

func Init(path string) (*App, error) {
	fullPath, err := filepath.Abs(path)
	if err != nil {
		msg := fmt.Sprintf("error fetching full path for %s", path)
		log.Logger.Error(msg)
		return nil, fmt.Errorf(msg)
	}
	app := &App{
		Path:     fullPath,
		Services: make(map[string]*service.ServiceNode),
	}
	log.Logger.Infof("initialized app at %s", app.Path)
	return app, nil
}

func (app *App) AddServiceNode(serviceSpec *workflowspec.Service, services ...*workflowspec.Service) error {
	fset := token.NewFileSet()
	filepath := serviceSpec.Iface.File.Name
	file, err := goparser.ParseFile(fset, filepath, nil, goparser.ParseComments)
	if err != nil {
		log.Logger.Errorf("error parsing file %s: %s", filepath, err.Error())
		return err
	}
	node := &service.ServiceNode{
		Name:           serviceSpec.Iface.Name,
		Impl:           serviceSpec.Iface.Name + "Impl", // FIX THIS hardcoded value
		Package:        serviceSpec.Iface.File.Package.Name,
		Filepath:       filepath,
		File:           file,
		Fields:         make(map[string]service.ParsedField),
		Imports:        make(map[string]*service.ParsedImportSpec),
		Services:       make(map[string]*service.ServiceNode),
		ExposedMethods: make(map[string]*service.ParsedFuncDecl),
		ParsedCFGs:     make(map[string]*models.ParsedCFG),
	}
	for _, s := range services {
		node.Services[s.Iface.Name] = app.Services[s.Iface.Name]
	}
	for _, m := range serviceSpec.Iface.Ast.Methods.List {
		node.ExposedMethods[m.Names[0].Name] = nil
	}
	app.Services[node.Name] = node
	log.Logger.Infof("added node %s at package %s with dependence on %d services", node.Name, node.Package, len(node.Services))
	return nil
}
