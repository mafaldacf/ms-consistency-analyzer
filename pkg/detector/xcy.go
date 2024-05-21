package detector

import (
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/abstractgraph"
	"fmt"
)

type Write struct {
	Key 		*types.Variable
	Object 		*types.Variable
	Database 	types.DatabaseInstance
	Service 	string
}

func (write *Write) String() string {
	if write.Key != nil {
		return fmt.Sprintf("{ %s(%d):%s(%d) @ %s (%s) }", write.Key.Name, write.Key.Id, write.Object.Name, write.Object.Id, write.Database.GetName(), write.Service)
	}
	return fmt.Sprintf("{ :%s (%d) @ %s (%s) }", write.Object.Name, write.Object.Id, write.Database.GetName(), write.Service)
}

type Request struct { 
	Writes []*Write
}

func (request *Request) addWrite(key *types.Variable, object *types.Variable, service string, database types.DatabaseInstance) *Write {
	write := &Write{
		Key: key,
		Object: object,
		Service: service,
		Database: database,
	}
	request.Writes = append(request.Writes, write)
	return write
}

func CaptureInconsistencies(entryNode abstractgraph.AbstractNode) {
	request := &Request{}
	for _, edge := range entryNode.GetChildren() {
		captureInconsistencies(request, edge)
	}
}



func captureInconsistencies(request *Request, node abstractgraph.AbstractNode) {
	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		if backend, ok := dbCall.ParsedCall.Method.(*frameworks.BlueprintBackend); ok {
			if backend.IsWrite() {
				key := dbCall.GetParam(backend.GetWrittenKeyIndex())
				object := dbCall.GetParam(backend.GetWrittenObjectIndex())
				write := request.addWrite(key, object, dbCall.Service, dbCall.DbInstance)
				logger.Logger.Infof("found write %s", write.String())
			} else if !backend.IsQueueRead() {
				key := dbCall.GetParam(backend.GetReadKeyIndex())
				for _, prevWrite := range request.Writes {
					if dbCall.DbInstance == prevWrite.Database {
						if key.IsReferencedObject(prevWrite.Object) {
							logger.Logger.Infof("found read for key %v (id = %d) on previous write %v", key.String(), key.Id, prevWrite.String())
						}
					}
				}
			}
		}
	}

	for _, edge := range node.GetChildren() {
		captureInconsistencies(request, edge)
	}
}
