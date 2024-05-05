package main

import (
	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/frameworks/blueprint"
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
	"postnotification/wiring/specs"
)

func main() {

	appName := "postnotification"

	services, databases  := frameworks.BuildAndInspectIR(appName, specs.Docker)
	app, err := app.Init(appName, fmt.Sprintf("examples/%s/workflow/%s", appName, appName))
	if err != nil {
		return
	}
	app.RegisterDatabaseInstances(databases)
	app.RegisterServiceNodes(services)
	app.Save()
	entryPoints := []string{"UploadService"}
	abstractGraph := abstractgraph.Build(app, entryPoints)
	abstractGraph.Save()
}
