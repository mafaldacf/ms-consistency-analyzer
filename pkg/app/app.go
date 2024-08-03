package app

import (
	"encoding/json"
	"slices"

	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

type App struct {
	Name              string
	PackagePath       string
	Services          map[string]*service.Service
	Databases         map[string]datastores.DatabaseInstance
	AppPackages       map[string]*types.Package // key is package name (FIXME: should be path actually)
	BlueprintPackages map[string]*types.Package // key is package name (FIXME: should be path actually)
	ExternalPackages  map[string]*types.Package // key is package name (FIXME: should be path actually)
	TaintedVariables  map[string][]variables.Variable
	ServiceTypes      map[string]*gotypes.ServiceType
}

func (app *App) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string                                 `json:"name"`
		Services  map[string]*service.Service            `json:"services"`
		Databases map[string]datastores.DatabaseInstance `json:"datastores"`
	}{
		Name:      app.Name,
		Services:  app.Services,
		Databases: app.Databases,
	})
}

func (app *App) String() string {
	str, _ := app.MarshalJSON()
	return string(str)
}

func (app *App) GetDatastoreInstance(name string) datastores.DatabaseInstance {
	if instance, ok := app.Databases[name]; ok {
		return instance
	}
	logger.Logger.Fatalf("[APP] could not find datastore instance for name (%s)", name)
	return nil
}

func (app *App) GetAllAppPackages() []*types.Package {
	var allPkgs []*types.Package
	for _, pkg := range app.AppPackages {
		allPkgs = append(allPkgs, pkg)
	}
	return allPkgs
}

// this is just an helper to later print tainted dataflow in yaml files
func (app *App) AddTaintedVariableIfNotExists(fieldName string, variable variables.Variable) {
	if !slices.Contains(app.TaintedVariables[fieldName], variable) {
		app.TaintedVariables[fieldName] = append(app.TaintedVariables[fieldName], variable)
	}
}

func (app *App) GetAppPackages() map[string]*types.Package {
	return app.AppPackages
}

func (app *App) GetBlueprintPackages() map[string]*types.Package {
	return app.BlueprintPackages
}

func (app *App) AddAppPackage(name string, p *types.Package) {
	app.AppPackages[name] = p
}

func (app *App) AddBlueprintPackage(name string, p *types.Package) {
	app.BlueprintPackages[name] = p
}

func (app *App) AddExternalPackage(name string, p *types.Package) {
	app.ExternalPackages[name] = p
}

func (app *App) GetPackage(pkgName string) *types.Package {
	pkg, ok := app.AppPackages[pkgName]
	if !ok {
		packagesStr := ""
		for k, t := range app.AppPackages {
			packagesStr += "- " + k + ": " + t.String() + "\n"
		}
		logger.Logger.Fatalf("could not find package (%s) in app packages list\n%s", pkgName, packagesStr)
	}
	return pkg
}

func (app *App) GetServiceIfExists(name string) *service.Service {
	if service, ok := app.Services[name]; ok {
		return service
	}
	return nil
}

func InitApp(name string, servicesInfo []*frameworks.ServiceInfo) (*App, error) {
	app := &App{
		Name:              name,
		PackagePath:       utils.LoadAppPath(name),
		Services:          make(map[string]*service.Service),
		Databases:         make(map[string]datastores.DatabaseInstance),
		AppPackages:       make(map[string]*types.Package),
		BlueprintPackages: make(map[string]*types.Package),
		ExternalPackages:  make(map[string]*types.Package),
		TaintedVariables:  make(map[string][]variables.Variable),
		ServiceTypes:      make(map[string]*gotypes.ServiceType),
	}

	for _, info := range servicesInfo {
		app.ServiceTypes[info.Name] = &gotypes.ServiceType{
			Name:        info.Name,
			PackagePath: info.PackagePath,
		}
	}
	logger.Logger.Infof("[APP INIT] loading app %s", app.PackagePath)
	return app, nil
}
