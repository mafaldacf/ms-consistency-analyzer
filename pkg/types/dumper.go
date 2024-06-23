package types

import (
	"fmt"
	"slices"
	"sort"

	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

// ----
// CFGS
// ----

func (cfg *CFG) Yaml() map[string]interface{} {
	data := make(map[string]interface{})
	for _, block := range cfg.ParsedBlocks {
		data[block.Block.String()] = block.Yaml()
	}
	return data
}

// ------
// BLOCKS
// ------

func (block *Block) Yaml() []string {
	data := []string{}
	for _, v := range block.Vars {
		dfs := append(v.GetVariableInfo().Dataflows, v.GetVariableInfo().IndirectDataflows...)
		if len(dfs) > 0 {
			var dbs []string
			str := ""
			for _, df := range dfs {
				if !slices.Contains(dbs, df.Field.GetFullName()) {
					dbs = append(dbs, df.Field.GetFullName())
				}
			}
			for i, db := range dbs {
				str += db
				if i < len(dbs)-1 {
					str += ", "
				}
			}
			data = append(data, fmt.Sprintf("%s (%s) ----> (TAINTED @ %s)", v.String(), variables.GetVariableTypeAndTypeString(v), str))
		} else {
			data = append(data, fmt.Sprintf("%s (%s)", v.String(), variables.GetVariableTypeAndTypeString(v)))
		}
	}
	return data
}

// --------
// PACKAGES
// --------

// for blueprint packages
func (p *Package) DumpShortYaml() utils.OrderedProperties {
	propsData := utils.NewOrderedPropertyList()

	// metadata
	propsMetadata := utils.NewOrderedPropertyList()
	propsMetadata.AddOrderedProperty("package", p.Name)
	propsMetadata.AddOrderedProperty("package path", p.PackagePath)
	propsMetadata.AddOrderedProperty("module", p.Module)
	// save metadata
	propsData.AddOrderedProperty("metadata", propsMetadata.Result())

	// declared types
	declaredTypes := []string{}
	for _, e := range p.DeclaredTypes {
		declaredTypes = append(declaredTypes, e.LongString())
	}
	sort.Strings(declaredTypes)
	propsData.AddOrderedProperty("declared types", declaredTypes)

	// datastore types
	datastoreTypes := []string{}
	for _, e := range p.DatastoreTypes {
		datastoreTypes = append(datastoreTypes, e.LongString())
	}
	sort.Strings(datastoreTypes)
	propsData.AddOrderedProperty("datastore types", datastoreTypes)

	// save final data
	return propsData.Result()
}

func (p *Package) DumpYaml() utils.OrderedProperties {
	propsData := utils.NewOrderedPropertyList()

	// metadata
	propsMetadata := utils.NewOrderedPropertyList()
	propsMetadata.AddOrderedProperty("package", p.Name)
	propsMetadata.AddOrderedProperty("package path", p.PackagePath)
	propsMetadata.AddOrderedProperty("module", p.Module)
	// metadata > files
	files := []string{}
	for _, f := range p.Files {
		files = append(files, f.String())
	}
	sort.Strings(files)
	propsMetadata.AddOrderedProperty("files", files)
	// metadata > imports
	imports := []string{}
	for key := range p.ImportedPackages {
		imports = append(imports, key)
	}
	sort.Strings(imports)
	propsMetadata.AddOrderedProperty("imports", imports)
	// save metadata
	propsData.AddOrderedProperty("metadata", propsMetadata.Result())

	// imported types
	importedTypes := []string{}
	for _, e := range p.ImportedTypes {
		importedTypes = append(importedTypes, e.LongString())
	}
	sort.Strings(importedTypes)
	propsData.AddOrderedProperty("imported types", importedTypes)

	// declared types
	declaredTypes := []string{}
	for _, e := range p.DeclaredTypes {
		declaredTypes = append(declaredTypes, e.LongString())
	}
	sort.Strings(declaredTypes)
	propsData.AddOrderedProperty("declared types", declaredTypes)

	// service types
	serviceTypes := []string{}
	for _, e := range p.ServiceTypes {
		serviceTypes = append(serviceTypes, e.LongString())
	}
	sort.Strings(serviceTypes)
	propsData.AddOrderedProperty("service types", serviceTypes)

	// datastore types
	datastoreTypes := []string{}
	for _, e := range p.DatastoreTypes {
		datastoreTypes = append(datastoreTypes, e.LongString())
	}
	sort.Strings(datastoreTypes)
	propsData.AddOrderedProperty("datastore types", datastoreTypes)

	// declared variables
	declaredVariables := []string{}
	for _, v := range p.DeclaredVariables {
		declaredVariables = append(declaredVariables, v.String())
	}
	sort.Strings(declaredVariables)
	propsData.AddOrderedProperty("declared variables", declaredVariables)

	// parsed methods
	parsedMethods := []string{}
	for _, m := range p.ParsedMethods {
		parsedMethods = append(parsedMethods, m.LongString())
	}
	sort.Strings(parsedMethods)
	propsData.AddOrderedProperty("parsed methods", parsedMethods)

	// save final data
	return propsData.Result()
}
