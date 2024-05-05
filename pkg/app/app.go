package app

import (
	"analyzer/pkg/controlflow"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"encoding/json"
	"fmt"
	goparser "go/parser"
	"go/token"
	"os"
	"path/filepath"
	"reflect"
	"strings"

	"github.com/blueprint-uservices/blueprint/blueprint/pkg/ir"
	"github.com/blueprint-uservices/blueprint/plugins/golang"
	"github.com/blueprint-uservices/blueprint/plugins/rabbitmq"
	"github.com/blueprint-uservices/blueprint/plugins/redis"
	"github.com/blueprint-uservices/blueprint/plugins/workflow"
	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"
)

type App struct {
	Name      string                            `json:"app_name,omitempty"`
	Path      string                            `json:"-"`
	Services  map[string]*service.ServiceNode   `json:"app_services,omitempty"`
	Databases map[string]types.DatabaseInstance `json:"app_databases,omitempty"`
}

// MarshalJSON is used by app.Save()
func (app *App) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string                            `json:"name"`
		Services  map[string]*service.ServiceNode   `json:"package"`
		Databases map[string]types.DatabaseInstance `json:"app_databases"`
	}{
		Name:      app.Name,
		Services:  app.Services,
		Databases: app.Databases,
	})
}

func (app *App) String() string {
	str, _ := app.MarshalJSON()
	return string(str)
}

func Init(name string, path string) (*App, error) {
	fullPath, err := filepath.Abs(path)
	if err != nil {
		msg := fmt.Sprintf("error fetching full path for %s", path)
		logger.Logger.Error(msg)
		return nil, fmt.Errorf(msg)
	}
	app := &App{
		Name:      name,
		Path:      fullPath,
		Services:  make(map[string]*service.ServiceNode),
		Databases: make(map[string]types.DatabaseInstance),
	}
	logger.Logger.Infof("[APP] initialized app at %s", app.Path)
	return app, nil
}

func (app *App) Save() {
	// print in JSON format
	// https://omute.net/editor
	file, err := os.Create("assets/app.json")
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()
	data, err := json.MarshalIndent(app, "", "  ")
	if err != nil {
		logger.Logger.Error("error marshaling json:", err)
		return
	}
	file.Write(data)
}

func getDatabaseInstanceName(name string) string {
	// remove .client suffix (e.g. notification_queue.client)
	return strings.Split(name, ".")[0]
}

func (app *App) RegisterDatabaseInstances(databases map[string]ir.IRNode) {
	for name, node := range databases {
		name = getDatabaseInstanceName(name)
		switch node.(type) {
		case *redis.RedisGoClient:
			app.Databases[name] = &frameworks.CacheInstance{
				BlueprintDatabaseInstance: frameworks.BlueprintDatabaseInstance{
					Name: name,
				},
			}
		case *rabbitmq.RabbitmqGoClient:
			app.Databases[name] = &frameworks.QueueInstance{
				BlueprintDatabaseInstance: frameworks.BlueprintDatabaseInstance{
					Name: name,
				},
			}
		default:
			t := reflect.TypeOf(node).Elem().Name()
			logger.Logger.Warnf("unknown type for database instance: %s (type = %s)", name, t)
			continue
		}
		logger.Logger.Infof("[APP] registered database instance %s", app.Databases[name].String())
	}
}

func (app *App) RegisterServiceNodes(servicesSpec map[*workflowspec.Service][]golang.Service) error {
	err := app.createServiceNodes(servicesSpec)
	if err != nil {
		return err
	}
	app.matchServiceEdges()
	app.parseServicesInfo()
	app.parseServicesBody()

	for _, node := range app.Services {
		logger.Logger.Infof("[APP] registered service node %s", node.String())
	}
	return nil
}

func (app *App) matchServiceEdges() {
	for _, node := range app.Services {
		for edgeName := range node.Services {
			node.Services[edgeName] = app.Services[edgeName]
		}
	}
}

func (app *App) parseServicesInfo() {
	for _, node := range app.Services {
		node.ParseImports()
		node.ParseFields()
		node.ParseMethods()
	}
}

func (app *App) parseServicesBody() {
	for _, node := range app.Services {
		node.ParseMethodsBody()
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

func (app *App) createServiceNodes(servicesSpec map[*workflowspec.Service][]golang.Service) error {
	// services also include blueprint backends
	for serviceSpec, golangServices := range servicesSpec {
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
	return nil
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
