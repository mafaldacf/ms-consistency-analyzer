package main

import (
	"flag"
	"fmt"

	"gopkg.in/yaml.v2"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/detector"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
)

func main() {

	appName := flag.String("app", "", "The name of the application to be analyzed")
	flag.Parse()
	switch *appName {
	case "postnotification", "foobar", "sockshop", "trainticket", "threechain2":
	default:
		logger.Logger.Fatal(fmt.Sprintf("invalid app name (%s) must provide an application name ('postnotification' or 'foobar') using the -app flag", *appName))
	}

	servicesInfo, databaseInstances, frontends := blueprint.BuildBlueprintAppInfo(*appName)

	app, err := app.Init(*appName, fmt.Sprintf("examples/%s/workflow/%s", *appName, *appName))
	if err != nil {
		return
	}
	app.ParsePackages(servicesInfo)
	app.RegisterDatabaseInstances(databaseInstances)
	app.RegisterServiceNodes(servicesInfo)
	app.BuildServiceNodes()
	//app.PreDump()
	//logger.Logger.Fatal("EXIT!")

	fmt.Println()
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" -------------------------------------------- BUILD ABSTRACT GRAPH -------------------------------------------- ")
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println()

	abstractGraph := abstractgraph.Build(app, frontends)

	//logger.Logger.Fatal("EXIT")

	fmt.Println()
	fmt.Println(" ----------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" -------------------------------------------- BUILD DATASTORES SCHEMA -------------------------------------------- ")
	fmt.Println(" ----------------------------------------------------------------------------------------------------------------- ")
	fmt.Println()

	for _, entryNode := range abstractGraph.Nodes {
		abstractgraph.BuildSchema(app, entryNode)
	}

	fmt.Println()
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" --------------------------------------- CHECK XCY - TAINTED APPROACH  ---------------------------------------- ")
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println()

	var requests []*detector.Request
	detectionModes := detector.GetAllDetectioModes()
	for _, entryNode := range abstractGraph.Nodes {
		for i, detectionMode := range detectionModes {
			request := detector.InitRequest(entryNode, detectionMode)
			fmt.Printf("\n\n------------------------- ENTRY NODE = %s -------------------------\n", entryNode.String())
			fmt.Printf("------------------------- (%d/%d) XCY DETECTOR MODE = %s -------------------------\n\n", i+1, len(detectionModes), request.DetectionModeName())
			request.InitTransversal()
			requests = append(requests, request)
		}
	}

	for _, request := range requests {
		request.DumpToYAMLFile(app.Name)
	}

	/* fmt.Println()
	fmt.Println(" ----------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" --------------------------------------------------- DUMPERS ----------------------------------------------------- ")
	fmt.Println(" ----------------------------------------------------------------------------------------------------------------- ")
	fmt.Println() */

	app.Dump()
	abstractGraph.Dump()

	fmt.Println()

	fmt.Println()
	fmt.Println("-----------------------------------------------------------------------------------------------------------------")
	fmt.Println("------------------------------------------------- XCY SUMMARY ---------------------------------------------------")
	fmt.Println("-----------------------------------------------------------------------------------------------------------------")
	fmt.Println()

	for _, request := range requests {
		if len(request.Inconsistencies) > 0 {
			data, _ := yaml.Marshal(request.DumpYaml(false))
			fmt.Println(string(data))
			fmt.Println("----------------------------------------------------------")
		}
	}
}
