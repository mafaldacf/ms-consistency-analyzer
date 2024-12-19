package foreign_key

import (
	"fmt"
	"os"
	"path/filepath"
	"slices"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/objects"
	"analyzer/pkg/utils"
)

func NewDetector(app *app.App, graph *abstractgraph.AbstractGraph) *ForeignKeyDetector {
	return &ForeignKeyDetector{
		app:   app,
		graph: graph,
	}
}

func (detector *ForeignKeyDetector) Run() {
	detector.app.ResetAllDataflows()
	for requestIdx, entry := range detector.getGraph().Nodes {
		detector.analyzeNodes(entry.(*abstractgraph.AbstractServiceCall), entry, requestIdx)
		detector.app.ResetAllDataflows()
	}
}

// FIXME:
// checkForeignKeyRead gets all dependencies for the read object
// for each dependency, it iterates all previous read dataflows
// if the database field read on a previous (dependent) dataflow matches the current field
// then we detect a new foreignkey-based read
func (detector *ForeignKeyDetector) checkForeignKeyRead(obj objects.Object, originField *datastores.Entry, dbCall *abstractgraph.AbstractDatabaseCall) {
	logger.Logger.Infof("[FOREIGN KEY] check foreign key read for origin field (%s) and object: %s", originField.String(), obj.String())
	var savedOriginFieldName []string
	//datastore := dbCall.DbInstance.GetDatastore()
	for _, dep := range obj.GetNestedDependencies(true) {
		logger.Logger.Debugf("[FOREIGN KEY] \t dep: %s", dep.String())
		for _, df := range dep.GetVariableInfo().GetAllReadDataflowsExceptDatastore(dbCall.DbInstance.GetName()) { // except filter is just for sanity check
			//FIXME: for some reason there are some "loose" fields that
			// are not associated anymore with the (un)folded fields of the datastore schema
			// and which also unexpectedly do not have any References
			// so right now we are just getting the full name of the field that we want for the current dataflow
			// and then we get the field that is actually attached to the schema to get the correct References
			refField := df.Field.(*datastores.Entry)
			for _, field := range df.Field.GetDatastore().Schema.UnfoldedFields {
				if field.GetFullName() == refField.GetFullName() {
					attachedRefField := field.(*datastores.Entry)
					for _, refTarget := range attachedRefField.References {
						if !slices.Contains(savedOriginFieldName, originField.GetFullName()) && refTarget == originField {
							read := newForeignKeyRead(attachedRefField, originField, detector.app.GetDataflowForObjectDataflow(df).GetDatabaseCall(), dbCall.ParsedCall)
							detector.addForeignKeyRead(read)
							savedOriginFieldName = append(savedOriginFieldName, originField.GetFullName())
						}
					}
				}
			}
		}
	}
}

func (detector *ForeignKeyDetector) analyzeNodes(lastServiceCallNode *abstractgraph.AbstractServiceCall, node abstractgraph.AbstractNode, requestIdx int) {
	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		if dbCall.ParsedCall.Method.IsRead() {
			logger.Logger.Infof("[FOREIGN KEY] analyzing %s @ %s: %s", utils.GetType(dbCall), dbCall.DbInstance.GetName(), dbCall.String())
			datastore := dbCall.DbInstance.GetDatastore()
			params := dbCall.GetParams()
			returns := dbCall.GetReturns()

			switch datastore.Type {
			case datastores.Queue:
				msg := params[1]
				logger.Logger.Infof("[FOREIGN KEY - QUEUE MESSAGE] %s", msg.String())
				for _, df := range msg.GetVariableInfo().GetAllDataflows() {
					logger.Logger.Infof("[df] %s", df.String())
				}
				abstractgraph.TaintDataflowReadQueue(detector.app, msg, dbCall, datastore, datastores.ROOT_FIELD_NAME_QUEUE, requestIdx)
			case datastores.NoSQL:
				cursor, query := returns[0], params[1]

				queryObjs := abstractgraph.GetNoSQLQueryDocument(datastore, query)
				for _, qObj := range queryObjs {
					logger.Logger.Infof("[FOREIGN KEY - QUERY OBJ] %s", qObj.String())
					field := datastore.Schema.GetField(qObj.FieldName).(*datastores.Entry)
					detector.checkForeignKeyRead(qObj.Object, field, dbCall)
				}

				abstractgraph.TaintDataflowNoSQL(detector.app, cursor, dbCall, datastore, datastores.ROOT_FIELD_NAME_NOSQL, false, false, requestIdx)
				for _, obj := range queryObjs {
					logger.Logger.Infof("[FOREIGN KEY - QUERY OBJ] %s", obj.String())
					abstractgraph.TaintDataflowNoSQL(detector.app, obj.Object, dbCall, datastore, obj.FieldName, true, false, requestIdx)
				}
			case datastores.Cache:
				key, value := params[1], params[2]

				field := datastore.Schema.GetField(datastores.ROOT_FIELD_NAME_CACHE_KEY).(*datastores.Entry)
				detector.checkForeignKeyRead(key, field, dbCall)

				abstractgraph.TaintDataflowReadCache(detector.app, key, datastores.ROOT_FIELD_NAME_CACHE_KEY, dbCall, datastore, requestIdx)
				abstractgraph.TaintDataflowReadCache(detector.app, value, datastores.ROOT_FIELD_NAME_CACHE_VALUE, dbCall, datastore, requestIdx)

			default:
				logger.Logger.Fatalf("[FOREIGN KEY] TODO: %s", dbCall.String())
			}
		}
		/* if dbCall.ParsedCall.Method.IsWrite() {
			logger.Logger.Warnf("[FOREIGN KEY] skipping %s: %s", utils.GetType(dbCall), dbCall.String())
		} */
	} /*  else {
		logger.Logger.Debugf("[FOREIGN KEY] skipping %s: %s", utils.GetType(node), node.String())
	} */
	for _, child := range node.GetChildren() {
		detector.analyzeNodes(lastServiceCallNode, child, requestIdx)
	}
}

func (detector *ForeignKeyDetector) Results() string {
	results := "------------------------------------------------------------\n"
	results += "------------------- FOREIGN KEY ANALYSIS -------------------\n"
	results += "------------------------------------------------------------\n"
	for i, read := range detector.reads {
		results += fmt.Sprintf("foreign key read #%d:\n%s\n", i, read.String())
		if i < len(detector.reads)-1 {
			results += "\n" // enforce empty line between each foreign key read result
		}
	}
	detector.save(results)
	return results
}

func (detector *ForeignKeyDetector) save(results string) {
	path := fmt.Sprintf("output/%s/analysis/foreign_key.txt", detector.app.Name)

	dir := filepath.Dir(path)
	err := os.MkdirAll(dir, 0755)
	if err != nil {
		logger.Logger.Fatalf("[FOREIGN KEY] error creating directory %s: %s", dir, err.Error())
	}

	err = os.WriteFile(path, []byte(results), 0644)
	if err != nil {
		logger.Logger.Fatalf("[FOREIGN KEY] error writing data to %s: %s", path, err.Error())
	}
	logger.Logger.Tracef("[FOREIGN KEY] saved cascading detection results to %s", path)
}

func (detector *ForeignKeyDetector) CompactSchema() {
	for _, ds := range detector.app.Databases {
		for _, unfoldedField := range ds.GetDatastore().Schema.GetAllFields() {
			var refsToKeep []datastores.Field
			foreignReferences := detector.getUsedForeignReferencesForFieldInDatastore(unfoldedField.GetFullName(), ds.GetDatastore())
			for _, ref := range unfoldedField.(*datastores.Entry).References {
				if slices.Contains(foreignReferences, ref.GetFullName()) {
					refsToKeep = append(refsToKeep, ref)
				}
			}
			unfoldedField.(*datastores.Entry).References = refsToKeep
		}
	}
}
