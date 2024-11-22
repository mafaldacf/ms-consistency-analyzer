package abstractgraph

import (
	"fmt"
	"slices"

	/* "github.com/golang-collections/collections/stack" */

	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/objects"
	"analyzer/pkg/utils"
)

type DependencySet struct {
	Variable        objects.Object
	Dependencies    []objects.Object
	DependencyNames []string
}

func saveFieldToDatastore(variable objects.Object, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetType()
	datastore.Schema.GetOrCreateField(entryName, objType.GetName(), variable.GetId(), datastore)
	logger.Logger.Infof("[SCHEMA] [%s] added entry (%s): %s", datastore.Name, entryName, objType.LongString())
}

func saveUnfoldedFieldsToDatastore(variable objects.Object, entryName string, datastore *datastores.Datastore) {
	objType := variable.GetType()
	datastore.Schema.GetOrCreateField(entryName, objType.LongString(), variable.GetId(), datastore)
	logger.Logger.Infof("[SCHEMA] [%s] added entry (%s): %s", datastore.Name, entryName, objType.LongString())

	datastore.Schema.GetOrCreateField(objType.GetName(), objType.LongString(), variable.GetId(), datastore)
	logger.Logger.Infof("[SCHEMA] [%s] added field (%s): %s", datastore.Name, objType.GetName(), objType.LongString())

	datastore.Schema.GetOrCreateUnfoldedField(objType.GetName(), objType.LongString(), variable.GetId(), datastore)
	logger.Logger.Infof("[SCHEMA] [%s] added unfolded (entry) field (%s): %s", datastore.Name, objType.GetName(), objType.LongString())

	// add nested unfolded types
	types, names := objType.GetNestedFieldTypes(objType.GetName(), datastore.IsNoSQLDatabase())
	for i, t := range types {
		name := names[i]
		datastore.Schema.GetOrCreateUnfoldedField(name, t.LongString(), 0, datastore)
		logger.Logger.Infof("[SCHEMA] [%s] added nested field (%s): %s", datastore.GetName(), name, t.LongString())
	}
}

func taintDataflowOp(app *app.App, variable objects.Object, call *AbstractDatabaseCall, datastore *datastores.Datastore, fieldName string, includeNestedFields bool) {
	fmt.Printf("\n------------- TAINT WRITE DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetMethodStr(), datastore.Name)
	fmt.Println()

	// taint direct dataflow
	if fieldName == "" {
		fieldName = variable.GetType().GetName()
	}
	rootField := datastore.Schema.GetField(fieldName)
	df := variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable, rootField, true)
	app.AddDataflow(df, call.ParsedCall)
	logger.Logger.Debugf("[TAINT WRITE DIRECT] %s ---> (%02d) %s [%s]", rootField.GetFullName(), variable.GetId(), variable.String(), utils.GetType(variable))
	if !slices.Contains(app.TaintedVariables[rootField.GetFullName()], variable) {
		app.TaintedVariables[rootField.GetFullName()] = append(app.TaintedVariables[rootField.GetFullName()], variable)
	}
	var taintedVariables []objects.Object

	// taint indirect dataflow
	if fieldName == "" {
		fieldName = datastore.Schema.GetRootUnfoldedField().GetName()
	}
	var vars []objects.Object
	var names []string
	if includeNestedFields {
		vars, names = objects.GetReversedNestedFieldsAndNames(variable, fieldName, datastore.IsNoSQLDatabase(), datastore.IsQueue())
	} else {
		vars = []objects.Object{variable}
		names = []string{fieldName}
	}

	for i, v := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := v.GetNestedDependencies(false)
		logger.Logger.Infof("[TENTATIVE TAINT WRITE VAR] [%s] (%02d) (NUM DEPS = %d) %s", utils.GetType(v), v.GetId(), len(deps), v.LongString())

		for _, dep := range deps {
			logger.Logger.Debugf("visiting dep: %s", dep.String())
			for _, ref := range dep.GetVariableInfo().GetReferences() {
				logger.Logger.Warnf("ref: %s", ref.String())
			}
			if !slices.Contains(taintedVariables, dep) {
				df := v.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, variable, dbField, true)
				app.AddDataflow(df, call.ParsedCall)
				logger.Logger.Debugf("\t\t[TAINT WRITE INDIRECT] %s ---> (%02d) %s [%s]", dbField.GetFullName(), dep.GetId(), dep.String(), utils.GetType(dep))

				taintedVariables = append(taintedVariables, dep)
				app.AddTaintedVariableIfNotExists(dbField.GetFullName(), dep)
			}
		}

		/* if v.GetVariableInfo().GetName() == "postID_UploadSVC" {
			logger.Logger.Fatalf("%s", v.String())
		} */
	}
	fmt.Println()
}

func TaintDataflowReadQueue(app *app.App, variable objects.Object, call *AbstractDatabaseCall, datastore *datastores.Datastore, fieldName string) {
	fmt.Printf("\n------------- TAINT READ DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetName(), datastore.Name)
	fmt.Println()

	// taint direct dataflow
	rootField := datastore.Schema.GetField(fieldName)
	df := variable.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, variable, rootField, false)
	app.AddDataflow(df, call.ParsedCall)
	logger.Logger.Debugf("[TAINT READ DIRECT] %s ---> (%02d) %s [%s]", rootField.GetFullName(), variable.GetId(), variable.String(), utils.GetType(variable))
	if !slices.Contains(app.TaintedVariables[rootField.GetFullName()], variable) {
		app.TaintedVariables[rootField.GetFullName()] = append(app.TaintedVariables[rootField.GetFullName()], variable)
	}
	var taintedVariables []objects.Object

	// taint indirect dataflow
	rootUnfoldedField := datastore.Schema.GetRootUnfoldedField()
	logger.Logger.Debugf("rootUnfoldedField = %v", rootUnfoldedField)
	vars, names := objects.GetReversedNestedFieldsAndNames(variable, rootUnfoldedField.GetName(), datastore.IsNoSQLDatabase(), datastore.IsQueue())

	for i, v := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := v.GetNestedDependencies(false)
		logger.Logger.Infof("[TENTATIVE TAINT READ VAR] [%s] (%02d) (NUM DEPS = %d) %s", utils.GetType(v), v.GetId(), len(deps), v.LongString())
		for _, dep := range deps {
			if !slices.Contains(taintedVariables, dep) {
				df := v.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, variable, dbField, false)
				app.AddDataflow(df, call.ParsedCall)
				logger.Logger.Debugf("\t\t[TAINT READ INDIRECT] %s ---> (%02d) %s [%s]", dbField.GetFullName(), dep.GetId(), dep.String(), utils.GetType(dep))

				taintedVariables = append(taintedVariables, dep)
				app.AddTaintedVariableIfNotExists(dbField.GetFullName(), dep)
			}
		}
	}
	fmt.Println()
}

// aka TaintDataflowReadUnnamed
func TaintDataflowReadNoSQL(app *app.App, obj objects.Object, call *AbstractDatabaseCall, datastore *datastores.Datastore, fieldName string, queryField bool) {
	fmt.Printf("\n------------- TAINT READ (DOC) DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetMethodStr(), datastore.Name)
	fmt.Println()

	var field datastores.Field
	if queryField {
		field = datastore.Schema.GetOrCreateUnfoldedField(fieldName, obj.GetType().GetName(), obj.GetId(), datastore)
	} else { // cursor
		field = datastore.Schema.GetOrCreateRootField(datastores.ROOT_FIELD_NAME_NOSQL, datastores.UNKNOWN_FIELD_TYPE, -1, datastore)
	}

	// taint direct dataflow
	df := obj.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, obj, field, false)
	app.AddDataflow(df, call.ParsedCall)
	logger.Logger.Debugf("[TAINT READ (DOC) DIRECT] %s ---> (%02d) %s [%s]", field.GetFullName(), obj.GetId(), obj.String(), utils.GetType(obj))
	if !slices.Contains(app.TaintedVariables[field.GetFullName()], obj) {
		app.TaintedVariables[field.GetFullName()] = append(app.TaintedVariables[field.GetFullName()], obj)
	}

	var taintedVariables []objects.Object
	logger.Logger.Infof("[TENTATIVE TAINT READ (DOC) VAR] [%s] (%02d) @ %s", utils.GetType(obj), obj.GetId(), obj.LongString())
	obj = getTargetVariableIfNoSQLCursorRead(datastore, obj)
	deps := obj.GetNestedDependencies(false)
	logger.Logger.Infof("[TENTATIVE TAINT READ (DOC) VAR] [%s] NUM DEPS = %d @ %s", utils.GetType(obj), len(deps), obj.LongString())
	for _, dep := range deps {
		if !slices.Contains(taintedVariables, dep) {
			typeName := dep.GetType().GetName()

			if queryField {
				df := obj.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, obj, field, false)
				app.AddDataflow(df, call.ParsedCall)
			} else {
				entry := datastores.NewEntry(typeName, typeName, 0, datastore)
				df := obj.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, obj, entry, false)
				app.AddDataflow(df, call.ParsedCall)
			}
			logger.Logger.Debugf("\t\t[TAINT READ (DOC) INDIRECT] <unnamed> ---> (%02d) %s [%s]", dep.GetId(), dep.String(), utils.GetType(dep))

			taintedVariables = append(taintedVariables, dep)
			app.AddTaintedVariableIfNotExists(dep.GetType().GetName(), dep)
		}
	}

	if call.GetName() == "FindOne" && datastore.Name == "product_db" {
		logger.Logger.Debug("HERE!")
	}

	fmt.Println()
}

// aka TaintDataflowReadUnnamed
func TaintDataflowReadCache(app *app.App, obj objects.Object, fieldName string, call *AbstractDatabaseCall, datastore *datastores.Datastore) {
	fmt.Printf("\n------------- TAINT READ (KV) DATAFLOW FOR CALL %s @ %s -------------\n\n", call.GetMethodStr(), datastore.Name)
	fmt.Println()

	// taint direct dataflow
	rootField := datastore.Schema.GetOrCreateField(fieldName, datastores.UNKNOWN_FIELD_TYPE, -1, datastore)
	df := obj.GetVariableInfo().SetDirectDataflow(datastore.Name, call.Service, obj, rootField, false)
	app.AddDataflow(df, call.ParsedCall)
	logger.Logger.Debugf("[TAINT READ (KV) DIRECT] %s ---> (%02d) %s [%s]", rootField.GetFullName(), obj.GetId(), obj.String(), utils.GetType(obj))
	if !slices.Contains(app.TaintedVariables[rootField.GetFullName()], obj) {
		app.TaintedVariables[rootField.GetFullName()] = append(app.TaintedVariables[rootField.GetFullName()], obj)
	}

	var taintedVariables []objects.Object
	logger.Logger.Infof("[TENTATIVE TAINT READ (KV) VAR] [%s] (%02d) @ %s", utils.GetType(obj), obj.GetId(), obj.LongString())
	obj = getTargetVariableIfNoSQLCursorRead(datastore, obj)
	deps := obj.GetNestedDependencies(false)
	logger.Logger.Infof("[TENTATIVE TAINT READ (KV) VAR] [%s] NUM DEPS = %d @ %s", utils.GetType(obj), len(deps), obj.LongString())
	for _, dep := range deps {
		if !slices.Contains(taintedVariables, dep) {
			typeName := dep.GetType().GetName()

			entry := datastores.NewEntry(typeName, typeName, 0, datastore)
			df := obj.GetVariableInfo().SetIndirectDataflow(datastore.Name, call.Service, dep, obj, entry, false)
			app.AddDataflow(df, call.ParsedCall)

			logger.Logger.Debugf("\t\t[TAINT READ (KV) INDIRECT] <unnamed> ---> (%02d) %s [%s]", dep.GetId(), dep.String(), utils.GetType(dep))

			taintedVariables = append(taintedVariables, dep)
			app.AddTaintedVariableIfNotExists(dep.GetType().GetName(), dep)
		}
	}

	fmt.Println()
}

func getTargetVariableIfNoSQLCursorRead(datastore *datastores.Datastore, v objects.Object) objects.Object {
	if datastore.IsNoSQLDatabase() {
		if blueprintVariable, ok := v.(*blueprint.BlueprintBackendObject); ok && blueprintVariable.IsNoSQLCursor() {
			targetVariable := blueprintVariable.GetTargetObject()
			if ptrTargetVariable, ok := targetVariable.(*objects.PointerObject); ok {
				return ptrTargetVariable.PointerTo
			} else if ifaceTargetVariable, ok := targetVariable.(*objects.InterfaceObject); ok {
				logger.Logger.Fatalf("TODO!!!! %s", ifaceTargetVariable.String())
			} else { //FIXME: cursor.One(ctx, existing) --> this is happening in trainticket where "existing" object passed as a struct and not the ptr to it, but is this even possible
				logger.Logger.Warnf("????? [%s] %s", utils.GetType(targetVariable), targetVariable.String())
				return targetVariable
			}
		}
	}
	return v
}

type NoSQLQueryDocument struct {
	FieldName string
	Object    objects.Object
}

func (obj *NoSQLQueryDocument) String() string {
	return fmt.Sprintf("%s: %s", obj.FieldName, obj.Object.String())
}

func GetNoSQLQueryDocument_DEPRECATED(datastore *datastores.Datastore, variable objects.Object) []NoSQLQueryDocument {
	// should be a bson.D which is a slice with many (inline) structures
	// e.g. query := bson.D{{Key: "productid", Value: productID}}
	if sliceVariable, ok := variable.(*objects.SliceObject); ok {
		var queryObjects []NoSQLQueryDocument
		for i, elem := range sliceVariable.GetElements() {
			if structVariable, ok := elem.(*objects.StructObject); ok {
				logger.Logger.Warnf("MAP: %v", structVariable.GetFieldsMap())
				logger.Logger.Warnf("LIST: %v", structVariable.GetFieldsList())
				logger.Logger.Warnf("STRUCT: %v", structVariable.LongString())
				var key, val objects.Object
				if structVariable.NumFieldsList() != 0 {
					key = structVariable.GetFieldAt(0).GetWrappedVariable()
					val = structVariable.GetFieldAt(1).GetWrappedVariable()
				} else {
					key = structVariable.GetFieldByKey("Key").GetWrappedVariable()
					val = structVariable.GetFieldByKey("Value").GetWrappedVariable()
				}
				queryObj := NoSQLQueryDocument{
					FieldName: datastore.Schema.GetRootFieldName() + "." + key.GetType().GetBasicValue(),
					Object:    val,
				}
				queryObjects = append(queryObjects, queryObj)
				logger.Logger.Infof("[QUERY OBJ #%d] %s", i, queryObj.String())
				return queryObjects
			}
		}
		return nil
	}
	return nil
}

func GetNoSQLQueryDocument(datastore *datastores.Datastore, variable objects.Object) []NoSQLQueryDocument {
	// should be a bson.D which is a slice with many (inline) structures
	// e.g. query := bson.D{{Key: "productid", Value: productID}}
	if sliceVariable, ok := variable.(*objects.SliceObject); ok {
		var queryObjects []NoSQLQueryDocument
		for _, elem := range sliceVariable.GetElements() {
			if structVariable, ok := elem.(*objects.StructObject); ok {
				logger.Logger.Infof("[DOC_ELEM] [%s] %s", utils.GetType(structVariable), structVariable.LongString())

				key := structVariable.GetFieldAt(0).GetWrappedVariable()

				if key.GetType().GetBasicValue() == "$and" {
					// detect and handle the "$and" clause as an array of conditions
					//
					// e.g.
					// query := bson.D{{"$and", bson.A{
					//		bson.D{{"startstation", start}},
					//		bson.D{{"endstation", end}},
					// }}}
					// handle $and as an array of conditions
					andArray := structVariable.GetFieldAt(1).GetWrappedVariable()
					if andSlice, ok := andArray.(*objects.SliceObject); ok {
						logger.Logger.Warnf("[$AND_SLICE] [%s] %s", utils.GetType(andSlice), andSlice.LongString())
						for i, andElem := range andSlice.GetElements() {
							logger.Logger.Warnf("[$AND_ELEM #%d] [%s] %s", i, utils.GetType(andElem), andElem.LongString())
							for j, andNestedElem := range GetNoSQLQueryDocument(datastore, andElem) {
								logger.Logger.Warnf("[$AND_NESTED_ELEM #%d.%d] [%s] %s", i, j, utils.GetType(andNestedElem.Object), andNestedElem.Object.LongString())
								queryObjects = append(queryObjects, andNestedElem)
							}

							/* if andStruct, ok := andElem.(*objects.StructObject); ok {
								key := andStruct.GetFieldAt(0).GetWrappedVariable()
								val := andStruct.GetFieldAt(1).GetWrappedVariable()
								queryObj := NoSQLQueryDocument{
									FieldName: datastore.Schema.GetRootFieldName() + "." + key.GetType().GetBasicValue(),
									Object:    val,
								}
								queryObjects = append(queryObjects, queryObj)
								logger.Logger.Infof("[QUERY OBJ $AND] %s", queryObj.String())
							} */
						}
					}
				} else {
					// normal key-value pairs
					val := structVariable.GetFieldAt(1).GetWrappedVariable()
					queryObj := NoSQLQueryDocument{
						FieldName: datastore.Schema.GetRootFieldName() + "." + key.GetType().GetBasicValue(),
						Object:    val,
					}
					queryObjects = append(queryObjects, queryObj)
					logger.Logger.Debugf("[DOC QUERY OBJ] %s", queryObj.String())
				}
			}
		}
		return queryObjects
	}
	return nil
}

func referenceTaintedDataflowForSingleValue(writtenVariable objects.Object, datastore *datastores.Datastore, fieldName string) {
	fmt.Printf("\n------------- REFERENCE TAINTED DATAFLOW FOR WRITTEN VARIABLE %s @ %s -------------\n\n", writtenVariable.GetType().GetName(), datastore.Name)
	fmt.Println()
	dbField := datastore.Schema.GetField(fieldName)
	deps := writtenVariable.GetNestedDependencies(false)
	logger.Logger.Infof("[TENTATIVE REF TAINTED VAR] [%s] (%02d) %s", utils.GetType(writtenVariable), writtenVariable.GetId(), writtenVariable.LongString())
	for _, dep := range deps {
		for _, df := range dep.GetVariableInfo().GetAllDataflows() {
			if df.Datastore != datastore.Name {
				datastore.Schema.AddForeignReferenceToField(dbField, df.Field)
				datastore.AddReferencingDatastoreIfNotExists(df.Field.GetDatastore())
				logger.Logger.Debugf("\t\t[REF TAINTED DEP] (%s -> %s) from %s [%s]", dbField.GetFullName(), df.Field.GetFullName(), dep.String(), utils.GetType(dep))
			}
		}

	}
	fmt.Println()
}

func referenceTaintedDataflowForNestedFields(writtenVariable objects.Object, datastore *datastores.Datastore) {
	fmt.Printf("\n------------- REFERENCE TAINTED DATAFLOW FOR WRITTEN VARIABLE %s @ %s -------------\n\n", writtenVariable.GetType().GetName(), datastore.Name)
	fmt.Println()
	vars, names := objects.GetReversedNestedFieldsAndNames(writtenVariable, "", datastore.IsNoSQLDatabase(), datastore.IsQueue())
	for i, variable := range vars {
		dbField := datastore.Schema.GetField(names[i])
		deps := variable.GetNestedDependencies(false)
		logger.Logger.Infof("[TENTATIVE REF TAINTED VAR] [%s] (%02d) %s", objects.VariableTypeName(variable), variable.GetId(), variable.LongString())
		for _, dep := range deps {
			for _, df := range dep.GetVariableInfo().GetAllDataflows() {
				if df.Datastore != datastore.Name {
					datastore.Schema.AddForeignReferenceToField(dbField, df.Field)
					datastore.AddReferencingDatastoreIfNotExists(df.Field.GetDatastore())
					//logger.Logger.Fatalf("%s: %s", datastore.GetName(), datastore.ReferencedByDatastores[0].GetName())
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
			TaintDataflowReadQueue(app, msg, dbCall, datastore, datastores.ROOT_FIELD_NAME_QUEUE)
		case datastores.NoSQL:
			cursor, query := returns[0], params[1]
			TaintDataflowReadNoSQL(app, cursor, dbCall, datastore, datastores.ROOT_FIELD_NAME_NOSQL, false)
			queryObjs := GetNoSQLQueryDocument(datastore, query)
			for _, v := range queryObjs {
				TaintDataflowReadNoSQL(app, v.Object, dbCall, datastore, v.FieldName, true)
			}
		case datastores.Cache:
			key, value := params[1], params[2]
			TaintDataflowReadCache(app, key, datastores.ROOT_FIELD_NAME_CACHE_KEY, dbCall, datastore)
			TaintDataflowReadCache(app, value, datastores.ROOT_FIELD_NAME_CACHE_VALUE, dbCall, datastore)
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
			saveUnfoldedFieldsToDatastore(msg, datastores.ROOT_FIELD_NAME_QUEUE, datastore)
			taintDataflowOp(app, msg, dbCall, datastore, "", true)
			referenceTaintedDataflowForNestedFields(msg, datastore)

		case datastores.NoSQL:
			doc := params[1]
			saveUnfoldedFieldsToDatastore(doc, datastores.ROOT_FIELD_NAME_NOSQL, datastore)
			/* for i, param := range params {
				logger.Logger.Debugf("BUILD SCHEMA!!! (%d) (%s)", i, utils.GetType(param))
				if _, ok := param.(*objects.StructObject); ok {
					objects.GetReversedNestedFieldsAndNames(param, "", datastore.IsNoSQLDatabase(), datastore.IsQueue())
				}
			} */
			taintDataflowOp(app, doc, dbCall, datastore, "", true)
			referenceTaintedDataflowForNestedFields(doc, datastore)

		case datastores.Cache:
			key, value := params[1], params[2]
			saveFieldToDatastore(key, datastores.ROOT_FIELD_NAME_CACHE_KEY, datastore)
			saveFieldToDatastore(value, datastores.ROOT_FIELD_NAME_CACHE_VALUE, datastore)
			taintDataflowOp(app, value, dbCall, datastore, datastores.ROOT_FIELD_NAME_CACHE_KEY, false)
			taintDataflowOp(app, value, dbCall, datastore, datastores.ROOT_FIELD_NAME_CACHE_VALUE, false)
			referenceTaintedDataflowForSingleValue(key, datastore, datastores.ROOT_FIELD_NAME_CACHE_KEY)
			referenceTaintedDataflowForSingleValue(value, datastore, datastores.ROOT_FIELD_NAME_CACHE_VALUE)
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
