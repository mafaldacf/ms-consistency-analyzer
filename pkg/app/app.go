package app

import (
	"analyzer/pkg/controlflow"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	"encoding/json"
	"fmt"
	"go/parser"
	"go/token"
	"os"
	"path/filepath"
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
	Packages  map[string]*types.Package 		`json:"packages,omitempty"`
}

// MarshalJSON is used by app.Save()
func (app *App) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string                            `json:"name"`
		Services  map[string]*service.ServiceNode   `json:"app_services"`
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
		Packages:  make(map[string]*types.Package),
	}
	logger.Logger.Infof("[APP] initialized app at %s", app.Path)
	return app, nil
}

func (app *App) Save() {
	// print in JSON format
	// https://omute.net/editor
	path := fmt.Sprintf("assets/%s/app.json", app.Name)
	file, err := os.Create(path)
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
	logger.Logger.Infof("[JSON] app saved at %s", path)
}

func getShortDbInstanceName(name string) string {
	// remove .client suffix (e.g. notification_queue.client)
	splits := strings.Split(name, ".")[0]
	if len(splits) > 0 {
		return strings.Split(name, ".")[0]
	}
	return ""
}

func (app *App) RegisterDatabaseInstances(databases map[string]ir.IRNode) {
	for name, node := range databases {
		name = getShortDbInstanceName(name)
		switch node.(type) {
		case *redis.RedisGoClient:
			app.Databases[name] = &frameworks.CacheInstance{
				BlueprintDatabaseInstance: frameworks.BlueprintDatabaseInstance{
					Name: name,
					Kind: "Redis",
				},
			}
		case *rabbitmq.RabbitmqGoClient:
			app.Databases[name] = &frameworks.QueueInstance{
				BlueprintDatabaseInstance: frameworks.BlueprintDatabaseInstance{
					Name: name,
					Kind: "RabbitMQ",
				},
			}
		default:
			logger.Logger.Warnf("unknown type for database instance: %s (type = %s)", name, utils.GetType(node))
			continue
		}
		logger.Logger.Infof("[APP] registered database instance %s", app.Databases[name].String())
	}
}

func (app *App) RegisterServiceNodes(specs map[*workflowspec.Service][]golang.Service) {
	servicesToSpec := app.createServiceNodes(specs)
	app.matchServiceEdges()
	app.parseServicesInfo()

	for _, node := range app.Services {
		serviceSpec := servicesToSpec[node]
		serviceArgs := specs[serviceSpec]
		app.MatchServiceDatabases(node, serviceSpec, serviceArgs)
	}


	for _, node := range app.Services {
		logger.Logger.Infof("[APP] registered service node %s with %d service(s) and %d database(s)", node.Name, len(node.Services), len(node.Databases))
	}
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
		logger.Logger.Warnf("[PARSER] APP service %s", node.Name)
		node.ParseImports()
		node.RegisterConstructor()
		node.RegisterStructure()
		node.ParseFields()
	}
}

func (app *App) ParseServiceNodes() {
	// parse service methods
	for _, node := range app.Services {
		node.ParseMethods()
	}
	// keep this order
	// parse service methods body
	for _, node := range app.Services {
		fmt.Printf("\n ################################## %s ##################################\n", node.Name)
		node.ParseMethodsBody()

		var parseCFGsHelper = func (node *service.ServiceNode, methods map[string]*service.ParsedFuncDecl, visibility string) {
			for _, method := range methods {
				fmt.Printf("\n[%s] ------------------- %s -------------------\n", strings.ToUpper(visibility), method)
				controlflow.GenerateMethodCFG(method)
				controlflow.ParseServiceMethodCFG(node, method)
				fmt.Printf("\n-------------------------------------------------------\n")
			}
		}
		parseCFGsHelper(node, node.ExposedMethods, "exposed")
		parseCFGsHelper(node, node.QueueHandlerMethods, "worker")
		parseCFGsHelper(node, node.InternalMethods, "internal")
	}
}


func (app *App) MatchServiceDatabases(serviceNode *service.ServiceNode, serviceSpec *workflowspec.Service, serviceArgs []golang.Service) {
	var constructorArgs []string
	// key: index in constructor for database argument
	// value: database instance to be referenced
	dbInstancesConstructorIdx := make(map[int]types.DatabaseInstance)
	for idx, arg := range serviceArgs {
		_, isServiceIR := arg.(*workflow.WorkflowClient)
		databaseInstance, isRegisteredDb := app.Databases[getShortDbInstanceName(arg.Name())]
		// if it is not a service IR and it is a registered database instance in the app
		// then we save the instance and the index of the argument for the service constructor
		if !isServiceIR && isRegisteredDb {
			// args don't count with golang context whose index 0 is reserved to
			dbInstancesConstructorIdx[idx+1] = databaseInstance
			serviceNode.Databases[databaseInstance.GetName()] = databaseInstance
		}
	}
	for _, arg := range serviceSpec.Constructor.Arguments {
		constructorArgs = append(constructorArgs, arg.Name)
	}
	serviceNode.ParseConstructor(constructorArgs, dbInstancesConstructorIdx)
}

func (app *App) getOrCreatePackage(name string) *types.Package {
	if pkg, ok := app.Packages[name]; ok {
		return pkg
	}
	pkg := &types.Package{
		Name: 				name,
		DeclaredTypes: 		make(map[string]types.Type),
		DeclaredVariables: 	make(map[string]types.Variable),
	}
	app.Packages[name] = pkg
	return pkg
}

func getConstructorNameFromSpec(spec *workflowspec.Service) string {
	for _, pkg := range spec.Iface.File.Package.Module.Packages {
		for _, f := range pkg.Funcs {
			if workflowspec.IsConstructorOfIface(f, spec.Iface) {
				return f.Name
			}
		}
	}
	logger.Logger.Fatalf("could not find constructor name from spec")
	return ""
}

func (app *App) createServiceNodes(specs map[*workflowspec.Service][]golang.Service) map[*service.ServiceNode]*workflowspec.Service {
	serviceSpec := make(map[*service.ServiceNode]*workflowspec.Service)
	logger.Logger.Debugf("[APP] loading #%d specs", len(specs))
	// services also include blueprint backends
	for spec, edges := range specs {
		fset := token.NewFileSet()
		filepath := spec.Iface.File.Name
		fileAst, err := parser.ParseFile(fset, filepath, nil, parser.ParseComments)
		if err != nil {
			logger.Logger.Fatalf("error parsing file %s: %s", filepath, err.Error())
		}
		file := &types.File{
			Ast: 		fileAst,
			Path: 		filepath,
			Package:  	app.getOrCreatePackage(fileAst.Name.Name),
			Imports:    make(map[string]*types.Import),
		}
		node := &service.ServiceNode{
			Name:                spec.Iface.Name,
			File:             	 file,
			Fields:              make(map[string]types.Field),
			Services:            make(map[string]*service.ServiceNode),
			Databases:           make(map[string]types.DatabaseInstance),
			ExposedMethods:      make(map[string]*service.ParsedFuncDecl),
			QueueHandlerMethods: make(map[string]*service.ParsedFuncDecl),
			InternalMethods:     make(map[string]*service.ParsedFuncDecl),
			ConstructorName: 	 getConstructorNameFromSpec(spec),
		}
		serviceSpec[node] = spec
		// add entry for methods that will be later parsed
		for _, m := range spec.Iface.Ast.Methods.List {
			node.ExposedMethods[m.Names[0].Name] = nil
		}

		// add entry in map but with nil value
		// after we have created all service nodes
		// then we are going to reference all edges correctly
		for _, edge := range edges {
			if workflowClient, ok := edge.(*workflow.WorkflowClient); ok {
				node.Services[workflowClient.ServiceType] = nil
			}
		}
		app.Services[node.Name] = node
		logger.Logger.Infof("[APP] created service node: %s", node.Name)
	}
	return serviceSpec
}
