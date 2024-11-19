package cascade

import (
	"fmt"
	"os"
	"path/filepath"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/logger"
)

func InitDetector(app *app.App, graph *abstractgraph.AbstractGraph) *CascadeDetector {
	return &CascadeDetector{
		app:   app,
		graph: graph,
	}
}

func (detector *CascadeDetector) Run() {
	for idx, entry := range detector.getGraph().Nodes {
		detector.analyzeDependencyNodes(entry.(*abstractgraph.AbstractServiceCall), entry, idx)
	}
}

func (detector *CascadeDetector) analyzeDependencyNodes(lastServiceCallNode *abstractgraph.AbstractServiceCall, node abstractgraph.AbstractNode, child_idx int) {
	if svcCall, ok := node.(*abstractgraph.AbstractServiceCall); ok {
		lastServiceCallNode = svcCall
	}

	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsDelete() {
		// 1. check if other datastores hold a foreign key referencing the deleted object
		// 2. for each one of these services, check if they were notified about the deletion of the object
		// either before the deletion (which does not make sense, but is still possible) or after deleting
		// the "deletion notification" is expected to contain some information about the object that was just deleted and is done throught one of the following:
		// (i) message broker (queue)
		// (ii) RPC
		// NOTE: for now, we ony consider message brokers

		// 3. TODO LATER: to be more precise, we can check which object was deleted and if that specific reference to that object was deleted aswell

		deleteOp := &deleteOperation{
			call:         dbCall,
			datastore:    dbCall.DbInstance.GetDatastore(),
		}

		for _, datastoreInstance := range detector.getApp().GetDbInstances() {
			dependentDatastore := datastoreInstance.GetDatastore()
			// discard current datastore
			if dependentDatastore != deleteOp.datastore {
				// found a datastore that has fields referencing the current one
				if dependentDatastore.IsReferencingDatastore(deleteOp.datastore) {
					for _, service := range detector.getApp().GetServices() {
						if service.HasDatastore(dependentDatastore) {
							deleteDep := &deleteDependency{
								service: service,
								datastore: dependentDatastore,
							}
							if !deleteOp.hasDependency(deleteDep) {
								deleteOp.addDependency(deleteDep)
								logger.Logger.Debugf("[CASCADE DETECTOR] added dependency %s to %s", deleteDep.String(), deleteOp.String())
							}
						}
					}
				}
			}
		}
		detector.addDeleteOperation(deleteOp)
		detector.searchCascadingDeletes(deleteOp, lastServiceCallNode, dbCall, child_idx)
	}

	for idx, child := range node.GetChildren() {
		detector.analyzeDependencyNodes(lastServiceCallNode, child, idx)
	}
}

func (detector *CascadeDetector) searchCascadingDeletes(deleteOp *deleteOperation, lastServiceCallNode *abstractgraph.AbstractServiceCall, deleteCall *abstractgraph.AbstractDatabaseCall, child_idx int) {
	logger.Logger.Infof("[CASCADE DETECTOR] searching for cascading deletes originating @ (%s, %s): %s", deleteCall.GetCallerStr(), deleteCall.DbInstance.GetDatastore().GetName(), deleteCall.LongString())
	for idx := child_idx + 1; idx < len(lastServiceCallNode.GetChildren()); idx++ {
		node := lastServiceCallNode.GetChildren()[idx]
		// found call that pushes notifications
		if pushCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok && pushCall.DbInstance.GetDatastore().IsQueue() && pushCall.ParsedCall.Method.IsWrite() {
			logger.Logger.Debugf("[CASCADE DETECTOR] found push call @ (%s, %s): %s", pushCall.GetCallerStr(), pushCall.DbInstance.GetDatastore().GetName(), pushCall.String())
			queueReadNodes := pushCall.GetChildren()
			// check all calls that follow the read of the queue
			for _, queueReadNode := range queueReadNodes {
				// check if after reading the queue, there is a delete operation to the same original database that is being referenced
				for _, child := range queueReadNode.GetChildren() {
					if childDeleteCall, ok := child.(*abstractgraph.AbstractDatabaseCall); ok && childDeleteCall.ParsedCall.Method.IsUpdate() || childDeleteCall.ParsedCall.Method.IsDelete() {
						logger.Logger.Debugf("[CASCADE DETECTOR] found child update/delete call @ (%s, %s): %s", childDeleteCall.Service, childDeleteCall.DbInstance, childDeleteCall.LongString())
						if deleteDep := deleteOp.getDependency(childDeleteCall.Service, childDeleteCall.DbInstance.GetDatastore()); deleteDep != nil {
							logger.Logger.Debugf("[CASCADE DETECTOR] found cascading action!")
							deleteDep.cascading = true
						}
					}
				}
			}
		}
	}
}

func (detector *CascadeDetector) Results() string {
	// red := "\033[31m"
	// reset := "\033[0m"
	bold_light_red := "\033[1;31m"
	results := "-------------------- CASCADING ANALYSIS --------------------"
	
	for _, op := range detector.getDeleteOperations() {
		results += fmt.Sprintf("\norigin operation = %s\n", op.LongString())
		for _, dep := range op.getDependencies() {
			if !dep.cascading {
				results += fmt.Sprintf("\t - missing cascading delete @ %s\n", dep.LongString())
			}
		}
	}
	detector.saveResults(results)
	return "\n\n" + bold_light_red + results
}

func (detector *CascadeDetector) saveResults(results string) {
	path := fmt.Sprintf("output/%s/analysis/cascade.txt", detector.app.Name)

	dir := filepath.Dir(path)
	err := os.MkdirAll(dir, 0755)
	if err != nil {
		logger.Logger.Fatalf("[CASCADE] error creating directory %s: %s", dir, err.Error())
	}

	err = os.WriteFile(path, []byte(results), 0644)
	if err != nil {
		logger.Logger.Fatalf("[CASCADE] error writing data to %s: %s", path, err.Error())
	}
	logger.Logger.Tracef("[CASCADE] saved cascading detection results to %s", path)
}
