package detection

import (
	"slices"

	"github.com/golang-collections/collections/stack"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/datastores"
	"analyzer/pkg/detection/xcy"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
	"analyzer/pkg/types/objects"
)

type DetectionSet struct {
	DetectionMode DetectionMode
	Requests      []*xcy.Request
}

type Detector struct {
	DetectionMode DetectionMode
	Requests      []*xcy.Request
	DatastoresOps map[*datastores.Datastore][]*xcy.Operation
}

type DetectionMode int

const (
	FOREIGN_KEYS_DEFAULT DetectionMode = iota
	FOREIGN_KEYS_LINEAGES
	XCY_ALL_DATASTORES
	XCY_EQUAL_DATASTORES
	DEBUG_LINEAGES
	DEBUG_XCY_MISSING_DEPENDENCIES
	DEBUG_XCY_MINIMIZE_DEPENDENCIES
)

func GetAllDetectioModes() []DetectionMode {
	return []DetectionMode{
		XCY_ALL_DATASTORES,
		XCY_EQUAL_DATASTORES,
		FOREIGN_KEYS_DEFAULT,
		FOREIGN_KEYS_LINEAGES,
		DEBUG_LINEAGES,
		DEBUG_XCY_MISSING_DEPENDENCIES,
		DEBUG_XCY_MINIMIZE_DEPENDENCIES,
	}
}

func (detector *Detector) DetectionModeName() string {
	var detectionMap = map[DetectionMode]string{
		FOREIGN_KEYS_DEFAULT:            "FOREIGN_KEYS_DEFAULT",
		FOREIGN_KEYS_LINEAGES:           "FOREIGN_KEYS_LINEAGES",
		XCY_ALL_DATASTORES:              "XCY_ALL_DATASTORES",
		XCY_EQUAL_DATASTORES:            "XCY_EQUAL_DATASTORES",
		DEBUG_LINEAGES:                  "DEBUG_LINEAGES",
		DEBUG_XCY_MISSING_DEPENDENCIES:  "DEBUG_XCY_MISSING_DEPENDENCIES",
		DEBUG_XCY_MINIMIZE_DEPENDENCIES: "DEBUG_XCY_MINIMIZE_DEPENDENCIES",
	}
	return detectionMap[detector.DetectionMode]
}

func (detector *Detector) DetectionModeUsesLineages() bool {
	var modesWithLineages = []DetectionMode{
		FOREIGN_KEYS_LINEAGES,
		XCY_ALL_DATASTORES,
		XCY_EQUAL_DATASTORES,
		DEBUG_LINEAGES,
		DEBUG_XCY_MISSING_DEPENDENCIES,
		DEBUG_XCY_MINIMIZE_DEPENDENCIES,
	}
	return slices.Contains(modesWithLineages, detector.DetectionMode)
}

func (detector *Detector) GetRequests() []*xcy.Request {
	return detector.Requests
}

func NewDatastoreOps() map[*datastores.Datastore][]*xcy.Operation {
	return make(map[*datastores.Datastore][]*xcy.Operation)
}

func InitDetector(datastoreOps map[*datastores.Datastore][]*xcy.Operation, mode DetectionMode) *Detector {
	return &Detector{
		DatastoresOps: datastoreOps,
		DetectionMode: mode,
	}
}

func (detector *Detector) GetDatastoreOps() map[*datastores.Datastore][]*xcy.Operation {
	return detector.DatastoresOps
}

func (detector *Detector) UpdateDatastoreOps(ops map[*datastores.Datastore][]*xcy.Operation) {
	detector.DatastoresOps = ops
}

func (detector *Detector) InitRequest(entryNode abstractgraph.AbstractNode) *xcy.Request {
	request := &xcy.Request{
		EntryNode:     entryNode,
		LineagesStack: stack.New(),
	}
	request.PushLineage()
	detector.Requests = append(detector.Requests, request)
	return request
}

func (detector *Detector) captureInconsistency(request *xcy.Request, read *xcy.Operation, readCall *abstractgraph.AbstractDatabaseCall) []*xcy.Inconsistency {
	var inconsistencies []*xcy.Inconsistency
	if readCall.DbInstance.IsQueue() {
		// skip inconsistencies between a write and a read in the same queue
		return inconsistencies
	}

	var dependencies []*xcy.Operation
	if detector.HasDetectionMode(DEBUG_XCY_MISSING_DEPENDENCIES) {
		dependencies = request.GetDependencies()
	} else {
		dependencies = request.CurrentLineage().GetDependenciesByMostRecent()
	}
	logger.Logger.Tracef("[XCY LINEAGES] got dependencies: %v", dependencies)

	for _, write := range dependencies {
		if detector.HasDetectionMode(XCY_ALL_DATASTORES) {
			inconsistency := &xcy.Inconsistency{
				Write: write,
				Read:  read,
			}
			request.AddInconsistency(inconsistency)
			continue
		}

		if detector.HasDetectionMode(XCY_EQUAL_DATASTORES) {
			if readCall.DbInstance.GetDatastore() == write.Datastore {
				inconsistency := &xcy.Inconsistency{
					Write: write,
					Read:  read,
				}
				request.AddInconsistency(inconsistency)
			}
			continue
		}

		if readCall.DbInstance.GetDatastore() == write.Datastore {
			logger.Logger.Debugf("[XCY] evaluating XCY violation for read (%s @ %s) and write (%s @ %s)", read.Key.GetVariableInfo().Name, readCall.DbInstance.GetName(), write.Key.GetVariableInfo().Name, write.Datastore.GetName())

			inconsistency := &xcy.Inconsistency{
				Write: write,
				Read:  read,
			}

			readUnderlyingVars := read.GetKeyUnderlyingVariables()
			writeUnderlyingVars := write.GetObjectUnderlyingVariables()
			logger.Logger.Tracef("[READ KEY] dependencies for (%s) %s: \n%v", utils.GetType(read.Key), read.Key.String(), objects.GetDependenciesStringLst(readUnderlyingVars...))
			logger.Logger.Tracef("[WRITE VALUE] dependencies for (%s) %s: \n%v", utils.GetType(write.Object), write.Object.String(), objects.GetDependenciesStringLst(writeUnderlyingVars...))

			for _, readVar := range readUnderlyingVars {
				readDfs := readVar.GetVariableInfo().GetAllDataflowsForDatastore(readCall.DbInstance.GetName())
				for _, readDf := range readDfs {
					for _, writeVar := range writeUnderlyingVars {
						if readDf.HasVariable(writeVar) {
							inconsistency.AppendDataflows(writeVar.GetVariableInfo().GetAllDataflows())
						}
					}
				}
			}

			if inconsistency.Dataflows != nil {
				logger.Logger.Warnf("[XCY] found inconsistency: %s", inconsistency.String())
				request.AddInconsistency(inconsistency)
				inconsistencies = append(inconsistencies, inconsistency)
			}
		}
	}
	return inconsistencies
}

func operationDataDependsOnPrevious(op_1 *xcy.Operation, op_2 *xcy.Operation) bool {
	datastore_1 := op_1.GetDatastore()
	datastore_2 := op_2.GetDatastore()

	if datastore_1 != datastore_2 {
		opUnderlyingVars_1 := op_1.GetAllUnderlyingVariables()
		opUnderlyingVars_2 := op_2.GetKeyUnderlyingVariables()

		for _, opVar_2 := range opUnderlyingVars_2 { //FIXME: SHOULD BE ONLY READ DATAFLOWS
			dataflows := opVar_2.GetVariableInfo().GetAllDataflowsForDatastore(datastore_2.GetName())
			for _, dataflow := range dataflows {
				if dataflow.HasAnyVariable(opUnderlyingVars_1) {
					return true
				}
			}
		}
	}
	return false
}

func filterWriteDependencySet(writes_1 []*xcy.Operation, read_2 *xcy.Operation) {
	for _, write_1 := range writes_1 {
		for _, dep_1 := range write_1.GetVisibleDependenciesForDatastore(read_2.GetDatastore()) {
			write_1.AddMinimizedDependencyIfNotExists(dep_1)
		}
	}
}

func (detector *Detector) MinimizeDependecySets(request *xcy.Request) {
	if !detector.HasDetectionMode(DEBUG_XCY_MINIMIZE_DEPENDENCIES) {
		return
	}
	reads := request.GetReadOperations()
	for i, read_1 := range reads {
		writes_1 := detector.getWriteOperationsForDatastore(read_1.GetDatastore())
		for j := i + 1; j < len(reads); j++ {
			read_2 := reads[j]
			if operationDataDependsOnPrevious(read_1, read_2) {
				logger.Logger.Warnf("READ 2 (%s) DEPENDS ON READ 1 (%s)", read_2.String(), read_1.String())
				filterWriteDependencySet(writes_1, read_2)
			}
		}
	}
}

func (detector *Detector) InitXCYRequestTransversal(request *xcy.Request) {
	logger.Logger.Tracef("[XCY] init tranversal for entry node: %s", request.EntryNode.GetName())
	for _, edge := range request.EntryNode.GetChildren() {
		/* fmt.Println("\n------------------------------------------------------------------------------------------------------------------------------------------------")
		logger.Logger.Infof("[XCY] transversing child node: %s", edge.GetName())
		fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------") */
		detector.transverseOperations(request, edge)
	}
}

func (detector *Detector) HasDetectionMode(mode DetectionMode) bool {
	return detector.DetectionMode == mode
}

func detectMissingDependencies(request *xcy.Request, inconsistencies []*xcy.Inconsistency) {
	for _, inconsistency := range inconsistencies {
		if !slices.Contains(request.CurrentLineage().GetDependenciesByMostRecent(), inconsistency.Write) {
			inconsistency.MissingDependency = true
		}
	}
}

func (detector *Detector) attachOperationToDatastore(operation *xcy.Operation) {
	detector.DatastoresOps[operation.GetDatastore()] = append(detector.DatastoresOps[operation.GetDatastore()], operation)
}

func (detector *Detector) getWriteOperationsForDatastore(datastore *datastores.Datastore) []*xcy.Operation {
	var ops []*xcy.Operation
	for _, op := range detector.DatastoresOps[datastore] {
		if op.Write {
			ops = append(ops, op)
		}
	}
	return ops
}

func (detector *Detector) transverseOperations(request *xcy.Request, node abstractgraph.AbstractNode) {
	// FIXME: maybe we should link the two stateful nodes (push and pop) in the abstract graph
	// instead of placing a stateless queue handler between both
	if detector.DetectionModeUsesLineages() {
		if _, ok := node.(*abstractgraph.AbstractQueueHandler); ok {
			request.PushLineage()
		}
	}

	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		var operation *xcy.Operation
		if backend, ok := dbCall.ParsedCall.Method.(*blueprint.BackendMethod); ok {
			if backend.IsWrite() || backend.IsUpdate() {
				operation = request.SaveWriteOperation(dbCall, backend)
				detector.attachOperationToDatastore(operation)
				logger.Logger.Infof("[XCY] saved write %s", operation.String())
			} else if backend.IsRead() {
				operation = request.SaveReadOperation(dbCall, backend)
				detector.attachOperationToDatastore(operation)
				logger.Logger.Infof("[XCY] saved read %s", operation.String())
				if !detector.HasDetectionMode(DEBUG_LINEAGES) {
					inconsistencies := detector.captureInconsistency(request, operation, dbCall)
					if detector.HasDetectionMode(DEBUG_XCY_MISSING_DEPENDENCIES) && len(inconsistencies) > 0 {
						detectMissingDependencies(request, inconsistencies)
					}
				}
			} else {
				logger.Logger.Warnf("[XCY] ignoring operation: %s", dbCall.String())
			}
			if operation != nil && detector.HasDetectionMode(DEBUG_XCY_MINIMIZE_DEPENDENCIES) {
				detector.attachOperationToDatastore(operation)
			}
		}
	}
	for _, edge := range node.GetChildren() {
		detector.transverseOperations(request, edge)
	}

	// FIXME: maybe we should link the two stateful nodes (push and pop) in the abstract graph
	// instead of placing a stateless queue handler between both
	if detector.DetectionModeUsesLineages() {
		if _, ok := node.(*abstractgraph.AbstractQueueHandler); ok {
			request.PopLineage()
		}
	}
}
