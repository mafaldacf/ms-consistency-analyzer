package detector

import (
	"encoding/json"
	"fmt"
	"os"
	"strings"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/datastores"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
)

type Parameters interface {
	String() string
}
type KeyValue struct {
	Parameters
	Key   types.Variable
	Value types.Variable
}

func (kv *KeyValue) String() string {
	return fmt.Sprintf("KV { key: %s (#%d), value: %s (#%d) }",
		kv.Key.GetVariableInfo().GetName(), kv.Key.GetVariableInfo().GetId(),
		kv.Value.GetVariableInfo().GetName(), kv.Value.GetVariableInfo().GetId(),
	)
}

type Message struct {
	Parameters
	Message types.Variable
}

func (m *Message) String() string {
	return fmt.Sprintf("MSG { message: %s (#%d) }",
		m.Message.GetVariableInfo().GetName(), m.Message.GetVariableInfo().GetId(),
	)
}

type Operation struct {
	Service  string
	Method   string
	Key      types.Variable
	Object   types.Variable
	Database datastores.DatabaseInstance
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
		Key:      fmt.Sprintf("%s (#%d)", op.Key.GetVariableInfo().GetName(), op.Key.GetVariableInfo().GetId()),
		Object:   fmt.Sprintf("%s (#%d)", op.Object.GetVariableInfo().GetName(), op.Object.GetVariableInfo().GetId()),
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
	return fmt.Sprintf("{ %s \t > datastore: %s, key: %s (#%d), value: %s (#%d) }",
		op.Service,
		op.Database.GetName(),
		op.Key.GetVariableInfo().GetName(),
		op.Key.GetVariableInfo().GetId(),
		op.Object.GetVariableInfo().GetName(),
		op.Object.GetVariableInfo().GetId(),
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

func createOperation(key types.Variable, object types.Variable, call *abstractgraph.AbstractDatabaseCall) *Operation {
	return &Operation{
		Key:      key,
		Object:   object,
		Service:  call.Service,
		Database: call.DbInstance,
		Method:   call.Method,
	}
}

func (request *Request) saveWriteOperation(call *abstractgraph.AbstractDatabaseCall, backend *blueprint.BackendMethod) *Operation {
	keyIndex := backend.GetWrittenKeyIndex()
	objIndex := backend.GetWrittenObjectIndex()
	key := call.GetParam(keyIndex)
	object := call.GetParam(objIndex)

	write := createOperation(key, object, call)
	request.Writes = append(request.Writes, write)
	logger.Logger.Infof("[XCY] created write %s", write.String())
	return write
}

func (request *Request) saveReadOperation(call *abstractgraph.AbstractDatabaseCall, backend *blueprint.BackendMethod) *Operation {
	keyIndex := backend.GetReadKeyIndex()
	objIndex := backend.GetReadObjectIndex()

	var object types.Variable
	key := call.GetParam(keyIndex)
	
	if objIndex >= 0 {
		object = call.GetParam(objIndex)
	} else {
		// gives index in inverse
		// e.g. -1 is 0 | -2 is 1 | -3 is 2 |
		objIndex = -objIndex - 1
		object = call.GetReturn(objIndex)
	}

	read := createOperation(key, object, call)
	request.Reads = append(request.Reads, read)
	logger.Logger.Infof("[XCY] created read %s", read.String())
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
	for _, edge := range request.EntryNode.GetChildren() {
		request.transverseOperations(edge)
	}
}

func (request *Request) captureInconsistency(read *Operation, readCall *abstractgraph.AbstractDatabaseCall) {
	if readCall.Subscriber {
		return
	}
	// iterate in reverse
	for i := len(request.Writes) - 1; i >= 0; i-- {
		write := request.Writes[i]
		logger.Logger.Debugf("evaluating XCY violation for read (%s @ %s) and write (%s @ %s)",
			read.Key.GetVariableInfo().Name,
			readCall.DbInstance.GetName(),
			write.Key.GetVariableInfo().Name,
			write.Database.GetName(),
		)
		if readCall.DbInstance == write.Database {
			if types.ContainsMatchingDependencies(read.Key, write.Object) {
				request.addInconsistency(write, read)
			}
		}
	}
}

func (request *Request) transverseOperations(node abstractgraph.AbstractNode) {
	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		if backend, ok := dbCall.ParsedCall.Method.(*blueprint.BackendMethod); ok {
			if backend.IsWrite() {
				request.saveWriteOperation(dbCall, backend)
			} else {
				read := request.saveReadOperation(dbCall, backend)
				request.captureInconsistency(read, dbCall)
			}
		}
	}
	for _, edge := range node.GetChildren() {
		request.transverseOperations(edge)
	}
}

func (request *Request) SaveInconsistencies(app string) {
	filename := fmt.Sprintf("xcy_%s_%s.json", strings.ToLower(request.EntryNode.GetCallee()), strings.ToLower(request.EntryNode.GetName()))
	path := fmt.Sprintf("assets/%s/%s", app, filename)
	file, err := os.Create(path)
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()
	data, err := json.MarshalIndent(request, "", "  ")
	if err != nil {
		logger.Logger.Error("error marshaling json:", err)
		return
	}
	logger.Logger.Infof("[JSON] xcy saved at %s", path)
	file.Write(data)
}
