package abstractgraph

import (
	"fmt"
	"slices"

	/* "github.com/golang-collections/collections/stack" */

	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

type DependencySet struct {
	Variable        variables.Variable
	Dependencies    []variables.Variable
	DependencyNames []string
}

func saveFieldToDatastore(variable variables.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetType()
	datastore.Schema.AddOrGetField(entryName, objType.GetName(), variable.GetId(), datastore)
	logger.Logger.Infof("[SCHEMA] [%s] added entry (%s): %s", datastore.Name, entryName, objType.LongString())
}

func saveUnfoldedFieldsToDatastore(variable variables.Variable, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetType()
	datastore.Schema.AddOrGetField(entryName, objType.LongString(), variable.GetId(), datastore)
	logger.Logger.Infof("[SCHEMA] [%s] added entry (%s): %s", datastore.Name, entryName, objType.LongString())

	datastore.Schema.AddOrGetField(objType.GetName(), objType.LongString(), variable.GetId(), datastore)
	logger.Logger.Infof("[SCHEMA] [%s] added field (%s): %s", datastore.Name, objType.GetName(), objType.LongString())

	datastore.Schema.AddOrGetUnfoldedField(objType.GetName(), objType.LongString(), variable.GetId(), datastore)
	logger.Logger.Infof("[SCHEMA] [%s] added unfolded (entry) field (%s): %s", datastore.Name, objType.GetName(), objType.LongString())

	// add nested unfolded types
	types, names := objType.GetNestedFieldTypes(objType.GetName(), datastore.IsNoSQLDatabase())
	for i, t := range types {
		name := names[i]
		datastore.Schema.AddOrGetUnfoldedField(name, t.LongString(), 0, datastore)
		logger.Logger.Infof("[SCHEMA] [%s] added nested field (%s): %s", datastore.GetName(), name, t.LongString())
	}
}

func taintDataflowOp(app *app.App, variable variables.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore, fieldName string, includeNestedFields bool) {
	fmt.Printf("\n------------- TAINT WRITE DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetMethodStr(), datastore.Name)
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
		vars, names = variables.GetReversedNestedFieldsAndNames(variable, fieldName, datastore.IsNoSQLDatabase(), datastore.IsQueue())
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
	logger.Logger.Debugf("rootUnfoldedField = %v", rootUnfoldedField)
	vars, names := variables.GetReversedNestedFieldsAndNames(variable, rootUnfoldedField.GetName(), datastore.IsNoSQLDatabase(), datastore.IsQueue())

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

func taintDataflowReadOpUnnamed(app *app.App, variable variables.Variable, call *AbstractDatabaseCall, datastore *datastores.Datastore, fieldName string, query bool) {
	fmt.Printf("\n------------- TAINT READ UNNAMED DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetMethodStr(), datastore.Name)
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
	logger.Logger.Infof("[TENTATIVE TAINT READ UNNAMED VAR] [%s] (%02d) @ %s", utils.GetType(variable), variable.GetId(), variable.LongString())
	variable = getTargetVariableIfNoSQLCursorRead(datastore, variable)
	deps := variable.GetNestedDependencies(false)
	logger.Logger.Infof("[TENTATIVE TAINT READ UNNAMED VAR] [%s] NUM DEPS = %d @ %s", utils.GetType(variable), len(deps), variable.LongString())
	for _, dep := range deps {
		if !slices.Contains(taintedVariables, dep) {
			typeName := dep.GetType().GetName()

			if query {
				variable.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, variable, rootField, false)
			} else {
				entry := datastores.CreateEntry(typeName, typeName, 0, datastore)
				variable.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, variable, entry, false)
			}
			logger.Logger.Debugf("\t\t[TAINT READ UNNAMED INDIRECT] <unnamed> ---> (%02d) %s [%s]", dep.GetId(), dep.String(), utils.GetType(dep))

			taintedVariables = append(taintedVariables, dep)
			app.AddTaintedVariableIfNotExists(dep.GetType().GetName(), dep)
		}
	}

	if call.GetName() == "FindOne" && datastore.Name == "product_db" {
		logger.Logger.Debug("HERE!")
	}

	fmt.Println()
}

func getTargetVariableIfNoSQLCursorRead(datastore *datastores.Datastore, v variables.Variable) variables.Variable {
	if datastore.IsNoSQLDatabase() {
		if blueprintVariable, ok := v.(*blueprint.BlueprintBackendVariable); ok && blueprintVariable.IsNoSQLCursor() {
			targetVariable := blueprintVariable.GetTargetVariable()
			if ptrTargetVariable, ok := targetVariable.(*variables.PointerVariable); ok {
				return ptrTargetVariable.PointerTo
			} else if ifaceTargetVariable, ok := targetVariable.(*variables.InterfaceVariable); ok {
				logger.Logger.Fatalf("TODO!!!! %s", ifaceTargetVariable.String())
			} else {
				logger.Logger.Fatalf("????? %s", targetVariable.String())
			}
		}
	}
	return v
}

type noSQLQueryVariable struct {
	field string
	value variables.Variable
}

func getUnderlyingQueryVariablesIfNoSQLCollectionRead(datastore *datastores.Datastore, variable variables.Variable) []noSQLQueryVariable {
	if datastore.IsNoSQLDatabase() {
		// should be a bson.D which is a slice with many (inline) structures
		// e.g. query := bson.D{{Key: "productid", Value: productID}}
		if sliceVariable, ok := variable.(*variables.SliceVariable); ok {
			var queryVariables []noSQLQueryVariable
			for _, elem := range sliceVariable.GetElements() {
				if structVariable, ok := elem.(*variables.StructVariable); ok {
					logger.Logger.Warnf("%v", structVariable.Fields)
					var key, val variables.Variable
					if len(structVariable.FieldsLst) != 0 {
						key = structVariable.FieldsLst[0].(*variables.FieldVariable).GetWrappedVariable()
						val = structVariable.FieldsLst[1].(*variables.FieldVariable).GetWrappedVariable()
					} else {
						key = structVariable.Fields["Key"].(*variables.FieldVariable).GetWrappedVariable()
						val = structVariable.Fields["Value"].(*variables.FieldVariable).GetWrappedVariable()
					}
					queryVar := noSQLQueryVariable{
						field: datastore.Schema.GetRootFieldName() + "." + key.GetType().GetBasicValue(),
						value: val,
					}
					queryVariables = append(queryVariables, queryVar)
					return queryVariables
				}
			}
			return nil
		}

	}
	return nil
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
	vars, names := variables.GetReversedNestedFieldsAndNames(writtenVariable, "", datastore.IsNoSQLDatabase(), datastore.IsQueue())
	for i, variable := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := variable.GetNestedDependencies(false)
		logger.Logger.Infof("[TENTATIVE REF TAINTED VAR] [%s] (%02d) %s", variables.VariableTypeName(variable), variable.GetId(), variable.LongString())
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

/* var pendingNodes *stack.Stack

func BuildSchema2(app *app.App, entryNodes []AbstractNode) {
	pendingNodes = stack.New()
	for _, entry := range entryNodes {
		pendingNodes.Push(entry)
	}
	for {
		node := pendingNodes.Pop().(*AbstractNode)
		if pendingNodes.Len() == 0 {
			break
		}
	}
} */

func BuildSchema(app *app.App, frontends []string, entryNodes []AbstractNode) {
	visited := make(map[AbstractNode]bool, 0)
	for _, frontend := range frontends {
		for _, exposedMethod := range app.Services[frontend].ExposedMethodsLst {
			for _, entry := range entryNodes {
				if entry.GetName() == exposedMethod.GetName() {
					if _, isVisited := visited[entry]; !isVisited {
						doBuildSchema(app, entry)
						visited[entry] = true
					}
				}
			}
		}
	}

	/* logger.Logger.Debug()
	for i, pendingNode := range pendingNodes {
		logger.Logger.Debugf("[%d] pending node %s ", i, pendingNode.dbCall.String())
	}
	logger.Logger.Info()
	for i, node := range visitedNodes {
		logger.Logger.Infof("[%d] visited node %s ", i, node.String())
	} */
}

/* type pendingNode struct {
	dbCall *AbstractDatabaseCall
	done   bool
}

var pendingNodes []*pendingNode
var pendingDBs map[*datastores.Datastore]bool = make(map[*datastores.Datastore]bool) */

var visitedNodes []AbstractNode
var writtenDatastores = make(map[string]bool, 0)

func doBuildSchema(app *app.App, node AbstractNode) bool {
	if dbCall, ok := node.(*AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsRead() {
		datastore := dbCall.DbInstance.GetDatastore()
		/* if found := writtenDatastores[datastore.Name]; !found {
			logger.Logger.Warnf("[SCHEMA] skipping read for abstract node: %s", dbCall.String())
			pendingNodes = append(pendingNodes, &pendingNode{dbCall: dbCall})
			return false
		} */
		params := dbCall.GetParams()
		returns := dbCall.GetReturns()
		switch datastore.Type {
		case datastores.Queue:
			msg := params[1]
			taintDataflowReadOp(app, msg, dbCall, datastore, "message")
		case datastores.NoSQL:
			cursor := returns[0]
			rootFieldName := datastore.Schema.GetRootFieldName()
			taintDataflowReadOpUnnamed(app, cursor, dbCall, datastore, rootFieldName, false)

			query := params[1]
			queryVars := getUnderlyingQueryVariablesIfNoSQLCollectionRead(datastore, query)
			for _, v := range queryVars {
				taintDataflowReadOpUnnamed(app, v.value, dbCall, datastore, v.field, true)
			}
		case datastores.Cache:
			key := params[1]
			taintDataflowReadOpUnnamed(app, key, dbCall, datastore, "key", false)
			obj := params[2]
			taintDataflowReadOpUnnamed(app, obj, dbCall, datastore, "value", false)
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
			saveUnfoldedFieldsToDatastore(msg, "message", datastore)
			taintDataflowOp(app, msg, dbCall, datastore, "", true)
			referenceTaintedDataflowForNestedFields(msg, datastore)

		case datastores.NoSQL:
			doc := params[1]
			saveUnfoldedFieldsToDatastore(doc, "document", datastore)
			for i, param := range params {
				logger.Logger.Debugf("BUILD SCHEMA!!! (%d) (%s)", i, utils.GetType(param))
				if _, ok := param.(*variables.StructVariable); ok {
					variables.GetReversedNestedFieldsAndNames(param, "", datastore.IsNoSQLDatabase(), datastore.IsQueue())
				}
			}
			taintDataflowOp(app, doc, dbCall, datastore, "", true)
			referenceTaintedDataflowForNestedFields(doc, datastore)

		case datastores.Cache:
			key := params[1]
			value := params[2]
			saveFieldToDatastore(key, "key", datastore)
			saveFieldToDatastore(value, "value", datastore)
			taintDataflowOp(app, value, dbCall, datastore, "key", false)
			taintDataflowOp(app, value, dbCall, datastore, "value", false)
			referenceTaintedDataflowForSingleValue(key, datastore, "key")
			referenceTaintedDataflowForSingleValue(value, datastore, "value")
		}

		/* if _, exists := pendingDBs[datastore]; exists {
			l := len(pendingNodes)
			for i := 0; i < l; i++ {
				pending := pendingNodes[i]
				if !pending.done {
					pending.done = doBuildSchema(app, pending.dbCall)
				}
			}
		} */
	}

	visitedNodes = append(visitedNodes, node)

	/* if dbCall, ok := node.(*AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsUpdate() {
		logger.Logger.Fatalf("TODO FOR DB CALL: %s", dbCall.String())
	} */

	for _, child := range node.GetChildren() {
		doBuildSchema(app, child)
	}
	return true
}
