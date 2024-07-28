package app

import (
	"fmt"
	"strings"

	"github.com/golang-collections/collections/stack"

	"analyzer/pkg/controlflow"
	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/logger"
	"analyzer/pkg/lookup"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
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
	app.loadFieldsFromServicesConstructor(servicesInfo)
}

func (app *App) createServiceNodes(servicesInfo []*frameworks.ServiceInfo) {
	logger.Logger.Tracef("[APP] loading #%d specs", len(servicesInfo))
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
			PackageMethods:      make(map[string]*types.ParsedMethod),
			ConstructorName:     info.ConstructorName,
			Type: &gotypes.ServiceType{
				Package: pkg.GetName(),
				Name:    info.Name,
			},
			Contexts: stack.New(),
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
		lookup.ParseImports(node.File)
		node.RegisterConstructor()
		node.RegisterImplStructure()
		node.ParseFields()
	}
}

func (app *App) BuildServiceNodes() {
	// 1. attach all methods to corresponding services
	for _, node := range app.Services {
		serviceImplementedMethods := node.AttachParsedMethods()
		for _, method := range serviceImplementedMethods {
			controlflow.InitServiceReceiverFieldsForParsedCFG(node, method)
		}
	}
	// 2. attach all package methods that have no service assigned
	for _, node := range app.Services {
		node.AttachAllPackageMethods()
	}

	var parser = func(node *service.Service, methods map[string]*types.ParsedMethod, visibility string) {
		for _, method := range methods {
			fmt.Println("----------------------------------------------------------------------------------------------------------------------------------")
			fmt.Println("----------------------------------------------------------------------------------------------------------------------------------")
			logger.Logger.Infof("[PARSER - %s] [%s] %s", strings.ToUpper(visibility), node.GetName(), method)
			fmt.Println("----------------------------------------------------------------------------------------------------------------------------------")
			controlflow.ParseServiceMethodCFG(node, method)
			fmt.Println()
		}
	}

	// 3. parse all attached methods for each service
	for _, node := range app.Services {
		parser(node, node.ExposedMethods, "exposed")
		parser(node, node.InternalMethods, "internal") // internal already contains workers
		parser(node, node.PackageMethods, "package")
	}
}

func (app *App) loadFieldsFromServicesConstructor(servicesInfo []*frameworks.ServiceInfo) {
	logger.Logger.Infof("[APP] loading fields for services constructors")
	for _, info := range servicesInfo {
		service := app.Services[info.Name]
		paramsDBs := make(map[string]datastores.DatabaseInstance, 0)
		for param, instanceName := range info.ConstructorDBs {
			dbInstance := app.Databases[instanceName]
			paramsDBs[param] = dbInstance
			service.Databases[dbInstance.GetName()] = dbInstance
		}
		service.AttachDatastoreInstances(paramsDBs)
		logger.Logger.Tracef("[APP] registered service node %s with %d service(s) and %d database(s)", service.Name, len(service.Services), len(service.Databases))
	}
}
