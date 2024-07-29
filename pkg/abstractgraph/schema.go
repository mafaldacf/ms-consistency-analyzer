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

func taintDataflowOp(app *app.App, variable variables.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore, fieldName string, includeNestedFields bool) {
	fmt.Printf("\n------------- TAINT WRITE DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetName(), datastore.Name)
	fmt.Println()

	// taint direct dataflow
	if fieldName == "" {
		fieldName = variable.GetType().GetName()
	}
	rootField := datastore.Schema.GetField(fieldName)
	variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable, rootField, true)
	logger.Logger.Debugf("[TAINT WRITE DIRECT] %s ---> (%02d) %s [%s]", rootField.GetFullName(), variable.GetId(), variable.String(), utils.GetType(variable))
	if !slices.Contains(app.TaintedVariables[rootField.GetFullName()], variable) {
		app.TaintedVariables[rootField.GetFullName()] = append(app.TaintedVariables[rootField.GetFullName()], variable)
	}
	var taintedVariables []variables.Variable

	// taint indirect dataflow
	if fieldName == "" {
		fieldName = datastore.Schema.GetRootUnfoldedField().GetName()
	}
	var vars []variables.Variable
	var names []string
	if includeNestedFields {
		vars, names = variables.GetReversedNestedFieldsAndNames(variable, fieldName)
	} else {
		vars = []variables.Variable{variable}
		names = []string{fieldName}
	}

	for i, v := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := v.GetNestedDependencies(false)
		logger.Logger.Infof("[TENTATIVE TAINT WRITE VAR] [%s] (%02d) (NUM DEPS = %d) %s", utils.GetType(v), v.GetId(), len(deps), v.LongString())
		for _, dep := range deps {
			if !slices.Contains(taintedVariables, dep) {
				v.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, variable, dbField, true)
				logger.Logger.Debugf("\t\t[TAINT WRITE INDIRECT] %s ---> (%02d) %s [%s]", dbField.GetFullName(), dep.GetId(), dep.String(), utils.GetType(dep))

				taintedVariables = append(taintedVariables, dep)
				app.AddTaintedVariableIfNotExists(dbField.GetFullName(), dep)
			}
		}
	}
	fmt.Println()
}

func taintDataflowReadOp(app *app.App, variable variables.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore, fieldName string) {
	fmt.Printf("\n------------- TAINT READ DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetName(), datastore.Name)
	fmt.Println()

	// taint direct dataflow
	rootField := datastore.Schema.GetField(fieldName)
	variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable, rootField, false)
	logger.Logger.Debugf("[TAINT READ DIRECT] %s ---> (%02d) %s [%s]", rootField.GetFullName(), variable.GetId(), variable.String(), utils.GetType(variable))
	if !slices.Contains(app.TaintedVariables[rootField.GetFullName()], variable) {
		app.TaintedVariables[rootField.GetFullName()] = append(app.TaintedVariables[rootField.GetFullName()], variable)
	}
	var taintedVariables []variables.Variable

	// taint indirect dataflow
	rootUnfoldedField := datastore.Schema.GetRootUnfoldedField()
	vars, names := variables.GetReversedNestedFieldsAndNames(variable, rootUnfoldedField.GetName())

	for i, v := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := v.GetNestedDependencies(false)
		logger.Logger.Infof("[TENTATIVE TAINT READ VAR] [%s] (%02d) (NUM DEPS = %d) %s", utils.GetType(v), v.GetId(), len(deps), v.LongString())
		for _, dep := range deps {
			if !slices.Contains(taintedVariables, dep) {
				v.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, variable, dbField, false)
				logger.Logger.Debugf("\t\t[TAINT READ INDIRECT] %s ---> (%02d) %s [%s]", dbField.GetFullName(), dep.GetId(), dep.String(), utils.GetType(dep))

				taintedVariables = append(taintedVariables, dep)
				app.AddTaintedVariableIfNotExists(dbField.GetFullName(), dep)
			}
		}
	}
	fmt.Println()
}

func taintDataflowReadOpUnnamed(app *app.App, variable variables.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore, fieldName string) {
	fmt.Printf("\n------------- TAINT READ UNNAMED DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetName(), datastore.Name)
	fmt.Println()

	// taint direct dataflow
	rootField := datastore.Schema.GetField(fieldName)
	// variable is expected to be e.g. a cursor for nosql
	variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable, rootField, false)
	logger.Logger.Debugf("[TAINT READ DIRECT] %s ---> (%02d) %s [%s]", rootField.GetFullName(), variable.GetId(), variable.String(), utils.GetType(variable))
	if !slices.Contains(app.TaintedVariables[rootField.GetFullName()], variable) {
		app.TaintedVariables[rootField.GetFullName()] = append(app.TaintedVariables[rootField.GetFullName()], variable)
	}

	var taintedVariables []variables.Variable
	deps := variable.GetNestedDependencies(false)
	logger.Logger.Infof("[TENTATIVE TAINT READ UNNAMED VAR] [%s] (%02d) (NUM DEPS = %d) %s", utils.GetType(variable), variable.GetId(), len(deps), variable.LongString())
	for _, dep := range deps {
		if !slices.Contains(taintedVariables, dep) {
			variable.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, variable, &datastores.Entry{
				Name:      dep.GetType().GetName(),
				Type:      dep.GetType().GetName(),
				Datastore: datastore.Name,
			}, false)
			logger.Logger.Debugf("\t\t[TAINT READ UNNAMED INDIRECT] <unnamed> ---> (%02d) %s [%s]", dep.GetId(), dep.String(), utils.GetType(dep))

			taintedVariables = append(taintedVariables, dep)
			app.AddTaintedVariableIfNotExists(dep.GetType().GetName(), dep)
		}
	}
	fmt.Println()
}

func referenceTaintedDataflowForSingleValue(writtenVariable variables.Variable, datastore *datastores.Datastore, fieldName string) {
	fmt.Printf("\n------------- REFERENCE TAINTED DATAFLOW FOR WRITTEN VARIABLE %s @ %s -------------\n\n", writtenVariable.GetType().GetName(), datastore.Name)
	fmt.Println()
	dbField := datastore.Schema.GetField(fieldName)
	deps := writtenVariable.GetNestedDependencies(false)
	logger.Logger.Infof("[TENTATIVE REF TAINTED VAR] [%s] (%02d) %s", utils.GetType(writtenVariable), writtenVariable.GetId(), writtenVariable.LongString())
	for _, dep := range deps {
		for _, df := range dep.GetVariableInfo().GetAllDataflows() {
			if df.Datastore != datastore.Name {
				datastore.Schema.AddForeignReferenceToField(dbField, df.Field)
				logger.Logger.Debugf("\t\t[REF TAINTED DEP] (%s -> %s) from %s [%s]", dbField.GetFullName(), df.Field.GetFullName(), dep.String(), utils.GetType(dep))
			}
		}
	
	}
	fmt.Println()
}

func referenceTaintedDataflowForNestedFields(writtenVariable variables.Variable, datastore *datastores.Datastore) {
	fmt.Printf("\n------------- REFERENCE TAINTED DATAFLOW FOR WRITTEN VARIABLE %s @ %s -------------\n\n", writtenVariable.GetType().GetName(), datastore.Name)
	fmt.Println()
	vars, names := variables.GetReversedNestedFieldsAndNames(writtenVariable, "")
	for i, variable := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := variable.GetNestedDependencies(false)
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

var writtenDatastores = make(map[string]bool, 0)

func BuildSchema(app *app.App, node AbstractNode) {
	if dbCall, ok := node.(*AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsRead() {
		datastore := dbCall.DbInstance.GetDatastore()
		if found := writtenDatastores[datastore.Name]; !found {
			logger.Logger.Warnf("[SCHEMA] skipping read for abstract node: %s", dbCall.String())
			return
		}
		params := dbCall.GetParams()
		returns := dbCall.GetReturns()
		switch datastore.Type {
		case datastores.Queue:
			msg := params[1]
			taintDataflowReadOp(app, msg, dbCall, datastore, "message")
		case datastores.NoSQL:
			doc := returns[0]
			taintDataflowReadOpUnnamed(app, doc, dbCall, datastore, "document")
			query := params[1]
			taintDataflowReadOpUnnamed(app, query, dbCall, datastore, "document")
		}

	}
	if dbCall, ok := node.(*AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsWrite() {
		datastore := dbCall.DbInstance.GetDatastore()
		if found := writtenDatastores[datastore.Name]; !found {
			writtenDatastores[datastore.Name] = true
		}
		params := dbCall.GetParams()
		logger.Logger.Infof("[SCHEMA] [%s] building schema based on abstract node (%s)", datastore.Name, dbCall.GetName())

		switch datastore.Type {
		case datastores.Queue:
			msg := params[1]
			addUnfoldedEntriesToDatastore(msg, "message", datastore)
			taintDataflowOp(app, msg, dbCall, datastore, "", true)
			referenceTaintedDataflowForNestedFields(msg, datastore)

		case datastores.NoSQL:
			doc := params[1]
			addUnfoldedEntriesToDatastore(doc, "document", datastore)
			for i, param := range params {
				logger.Logger.Debugf("BUILD SCHEMA!!! (%d) (%s)", i, utils.GetType(param))
				if _, ok := param.(*variables.StructVariable); ok {
					variables.GetReversedNestedFieldsAndNames(param, "")
				}
			}
			taintDataflowOp(app, doc, dbCall, datastore, "", true)
			referenceTaintedDataflowForNestedFields(doc, datastore)

		case datastores.Cache:
			key := params[1]
			value := params[2]
			addEntryToDatastore(key, "key", datastore)
			addEntryToDatastore(value, "value", datastore)
			taintDataflowOp(app, value, dbCall, datastore, "key", false)
			taintDataflowOp(app, value, dbCall, datastore, "value", false)
			referenceTaintedDataflowForSingleValue(key, datastore, "key")
			referenceTaintedDataflowForSingleValue(value, datastore, "value")
		}
	}

	if dbCall, ok := node.(*AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsUpdate() {
		logger.Logger.Fatalf("TODO FOR DB CALL: %s", dbCall.String())
	}

	for _, child := range node.GetChildren() {
		BuildSchema(app, child)
	}
}
