package main

import (
	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/controlflow"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/logger"
	"fmt"
	"postnotification/wiring/specs"

	// this needs to target the root of the app otherwise (and then replace the path in the go.mod file)
	// otherwise the blueprint workflow plugin won't be able to locate the package
	// more specifically, this occurs at
	// blueprint/plugins/workflow/workflowspec/cache.go GetService() -> cached.get()
	// blueprint/plugins/workflow/workflowspec/spec.go  get() -> pkg, pkgExists := mod.Packages[pkgName]
	// the pkgName used as argument is the package name imported here '
	// 		analyzer/apps/postnotification/workflow/postnotification'
	// but the existing packages in the mod.Package represents the root of the app
	// 		'postnotification/workflow/postnotification'
	"postnotification/workflow/postnotification"
	"postnotification/workflow/postnotification/dummy"

	"github.com/blueprint-uservices/blueprint/blueprint/pkg/wiring"
	"github.com/blueprint-uservices/blueprint/plugins/cmdbuilder"
)

type BlueprintType interface {
}

func main() {
	dummyServiceSpec, err0 := frameworks.GetBlueprintServiceSpec[dummy.DummyService]()
	storageServiceSpec, err1 := frameworks.GetBlueprintServiceSpec[postnotification.StorageService]()
	notifyServiceSpec, err2 := frameworks.GetBlueprintServiceSpec[postnotification.NotifyService]()
	uploadServiceSpec, err3 := frameworks.GetBlueprintServiceSpec[postnotification.UploadService]()

	// Build a supported wiring spec
	builder := cmdbuilder.CmdBuilder{}
	builder.Name = "PostNotification"
	builder.Registry = make(map[string]cmdbuilder.SpecOption)
	builder.Registry[specs.Docker.Name] = specs.Docker
	builder.Spec = specs.Docker

	logger.Logger.Warnf("NewWiringSpec!")
	builder.Wiring = wiring.NewWiringSpec(builder.Name)
	if builder.Wiring == nil {
		return
	}
	nodesToBuild, err := builder.Spec.Build(builder.Wiring)
	if err != nil {
		return
	}

	// Construct the IR
	builder.IR, err = builder.Wiring.BuildIR(nodesToBuild...)
	if err != nil {
		return
	}
	fmt.Sprintf("IR: %v", builder.IR)

	if err0 != nil || err1 != nil || err2 != nil || err3 != nil {
		return
	}
	app, err := app.Init("examples/postnotification/workflow/postnotification")
	if err != nil {
		return
	}
	err = app.AddServiceNode(dummyServiceSpec)
	if err != nil {
		return
	}
	err = app.AddServiceNode(storageServiceSpec, dummyServiceSpec)
	if err != nil {
		return
	}
	err = app.AddServiceNode(notifyServiceSpec, storageServiceSpec)
	if err != nil {
		return
	}
	err = app.AddServiceNode(uploadServiceSpec, storageServiceSpec, notifyServiceSpec)
	if err != nil {
		return
	}

	for _, node := range app.Services {
		fmt.Printf("\n######################## %s ########################\n", node.Name)
		node.ParseImports()
		node.ParseStructFields()
		node.ParseMethods()
		for _, method := range node.ExposedMethods {
			fmt.Printf("\n------------------------ %s ------------------------\n", method)
			node.ParseMethodBodyCalls(method)
			parsedCfg, err := controlflow.ParseCFG(node, method)
			if err != nil {
				return
			}
			controlflow.VisitServiceMethodCFG(parsedCfg, method)
		}
		if node.ImplementsQueue {
			node.ParseQueueImplementation()
		}
	}
	entryPoints := []string{"UploadService"}
	abstractGraph := abstractgraph.Build(app, entryPoints)
	abstractGraph.Save()
}
