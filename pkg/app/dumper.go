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
	app.dumpDiGraph()
	app.dumpYamlPackages()
	app.dumpYamlDatastores()
	app.dumpYamlDataflow()
	app.dumpYamlServices()
	app.dumpYamlControlflow()
	app.dumpYamlCalls()
}

func (app *App) PreDump() {
	app.dumpYamlPackages()
	app.dumpYamlServices()
	app.dumpYamlControlflow()
	app.dumpYamlCalls()
}

func (app *App) dumpDiGraph() {
	type node struct {
		Id   string `json:"id"`
		Type string `json:"type"`
	}
	type edge struct {
		Caller string `json:"caller"`
		Callee string `json:"callee"`
	}
	type digraph struct {
		Nodes []node `json:"nodes"`
		Edges []edge `json:"edges"`
	}

	var nodeTypeOrder = map[string]int{
		"client":    1,
		"service":   2,
		"datastore": 3,
	}
	var sortNodes = func(nodes []node) {
		sort.Slice(nodes, func(i, j int) bool {
			if nodes[i].Type != nodes[j].Type {
				return nodeTypeOrder[nodes[i].Type] < nodeTypeOrder[nodes[j].Type]
			}
			return nodes[i].Id < nodes[j].Id
		})
	}
	var sortEdges = func(edges []edge) {
		sort.Slice(edges, func(i, j int) bool {
			if edges[i].Caller != edges[j].Caller {
				return edges[i].Caller < edges[j].Caller
			}
			return edges[i].Callee < edges[j].Callee
		})
	}

	nodes := []node{}
	edges := []edge{}
	servicesVisited := make(map[string]bool)

	// get services list
	for _, s := range app.Services {
		servicesVisited[s.GetName()] = true
		nodes = append(nodes, node{Id: s.GetName(), Type: "service"})
	}

	// get and add edges
	for _, service := range app.Services {
		for _, callee := range service.Services {
			if _, exists := servicesVisited[callee.GetName()]; exists {
				edges = append(edges, edge{Caller: service.GetName(), Callee: callee.GetName()})
			}
		}
	}

	// datastores
	datastores := make(map[string]bool)
	for _, service := range app.Services {
		for _, ds := range service.Databases {
			if _, exists := datastores[ds.String()]; !exists {
				nodes = append(nodes, node{Id: ds.String(), Type: "datastore"})
				datastores[ds.String()] = true
			}
			edges = append(edges, edge{Caller: service.GetName(), Callee: ds.String()})
		}
	}

	sortNodes(nodes)
	sortEdges(edges)
	outputGraph := digraph{Nodes: nodes, Edges: edges}
	utils.DumpToJSONFile(outputGraph, app.Name, "digraphs/app_graph")
}

func (app *App) dumpYamlPackages() {
	// blueprint
	blueprintPackages := make(map[string]interface{})
	for _, p := range app.BlueprintPackages {
		blueprintPackages[p.Name] = p.DumpBlueprintYaml()
	}
	utils.DumpToYamlFile(blueprintPackages, app.Name, "packages/blueprint")

	// external
	externalPackages := make(map[string]interface{})
	for _, p := range app.ExternalPackages {
		externalPackages[p.Name] = p.DumpExternalYaml()
	}
	utils.DumpToYamlFile(externalPackages, app.Name, "packages/external")

	// application
	appPackages := make(map[string]interface{})
	for _, p := range app.Packages {
		appPackages[p.Name] = p.DumpYaml()
	}
	utils.DumpToYamlFile(appPackages, app.Name, "packages/app")
}

func (app *App) dumpYamlDataflow() {
	data := make(map[string][]string)
	for k, lst := range app.TaintedVariables {
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
		utils.DumpToYamlFile(data, app.Name, fmt.Sprintf("controlflow/services/%s", strings.ToLower(name)))
	}

	for _, p := range app.Packages {
		pkgData := make(map[string]interface{})
		for _, m := range p.ParsedMethods {
			data := m.Yaml()
			pkgData[m.LongString()] = data
		}
		utils.DumpToYamlFile(pkgData, app.Name, fmt.Sprintf("controlflow/packages/%s", strings.ToLower(p.Name)))
	}
}

func (app *App) dumpYamlCalls() {
	for name, service := range app.Services {
		data := service.YamlCalls()
		utils.DumpToYamlFile(data, app.Name, fmt.Sprintf("calls/%s", strings.ToLower(name)))
	}
}
