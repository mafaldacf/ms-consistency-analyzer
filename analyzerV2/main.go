package main

import (
	"flag"
	"fmt"
	"slices"
	"time"

	"analyzer/pkg/app/app"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	controlflow "analyzer/pkg/parser"
	"analyzer/pkg/utils"
)

func main() {

	appName := flag.String("app", "", "The name of the application to be analyzed")
	xcyDetection := flag.Bool("xcy", false, "Enable detection of xcy dependencies and inconsistencies")
	cascadeDetection := flag.Bool("cascade", false, "Enable detection of the absence of cascading delete logic")
	allFlag := flag.String("all", "", fmt.Sprintf("Run analyzer for all applications: %v", utils.Apps))
	flag.Parse()
	if *allFlag == "true" || *allFlag == "True" || *allFlag == "1" {
		for _, app := range utils.Apps {
			logger.Logger.Infof(fmt.Sprintf("running analyzer for '%s'...", app))
			time.Sleep(1500 * time.Millisecond)
			initAnalyzer(app, *xcyDetection, *cascadeDetection)
			fmt.Println()
			fmt.Println()
		}
		return
	}
	if !slices.Contains(utils.Apps, *appName) {
		logger.Logger.Fatal(fmt.Sprintf("invalid app name (%s) must provide an application name using the -app flag for one of the available applications: %v", *appName, utils.Apps))

	}
	initAnalyzer(*appName, *xcyDetection, *cascadeDetection)
}

func initAnalyzer(appName string, xcyDetection bool, cascadeDetection bool) {
	servicesInfo, datastoreInstances, _ := blueprint.LoadWiring(appName)

	app := app.RegisterApp(appName, servicesInfo, datastoreInstances)
	controlflow.ParseRPCMethods(app)
	app.ToYaml()

	/* app.BuildServiceNodes()

	for _, pkg := range app.Packages {
		logger.Logger.Infof("package = %s", pkg.Name)
		for ident, obj := range pkg.TypesInfo.Defs {
			if varObj, ok := obj.(*golangtypes.Var); ok {
				logger.Logger.Debugf("%s (%s, %s): %v", ident.Name, utils.GetType(varObj.Type()), utils.GetType(varObj.Type().Underlying()), varObj.Type().String())
			}
		}
	} */
}
