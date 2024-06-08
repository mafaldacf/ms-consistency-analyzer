package app

import (
	"analyzer/pkg/controlflow"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"encoding/json"
	"fmt"
	"go/parser"
	"go/token"
	"os"
	"path/filepath"
	"strings"
)

type App struct {
	Name      string                                 `json:"app_name,omitempty"`
	Path      string                                 `json:"-"`
	Services  map[string]*service.ServiceNode        `json:"app_services,omitempty"`
	Databases map[string]datastores.DatabaseInstance `json:"app_databases,omitempty"`
	Packages  map[string]*types.Package              `json:"packages,omitempty"`
}

// MarshalJSON is used by app.Save()
func (app *App) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string                                 `json:"name"`
		Services  map[string]*service.ServiceNode        `json:"app_services"`
		Databases map[string]datastores.DatabaseInstance `json:"app_databases"`
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
		Databases: make(map[string]datastores.DatabaseInstance),
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

func (app *App) RegisterDatabaseInstances(instances []datastores.DatabaseInstance) {
	for _, instance := range instances {
		app.Databases[instance.GetName()] = instance
		logger.Logger.Infof("[APP] registered database instance %s", instance.String())
	}
}

func (app *App) RegisterServiceNodes(servicesInfo []*types.ServiceInfo) {
	app.createServiceNodes(servicesInfo)
	app.matchServiceEdges()
	app.parseServicesInfo()
	app.matchServiceDatabases(servicesInfo)
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

		var parseCFGsHelper = func(node *service.ServiceNode, methods map[string]*service.ParsedFuncDecl, visibility string) {
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

func (app *App) matchServiceDatabases(servicesInfo []*types.ServiceInfo) {
	for _, info := range servicesInfo {
		node := app.Services[info.Name]
		paramsDBs := make(map[string]datastores.DatabaseInstance, 0)
		for param, instanceName := range info.ConstructorDBs {
			dbInstance := app.Databases[instanceName]
			paramsDBs[param] = dbInstance
			node.Databases[dbInstance.GetName()] = dbInstance
		}
		node.ParseConstructor(paramsDBs)
		logger.Logger.Infof("[APP] registered service node %s with %d service(s) and %d database(s)", node.Name, len(node.Services), len(node.Databases))
	}
}

func (app *App) getOrCreatePackage(name string) *types.Package {
	if pkg, ok := app.Packages[name]; ok {
		return pkg
	}
	pkg := &types.Package{
		Name:              name,
		DeclaredTypes:     make(map[string]types.Type),
		DeclaredVariables: make(map[string]types.Variable),
	}
	app.Packages[name] = pkg
	return pkg
}

func (app *App) createServiceNodes(servicesInfo []*types.ServiceInfo) {
	logger.Logger.Debugf("[APP] loading #%d specs", len(servicesInfo))
	// services also include blueprint backends
	for _, info := range servicesInfo {
		fset := token.NewFileSet()
		filepath := info.Filepath
		fileAst, err := parser.ParseFile(fset, filepath, nil, parser.ParseComments)
		if err != nil {
			logger.Logger.Fatalf("error parsing file %s: %s", filepath, err.Error())
		}
		file := &types.File{
			Ast:     fileAst,
			Path:    filepath,
			Package: app.getOrCreatePackage(fileAst.Name.Name),
			Imports: make(map[string]*types.Import),
		}
		node := &service.ServiceNode{
			Name:                info.Name,
			File:                file,
			Fields:              make(map[string]types.Field),
			Services:            make(map[string]*service.ServiceNode),
			Databases:           make(map[string]datastores.DatabaseInstance),
			ExposedMethods:      make(map[string]*service.ParsedFuncDecl),
			QueueHandlerMethods: make(map[string]*service.ParsedFuncDecl),
			InternalMethods:     make(map[string]*service.ParsedFuncDecl),
			ConstructorName:     info.ConstructorName,
		}

		// add entries to be later parsed
		for _, name := range info.Methods {
			node.ExposedMethods[name] = nil
		}
		for _, name := range info.Edges {
			node.Services[name] = nil
		}

		app.Services[node.Name] = node
		logger.Logger.Infof("[APP] created service node: %s", node.Name)
	}
}
