package main

import (
	"flag"
	"fmt"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/detector"
	bp "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
)

func main() {

	appName := flag.String("app", "", "The name of the application to be analyzed")
	flag.Parse()
	switch *appName {
	case "postnotification", "foobar", "sockshop", "trainticket":
	default:
		logger.Logger.Fatal(fmt.Sprintf("invalid app name (%s) must provide an application name ('postnotification' or 'foobar') using the -app flag", *appName))
	}

	servicesInfo, databaseInstances, frontends := bp.BuildBlueprintAppInfo(*appName)

	app, err := app.Init(*appName, fmt.Sprintf("examples/%s/workflow/%s", *appName, *appName))
	if err != nil {
		return
	}
	app.ParsePackages(servicesInfo)
	//app.Dump()
	app.RegisterDatabaseInstances(databaseInstances)
	app.RegisterServiceNodes(servicesInfo)
	app.BuildServiceNodes()

	fmt.Println()
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" -------------------------------------------- BUILD ABSTRACT GRAPH -------------------------------------------- ")
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println()
	app.Dump()

	abstractGraph := abstractgraph.Build(app, frontends)

	fmt.Println()
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" -------------------------------------------- CHECK XCY VIOLATIONS -------------------------------------------- ")
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println()

	var requests []*detector.Request
	for _, entryNode := range abstractGraph.Nodes {
		request := detector.InitRequest(entryNode)
		request.TransverseRequestOperations()
		requests = append(requests, request)
	}

	fmt.Println()
	fmt.Println(" ----------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" -------------------------------------------- BUILD DATASTORES SCHEMA -------------------------------------------- ")
	fmt.Println(" ----------------------------------------------------------------------------------------------------------------- ")
	fmt.Println()

	for _, entryNode := range abstractGraph.Nodes {
		abstractgraph.BuildSchema(app, entryNode)
	}

	app.Dump()
	abstractGraph.Dump()
	for _, request := range requests {
		request.SaveInconsistencies(app.Name)
	}

	fmt.Println()
}
