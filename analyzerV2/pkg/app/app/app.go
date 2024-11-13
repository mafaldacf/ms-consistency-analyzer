package app

import (
	"fmt"
	"os"
	"path/filepath"

	"gopkg.in/yaml.v2"

	"analyzer/pkg/app/datastores"
	"analyzer/pkg/app/services"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
)

type App struct {
	Name        string
	PackagePath string
	Services    map[string]*services.Service
	Datastores  map[string]*datastores.Datastore
	// key is the package path
	// includes app packages, blueprint packages, and external (i.e., imported) packages
	Packages map[string]*types.Package `yaml:"packages"`
}

func (app *App) MarshalYAML() (interface{}, error) {
	return &struct {
		Name              string                           `yaml:"name"`
		PackagePath       string                           `yaml:"-"`
		Services          map[string]*services.Service     `yaml:"services"`
		Datastores        map[string]*datastores.Datastore `yaml:"datastores"`
		AppPackages       map[string]*types.Package        `yaml:"app_packages"`
		BuiltinPackages   map[string]*types.Package        `yaml:"builtin_packages"`
		BlueprintPackages map[string]*types.Package        `yaml:"blueprint_packages"`
		ExternalPackages  map[string]*types.Package        `yaml:"external_packages"`
	}{
		Name:              app.Name,
		PackagePath:       app.PackagePath,
		Services:          app.Services,
		Datastores:        app.Datastores,
		AppPackages:       app.GetAppPackages(),
		BlueprintPackages: app.GetBuiltinPackages(),
		BuiltinPackages:   app.GetBlueprintPackages(),
		ExternalPackages:  app.GetExternalPackages(),
	}, nil
}

func RegisterApp(name string, servicesInfo map[string]*frameworks.ServiceInfo, datastoreInstances []*datastores.Datastore) *App {
	app := &App{
		Name:        name,
		PackagePath: utils.LoadAppPath(name),
		Services:    make(map[string]*services.Service),
		Datastores:  make(map[string]*datastores.Datastore),
		Packages:    make(map[string]*types.Package),
	}

	logger.Logger.Infof("[APP INIT] loading app %s", app.PackagePath)

	app.registerPackages()
	app.registerDatastores(datastoreInstances)
	app.registerServices(servicesInfo)
	app.attachPackageMethodsToServices(servicesInfo)

	return app
}

func (app *App) GetService(name string) *services.Service {
	return app.Services[name]
}

func (app *App) GetDatastore(name string) *datastores.Datastore {
	return app.Datastores[name]
}

func (app *App) HasService(name string) bool {
	_, exists := app.Services[name]
	return exists
}

func (app *App) HasDatastore(name string) bool {
	_, exists := app.Datastores[name]
	return exists
}

func (app *App) AddPackage(path string, p *types.Package) {
	app.Packages[path] = p
}

func (app *App) GetPackage(path string) *types.Package {
	return app.Packages[path]
}

func (app *App) GetPackages() map[string]*types.Package {
	return app.Packages
}

func (app *App) GetBlueprintPackages() map[string]*types.Package {
	pkgs := make(map[string]*types.Package)
	for path, pkg := range app.Packages {
		if pkg.Type == types.BLUEPRINT {
			pkgs[path] = pkg
		}
	}
	return pkgs
}

func (app *App) GetAppPackages() map[string]*types.Package {
	pkgs := make(map[string]*types.Package)
	for path, pkg := range app.Packages {
		if pkg.Type == types.APP {
			pkgs[path] = pkg
		}
	}
	return pkgs
}

func (app *App) GetBuiltinPackages() map[string]*types.Package {
	pkgs := make(map[string]*types.Package)
	for path, pkg := range app.Packages {
		if pkg.Type == types.BUILTIN {
			pkgs[path] = pkg
		}
	}
	return pkgs
}

func (app *App) GetExternalPackages() map[string]*types.Package {
	pkgs := make(map[string]*types.Package)
	for path, pkg := range app.Packages {
		if pkg.Type == types.EXTERNAL {
			pkgs[path] = pkg
		}
	}
	return pkgs
}

func (app *App) ToYaml() {
	path := fmt.Sprintf("output/%s/app.yaml", app.Name)

	dir := filepath.Dir(path)
	err := os.MkdirAll(dir, 0755)
	if err != nil {
		logger.Logger.Fatalf("[APP] error creating directories for %s: %s", dir, err.Error())
	}

	file, err := os.OpenFile(path, os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0600)
	if err != nil {
		logger.Logger.Fatalf("[APP] error opening or creating file: %v", err)
	}
	defer file.Close()

	enc := yaml.NewEncoder(file)
	err = enc.Encode(app)
	if err != nil {
		logger.Logger.Fatalf("[APP] error converting app to yaml: %s", err.Error())
	}

	logger.Logger.Infof("[APP] successfuly saved app to %s", path)
}
