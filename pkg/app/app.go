package app

import (
	"encoding/json"
	"fmt"
	"path/filepath"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
)

type App struct {
	Name              string
	Path              string
	Services          map[string]*service.Service
	Databases         map[string]datastores.DatabaseInstance
	Packages          map[string]*types.Package
	BlueprintPackages map[string]*types.Package
}

// MarshalJSON is used by app.Save()
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

func (app *App) GetPackage(pkgName string) *types.Package {
	pkg, ok := app.Packages[pkgName]
	if !ok {
		logger.Logger.Fatalf("could not find package %s in app packages list %v", pkgName, app.Packages)
	}
	return pkg
}

func (app *App) GetServiceIfExists(name string) *service.Service {
	if service, ok := app.Services[name]; ok {
		return service
	}
	return nil
}

func Init(name string, path string) (*App, error) {
	fullPath, err := filepath.Abs(path)
	if err != nil {
		msg := fmt.Sprintf("error fetching full path for %s", path)
		logger.Logger.Error(msg)
		return nil, fmt.Errorf(msg)
	}
	app := &App{
		Name:              name,
		Path:              fullPath,
		Services:          make(map[string]*service.Service),
		Databases:         make(map[string]datastores.DatabaseInstance),
		Packages:          make(map[string]*types.Package),
		BlueprintPackages: make(map[string]*types.Package),
	}
	logger.Logger.Infof("[APP] initialized app at %s", app.Path)
	return app, nil
}
