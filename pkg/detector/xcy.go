package detector

import (
	"encoding/json"
	"fmt"
	"slices"

	"github.com/golang-collections/collections/stack"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

type Request struct {
	EntryNode       abstractgraph.AbstractNode `json:"-"`
	DetectionMode   DetectionMode              `json:"detection_mode"`
	Inconsistencies []*Inconsistency           `json:"xcy_inconsistencies"`
	Lineages        []*Lineage                 `json:"lineages"`
	Operations      []*Operation               `json:"-"`
	LineagesStack   *stack.Stack               `json:"-"`
}

func GetAllDetectioModes() []DetectionMode {
	return []DetectionMode{CROSS_ASSOCIATIONS_DEFAULT, CROSS_ASSOCIATIONS_LINEAGES, LINEAGES_IMPLICIT_DEFAULT, LINEAGES_IMPLICIT_EQUAL_DATASTORES, DEBUG_OPERATIONS}
}

type DetectionMode int

const (
	CROSS_ASSOCIATIONS_DEFAULT DetectionMode = iota
	CROSS_ASSOCIATIONS_LINEAGES
	LINEAGES_IMPLICIT_DEFAULT
	LINEAGES_IMPLICIT_EQUAL_DATASTORES
	DEBUG_OPERATIONS
)

func (request *Request) DetectionModeName() string {
	var detectionMap = map[DetectionMode]string{
		CROSS_ASSOCIATIONS_DEFAULT:         "CROSS_ASSOCIATIONS_DEFAULT",
		CROSS_ASSOCIATIONS_LINEAGES:        "CROSS_ASSOCIATIONS_LINEAGES",
		LINEAGES_IMPLICIT_DEFAULT:          "LINEAGES_IMPLICIT_DEFAULT",
		LINEAGES_IMPLICIT_EQUAL_DATASTORES: "LINEAGES_IMPLICIT_EQUAL_DATASTORES",
		DEBUG_OPERATIONS:                   "DEBUG_OPERATIONS",
	}
	return detectionMap[request.DetectionMode]
}

func (request *Request) DetectionModeUsesLineages() bool {
	var modesWithLineages = []DetectionMode{
		CROSS_ASSOCIATIONS_LINEAGES,
		LINEAGES_IMPLICIT_DEFAULT,
		LINEAGES_IMPLICIT_EQUAL_DATASTORES,
		DEBUG_OPERATIONS,
	}
	return slices.Contains(modesWithLineages, request.DetectionMode)
}

func (request *Request) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Mode                  string           `json:"detection_mode"`
		NumberInconsistencies int              `json:"number_inconsistencies"`
		Inconsistencies       []*Inconsistency `json:"xcy_inconsistencies"`
		Lineages              []*Lineage       `json:"lineages"`
	}{
		Mode:                  request.DetectionModeName(),
		NumberInconsistencies: len(request.Inconsistencies),
		Inconsistencies:       request.Inconsistencies,
		Lineages:              request.Lineages,
	})
}

func (request *Request) AddInconsistency(inconsistency *Inconsistency) {
	request.Inconsistencies = append(request.Inconsistencies, inconsistency)
}

func (request *Request) AddWrite(op *Operation) {
	op.ID = len(request.CurrentLineage().Operations)
	op.LineageID = request.CurrentLineage().ID
	request.Operations = append(request.Operations, op)
}

func (request *Request) AddRead(op *Operation) {
	op.ID = len(request.CurrentLineage().Operations)
	op.LineageID = request.CurrentLineage().ID
	request.Operations = append(request.Operations, op)
}

func (request *Request) PushLineage() {
	lineage := &Lineage{
		ID: len(request.Lineages),
	}
	if lineage.ID != 0 {
		lineage.Previous = request.CurrentLineage()
	}
	request.LineagesStack.Push(lineage)
	logger.Logger.Infof("[XCY LINEAGES - PUSH] %s", lineage.String())
	request.Lineages = append(request.Lineages, lineage)
}

func (request *Request) CurrentLineage() *Lineage {
	lineage := request.LineagesStack.Peek().(*Lineage)
	logger.Logger.Tracef("[XCY LINEAGES - PEEK] %s", lineage.String())
	return lineage
}

func (request *Request) PopLineage() *Lineage {
	lineage := request.LineagesStack.Pop().(*Lineage)
	logger.Logger.Infof("[XCY LINEAGES - POP] %s", lineage.String())
	return lineage
}

type Inconsistency struct {
	Write     *Operation
	Read      *Operation
	Dataflows []*variables.Dataflow
}

func (inconsistency *Inconsistency) MarshalJSON() ([]byte, error) {
	var dataflows []string
	for _, df := range inconsistency.Dataflows {
		prefix := ""
		if !df.Direct {
			prefix = "[indirect] "
		}
		repr := fmt.Sprintf("%s%s(%s, %s.%s)", prefix, df.GetOpString(), df.Service, df.Datastore, df.Field.GetName())
		if !slices.Contains(dataflows, repr) {
			dataflows = append(dataflows, repr)
		}
	}

	return json.Marshal(&struct {
		Write     *Operation `json:"write"`
		Read      *Operation `json:"read"`
		Dataflows []string   `json:"-"`
	}{
		Write:     inconsistency.Write,
		Read:      inconsistency.Read,
		Dataflows: dataflows,
	})
}

func (i *Inconsistency) String() string {
	return fmt.Sprintf("READ = %v / WRITE = %v", i.Read.String(), i.Write.String())
}

func InitRequest(entryNode abstractgraph.AbstractNode, detectionMode DetectionMode) *Request {
	request := &Request{
		EntryNode:     entryNode,
		LineagesStack: stack.New(),
		DetectionMode: detectionMode,
	}
	request.PushLineage()
	return request
}

func createOperation(key variables.Variable, object variables.Variable, call *abstractgraph.AbstractDatabaseCall, write bool) *Operation {
	return &Operation{
		Key:      key,
		Object:   object,
		Service:  call.Service,
		Database: call.DbInstance,
		Method:   call.GetMethodStr(),
		Write:    write,
	}
}

func (request *Request) saveWriteOperation(call *abstractgraph.AbstractDatabaseCall, backend *blueprint.BackendMethod) *Operation {
	keyIndex := backend.GetWrittenKeyIndex()
	objIndex := backend.GetWrittenObjectIndex()
	key := call.GetParam(keyIndex)
	object := call.GetParam(objIndex)

	write := createOperation(key, object, call, true)

	request.AddWrite(write)
	request.CurrentLineage().AddOperation(write)

	return write
}

func (request *Request) saveReadOperation(call *abstractgraph.AbstractDatabaseCall, backend *blueprint.BackendMethod) *Operation {
	keyIndex := backend.GetReadKeyIndex()
	objIndex := backend.GetReadObjectIndex()

	var object variables.Variable
	key := call.GetParam(keyIndex)

	if objIndex >= 0 {
		object = call.GetParam(objIndex)
	} else {
		// gives index in inverse
		// e.g. -1 is 0 | -2 is 1 | -3 is 2 |
		objIndex = -objIndex - 1
		object = call.GetReturn(objIndex)
	}

	read := createOperation(key, object, call, false)
	request.AddRead(read)

	if request.DetectionMode == DEBUG_OPERATIONS {
		request.CurrentLineage().AddOperation(read)
	}

	return read
}

func (request *Request) captureInconsistency(read *Operation, readCall *abstractgraph.AbstractDatabaseCall) {
	if readCall.DbInstance.IsQueue() {
		// skip inconsistencies between a write and a read in the same queue
		return
	}

	dependencies := request.CurrentLineage().GetDependencies()
	logger.Logger.Tracef("[XCY LINEAGES] got dependencies: %v", dependencies)

	for _, write := range dependencies {
		if request.DetectionMode == LINEAGES_IMPLICIT_DEFAULT {
			inconsistency := &Inconsistency{
				Write: write,
				Read:  read,
			}
			request.AddInconsistency(inconsistency)
			continue
		}

		if request.DetectionMode == LINEAGES_IMPLICIT_EQUAL_DATASTORES {
			if readCall.DbInstance == write.Database {
				inconsistency := &Inconsistency{
					Write: write,
					Read:  read,
				}
				request.AddInconsistency(inconsistency)
			}
			continue
		}

		if readCall.DbInstance == write.Database {
			logger.Logger.Debugf("[XCY] evaluating XCY violation for read (%s @ %s) and write (%s @ %s)", read.Key.GetVariableInfo().Name, readCall.DbInstance.GetName(), write.Key.GetVariableInfo().Name, write.Database.GetName())
			readKeyDeps := read.Key.GetNestedDependencies(false)
			writeValueDeps := write.Object.GetNestedDependencies(false)

			logger.Logger.Tracef("[READ KEY] dependencies for (%s) %s: \n%v", utils.GetType(read.Key), read.Key.String(), variables.GetDependenciesStringLst(readKeyDeps...))
			logger.Logger.Tracef("[WRITE VALUE] dependencies for (%s) %s: \n%v", utils.GetType(write.Object), write.Object.String(), variables.GetDependenciesStringLst(writeValueDeps...))

			inconsistency := &Inconsistency{
				Write: write,
				Read:  read,
			}

			for _, dep := range readKeyDeps {
				dfs := dep.GetVariableInfo().GetAllDataflowsForDatastore(readCall.DbInstance.GetName())
				for _, df := range dfs {
					for _, v := range writeValueDeps {
						if df.Variable == v {
							inconsistency.Dataflows = append(inconsistency.Dataflows, v.GetVariableInfo().GetAllDataflows()...)
						}
					}
				}
			}

			if inconsistency.Dataflows != nil {
				logger.Logger.Warnf("[XCY] found inconsistency: %s", inconsistency.String())
				request.AddInconsistency(inconsistency)
			}
		}
	}
}

func (request *Request) InitTransversal() {
	logger.Logger.Tracef("[XCY] init tranversal for entry node: %s", request.EntryNode.GetName())
	for _, edge := range request.EntryNode.GetChildren() {
		/* fmt.Println("\n------------------------------------------------------------------------------------------------------------------------------------------------")
		logger.Logger.Infof("[XCY] transversing child node: %s", edge.GetName())
		fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------") */
		request.transverseOperations(edge)
	}
}

func (request *Request) transverseOperations(node abstractgraph.AbstractNode) {
	// FIXME: maybe we should link the two stateful nodes (push and pop) in the abstract graph
	// instead of placing a stateless queue handler between both
	if request.DetectionModeUsesLineages() {
		if _, ok := node.(*abstractgraph.AbstractQueueHandler); ok {
			request.PushLineage()
		}
	}

	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		var operation *Operation
		if backend, ok := dbCall.ParsedCall.Method.(*blueprint.BackendMethod); ok {
			if backend.IsWrite() || backend.IsUpdate() {
				operation = request.saveWriteOperation(dbCall, backend)
				logger.Logger.Infof("[XCY] saved write %s", operation.String())
			} else if backend.IsRead() {
				operation = request.saveReadOperation(dbCall, backend)
				logger.Logger.Infof("[XCY] saved read %s", operation.String())
				if request.DetectionMode != DEBUG_OPERATIONS {
					request.captureInconsistency(operation, dbCall)
				}
			} else {
				logger.Logger.Warnf("[XCY] ignoring operation: %s", dbCall.String())
			}
		}
	}
	for _, edge := range node.GetChildren() {
		request.transverseOperations(edge)
	}

	// FIXME: maybe we should link the two stateful nodes (push and pop) in the abstract graph
	// instead of placing a stateless queue handler between both
	if request.DetectionModeUsesLineages() {
		if _, ok := node.(*abstractgraph.AbstractQueueHandler); ok {
			request.PopLineage()
		}
	}
}
