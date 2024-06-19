package abstractgraph

import (
	"fmt"
	"slices"

	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
)

type DependencySet struct {
	Variable        types.Variable
	Dependencies    []types.Variable
	DependencyNames []string
}

func addNestedDatastoreEntry(variable types.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetVariableInfo().GetType()
	datastore.Schema.AddField(entryName, objType.FullString(), variable.GetVariableInfo().GetId(), datastore.Name)
	datastore.Schema.AddUnfoldedFieldWithId(objType.GetName(), objType.FullString(), variable.GetVariableInfo().GetId(), datastore.Name)

	// add nested unfolded types
	types, names := objType.GetNestedFieldTypes(objType.GetName())
	for i, t := range types {
		name := names[i]
		datastore.Schema.AddUnfoldedField(name, t.FullString(), datastore.Name)
	}
}

func addDatastoreEntry(variable types.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetVariableInfo().GetType()
	datastore.Schema.AddField(entryName, objType.GetName(), variable.GetVariableInfo().GetId(), datastore.Name)
}

func computeDependencySets(parentSet *DependencySet, v types.Variable) []*DependencySet {
	var sets []*DependencySet
	set := &DependencySet{
		Variable: v,
	}
	sets = append(sets, set)
	logger.Logger.Infof("\t\tvisiting %s (%s)", v.String(), utils.GetType(v))

	if parentSet != nil {
		parentSet.Dependencies = append(parentSet.Dependencies, v)
	}

	// indirect dependencySets from potential reference
	if v.GetVariableInfo().HasReference() {
		sets = append(sets, computeDependencySets(set, v.GetVariableInfo().Reference.Variable)...)
	}
	// direct dependencySets
	for _, dep := range v.GetDependencies() {
		sets = append(sets, computeDependencySets(set, dep)...)
	}

	return sets
}

func GetNestedFields(variable types.Variable) []types.Variable {
	var nestedFields []types.Variable
	return nestedFields
}

func addDataflow(app *app.App, variable types.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore) {
	rootField := datastore.Schema.GetField(variable.GetVariableInfo().GetType().GetName())
	variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable, rootField)
	if !slices.Contains(app.PersistedVariables[rootField.GetFullName()], variable) {
		app.PersistedVariables[rootField.GetFullName()] = append(app.PersistedVariables[rootField.GetFullName()], variable)
	}

	var persistedVars []types.Variable

	// add nested unfolded types
	if structVariable, ok := variable.(*types.StructVariable); ok {
		variables := []types.Variable{structVariable}
		names := []string{structVariable.GetVariableInfo().GetType().GetName()}
		nestedVariables, nestedNames := structVariable.GetNestedFieldVariables(variable.GetVariableInfo().GetType().GetName())

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)

		slices.Reverse(variables)
		slices.Reverse(names)
		
		for i, v := range variables {
			logger.Logger.Infof("VISITING VARIABLE %s", v.String())
			name := names[i]
			field := datastore.Schema.GetField(name)
			deps := getDependencies(false, v)
			for _, d := range deps {
				logger.Logger.Warnf("VISITING VARIABLE %s (FIELD %s) DEP %s", v.String(), field.GetName(), d.String())
				if !slices.Contains(persistedVars, d) {
					v.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, d, variable, field)
					persistedVars = append(persistedVars, d)
					if !slices.Contains(app.PersistedVariables[field.GetFullName()], d) {
						app.PersistedVariables[field.GetFullName()] = append(app.PersistedVariables[field.GetFullName()], d)
					}
				}
			}
		}
	}
	//logger.Logger.Fatalf("EXITING")
}

func addForeignFields(variable types.Variable, datastore *datastores.Datastore) {
	if structVariable, ok := variable.(*types.StructVariable); ok {
		variables := []types.Variable{structVariable}
		names := []string{structVariable.GetVariableInfo().GetType().GetName()}
		nestedVariables, nestedNames := structVariable.GetNestedFieldVariables(variable.GetVariableInfo().GetType().GetName())

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)
		
		for i, v := range variables {
			name := names[i]
			field := datastore.Schema.GetField(name)
			deps := getDependencies(false, v)
			logger.Logger.Infof("VAR %s, deps %v", v.String(), deps)
			for _, d := range deps {
				if dfs := d.GetVariableInfo().GetAllDataflows(); dfs != nil {
					for _, df := range dfs {
						logger.Logger.Warnf("DEP %s, df %v", d.String(), df.String())
						if df.Datastore != datastore.Name {
							datastore.Schema.AddForeignReferenceToField(field, df.Field)
							logger.Logger.Infof("ADDED FOREIGN REFERENCE FOR FIELD %s: %s", field.GetFullName(), df.Field.GetFullName())
						}
					}
				}
			}
		}
	}
}

func computeForeignDependencySets(parentSet *DependencySet, v types.Variable) []*DependencySet {
	var sets []*DependencySet
	set := &DependencySet{
		Variable: v,
	}
	sets = append(sets, set)
	logger.Logger.Infof("visiting %s (%s)", v.String(), utils.GetType(v))
	appendDataflowDependencies := func(dep types.Variable, isRef bool) {
		logger.Logger.Infof("\t\tgetting data flow dependencies for %s (%s)", dep.String(), utils.GetType(dep))
		for _, df := range dep.GetVariableInfo().Dataflows {
			if df.DirectWrite {
				logger.Logger.Infof("\t\t\tappending dataflow: %s", df.String())
				name := dep.GetVariableInfo().GetType().GetName()
				if compositeVariable, ok := set.Variable.(*types.CompositeVariable); ok && parentSet != nil {
					logger.Logger.Warnf("skipping composite variable %s", compositeVariable.String())
					parentSet.Dependencies = append(parentSet.Dependencies, dep)
					parentSet.DependencyNames = append(set.DependencyNames, name)
				} else {
					set.Dependencies = append(set.Dependencies, dep)
					set.DependencyNames = append(set.DependencyNames, name)
				}

			} else {
				name := df.IndirectSource.GetVariableInfo().GetType().GetName()
				if isRef {
					name = v.GetVariableInfo().GetType().GetName() + "." + name
					logger.Logger.Infof("\t\t\t appending dataflow: %s", df.String())
				} else {
					logger.Logger.Infof("\t\t\t appending (ref) dataflow: %s", df.String())
				}
				if compositeVariable, ok := set.Variable.(*types.CompositeVariable); ok && parentSet != nil {
					logger.Logger.Warnf("skipping composite variable %s", compositeVariable.String())
					parentSet.Dependencies = append(parentSet.Dependencies, dep)
					parentSet.DependencyNames = append(set.DependencyNames, name)
				} else {
					set.Dependencies = append(set.Dependencies, dep)
					set.DependencyNames = append(set.DependencyNames, name)
				}
			}
		}
	}
	if v.GetVariableInfo().HasReference() {
		appendDataflowDependencies(v.GetVariableInfo().GetReference(), false)
		sets = append(sets, computeForeignDependencySets(set, v.GetVariableInfo().GetReference())...)
	}
	for _, dep := range v.GetDependencies() {
		if !slices.Contains(set.Dependencies, dep) {
			appendDataflowDependencies(dep, true)
			sets = append(sets, computeForeignDependencySets(set, dep)...)
		}
	}

	return sets
}

func searchForeignDataflow(variable types.Variable, datastore *datastores.Datastore, app *app.App) {
	fmt.Printf("\n------------------------ SEARCH FOREIGN DATAFLOW @ %s ------------------------\n\n", datastore.Name)
	sets := computeForeignDependencySets(nil, variable)
	fmt.Println()
	for _, set := range sets {
		logger.Logger.Infof("------ visiting set for %v ------", set.Variable.String())
		for _, v := range set.Dependencies {
			var foreignVariables []types.Variable
			var foreignDatastores []datastores.DatabaseInstance

			for _, df := range v.GetVariableInfo().GetForeignDataflows(datastore) {
				logger.Logger.Infof("\t\t foreign dataflow: %s", df.String())
				foreignVariables = append(foreignVariables, df.GetVariable())
				foreignDatastores = append(foreignDatastores, app.Databases[df.GetDatastore()])
			}

			for i, foreignVariable := range foreignVariables {
				foreignDatastore := foreignDatastores[i]
				logger.Logger.Infof("\t\t\t foreign variable %s (id = %d) @ %s", foreignVariable.String(), foreignVariable.GetVariableInfo().Id, foreignDatastore.GetName())
				foreignField := foreignDatastore.GetDatastore().Schema.GetFieldById(foreignVariable.GetVariableInfo().Id)
				if foreignField == nil {
					foreignField = foreignDatastore.GetDatastore().Schema.GetField(foreignVariable.GetVariableInfo().GetType().GetName())
				}

				datastore.Schema.AddFKReference(
					set.Variable.GetVariableInfo().Name,
					foreignVariable.GetVariableInfo().Type.String(),
					foreignField,
					foreignDatastore.GetDatastore().Name,
				)
			}
			fmt.Println()
		}
	}
}
func BuildSchema(app *app.App, node AbstractNode) {
	if dbCall, ok := node.(*AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsWrite() {
		datastore := dbCall.DbInstance.GetDatastore()
		params := dbCall.Params
		logger.Logger.Infof("[SCHEMA] building schema for abstract node %s with params = %v", dbCall.String(), params)
		switch datastore.Type {
		case datastores.Cache:
			key := params[1]
			value := params[2]
			addDatastoreEntry(key, "key", datastore)
			addNestedDatastoreEntry(value, "value", datastore)
			//addDataflow(app, key, dbCall, datastore)
			addDataflow(app, value, dbCall, datastore)
			//logger.Logger.Fatal("exiting...")
			searchForeignDataflow(key, datastore, app)
			searchForeignDataflow(value, datastore, app)

		case datastores.NoSQL:
			doc := params[1]
			addNestedDatastoreEntry(doc, "document", datastore)
			addDataflow(app, doc, dbCall, datastore)
			searchForeignDataflow(doc, datastore, app)

		case datastores.Queue:
			msg := params[1]
			addNestedDatastoreEntry(msg, "message", datastore)
			searchForeignDataflow(msg, datastore, app)
			addForeignFields(msg, datastore)
		}

	}
	for _, child := range node.GetChildren() {
		BuildSchema(app, child)
	}
}
