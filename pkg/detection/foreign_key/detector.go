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
	for idx, entry := range detector.getGraph().Nodes {
		detector.analyzeNodes(entry.(*abstractgraph.AbstractServiceCall), entry, idx)
		detector.app.ResetAllDataflows()
	}
}

func (detector *ForeignKeyDetector) checkForeignKeyRead(obj objects.Object, originField *datastores.Entry, datastore *datastores.Datastore) {
	var savedOriginFieldName []string
	for _, dep := range obj.GetNestedDependencies(false) {
		for _, df := range dep.GetVariableInfo().GetAllReadDataflowsExceptDatastore(datastore.Name) {
			refField := df.Field.(*datastores.Entry)
			for _, refTarget := range refField.References {
				if !slices.Contains(savedOriginFieldName, originField.GetFullName()) && refTarget == originField {
					read := newForeignKeyRead(originField, refField)
					detector.addForeignKeyRead(read)
					savedOriginFieldName = append(savedOriginFieldName, originField.GetFullName())
				}
			}
		}
	}
}

func (detector *ForeignKeyDetector) analyzeNodes(lastServiceCallNode *abstractgraph.AbstractServiceCall, node abstractgraph.AbstractNode, child_idx int) {
	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		if dbCall.ParsedCall.Method.IsRead() {
			logger.Logger.Infof("[FOREIGN KEY] analyzing %s: %s", utils.GetType(dbCall), dbCall.String())
			datastore := dbCall.DbInstance.GetDatastore()
			params := dbCall.GetParams()
			//returns := dbCall.GetReturns()

			switch datastore.Type {
			case datastores.Queue:
				msg := params[1]
				logger.Logger.Infof("[QUEUE MESSAGE] %s", msg.String())
				for _, df := range msg.GetVariableInfo().GetAllDataflows() {
					logger.Logger.Infof("[df] %s", df.String())
				}
				abstractgraph.TaintDataflowReadQueue(detector.app, msg, dbCall, datastore, "message")
			case datastores.NoSQL:

				query := params[1]
				queryObjs := abstractgraph.GetQueryObjectsIfNoSQLRead(datastore, query)
				for _, obj := range queryObjs {
					logger.Logger.Infof("[QUERY OBJ] %s", obj.String())
					field := datastore.Schema.GetField(obj.Field).(*datastores.Entry)
					detector.checkForeignKeyRead(obj.Value, field, dbCall.DbInstance.GetDatastore())
				}
				for _, obj := range queryObjs {
					logger.Logger.Infof("[QUERY OBJ] %s", obj.String())
					/* for _, df := range obj.Value.GetVariableInfo().GetAllDataflows() {
						logger.Logger.Warnf("[df] %s", df.String())
					}
					for _, dep := range obj.Value.GetNestedDependencies(false) {
						logger.Logger.Infof("\t[QUERY DEP] %s", dep.String())
						for _, df := range dep.GetVariableInfo().GetAllWriteDataflowsForDatastore("notifications_queue") {
							logger.Logger.Warnf("\t[df] %s", df.String())
						}
					} */
					abstractgraph.TaintDataflowRead(detector.app, obj.Value, dbCall, datastore, obj.Field, true)
				}
			default:
				logger.Logger.Fatalf("[FOREIGN KEY] TODO: %s", dbCall.String())
			}
		}
		if dbCall.ParsedCall.Method.IsWrite() {
			logger.Logger.Warnf("[FOREIGN KEY] analyzing %s: %s", utils.GetType(dbCall), dbCall.String())
		}
	} else {
		logger.Logger.Debugf("[FOREIGN KEY] analyzing %s: %s", utils.GetType(node), node.String())
	}
	for i, child := range node.GetChildren() {
		detector.analyzeNodes(lastServiceCallNode, child, i)
	}
}

func (detector *ForeignKeyDetector) Results() string {
	results := "------------------------------------------------------------\n"
	results += "------------------- FOREIGN KEY ANALYSIS -------------------\n"
	results += "------------------------------------------------------------\n"
	for i, read := range detector.reads {
		results += fmt.Sprintf("foreign key read #%d:\t%s ---> %s\n", i, read.refField.GetFullName(), read.originField.GetFullName())
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
