package app

import (
	"fmt"
	"sort"
	"strings"

	"analyzer/pkg/datastores"
	"analyzer/pkg/utils"
)

// -------
// Dumpers
// -------

func (app *App) Dump() {
	app.dumpYamlPackages()
	app.dumpYamlDatastores()
	app.dumpYamlDataflow()
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

func (app *App) dumpYamlDataflow() {
	data := make(map[string][]string)
	for k, lst := range app.PersistedVariables {
		var dataflow []string
		for _, v := range lst {
			for _, df := range v.GetVariableInfo().Dataflows {
				dataflow = append(dataflow, df.ShortString())
			}
		}
		data[k] = dataflow
	}
	utils.DumpToYamlFile(data, app.Name, "dataflow")
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

		propsForeignKeys := utils.NewOrderedPropertyList()
		for _, f := range datastore.GetDatastore().Schema.Fields {
			entry := f.(*datastores.Entry)
			if len(entry.References) > 0 {
				var lst []string
				for _, r := range entry.References {
					lst = append(lst, r.GetFullName())
				}
				sort.Strings(lst)
				propsForeignKeys.AddOrderedProperty(entry.GetName(), lst)
			}
		}
		for _, f := range datastore.GetDatastore().Schema.UnfoldedFields {
			entry := f.(*datastores.Entry)
			if len(entry.References) > 0 {
				var lst []string
				for _, r := range entry.References {
					lst = append(lst, r.GetFullName())
				}
				sort.Strings(lst)
				propsForeignKeys.AddOrderedProperty(entry.GetName(), lst)
			}
		}
		schema.AddOrderedProperty("foreign_fields", propsForeignKeys.Result())

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
