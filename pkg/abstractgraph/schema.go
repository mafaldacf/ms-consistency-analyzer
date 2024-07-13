package abstractgraph

import (
	"fmt"
	"slices"

	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

type DependencySet struct {
	Variable        variables.Variable
	Dependencies    []variables.Variable
	DependencyNames []string
}

func addNestedDatastoreEntry(variable variables.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetType()
	datastore.Schema.AddField(entryName, objType.LongString(), variable.GetId(), datastore.Name)
	logger.Logger.Infof("[SCHEMA] [%s] added entry (%s): %s", datastore.Name, entryName, objType.LongString())

	datastore.Schema.AddUnfoldedFieldWithId(objType.GetName(), objType.LongString(), variable.GetId(), datastore.Name)
	logger.Logger.Infof("[SCHEMA] [%s] added field (%s): %s", datastore.Name, objType.GetName(), objType.LongString())

	// add nested unfolded types
	types, names := objType.GetNestedFieldTypes(objType.GetName())
	for i, t := range types {
		name := names[i]
		datastore.Schema.AddUnfoldedField(name, t.LongString(), datastore.Name)
		logger.Logger.Infof("[SCHEMA] [%s] added nested field (%s): %s", datastore.Name, name, t.LongString())
	}
}

func addDatastoreEntry(variable variables.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetType()
	datastore.Schema.AddField(entryName, objType.GetName(), variable.GetId(), datastore.Name)
	logger.Logger.Infof("[SCHEMA] [%s] added entry (%s): %s", datastore.Name, entryName, objType.LongString())
}

func computeDependencySets(parentSet *DependencySet, v variables.Variable) []*DependencySet {
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

func GetNestedFields(variable variables.Variable) []variables.Variable {
	var nestedFields []variables.Variable
	return nestedFields
}

func addDataflow(app *app.App, variable variables.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore) {
	fmt.Printf("\n------------------------ ADD DATAFLOW FOR CALL %s @ %s ------------------------\n\n", call.GetName(), datastore.Name)
	fmt.Println()
	rootField := datastore.Schema.GetField(variable.GetType().GetName())
	variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable, rootField)
	if !slices.Contains(app.PersistedVariables[rootField.GetFullName()], variable) {
		app.PersistedVariables[rootField.GetFullName()] = append(app.PersistedVariables[rootField.GetFullName()], variable)
	}

	var persistedVars []variables.Variable

	// add nested unfolded types
	if structVariable, ok := variable.(*variables.StructVariable); ok {
		variables := []variables.Variable{structVariable}
		names := []string{structVariable.GetType().GetName()}
		nestedVariables, nestedNames := structVariable.GetNestedFieldVariables(variable.GetType().GetName())

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)

		slices.Reverse(variables)
		slices.Reverse(names)

		for i, v := range variables {
			logger.Logger.Infof("[TAINTED VAR] %s (type = %s)", v.LongString(), utils.GetType(v))
			name := names[i]
			field := datastore.Schema.GetField(name)
			deps := getDependencies(v)
			for _, d := range deps {
				if !slices.Contains(persistedVars, d) {
					logger.Logger.Warnf("\t\t[TAINTED VAR DEP] field %s ---> %s (type = %s)", field.GetName(), d.String(), utils.GetType(d))
					v.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, d, variable, field)
					persistedVars = append(persistedVars, d)
					if !slices.Contains(app.PersistedVariables[field.GetFullName()], d) {
						app.PersistedVariables[field.GetFullName()] = append(app.PersistedVariables[field.GetFullName()], d)
					}
				}
			}
		}
	}
	fmt.Println()
}

func addForeignFields(variable variables.Variable, datastore *datastores.Datastore) {
	if structVariable, ok := variable.(*variables.StructVariable); ok {
		variables := []variables.Variable{structVariable}
		names := []string{structVariable.GetType().GetName()}
		nestedVariables, nestedNames := structVariable.GetNestedFieldVariables(variable.GetType().GetName())

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)

		for i, v := range variables {
			name := names[i]
			field := datastore.Schema.GetField(name)
			deps := getDependencies(v)
			logger.Logger.Infof("[NESTED VAR] %s (type = %s)", v.LongString(), utils.GetType(v))
			for _, d := range deps {
				if dfs := d.GetVariableInfo().GetAllDataflows(); dfs != nil {
					for _, df := range dfs {
						logger.Logger.Warnf("\t\t[NESTED VAR DEP] field %s ---> %s (type = %s)", field.GetName(), d.String(), utils.GetType(d))
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

func computeForeignDependencySets(parentSet *DependencySet, v variables.Variable) []*DependencySet {
	var sets []*DependencySet
	set := &DependencySet{
		Variable: v,
	}
	sets = append(sets, set)
	logger.Logger.Debugf("visiting %s (%s)", v.String(), utils.GetType(v))
	appendDataflowDependencies := func(dep variables.Variable, isRef bool) {
		logger.Logger.Infof("\t\tgetting data flow dependencies for %s (%s)", dep.String(), utils.GetType(dep))
		for _, df := range dep.GetVariableInfo().Dataflows {
			if df.DirectWrite {
				logger.Logger.Infof("\t\t\tappending dataflow: %s", df.String())
				name := dep.GetType().GetName()
				if compositeVariable, ok := set.Variable.(*variables.CompositeVariable); ok && parentSet != nil {
					logger.Logger.Warnf("skipping composite variable %s", compositeVariable.String())
					parentSet.Dependencies = append(parentSet.Dependencies, dep)
					parentSet.DependencyNames = append(set.DependencyNames, name)
				} else {
					set.Dependencies = append(set.Dependencies, dep)
					set.DependencyNames = append(set.DependencyNames, name)
				}

			} else {
				name := df.IndirectSource.GetType().GetName()
				if isRef {
					name = v.GetType().GetName() + "." + name
					logger.Logger.Infof("\t\t\t appending dataflow: %s", df.String())
				} else {
					logger.Logger.Infof("\t\t\t appending (ref) dataflow: %s", df.String())
				}
				if compositeVariable, ok := set.Variable.(*variables.CompositeVariable); ok && parentSet != nil {
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

func searchForeignDataflow(variable variables.Variable, datastore *datastores.Datastore, app *app.App) {
	fmt.Printf("\n------------------------ SEARCH FOREIGN DATAFLOW @ %s ------------------------\n\n", datastore.Name)
	sets := computeForeignDependencySets(nil, variable)
	for _, set := range sets {
		logger.Logger.Debugf("------ visiting set for %v ------", set.Variable.String())
		for _, v := range set.Dependencies {
			var foreignVariables []variables.Variable
			var foreignDatastores []datastores.DatabaseInstance

			for _, df := range v.GetVariableInfo().GetForeignDataflows(datastore) {
				logger.Logger.Infof("\t\t foreign dataflow: %s", df.String())
				foreignVariables = append(foreignVariables, df.GetVariable())
				foreignDatastores = append(foreignDatastores, app.Databases[df.GetDatastore()])
			}

			for i, foreignVariable := range foreignVariables {
				foreignDatastore := foreignDatastores[i]
				logger.Logger.Infof("\t\t\t foreign variable %s (id = %d) @ %s", foreignVariable.String(), foreignVariable.GetId(), foreignDatastore.GetName())
				foreignField := foreignDatastore.GetDatastore().Schema.GetFieldById(foreignVariable.GetId())
				if foreignField == nil {
					foreignField = foreignDatastore.GetDatastore().Schema.GetField(foreignVariable.GetType().GetName())
				}

				datastore.Schema.AddFKReference(
					set.Variable.GetVariableInfo().Name,
					foreignVariable.GetType().String(),
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
		logger.Logger.Infof("[SCHEMA] [%s] building schema based on abstract node (%s)", datastore.Name, dbCall.GetName())
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
			addDataflow(app, msg, dbCall, datastore)

			searchForeignDataflow(msg, datastore, app)
			addForeignFields(msg, datastore)
		}

	}
	for _, child := range node.GetChildren() {
		BuildSchema(app, child)
	}
}
