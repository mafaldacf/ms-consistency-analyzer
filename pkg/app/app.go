package app

import (
	"analyzer/pkg/controlflow"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"fmt"
	goparser "go/parser"
	"go/token"
	"path/filepath"
	"strings"

	"github.com/blueprint-uservices/blueprint/plugins/golang"
	"github.com/blueprint-uservices/blueprint/plugins/workflow"
	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"
)

type App struct {
	Name 		string
	Path      	string
	Services  	map[string]*service.ServiceNode
	Databases 	map[string]*types.DatabaseInstance
}

func (app *App) String() string {
	repr := fmt.Sprintf("\n### APP: %s\n", app.Name)
	for _, service := range app.Services {
		repr += "> " + service.String() + "\n"
	}
	return repr
}

func Init(name string, path string) (*App, error) {
	fullPath, err := filepath.Abs(path)
	if err != nil {
		msg := fmt.Sprintf("error fetching full path for %s", path)
		logger.Logger.Error(msg)
		return nil, fmt.Errorf(msg)
	}
	app := &App{
		Name: 		name,
		Path:      	fullPath,
		Services:  	make(map[string]*service.ServiceNode),
		Databases: 	make(map[string]*types.DatabaseInstance),
	}
	logger.Logger.Infof("initialized app at %s", app.Path)
	return app, nil
}

func (app *App) RegisterServiceNodes(workflowHandlers map[*workflow.WorkflowHandler][]golang.Service) error {
	// services also include blueprint backends
	for handler, golangServices := range workflowHandlers {
		serviceSpec := handler.ServiceInfo
		fset := token.NewFileSet()
		filepath := serviceSpec.Iface.File.Name
		file, err := goparser.ParseFile(fset, filepath, nil, goparser.ParseComments)
		if err != nil {
			logger.Logger.Errorf("error parsing file %s: %s", filepath, err.Error())
			return err
		}
		node := &service.ServiceNode{
			Name:            serviceSpec.Iface.Name,
			Impl:            serviceSpec.Iface.Name + "Impl", // FIX THIS hardcoded value
			Package:         serviceSpec.Iface.File.Package.Name,
			Filepath:        filepath,
			File:            file,
			Fields:          make(map[string]types.Field),
			Imports:         make(map[string]*service.ParsedImportSpec),
			Services:        make(map[string]*service.ServiceNode),
			ExposedMethods:  make(map[string]*service.ParsedFuncDecl),
			WorkerMethods:   make(map[string]*service.ParsedFuncDecl),
			InternalMethods: make(map[string]*service.ParsedFuncDecl),
			ParsedCFGs:      make(map[string]*types.ParsedCFG),
		}
		// add entry for methods that will be later parsed
		for _, m := range serviceSpec.Iface.Ast.Methods.List {
			node.ExposedMethods[m.Names[0].Name] = nil
		}

		// add entry in map but with nil value
		// after we have created all service nodes
		// then we are going to reference all edges correctly
		for _, golangService := range golangServices {
			if workflowClient, ok := golangService.(*workflow.WorkflowClient); ok {
				node.Services[workflowClient.ServiceType] = nil
			}
		}
		app.Services[node.Name] = node
	}
	// at the end, match all services correctly
	for _, serviceNode := range app.Services {
		for edgeName := range serviceNode.Services {
			serviceNode.Services[edgeName] = app.Services[edgeName]
		}
		logger.Logger.Infof("register app service node %s", serviceNode.String())
	}

	return nil
}

func (app *App) Parse() {
	for _, node := range app.Services {
		fmt.Printf("\n######################## %s ########################\n", node.Name)
		node.ParseImports()
		node.ParseServiceFields()
		node.ParseMethods()
	}
	for _, node := range app.Services {
		// can only parse and visit methods only after we have parsed all methods
		node.ParseMethodsBody()
	}
	for _, node := range app.Services {
		parseAndVisitCFG(node, node.ExposedMethods, "exposed")
		parseAndVisitCFG(node, node.WorkerMethods, "worker")
		parseAndVisitCFG(node, node.InternalMethods, "internal")
	}
}

func parseAndVisitCFG(node *service.ServiceNode, methods map[string]*service.ParsedFuncDecl, visibility string) {
	for _, method := range methods {
		fmt.Printf("\n[%s] ------------------------ %s ------------------------\n", strings.ToUpper(visibility), method)
		if parsedCfg, err := controlflow.ParseCFG(node, method); err == nil {
			controlflow.VisitServiceMethodCFG(parsedCfg, method)
		}
	}
}

// RegisterSimpleServiceNode is deprecated
// only used when we use frameworks.GetBlueprintServiceSpec[T]() directly
func (app *App) RegisterSimpleServiceNode(serviceSpec *workflowspec.Service, services ...*workflowspec.Service) error {
	fset := token.NewFileSet()
	filepath := serviceSpec.Iface.File.Name
	file, err := goparser.ParseFile(fset, filepath, nil, goparser.ParseComments)
	if err != nil {
		logger.Logger.Errorf("error parsing file %s: %s", filepath, err.Error())
		return err
	}
	node := &service.ServiceNode{
		Name:            serviceSpec.Iface.Name,
		Impl:            serviceSpec.Iface.Name + "Impl", // FIX THIS hardcoded value
		Package:         serviceSpec.Iface.File.Package.Name,
		Filepath:        filepath,
		File:            file,
		Fields:          make(map[string]types.Field),
		Imports:         make(map[string]*service.ParsedImportSpec),
		Services:        make(map[string]*service.ServiceNode),
		ExposedMethods:  make(map[string]*service.ParsedFuncDecl),
		WorkerMethods:   make(map[string]*service.ParsedFuncDecl),
		InternalMethods: make(map[string]*service.ParsedFuncDecl),
		ParsedCFGs:      make(map[string]*types.ParsedCFG),
	}
	for _, s := range services {
		node.Services[s.Iface.Name] = app.Services[s.Iface.Name]
	}
	for _, m := range serviceSpec.Iface.Ast.Methods.List {
		node.ExposedMethods[m.Names[0].Name] = nil
	}

	app.Services[node.Name] = node
	logger.Logger.Infof("register app service node %s", node.String())
	return nil
}
