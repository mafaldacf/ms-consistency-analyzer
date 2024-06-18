package app

import (
	"fmt"
	"strings"

	"analyzer/pkg/utils"
)

// -------
// Dumpers
// -------

func (app *App) Dump() {
	app.dumpYamlPackages()
	app.dumpYamlDatastores()
	app.dumpYamlServices()
	app.dumpYamlControlflow()
}

func (app *App) dumpYamlPackages() {
	data := make(map[string]utils.OrderedProperties)
	propsPackages := utils.NewOrderedPropertyList()
	// blueprint
	blueprintPackages := make(map[string]interface{})
	for _, p := range app.BlueprintPackages {
		blueprintPackages[p.Name] = p.DumpShortYaml()
	}
	propsPackages.AddOrderedProperty("blueprint", blueprintPackages)
	// application
	appPackages := make(map[string]interface{})
	for _, p := range app.Packages {
		appPackages[p.Name] = p.DumpYaml()
	}
	propsPackages.AddOrderedProperty("application", appPackages)
	// save all
	data["packages"] = propsPackages.Result()
	utils.DumpToYamlFile(data, app.Name, "packages")
}

func (app *App) dumpYamlDatastores() {
	data := make(map[string]utils.OrderedProperties)
	for _, datastore := range app.Databases {
		schema := utils.NewOrderedPropertyList()

		var fields []map[string]string
		for _, f := range datastore.GetDatastore().Schema.Fields {
			fields = append(fields, map[string]string{f.GetName(): f.GetType()})
		}
		schema.AddOrderedProperty("fields", fields)

		var unfoldedFields []map[string]string
		for _, f := range datastore.GetDatastore().Schema.UnfoldedFields {
			unfoldedFields = append(unfoldedFields, map[string]string{f.GetName(): f.GetType()})
		}
		schema.AddOrderedProperty("unfolded_fields", unfoldedFields)

		var foreignKeys []map[string]string
		for _, f := range datastore.GetDatastore().Schema.ForeignKeys {
			foreignKeys = append(foreignKeys, map[string]string{f.GetName(): strings.ToUpper(f.Datastore) + "." + f.Reference.GetName()})
		}
		schema.AddOrderedProperty("foreign_keys", foreignKeys)

		props := utils.NewOrderedPropertyList()
		props.AddOrderedProperty("type", datastore.GetDatastore().GetTypeString())
		props.AddOrderedProperty("kind", datastore.GetDatastore().GetKindString())
		props.AddOrderedProperty("schema", schema.Result())
		data[strings.ToUpper(datastore.GetName())] = props.Result()
	}
	utils.DumpToYamlFile(data, app.Name, "datastores")
}

func (app *App) dumpYamlServices() {
	data := make(map[string]utils.OrderedProperties)
	for _, service := range app.Services {
		fields := make(map[string]string)
		for _, f := range service.Fields {
			fields[f.GetName()] = f.GetTypeName()
		}
		services := make(map[string]string)
		for _, childService := range service.Services {
			services[childService.Name] = childService.ServiceShortPath()
		}
		datastores := make(map[string]string)
		for _, datastore := range service.Databases {
			datastores[datastore.GetName()] = datastore.GetTypeName()
		}

		props := utils.NewOrderedPropertyList()
		props.AddOrderedProperty("fields", fields)
		props.AddOrderedProperty("services", services)
		props.AddOrderedProperty("datastores", datastores)
		data[service.Name] = props.Result()
	}
	utils.DumpToYamlFile(data, app.Name, "services")
}

func (app *App) dumpYamlControlflow() {
	for name, service := range app.Services {
		data := service.Yaml()
		utils.DumpToYamlFile(data, app.Name, fmt.Sprintf("controlflow/%s", strings.ToLower(name)))
	}
}
