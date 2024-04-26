package app

import (
	"analyzer/pkg/models"
	"fmt"
	"go/parser"
	"go/token"
	"analyzer/pkg/logger"
	"path/filepath"

	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"
)

type App struct {
	Path     string
	Services map[string]*models.ServiceNode
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
		Services: make(map[string]*models.ServiceNode),
	}
	log.Logger.Infof("initialized app at %s", app.Path)
	return app, nil
}

func (app *App) AddServiceNode(serviceSpec *workflowspec.Service, services ...*workflowspec.Service) error {
	fset := token.NewFileSet()
	filepath := serviceSpec.Iface.File.Name
	file, err := parser.ParseFile(fset, filepath, nil, parser.ParseComments)
	if err != nil {
		log.Logger.Errorf("error parsing file %s: %s", filepath, err.Error())
		return err
	}
	node := &models.ServiceNode{
		Name:       serviceSpec.Iface.Name,
		Impl:       serviceSpec.Iface.Name + "Impl", // FIX THIS hardcoded value
		Package:    serviceSpec.Iface.File.Package.Name,
		Filepath:   filepath,
		File:       file,
		Fields:     make(map[string]models.ParsedField),
		Imports:    make(map[string]*models.ParsedImportSpec),
		Services:   make(map[string]*models.ServiceNode),
		Methods:    make(map[string]*models.ParsedFuncDecl),
		ParsedCFGs: make(map[string]*models.ParsedCFG),
	}
	for _, s := range services {
		node.Services[s.Iface.Name] = app.Services[s.Iface.Name]
	}
	app.Services[node.Name] = node
	log.Logger.Infof("added node %s at package %s with dependence on %d services", node.Name, node.Package, len(node.Services))
	return nil
}
