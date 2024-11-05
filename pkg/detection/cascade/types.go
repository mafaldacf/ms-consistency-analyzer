package cascade

import (
	"fmt"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
)

// ----------------
// CASCADE DETECTOR
// ----------------

type CascadeDetector struct {
	app              *app.App
	graph            *abstractgraph.AbstractGraph
	deleteOperations []*deleteOperation
}

func (detector *CascadeDetector) getApp() *app.App {
	return detector.app
}

func (detector *CascadeDetector) getGraph() *abstractgraph.AbstractGraph {
	return detector.graph
}

func (detector *CascadeDetector) addDeleteOperation(op *deleteOperation) {
	detector.deleteOperations = append(detector.deleteOperations, op)
}

func (detector *CascadeDetector) getDeleteOperations() []*deleteOperation {
	return detector.deleteOperations
}

// ----------------
// DELETE OPERATION
// ----------------

type deleteOperation struct {
	call         *abstractgraph.AbstractDatabaseCall
	datastore    *datastores.Datastore
	dependencies []*deleteDependency
}

func (op *deleteOperation) getCall() *abstractgraph.AbstractDatabaseCall {
	return op.call
}

func (op *deleteOperation) getDependencies() []*deleteDependency {
	return op.dependencies
}

func (op *deleteOperation) addDependency(dep *deleteDependency) {
	op.dependencies = append(op.dependencies, dep)
}

func (op *deleteOperation) hasDependency(other *deleteDependency) bool {
	for _, dep := range op.getDependencies() {
		if dep.isEqual(other) {
			return true
		}
	}
	return false
}

func (op *deleteOperation) getDependency(serviceName string, datastore *datastores.Datastore) *deleteDependency {
	for _, dep := range op.getDependencies() {
		if dep.hasServiceAndDatastore(serviceName, datastore) {
			return dep
		}
	}
    logger.Logger.Warnf("[CASCADE DETECTOR] could not find dependency for service (%s) and datastore (%s) for origin delete operation %s")
	return nil
}

func (op *deleteOperation) LongString() string {
	call := op.getCall()
	return fmt.Sprintf("(%s, %s) -> %s", call.GetCallerStr(), call.DbInstance.GetDatastore().GetName(), call.LongString())
}

func (op *deleteOperation) String() string {
	return fmt.Sprintf("datastore = %s", op.datastore.Name)
}

// -----------------
// DELETE DEPENDENCY
// -----------------

type deleteDependency struct {
	service   *service.Service
	datastore *datastores.Datastore
	cascading bool
}

func (dep *deleteDependency) hasServiceAndDatastore(serviceName string, datastore *datastores.Datastore) bool {
	return dep.service.GetName() == serviceName && dep.datastore == datastore
}

func (dep *deleteDependency) isEqual(other *deleteDependency) bool {
	return dep.service == other.service && dep.datastore == other.datastore
}

func (dep *deleteDependency) String() string {
	return fmt.Sprintf("(%s, %s)", dep.service.Name, dep.datastore.GetName())
}

func (dep *deleteDependency) LongString() string {
	return fmt.Sprintf("(%s, %s)", dep.service.Name, dep.datastore.GetName())
}
