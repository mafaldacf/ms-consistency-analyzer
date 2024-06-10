package abstractgraph

import (
	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
)

func GetIndirectDependencies(first bool, v types.Variable) []types.Variable {
	indirectDeps := []types.Variable{}
	if !first {
		indirectDeps = append(indirectDeps, v)
	}

	// indirect dependencies from potential reference
	if v.GetVariableInfo().HasReference() {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(false, v.GetVariableInfo().GetReference())...)
	}
	// direct dependencies
	for _, dep := range v.GetDependencies() {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(false, dep)...)
	}
	// edge cases
	if addressVariable, ok := v.(*types.AddressVariable); ok {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(false, addressVariable.AddressOf)...)
	} else if pointerVariable, ok := v.(*types.PointerVariable); ok {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(false, pointerVariable.PointerTo)...)
	}

	return indirectDeps
}

func GetForeignDependencies(first bool, v types.Variable) []types.Variable {
	foreignDeps := []types.Variable{}
	if !first && v.GetVariableInfo().Dataflow != nil {
		if v.GetVariableInfo().Dataflow.DirectWrite {
			return []types.Variable{v}
		}
		return []types.Variable{v.GetVariableInfo().Dataflow.Source}
	}

	// indirect dependencies from potential reference
	if v.GetVariableInfo().HasReference() {
		foreignDeps = append(foreignDeps, GetForeignDependencies(false, v.GetVariableInfo().GetReference())...)
	}
	// direct dependencies
	for _, dep := range v.GetDependencies() {
		foreignDeps = append(foreignDeps, GetForeignDependencies(false, dep)...)
	}
	// edge cases
	if addressVariable, ok := v.(*types.AddressVariable); ok {
		foreignDeps = append(foreignDeps, GetForeignDependencies(false, addressVariable.AddressOf)...)
	} else if pointerVariable, ok := v.(*types.PointerVariable); ok {
		foreignDeps = append(foreignDeps, GetForeignDependencies(false, pointerVariable.PointerTo)...)
	}

	return foreignDeps
}


//var writes map[*datastores.Datastore][]types.Variable = make(map[*datastores.Datastore][]types.Variable)

func BuildSchema(app *app.App, node AbstractNode) {
	if dbCall, ok := node.(*AbstractDatabaseCall); ok && dbCall.ParsedCall.Method.IsWrite() {
		logger.Logger.Infof("building schema for abstract node %s", dbCall.String())
		datastore := dbCall.DbInstance.GetDatastore()
		params := dbCall.Params
		switch datastore.Type {
			case datastores.Cache:
				key := params[1]
				value := params[2]

				
				datastore.Schema.AddKey(key.GetVariableInfo().GetName(), key.GetVariableInfo().Type.String())
				datastore.Schema.AddEntry(value.GetVariableInfo().GetName(), value.GetVariableInfo().Type.String())
				
				//writes[datastore] = append(writes[datastore], value)

				logger.Logger.Debugf("SET DIRECT WRITE FOR KEY: %v (id = %d)", key, key.GetVariableInfo().Id)
				key.GetVariableInfo().SetDirectWrite(datastore.Name, dbCall.Service)
				indirectDependencies := GetIndirectDependencies(true, key)
				for _, v := range indirectDependencies {
					logger.Logger.Debugf("SET INDIRECT WRITE FOR KEY: %v (id = %d)", v, v.GetVariableInfo().Id)
					v.GetVariableInfo().SetIndirectWrite(key)
				}
				
				fmt.Println()

				logger.Logger.Debugf("SET DIRECT WRITE FOR VALUE: %v (id = %d)", value, value.GetVariableInfo().Id)
				value.GetVariableInfo().SetDirectWrite(datastore.Name, dbCall.Service)
				indirectDependencies = GetIndirectDependencies(true, value)
				for _, v := range indirectDependencies {
					logger.Logger.Debugf("SET INDIRECT WRITE FOR VALUE: %v (id = %d)", v, v.GetVariableInfo().Id)
					v.GetVariableInfo().SetIndirectWrite(value)
				}
				fmt.Println()
				logger.Logger.Infof("added kv to schema  %s", datastore.Schema)

			case datastores.Queue:
				obj := params[1]
				datastore.Schema.AddEntry(obj.GetVariableInfo().GetName(), obj.GetVariableInfo().Type.String())

				foreignDependencies := GetForeignDependencies(true, obj)
				for _, v := range foreignDependencies {
					logger.Logger.Warnf("GOT FOREIGN DEPENDENCY: %v", v)
					foreignVariable := v
					if !v.GetVariableInfo().Dataflow.DirectWrite {
						foreignVariable = v.GetVariableInfo().Dataflow.Source
					}
					foreignDatastore := app.Databases[foreignVariable.GetVariableInfo().Dataflow.Datastore]
					foreignField := foreignDatastore.GetDatastore().Schema.GetField(foreignVariable.GetVariableInfo().Name)
					datastore.Schema.AddForeignEntry(foreignVariable.GetVariableInfo().GetName(), foreignVariable.GetVariableInfo().Type.String(), foreignField)
				}
				fmt.Println()
				logger.Logger.Infof("added kv to schema %s", datastore.Schema)
		}
	}
	for _, child := range node.GetChildren() {
		BuildSchema(app, child)
	}
}
