package main

import (
	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/detector"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"flag"
	"fmt"
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
	app.Save()
	abstractGraph.Save()
	for _, request := range requests {
		request.SaveInconsistencies(app.Name)
	}
}
