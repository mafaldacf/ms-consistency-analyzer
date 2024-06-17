package abstractgraph

import (
	"fmt"

	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
)

func GetIndirectDependencies(first bool, v types.Variable) []types.Variable {
	indirectDeps := []types.Variable{}
	if !first {
		indirectDeps = append(indirectDeps, v)
	}

	// indirect dependencies from potential reference
	if v.GetVariableInfo().HasReference() {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(false, v.GetVariableInfo().GetReference())...)
	}
	// direct dependencies
	for _, dep := range v.GetDependencies() {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(false, dep)...)
	}

	return indirectDeps
}

func GetNestedDependencies(first bool, v types.Variable) ([]types.Variable, []string) {
	foreignDeps := []types.Variable{}
	foreignNames := []string{}
	if !first && v.GetVariableInfo().Dataflows != nil {
		for _, df := range v.GetVariableInfo().Dataflows {
			if df.DirectWrite {
				foreignDeps = append(foreignDeps, v)
				foreignNames = append(foreignNames, v.GetVariableInfo().GetType().GetName())
			} else {
				foreignDeps = append(foreignDeps, df.IndirectSource)
				foreignNames = append(foreignNames, df.IndirectSource.GetVariableInfo().GetType().GetName())
			}
		}
	}

	if v.GetVariableInfo().HasReference() {
		r1, r2 := GetNestedDependencies(false, v.GetVariableInfo().GetReference())
		foreignDeps = append(foreignDeps, r1...)
		foreignNames = append(foreignNames, r2...)
	}

	for _, dep := range v.GetDependencies() {
		deps2, names2 := GetNestedDependencies(false, dep)
		for _, n := range names2 {
			n = v.GetVariableInfo().GetType().GetName() + "." + n
			foreignNames = append(foreignNames, n)
		}
		foreignDeps = append(foreignDeps, deps2...)
	}

	return foreignDeps, foreignNames
}

func addNestedDatastoreEntry(variable types.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetVariableInfo().GetType()
	datastore.Schema.AddEntry(entryName, objType.FullString(), variable.GetVariableInfo().GetId())
	datastore.Schema.AddUnfoldedFieldWithId(objType.GetName(), objType.FullString(), variable.GetVariableInfo().GetId())

	// add nested unfolded types
	types, names := objType.GetNestedTypes(objType.GetName())
	for i, t := range types {
		name := names[i]
		datastore.Schema.AddUnfoldedField(name, t.FullString())
	}
}

func addDatastoreEntry(variable types.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetVariableInfo().GetType()
	datastore.Schema.AddEntry(entryName, objType.GetName(), variable.GetVariableInfo().GetId())
}

func addDataflow(variable types.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore) {
	logger.Logger.Infof("\t\t[DIRECT DATAFLOW] set direct write for %v (id = %d)", variable, variable.GetVariableInfo().Id)
	variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable)
	indirectDependencies := GetIndirectDependencies(true, variable)
	for _, v := range indirectDependencies {
		logger.Logger.Warnf("\t\t\t[INDIRECT DATAFLOW] set indirect write for %v (id = %d)", v, v.GetVariableInfo().Id)
		v.GetVariableInfo().SetIndirectDataflow(variable)
	}
}

func searchForeignDataflow(variable types.Variable, datastore *datastores.Datastore, app *app.App) {
	fmt.Printf("\n------------------------ SEARCH FOREIGN DATAFLOW @ %s ------------------------\n\n", datastore.Name)
	foreignDependencies, _ := GetNestedDependencies(false, variable)
	for _, v := range foreignDependencies {
		var foreignVariables []types.Variable
		var foreignDatastores []datastores.DatabaseInstance

		for _, df := range v.GetVariableInfo().GetForeignDataflows(datastore) {
			foreignVariables = append(foreignVariables, df.GetVariable())
			foreignDatastores = append(foreignDatastores, app.Databases[df.GetDatastore()])
		}

		for i, foreignVariable := range foreignVariables {
			foreignDatastore := foreignDatastores[i]
			logger.Logger.Infof("foreign variable %s (id = %d) @ %s", foreignVariable.String(), foreignVariable.GetVariableInfo().Id, foreignDatastore.GetName())
			foreignField := foreignDatastore.GetDatastore().Schema.GetFieldById(foreignVariable.GetVariableInfo().Id)
			if foreignField != nil {
				datastore.Schema.AddFKReference(foreignVariable.GetVariableInfo().GetName(), foreignVariable.GetVariableInfo().Type.String(), foreignField, foreignDatastore.GetDatastore().Name)
			} else {
				// this is duplicating if not else
				foreignField = foreignDatastore.GetDatastore().Schema.GetField(foreignVariable.GetVariableInfo().GetType().GetName())
				if foreignField != nil {
					datastore.Schema.AddFKReference(foreignVariable.GetVariableInfo().GetName(), foreignVariable.GetVariableInfo().Type.String(), foreignField, foreignDatastore.GetDatastore().Name)
				}
			}
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
			addDataflow(key, dbCall, datastore)
			addDataflow(value, dbCall, datastore)
			searchForeignDataflow(key, datastore, app)
			searchForeignDataflow(value, datastore, app)

		case datastores.NoSQL:
			doc := params[1]
			addNestedDatastoreEntry(doc, "document", datastore)
			addDataflow(doc, dbCall, datastore)
			searchForeignDataflow(doc, datastore, app)

		case datastores.Queue:
			msg := params[1]
			addNestedDatastoreEntry(msg, "message", datastore)
			searchForeignDataflow(msg, datastore, app)
		}

	}
	for _, child := range node.GetChildren() {
		BuildSchema(app, child)
	}
}
