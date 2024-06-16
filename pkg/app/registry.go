package app

import (
	"fmt"
	"strings"

	"analyzer/pkg/controlflow"
	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
)

func (app *App) RegisterDatabaseInstances(instances []datastores.DatabaseInstance) {
	for _, instance := range instances {
		app.Databases[instance.GetName()] = instance
		logger.Logger.Infof("[APP] registered database instance %s", instance.String())
	}
}

func (app *App) RegisterServiceNodes(servicesInfo []*frameworks.ServiceInfo) {
	app.createServiceNodes(servicesInfo)
	app.matchServiceEdges()
	app.buildServiceInfo()
	app.loadFieldsFromConstructor(servicesInfo)
}

func (app *App) createServiceNodes(servicesInfo []*frameworks.ServiceInfo) {
	logger.Logger.Debugf("[APP] loading #%d specs", len(servicesInfo))
	// services also include blueprint backends
	for _, info := range servicesInfo {
		pkg := app.GetPackage(info.Package)
		file := pkg.GetFile(info.Filepath)

		node := &service.Service{
			Name:                info.Name,
			File:                file,
			Fields:              make(map[string]types.Field),
			Services:            make(map[string]*service.Service),
			Databases:           make(map[string]datastores.DatabaseInstance),
			ExposedMethods:      make(map[string]*types.ParsedMethod),
			QueueHandlerMethods: make(map[string]*types.ParsedMethod),
			InternalMethods:     make(map[string]*types.ParsedMethod),
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

		var parser = func(node *service.Service, methods map[string]*types.ParsedMethod, visibility string) {
			for _, method := range methods {
				fmt.Printf("\n[%s] ------------------- %s -------------------\n", strings.ToUpper(visibility), method)
				controlflow.GenerateMethodCFG(method)
				controlflow.ParseServiceMethodCFG(node, method)
				fmt.Printf("\n-------------------------------------------------------\n")
			}
		}
		parser(node, node.ExposedMethods, "exposed")
		parser(node, node.QueueHandlerMethods, "worker")
		// internal already contains workers
		parser(node, node.InternalMethods, "internal")
	}
}

func (app *App) loadFieldsFromConstructor(servicesInfo []*frameworks.ServiceInfo) {
	for _, info := range servicesInfo {
		node := app.Services[info.Name]
		paramsDBs := make(map[string]datastores.DatabaseInstance, 0)
		for param, instanceName := range info.ConstructorDBs {
			dbInstance := app.Databases[instanceName]
			paramsDBs[param] = dbInstance
			node.Databases[dbInstance.GetName()] = dbInstance
		}
		node.ParseConstructorAndLoadFields(paramsDBs)
		logger.Logger.Infof("[APP] registered service node %s with %d service(s) and %d database(s)", node.Name, len(node.Services), len(node.Databases))
	}
}
