package app

import (
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
)

type App struct {
	Name      string
	Path      string
	Services  map[string]*service.ServiceNode
	Databases map[string]datastores.DatabaseInstance
	Packages  map[string]*types.Package
}

// MarshalJSON is used by app.Save()
func (app *App) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string                                 `json:"name"`
		Services  map[string]*service.ServiceNode        `json:"services"`
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

func Init(name string, path string) (*App, error) {
	fullPath, err := filepath.Abs(path)
	if err != nil {
		msg := fmt.Sprintf("error fetching full path for %s", path)
		logger.Logger.Error(msg)
		return nil, fmt.Errorf(msg)
	}
	app := &App{
		Name:      name,
		Path:      fullPath,
		Services:  make(map[string]*service.ServiceNode),
		Databases: make(map[string]datastores.DatabaseInstance),
		Packages:  make(map[string]*types.Package),
	}
	logger.Logger.Infof("[APP] initialized app at %s", app.Path)
	return app, nil
}

func (app *App) Save() {
	// print in JSON format
	// https://omute.net/editor
	path := fmt.Sprintf("assets/%s/app.json", app.Name)
	file, err := os.Create(path)
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()
	data, err := json.MarshalIndent(app, "", "  ")
	if err != nil {
		logger.Logger.Error("error marshaling json:", err)
		return
	}
	file.Write(data)
	logger.Logger.Infof("[JSON] app saved at %s", path)
}

func (app *App) Yaml() map[string]interface{} {
	data := make(map[string]interface{})
	for _, p := range app.Packages {
		data[p.Name] = p.Yaml()
	}
	return data
}
