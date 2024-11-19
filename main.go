package main

import (
	"flag"
	"fmt"
	"slices"
	"time"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/detection/xcy"
	"analyzer/pkg/detection/cascade"
	"analyzer/pkg/detection/foreign_key"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

func main() {

	appName := flag.String("app", "", "The name of the application to be analyzed")
	xcyDetection := flag.Bool("xcy", false, "Enable detection of xcy dependencies and inconsistencies")
	foreignKeyDetection := flag.Bool("fk", false, "Enable detection of anomalies in foreign key constraints")
	cascadeDetection := flag.Bool("cascade", false, "Enable detection of the absence of cascading delete logic")
	allFlag := flag.String("all", "", fmt.Sprintf("Run analyzer for all applications: %v", utils.Apps))
	flag.Parse()
	if *allFlag == "true" || *allFlag == "True" || *allFlag == "1" {
		for _, app := range utils.Apps {
			logger.Logger.Infof(fmt.Sprintf("running analyzer for '%s'...", app))
			time.Sleep(1500 * time.Millisecond)
			initAnalyzer(app, *xcyDetection, *cascadeDetection, *foreignKeyDetection)
			fmt.Println()
			fmt.Println()
		}
		return
	}
	if !slices.Contains(utils.Apps, *appName) {
		logger.Logger.Fatal(fmt.Sprintf("invalid app name (%s) must provide an application name using the -app flag for one of the available applications: %v", *appName, utils.Apps))

	}
	initAnalyzer(*appName, *xcyDetection, *cascadeDetection, *foreignKeyDetection)
}

func initAnalyzer(appName string, xcyDetection bool, cascadeDetection bool, foreignKeyDetection bool) {
	servicesInfo, databaseInstances, frontends := blueprint.LoadWiring(appName)

	app, err := app.InitApp(appName, servicesInfo)
	if err != nil {
		return
	}
	app.RegisterPackages()
	app.RegisterDatastoreInstances(databaseInstances)
	app.RegisterServiceNodes(servicesInfo)
	app.BuildServiceNodes()
	/* app.PreDump()
	logger.Logger.Fatalf("EXIT!") */

	fmt.Println()
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" -------------------------------------------- BUILD ABSTRACT GRAPH -------------------------------------------- ")
	fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
	fmt.Println()

	abstractGraph := abstractgraph.Build(app, frontends)

	fmt.Println()
	fmt.Println(" ----------------------------------------------------------------------------------------------------------------- ")
	fmt.Println(" -------------------------------------------- BUILD DATASTORES SCHEMA -------------------------------------------- ")
	fmt.Println(" ----------------------------------------------------------------------------------------------------------------- ")
	fmt.Println()

	abstractgraph.BuildSchema(app, frontends, abstractGraph.Nodes)
	app.Dump()
	abstractGraph.Dump()
	fmt.Println()

	summary := "\n\n"

	if xcyDetection {
		fmt.Println()
		fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
		fmt.Println(" --------------------------------------- CHECK XCY - TAINTED APPROACH  ---------------------------------------- ")
		fmt.Println(" -------------------------------------------------------------------------------------------------------------- ")
		fmt.Println()
		
		var detectors []*xcy.Detector
		allDatastoresOps := xcy.NewDatastoreOps()

		detectionModes := xcy.GetAllDetectionModes()
		for _, entryNode := range abstractGraph.Nodes {
			for i, detectionMode := range detectionModes {
				detector := xcy.InitDetector(app, allDatastoresOps, detectionMode)
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
			//logger.Logger.Infof("MINIMIZING FOR DETECTOR %v", detector.Requests)
			for _, request := range detector.GetRequests() {
				detector.MinimizeDependecySets(request)
			}
		}
		
		var allResults string
		for _, detector := range detectors {
			detector.DumpYaml(app.Name)
			if detector.Inconsistencies > 0 {
				results := detector.Results()
				allResults += results + "\n\n"
				summary += results + "\n\n"
			}
		}
		xcy.Save(app.Name, allResults)
	}

	app.ResetAllDataflows()

	if cascadeDetection {
		fmt.Println()
		fmt.Println(" ------------------------------------------------------------------------------------------------------------------ ")
		fmt.Println(" --------------------------------------- CHECK ABSENCE OF CASCADING DELETE ---------------------------------------- ")
		fmt.Println(" ------------------------------------------------------------------------------------------------------------------ ")
		fmt.Println()
		detector := cascade.InitDetector(app, abstractGraph)
		detector.Run()
		results := detector.Results()
		summary += results + "\n\n"
	}

	if foreignKeyDetection {
		fmt.Println()
		fmt.Println(" ------------------------------------------------------------------------------------------------------------------ ")
		fmt.Println(" ----------------------------------- CHECK INTEGRITY ANOMALIES FOR FOREIGN KEYS ----------------------------------- ")
		fmt.Println(" ------------------------------------------------------------------------------------------------------------------ ")
		fmt.Println()
		detector := foreign_key.InitDetector(app, abstractGraph)
		detector.Run()
		results := detector.Results()
		summary += results + "\n\n"
	}

	bold_light_red := "\033[1;31m"
	fmt.Println(bold_light_red + summary)
}
