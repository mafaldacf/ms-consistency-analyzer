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
	logger.Logger.Tracef("[YAML] dumping yaml data for method (%s)", f.Name)
	if f.ParsedCfg != nil {
		return f.ParsedCfg.Yaml()
	}
	return nil
}

func (f *ParsedMethod) YamlCalls() []string {
	logger.Logger.Tracef("[YAML CALLS] dumping yaml calls for method (%s)", f.Name)
	var lst []string
	for _, c := range f.Calls {
		logger.Logger.Tracef("\t\t\t - call: %s, method: %v", c.GetName(), c.GetMethod())
		lst = append(lst, c.GetMethod().LongString())
	}
	return lst
}

// ----
// CFGS
// ----

func (cfg *CFG) Yaml() map[string][]string {
	data := make(map[string][]string)

	// iterate in reverse
	for i := len(cfg.ParsedBlocks) - 1; i >= 0; i-- {
		block := cfg.ParsedBlocks[i]
		if block.Block.Live {
			data[block.Block.String()] = block.Yaml()
			break
		}
	}

	/* if len(cfg.ParsedBlocks) > 0 {
		data[cfg.ParsedBlocks[len(cfg.ParsedBlocks)-1].Block.String()] = cfg.ParsedBlocks[len(cfg.ParsedBlocks)-1].Yaml()
	} */

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

func getTaintedFieldsListAndString(dfs []*variables.Dataflow) ([]string, string) {
	var fieldsLst []string
	fieldsStr := ""
	for _, df := range dfs {
		if df.Field == nil {
			logger.Logger.Fatalf("GOT NIL FIELD FOR DF (%s, %s). %s", df.Datastore, df.Service, df.Variable.String())
		}
		if !slices.Contains(fieldsLst, df.Field.GetFullName()) {
			fieldsLst = append(fieldsLst, df.Field.GetFullName())
		}
	}
	for i, db := range fieldsLst {
		fieldsStr += db
		if i < len(fieldsLst)-1 {
			fieldsStr += ", "
		}
	}
	return fieldsLst, fieldsStr
}

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
				variableString = "(inline) " + variableString
			}
			dfsWriteOps := v.GetVariableInfo().GetAllWriteDataflows()
			dfsReadOps := v.GetVariableInfo().GetAllReadDataflows()
			if len(dfsWriteOps) > 0 || len(dfsReadOps) > 0 {
				writeOpsLst, writeOpsStr := getTaintedFieldsListAndString(dfsWriteOps)
				readOpsLst, readOpsStr := getTaintedFieldsListAndString(dfsReadOps)
				if len(dfsWriteOps) > 0 && len(dfsReadOps) == 0 {
					data = append(data, fmt.Sprintf("%s -->\n   W-TAINTED %dx = (%s)", variableString, len(writeOpsLst), writeOpsStr))
				} else if len(dfsWriteOps) == 0 && len(dfsReadOps) > 0 {
					data = append(data, fmt.Sprintf("%s -->\n   R-TAINTED %dx = (%s)", variableString, len(readOpsLst), readOpsStr))
				} else {
					data = append(data, fmt.Sprintf("%s -->\n   W-TAINTED %dx = (%s)\n   R-TAINTED %dx = (%s)", variableString, len(writeOpsLst), writeOpsStr, len(readOpsLst), readOpsStr))
				}
			} else {
				data = append(data, variableString)
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
