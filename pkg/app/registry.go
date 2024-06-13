package app

import (
	"analyzer/pkg/controlflow"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"fmt"
	"strings"
)

func (app *App) RegisterDatabaseInstances(instances []datastores.DatabaseInstance) {
	for _, instance := range instances {
		app.Databases[instance.GetName()] = instance
		logger.Logger.Infof("[APP] registered database instance %s", instance.String())
	}
}

func (app *App) RegisterServiceNodes(servicesInfo []*types.ServiceInfo) {
	app.createServiceNodes(servicesInfo)
	app.matchServiceEdges()
	app.buildServiceInfo()
	app.matchServiceDatabases(servicesInfo)
}

func (app *App) createServiceNodes(servicesInfo []*types.ServiceInfo) {
	logger.Logger.Debugf("[APP] loading #%d specs", len(servicesInfo))
	// services also include blueprint backends
	for _, info := range servicesInfo {
		pkg := app.GetPackage(info.PackageName)
		file := pkg.GetFile(info.Filepath)

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
		logger.Logger.Infof("[APP] created service node %s", node.Name)
	}
}

func (app *App) matchServiceEdges() {
	for _, node := range app.Services {
		for edgeName := range node.Services {
			node.Services[edgeName] = app.Services[edgeName]
		}
	}
}

func (app *App) buildServiceInfo() {
	for _, node := range app.Services {
		node.ParseImports()
		node.RegisterConstructor()
		node.RegisterStructure()
		node.ParseFields()
	}
}

func (app *App) BuildServiceNodes() {
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
		DeclaredTypes:     make(map[string]*types.UserType),
		DeclaredVariables: make(map[string]types.Variable),
	}
	app.Packages[name] = pkg
	return pkg
}
