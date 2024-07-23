package types

import (
	"fmt"
	"slices"
	"sort"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

// --------------
// PARSED METHODS
// --------------

func (f *ParsedMethod) Yaml() interface{} {
	logger.Logger.Debugf("[YAML] dumping yaml data for method (%s)", f.Name)
	if f.ParsedCfg != nil {
		return f.ParsedCfg.Yaml()
	}
	return nil
}

func (f *ParsedMethod) YamlCalls() []string {
	logger.Logger.Debugf("[YAML CALLS] dumping yaml calls for method (%s)", f.Name)
	var lst []string
	for _, c := range f.Calls {
		logger.Logger.Debugf("\t\t\t - call: %s, method: %v", c.GetName(), c.GetMethod())
		lst = append(lst, c.GetMethod().LongString())
	}
	return lst
}

// ----
// CFGS
// ----

func (cfg *CFG) Yaml() map[string][]string {
	data := make(map[string][]string)

	if len(cfg.ParsedBlocks) > 0 {
		data[cfg.ParsedBlocks[0].Block.String()] = cfg.ParsedBlocks[0].Yaml()
	}

	/* var blocks []string
	for _, block := range cfg.ParsedBlocks {
		blocks = append(blocks, block.Block.String())
	}
	data["blocks"] = blocks */
	return data
}

// ------
// BLOCKS
// ------

func (block *Block) Yaml() []string {
	data := []string{}
	visited := make(map[variables.Variable]bool)
	for _, v := range block.Vars {
		deps := variables.GetIndirectDependenciesWithCurrent(v)
		slices.Reverse(deps)
		for i, v := range deps {
			lastIndex := len(deps) - 1
			if _, isVisited := visited[v]; isVisited {
				continue
			}
			visited[v] = true

			variableString := v.String()
			if i != lastIndex {
				// last index corresponds to the original variabl from where we got the parameters
				// note that it is the last since the deps slice was reversed
				variableString = "[INLINE] " + variableString
			}

			dfs := append(v.GetVariableInfo().Dataflows, v.GetVariableInfo().IndirectDataflows...)
			if len(dfs) > 0 {
				var taintedDBFields []string
				str := ""
				for _, df := range dfs {
					if !slices.Contains(taintedDBFields, df.Field.GetFullName()) {
						taintedDBFields = append(taintedDBFields, df.Field.GetFullName())
					}
				}
				for i, db := range taintedDBFields {
					str += db
					if i < len(taintedDBFields)-1 {
						str += ", "
					}
				}
				data = append(data, fmt.Sprintf("%s --> (TAINTED %dx) --> [%s]", variableString, len(taintedDBFields), str))
			} else {
				data = append(data, fmt.Sprintf("%s", variableString))
			}
		}

	}
	return data
}

// --------
// PACKAGES
// --------

// for external packages
func (p *Package) DumpExternalYaml() utils.OrderedProperties {
	propsData := utils.NewOrderedPropertyList()

	// metadata
	propsData.AddOrderedProperty("package", p.Name)
	propsData.AddOrderedProperty("package path", p.PackagePath)
	propsData.AddOrderedProperty("module", p.Module)

	// save final data
	return propsData.Result()
}

// for blueprint packages
func (p *Package) DumpBlueprintYaml() utils.OrderedProperties {
	propsData := utils.NewOrderedPropertyList()

	// metadata
	propsData.AddOrderedProperty("package", p.Name)
	propsData.AddOrderedProperty("package path", p.PackagePath)
	propsData.AddOrderedProperty("module", p.Module)

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
	propsData.AddOrderedProperty("package", p.Name)
	propsData.AddOrderedProperty("package path", p.PackagePath)
	propsData.AddOrderedProperty("module", p.Module)
	// metadata > files
	files := []string{}
	for _, f := range p.Files {
		files = append(files, f.String())
	}
	sort.Strings(files)
	propsData.AddOrderedProperty("files", files)
	// metadata > imports
	imports := []string{}
	for key := range p.ImportedPackages {
		imports = append(imports, key)
	}
	sort.Strings(imports)
	propsData.AddOrderedProperty("imports", imports)

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
