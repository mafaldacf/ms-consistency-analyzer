package main

import (
	"flag"
	"fmt"
	"time"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/detection"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
)

func main() {

	appName := flag.String("app", "", "The name of the application to be analyzed")
	allFlag := flag.String("all", "", "Run analyzer for all applications ('postnotification', 'shopping_app', 'sockshop2', 'trainticket')")
	flag.Parse()
	if *allFlag == "true" || *allFlag == "True" || *allFlag == "1" {
		var apps = []string{"trainticket", "postnotification_simple", "postnotification", "shopping_app", "sockshop2", "foobar"}
		for _, app := range apps {
			logger.Logger.Infof(fmt.Sprintf("running analyzer for '%s'...", app))
			time.Sleep(1500 * time.Millisecond)
			initAnalyzer(app)
			fmt.Println()
			fmt.Println()
		}
		return
	}
	switch *appName {
	case "postnotification", "trainticket", "shopping_app", "sockshop2", "foobar", "dsb_hotel", "dsb_sn", "postnotification_simple":
	default:
		logger.Logger.Fatal(fmt.Sprintf("invalid app name (%s) must provide an application name ('postnotification', 'trainticket', 'shopping_app', 'sockshop2', 'foobar', 'dsb_hotel', 'dsb_sn') using the -app flag", *appName))
	}
	initAnalyzer(*appName)
}

func initAnalyzer(appName string) {
	servicesInfo, databaseInstances, frontends := blueprint.BuildBlueprintAppInfo(appName)

	app, err := app.InitApp(appName, servicesInfo)
	if err != nil {
		return
	}
	app.RegisterPackages()
	app.RegisterDatastoreInstances(databaseInstances)
	app.RegisterServiceNodes(servicesInfo)
	app.BuildServiceNodes()
	app.PreDump()

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

	var detectors []*detection.Detector
	allDatastoresOps := detection.NewDatastoreOps()

	detectionModes := detection.GetAllDetectioModes()
	for _, entryNode := range abstractGraph.Nodes {
		for i, detectionMode := range detectionModes {
			detector := detection.InitDetector(allDatastoresOps, detectionMode)
			request := detector.InitRequest(entryNode)
			fmt.Printf("\n\n-------------------- ENTRY NODE = %s.%s --------------------\n", entryNode.GetCallee(), entryNode.GetName())
			fmt.Printf("-------------------- (%d/%d) XCY DETECTOR MODE = %s --------------------\n\n", i+1, len(detectionModes), detector.DetectionModeName())
			detector.InitXCYRequestTransversal(request)
			allDatastoresOps = detector.GetDatastoreOps()
			detectors = append(detectors, detector)
		}
	}
	fmt.Println()

	for _, detector := range detectors {
		detector.UpdateDatastoreOps(allDatastoresOps)
		logger.Logger.Infof("MINIMIZING FOR DETECTOR %v", detector.Requests)
		for _, request := range detector.GetRequests() {
			detector.MinimizeDependecySets(request)
		}
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

	for _, detector := range detectors {
		detector.DumpYaml(app.Name)
		detector.PrintResults()
	}
}
