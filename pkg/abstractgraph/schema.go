package abstractgraph

import (
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
)

func BuildSchema(node AbstractNode) {
	if dbCall, ok := node.(*AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsWrite() {
		logger.Logger.Infof("building schema for abstract node %s", node.String())
		datastore := dbCall.DbInstance.GetDatastore()
		params := dbCall.Params
		switch datastore.Type {
		case datastores.Cache:
			key := params[1]
			value := params[2]
			datastore.Schema.AddKey(key.GetVariableInfo().GetName(), key.GetVariableInfo().Type.GetName())
			datastore.Schema.AddValue(value.GetVariableInfo().GetName(), value.GetVariableInfo().Type.GetName())
			logger.Logger.Infof("added kv to schema %v", datastore.Schema)
		}
	}
	for _, child := range node.GetChildren() {
		BuildSchema(child)
	}
}
