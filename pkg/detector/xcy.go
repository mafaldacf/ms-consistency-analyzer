package detector

import (
	"analyzer/pkg/abstractgraph"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"encoding/json"
	"fmt"
	"os"
	"strings"
)

type Write struct {
	Key      types.Variable
	Object   types.Variable
	Service  string
	Database types.DatabaseInstance
	Call     string
}

func (w *Write) MarshalJSON() ([]byte, error) {
	if w.Key != nil {
		return json.Marshal(&struct {
			Key      string `json:"key"`
			Object   string `json:"object"`
			Service  string `json:"service"`
			Database string `json:"database"`
			Call     string `json:"call"`
		}{
			Key:      fmt.Sprintf("%s (%d)", w.Key.GetVariableInfo().GetName(), w.Key.GetVariableInfo().GetId()),
			Object:   fmt.Sprintf("%s (%d)", w.Object.GetVariableInfo().GetName(), w.Object.GetVariableInfo().GetId()),
			Service:  w.Service,
			Database: w.Database.GetName(),
			Call:     w.Call,
		})
	}
	return json.Marshal(&struct {
		Object   string `json:"object"`
		Service  string `json:"service"`
		Database string `json:"database"`
		Call     string `json:"call"`
	}{
		Object:   fmt.Sprintf("%s (%d)", w.Object.GetVariableInfo().GetName(), w.Object.GetVariableInfo().GetId()),
		Service:  w.Service,
		Database: w.Database.GetName(),
		Call:     w.Call,
	})
}

type Read struct {
	Key      types.Variable
	Service  string
	Write    *Write
	Database types.DatabaseInstance
	Call     string
}

func (r *Read) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		ReadKey  string `json:"key"`
		Service  string `json:"service"`
		Write    *Write `json:"write"`
		Database string `json:"database"`
		Call     string `json:"call"`
	}{
		ReadKey:  fmt.Sprintf("%s (%d)", r.Key.GetVariableInfo().GetName(), r.Key.GetVariableInfo().GetId()),
		Service:  r.Service,
		Database: r.Database.GetName(),
		Write:    r.Write,
		Call:     r.Call,
	})
}

func (write *Write) String() string {
	if write.Key != nil {
		return fmt.Sprintf("{ %s(%d):%s(%d) @ %s by %s }", write.Key.GetVariableInfo().GetName(), write.Key.GetVariableInfo().GetId(), write.Object.GetVariableInfo().GetName(), write.Object.GetVariableInfo().GetId(), write.Database.GetName(), write.Service)
	}
	return fmt.Sprintf("{ :%s (%d) @ %s by %s }", write.Object.GetVariableInfo().GetName(), write.Object.GetVariableInfo().GetId(), write.Database.GetName(), write.Service)
}

func (read *Read) String() string {
	return fmt.Sprintf("{ :%s (%d) by %s - WRITE: %s}", read.Key.GetVariableInfo().GetName(), read.Key.GetVariableInfo().GetId(), read.Service, read.Write.String())
}

type Request struct {
	EntryNode       abstractgraph.AbstractNode `json:"-"`
	Inconsistencies []*Read                    `json:"inconsistencies"`
	Writes          []*Write                   `json:"writes"`
}

func InitRequest(entryNode abstractgraph.AbstractNode) *Request {
	return &Request{
		EntryNode: entryNode,
	}
}

func (request *Request) addWrite(key types.Variable, object types.Variable, call *abstractgraph.AbstractDatabaseCall) {
	write := &Write{
		Key:      key,
		Object:   object,
		Service:  call.Service,
		Database: call.DbInstance,
		Call:     call.String(),
	}
	request.Writes = append(request.Writes, write)
	logger.Logger.Infof("added write %s", write.String())
}

func (request *Request) addInconsistency(prevWrite *Write, readKey types.Variable, call *abstractgraph.AbstractDatabaseCall) {
	read := &Read{
		Key:      readKey,
		Service:  call.GetCallerStr(),
		Database: prevWrite.Database,
		Write:    prevWrite,
		Call:     call.String(),
	}
	request.Inconsistencies = append(request.Inconsistencies, read)
	logger.Logger.Infof("added xcy violation %s", read.String())
}

func (request *Request) CaptureInconsistencies() {
	for _, edge := range request.EntryNode.GetChildren() {
		request.captureInconsistencies(edge)
	}
}

func (request *Request) captureInconsistencies(node abstractgraph.AbstractNode) {
	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		if backend, ok := dbCall.ParsedCall.Method.(*frameworks.BlueprintBackend); ok {
			if backend.IsWrite() {
				key := dbCall.GetParam(backend.GetWrittenKeyIndex())
				object := dbCall.GetParam(backend.GetWrittenObjectIndex())
				request.addWrite(key, object, dbCall)
			} else if !backend.IsQueueRead() {
				key := dbCall.GetParam(backend.GetReadKeyIndex())
				for _, prevWrite := range request.Writes {
					if dbCall.DbInstance == prevWrite.Database {
						if types.IsReferencedObject(key, prevWrite.Object) {
							request.addInconsistency(prevWrite, key, dbCall)
						}
					}
				}
			}
		}
	}

	for _, edge := range node.GetChildren() {
		request.captureInconsistencies(edge)
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
