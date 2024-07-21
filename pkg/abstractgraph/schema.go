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

func addEntryToDatastore(variable variables.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetType()
	datastore.Schema.AddField(entryName, objType.GetName(), variable.GetId(), datastore.Name)
	logger.Logger.Infof("[SCHEMA] [%s] added entry (%s): %s", datastore.Name, entryName, objType.LongString())
}

func addUnfoldedEntriesToDatastore(variable variables.Variable, entryName string, datastore *datastores.Datastore) {
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

func taintDataflow(app *app.App, variable variables.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore) {
	fmt.Printf("\n------------- TAINT DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetName(), datastore.Name)
	fmt.Println()

	// taint direct dataflow
	rootField := datastore.Schema.GetField(variable.GetType().GetName())
	variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable, rootField)
	if !slices.Contains(app.TaintedVariables[rootField.GetFullName()], variable) {
		app.TaintedVariables[rootField.GetFullName()] = append(app.TaintedVariables[rootField.GetFullName()], variable)
	}
	var taintedVariables []variables.Variable

	// taint indirect dataflow
	vars, names := variables.GetReversedNestedFieldsAndNames(variable, true)

	for i, v := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := variables.GetIndirectDependenciesWithCurrent(v)
		logger.Logger.Infof("[TENTATIVE TAINT VAR] [%s] (%02d) %s", utils.GetType(v), v.GetId(), v.LongString())
		for _, dep := range deps {
			if !slices.Contains(taintedVariables, dep) {
				v.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, variable, dbField)
				logger.Logger.Debugf("\t\t[TAINT DEP] %s ---> (%02d) %s [%s]", dbField.GetFullName(), dep.GetId(), dep.String(), utils.GetType(dep))

				taintedVariables = append(taintedVariables, dep)
				app.AddTaintedVariableIfNotExists(dbField.GetFullName(), dep)
			}
		}
	}
	fmt.Println()
}

func referenceTaintedDataflow(writtenVariable variables.Variable, datastore *datastores.Datastore) {
	fmt.Printf("\n------------- REFERENCE TAINTED DATAFLOW FOR WRITTEN VARIABLE %s @ %s -------------\n\n", writtenVariable.GetType().GetName(), datastore.Name)
	fmt.Println()
	vars, names := variables.GetReversedNestedFieldsAndNames(writtenVariable, true)
	for i, variable := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := variables.GetIndirectDependenciesWithCurrent(variable)
		logger.Logger.Infof("[TENTATIVE REF TAINTED VAR] [%s] (%02d) %s", utils.GetType(variable), variable.GetId(), variable.LongString())
		for _, dep := range deps {
			for _, df := range dep.GetVariableInfo().GetAllDataflows() {
				if df.Datastore != datastore.Name {
					datastore.Schema.AddForeignReferenceToField(dbField, df.Field)
					logger.Logger.Debugf("\t\t[REF TAINTED DEP] (%s -> %s) from %s [%s]", dbField.GetFullName(), df.Field.GetFullName(), dep.String(), utils.GetType(dep))
				}
			}
		}
	}
	fmt.Println()
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
	fmt.Printf("\n------------- SEARCH FOREIGN DATAFLOW @ %s -------------\n\n", datastore.Name)
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
			addEntryToDatastore(key, "key", datastore)
			addUnfoldedEntriesToDatastore(value, "value", datastore)

			//taintDataflow(app, key, dbCall, datastore)
			taintDataflow(app, value, dbCall, datastore)
			//logger.Logger.Fatal("exiting...")
			//searchForeignDataflow(key, datastore, app)
			//searchForeignDataflow(value, datastore, app)
			referenceTaintedDataflow(key, datastore)
			referenceTaintedDataflow(value, datastore)

		case datastores.NoSQL:
			doc := params[1]
			addUnfoldedEntriesToDatastore(doc, "document", datastore)
			taintDataflow(app, doc, dbCall, datastore)

			//searchForeignDataflow(doc, datastore, app)
			referenceTaintedDataflow(doc, datastore)

		case datastores.SQL:
			doc := params[1]
			addUnfoldedEntriesToDatastore(doc, "document", datastore)
			taintDataflow(app, doc, dbCall, datastore)

			//searchForeignDataflow(doc, datastore, app)
			referenceTaintedDataflow(doc, datastore)

		case datastores.Queue:
			msg := params[1]
			addUnfoldedEntriesToDatastore(msg, "message", datastore)
			taintDataflow(app, msg, dbCall, datastore)

			//searchForeignDataflow(msg, datastore, app)
			referenceTaintedDataflow(msg, datastore)
		}

	}
	for _, child := range node.GetChildren() {
		BuildSchema(app, child)
	}
}
