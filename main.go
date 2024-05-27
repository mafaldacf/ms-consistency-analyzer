package main

import (
	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/detector"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"flag"
	"fmt"

	// this needs to target the root of the app otherwise (and then replace the path in the go.mod file)
	// otherwise the blueprint workflow plugin won't be able to locate the package
	// more specifically, this occurs at
	// blueprint/plugins/workflow/workflowspec/cache.go GetService() -> cached.get()
	// blueprint/plugins/workflow/workflowspec/spec.go  get() -> pkg, pkgExists := mod.Packages[pkgName]
	// the pkgName used as argument is the package name imported here '
	// 		analyzer/apps/postnotification/workflow/postnotification'
	// but the existing packages in the mod.Package represents the root of the app
	// 		'postnotification/workflow/postnotification'
	fb_specs "github.com/blueprint-uservices/blueprint/examples/foobar/wiring/specs"
	pn_specs "github.com/blueprint-uservices/blueprint/examples/postnotification/wiring/specs"
	"github.com/blueprint-uservices/blueprint/plugins/cmdbuilder"
)

func main() {

	appName := flag.String("app", "", "The name of the application to be analyzed")
	flag.Parse()
	if *appName != "postnotification" && *appName != "foobar" {
		logger.Logger.Fatal(fmt.Sprintf("invalid app name (%s) must provide an application name ('postnotification' or 'foobar') using the -app flag", *appName))
	}

	var spec cmdbuilder.SpecOption
	if *appName == "postnotification" {
		spec = pn_specs.Docker
	} else if *appName == "foobar" {
		spec = fb_specs.Docker
	}

	services, databases, frontends := frameworks.BuildAndInspectIR(*appName, spec)
	app, err := app.Init(*appName, fmt.Sprintf("examples/%s/workflow/%s", *appName, *appName))
	if err != nil {
		return
	}
	app.RegisterDatabaseInstances(databases)
	app.RegisterServiceNodes(services)
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
