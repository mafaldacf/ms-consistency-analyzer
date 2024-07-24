package detector

import (
	"encoding/json"
	"fmt"
	"strings"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

type Parameters interface {
	String() string
}
type KeyValue struct {
	Parameters
	Key   variables.Variable
	Value variables.Variable
}

func (kv *KeyValue) String() string {
	return fmt.Sprintf("KV { key: %s (#%d), value: %s (#%d) }",
		kv.Key.GetVariableInfo().GetName(), kv.Key.GetId(),
		kv.Value.GetVariableInfo().GetName(), kv.Value.GetId(),
	)
}

type Message struct {
	Parameters
	Message variables.Variable
}

func (m *Message) String() string {
	return fmt.Sprintf("MSG { message: %s (#%d) }",
		m.Message.GetVariableInfo().GetName(), m.Message.GetId(),
	)
}

type Operation struct {
	Service  string
	Method   string
	Key      variables.Variable
	Object   variables.Variable
	Database datastores.DatabaseInstance
	Write    bool
}

func (op *Operation) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Service  string `json:"service"`
		Method   string `json:"method"`
		Key      string `json:"key"`
		Object   string `json:"object"`
		Database string `json:"database"`
	}{
		Service:  op.Service,
		Method:   op.Method,
		Key:      fmt.Sprintf("%s (#%d)", op.Key.GetVariableInfo().GetName(), op.Key.GetId()),
		Object:   fmt.Sprintf("%s (#%d)", op.Object.GetVariableInfo().GetName(), op.Object.GetId()),
		Database: op.Database.GetName(),
	})
}

func (op *Operation) String() string {
	if op.Key == nil {
		logger.Logger.Fatalf("nil key in %s", op.Method)
	}
	if op.Object == nil {
		logger.Logger.Fatalf("nil object in %s", op.Method)
	}
	opType := "write"
	if !op.Write {
		opType = "read"
	}
	return fmt.Sprintf("{ %s(%s, %s, %s, %s) }",
		opType,
		op.Service,
		op.Database.GetName(),
		op.Key.GetVariableInfo().GetName(),
		op.Object.GetVariableInfo().GetName(),
	)
}

type Inconsistency struct {
	Write *Operation `json:"write"`
	Read  *Operation `json:"read"`
}

func (i *Inconsistency) String() string {
	return fmt.Sprintf("READ: %v / WRITE: %v", i.Read.String(), i.Write.String())
}

type Request struct {
	EntryNode       abstractgraph.AbstractNode `json:"-"`
	Inconsistencies []*Inconsistency           `json:"xcy_violations"`
	Writes          []*Operation               `json:"writes"`
	Reads           []*Operation               `json:"reads"`
}

func InitRequest(entryNode abstractgraph.AbstractNode) *Request {
	return &Request{
		EntryNode: entryNode,
	}
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
	request.Writes = append(request.Writes, write)
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
	request.Reads = append(request.Reads, read)
	return read
}

func (request *Request) addInconsistency(write *Operation, read *Operation) {
	inconsistency := &Inconsistency{
		Write: write,
		Read:  read,
	}
	request.Inconsistencies = append(request.Inconsistencies, inconsistency)
	logger.Logger.Infof("[XCY] found inconsistency at datastore %s", inconsistency.Write.Database.GetName())
}

func (request *Request) TransverseRequestOperations() {
	logger.Logger.Infof("[XCY] init tranversal for entry node: %s", request.EntryNode.GetName())
	for _, edge := range request.EntryNode.GetChildren() {
		fmt.Println("\n------------------------------------------------------------------------------------------------------------------------------------------------")
		logger.Logger.Infof("[XCY] transversing child node: %s", edge.GetName())
		fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------")
		request.transverseOperations(edge)
	}
}

func (request *Request) captureInconsistency(read *Operation, readCall *abstractgraph.AbstractDatabaseCall) {
	/* if readCall.Subscriber {
		return
	} */
	// iterate in reverse
	for i := len(request.Writes) - 1; i >= 0; i-- {
		write := request.Writes[i]
		logger.Logger.Warnf("[XCY] evaluating XCY violation for read (%s @ %s) and write (%s @ %s)",
			read.Key.GetVariableInfo().Name,
			readCall.DbInstance.GetName(),
			write.Key.GetVariableInfo().Name,
			write.Database.GetName(),
		)
		readKeyDeps := variables.GetIndirectDependenciesWithCurrent(read.Key)
		logger.Logger.Debugf("[READ KEY] has ref? %t", read.Key.GetVariableInfo().HasReference())
		logger.Logger.Debugf("[READ KEY] dependencies for (%s) %s: \n%v", utils.GetType(read.Key), read.Key.String(), variables.GetDependenciesStringLst(readKeyDeps...))
		writeValueDeps := variables.GetIndirectDependenciesWithCurrent(write.Object)
		logger.Logger.Debugf("[WRITE VALUE] dependencies for (%s) %s: \n%v", utils.GetType(write.Object), write.Object.String(), variables.GetDependenciesStringLst(writeValueDeps...))
		
		if readCall.DbInstance == write.Database {
			if variables.ContainsMatchingDependencies2(readKeyDeps, writeValueDeps) {
				request.addInconsistency(write, read)
			}
		}
	}/* 
	if readCall.Subscriber {
		logger.Logger.Fatal("EXIT!")
	} */
}

func (request *Request) transverseOperations(node abstractgraph.AbstractNode) {
	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		if backend, ok := dbCall.ParsedCall.Method.(*blueprint.BackendMethod); ok {
			if backend.IsWrite() {
				write := request.saveWriteOperation(dbCall, backend)
				logger.Logger.Infof("[XCY] saved write %s", write.String())
			} else if backend.IsRead() {
				read := request.saveReadOperation(dbCall, backend)
				logger.Logger.Infof("[XCY] saved read %s", read.String())
				request.captureInconsistency(read, dbCall)
			} else {
				logger.Logger.Warnf("[XCY] ignoring operation: %s", dbCall.String())
			}
		}
	}
	for _, edge := range node.GetChildren() {
		request.transverseOperations(edge)
	}
}

func (request *Request) SaveInconsistencies(app string) {
	filename := fmt.Sprintf("detection/xcy_%s_%s.json", strings.ToLower(request.EntryNode.GetCallee()), strings.ToLower(request.EntryNode.GetName()))
	utils.DumpToJSONFile(request, app, filename)
}
