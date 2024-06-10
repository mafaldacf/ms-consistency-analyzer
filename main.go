package main

import (
	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/detector"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"flag"
	"fmt"
	"os"

	"gopkg.in/yaml.v2"
)

func main() {

	appName := flag.String("app", "", "The name of the application to be analyzed")
	flag.Parse()
	if *appName != "postnotification" && *appName != "foobar" {
		logger.Logger.Fatal(fmt.Sprintf("invalid app name (%s) must provide an application name ('postnotification' or 'foobar') using the -app flag", *appName))
	}

	servicesInfo, databaseInstances, frontends := frameworks.BuildBlueprintAppInfo(*appName)

	app, err := app.Init(*appName, fmt.Sprintf("examples/%s/workflow/%s", *appName, *appName))
	if err != nil {
		return
	}
	app.RegisterDatabaseInstances(databaseInstances)
	app.RegisterServiceNodes(servicesInfo)
	app.ParseServiceNodes()

	abstractGraph := abstractgraph.Build(app, frontends)

	var requests []*detector.Request
	for _, entryNode := range abstractGraph.Nodes {
		request := detector.InitRequest(entryNode)
		request.TransverseRequestOperations()
		requests = append(requests, request)
	}

	fmt.Println()
	fmt.Println()
	for _, entryNode := range abstractGraph.Nodes {
		abstractgraph.BuildSchema(app, entryNode)
	}

	fmt.Println()
	fmt.Println()
	app.Save()
	abstractGraph.Save()
	for _, request := range requests {
		request.SaveInconsistencies(app.Name)
	}

	fmt.Println()

	saveServices(app)
	saveDatastores(app)
}

func saveDatastores(app *app.App) {
	schemaRepresentation := make(map[string]interface{})

	for _, ds := range app.Databases {
		schema := make(map[string]interface{})
		var fields []map[string]string
		for _, f := range ds.GetDatastore().Schema.Fields {
			fields = append(fields, map[string]string{"name": f.GetName(), "type": f.GetType()})
		}
		schema["backend"] = ds.GetDatastore().GetTypeString()
		schema["kind"] = ds.GetDatastore().GetKindString()
		schema["schema"] = fields
		schemaRepresentation[ds.GetName()] = schema
	}

	// Marshal the schema into YAML
	yamlData, _ := yaml.Marshal(schemaRepresentation)
	path := fmt.Sprintf("assets/%s/datastores.yaml", app.Name)
	os.WriteFile(path, yamlData, 0644)
}

func saveServices(app *app.App) {
	schemaRepresentation := make(map[string]interface{})

	for _, service := range app.Services {
		properties := make(map[string]interface{})
		
		var fields []map[string]string
		for _, f := range service.Fields {
			fields = append(fields, map[string]string{"name": f.GetName(), "type": f.GetTypeName()})
		}
		var services []string
		for _, childService := range service.Services {
			services = append(services, childService.Name)
		}
		var datastores []string
		for _, datastore := range service.Databases {
			datastores = append(datastores, datastore.GetName())
		}

		properties["fields"] = fields
		properties["services"] = services
		properties["datastores"] = datastores
		schemaRepresentation[service.Name] = properties
	}

	// Marshal the schema into YAML
	yamlData, _ := yaml.Marshal(schemaRepresentation)
	path := fmt.Sprintf("assets/%s/services.yaml", app.Name)
	os.WriteFile(path, yamlData, 0644)
}
