package abstractgraph

import (
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/app"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	"encoding/json"
	"fmt"
	"os"
)


func Build(app *app.App, frontends []string) *AbstractGraph {
	graph := &AbstractGraph{
		AppName:  app.Name,
		Nodes:    make([]AbstractNode, 0),
		Services: app.Services,
		GIndex:   1,
	}
	for _, frontend := range frontends {
		service := app.Services[frontend]
		for _, method := range service.ExposedMethods {
			graph.initBuild(app, app.Services[frontend], method)
		}
	}

	for _, node := range graph.Nodes {
		graph.cleanVisited(node)
	}
	graph.GIndex = 1
	for _, abstractEntry := range graph.Nodes {
		graph.matchIdentifiers(abstractEntry)
	}
	return graph
}

func (graph *AbstractGraph) cleanVisited(node AbstractNode) {
	node.SetVisited(false)
	for _, edge := range node.GetChildren() {
		graph.cleanVisited(edge)
	}
}

func (graph *AbstractGraph) matchIdentifiers(node AbstractNode) {
	if node.IsVisited() {
		return
	}
	logger.Logger.Debugf("matching identifiers for node %s (params = %v)", node.String(), node.GetParams())
	node.SetVisited(true)
	/* graph.referenceCallerServiceParamss(node) */
	/* graph.matchQueuePublishersToReceiversParams(node) */
	logger.Logger.Debug()
	for _, child := range node.GetChildren() {
		graph.matchIdentifiers(child)
	}
}

// FIXME: this should be recursive!!
func getVariableIfPointer(variable types.Variable) types.Variable {
	if variable.GetVariableInfo() == nil {
		logger.Logger.Fatalf("missing info for variable %v", variable)
	}
	if variable.GetVariableInfo().GetType() == nil {
		logger.Logger.Fatalf("missing type for variable %v", variable)
	}

	if _, ok := variable.GetVariableInfo().GetType().(*types.PointerType); ok {
		return variable.GetDependencies()[0]
	}
	return variable
}

func (graph *AbstractGraph) Save() {
	// print in JSON format
	// https://omute.net/editor
	path := fmt.Sprintf("assets/%s/abstractgraph.json", graph.AppName)
	file, err := os.Create(path)
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()
	for _, node := range graph.Nodes {
		data, err := json.MarshalIndent(node, "", "  ")
		if err != nil {
			logger.Logger.Error("error marshaling json:", err)
			return
		}
		file.Write(data)
	}
	logger.Logger.Infof("[JSON] graph saved at %s", path)
}

func (graph *AbstractGraph) initBuild(app *app.App, serviceNode *service.ServiceNode, targetMethod *service.ParsedFuncDecl) {
	graph.addEntry(serviceNode, targetMethod)
	for _, abstractEntry := range graph.Nodes {
		if abstractServiceEntry, ok := abstractEntry.(*AbstractServiceCall); ok { // sanity check
			graph.recurseBuild(app, abstractServiceEntry)
		}
	}
}

func (graph *AbstractGraph) createDummyAbstractServiceCall(node *service.ServiceNode, method *service.ParsedFuncDecl, parent *AbstractDatabaseCall) AbstractServiceCall {
	logger.Logger.Debugf("[GRAPH - DUMMY] create dummy abstract service call for node %s and method %s with params %v", node.Name, method.Name, method.GetParams())

	var callerStr = "Client"
	if parent != nil {
		callerStr = parent.ParsedCall.CallerTypeName.GetName()
	}

	call := AbstractServiceCall{
		ParsedCall: &service.ServiceParsedCallExpr{
			ParsedCallExpr: service.ParsedCallExpr{
				TargetField: node.Name,
				Name:        method.Name,
				Method:      method,
			},
		},
		Caller: callerStr,
		Callee: node.Name,
		Method: method.String(),
	}
	for _, p := range method.GetParams() {
		call.ParsedCall.Params = append(call.ParsedCall.Params, &types.GenericVariable{
			VariableInfo: &types.VariableInfo{
				Name: p.GetName(),
				Type: p.GetType(),
				Id:   graph.getAndIncGIndex(),
			},
		})
	}
	call.Params = call.ParsedCall.Params
	return call
}

func (graph *AbstractGraph) addEntry(node *service.ServiceNode, method *service.ParsedFuncDecl) {
	// add entry node to graph
	entryCall := graph.createDummyAbstractServiceCall(node, method, nil)
	graph.Nodes = append(graph.Nodes, &entryCall)
	// build entry node
	for _, param := range entryCall.Params {
		param.GetVariableInfo().Reference = &types.Reference{
			Creator: "Client",
			Variable: &types.GenericVariable{
				VariableInfo: &types.VariableInfo{
					Name: param.GetVariableInfo().GetName(),
					Id:   graph.getAndIncGIndex(),
				},
			},
		}
	}
}

func (graph *AbstractGraph) recurseBuild(app *app.App, abstractNode AbstractNode) {
	if abstractNode.IsVisited() {
		return
	}
	abstractNode.SetVisited(true)

	switch node := abstractNode.(type) {
	case *AbstractServiceCall:
		targetMethod := graph.Services[node.Callee].GetExposedMethod(node.ParsedCall.Name)
		graph.appendAbstractEdges(node, node, targetMethod)
	case *AbstractDatabaseCall:
		if node.ParsedCall.Method.IsQueueWrite() {
			graph.appendPublisherQueueHandlers(app, node)
		}
	case *AbstractQueueHandler:
		targetMethod := graph.Services[node.Callee].GetQueueHandlerMethod(node.ParsedCall.Name)
		graph.appendAbstractEdges(node, node, targetMethod)
	default:
		logger.Logger.Warnf("Error recursing build for %s\nUnknown node type: %s", node, utils.GetType(node))
		return
	}
	for _, edge := range abstractNode.GetChildren() {
		graph.recurseBuild(app, edge)
	}
}

func (graph *AbstractGraph) appendAbstractEdges(rootParent AbstractNode, directParent AbstractNode, targetMethod *service.ParsedFuncDecl) {
	for _, call := range targetMethod.Calls {
		rootQueueHandler, rootIsQueueHandler := rootParent.(*AbstractQueueHandler)
		switch parsedCall := call.(type) {
		case *service.DatabaseParsedCallExpr:
			child := &AbstractDatabaseCall{
				ParsedCall: parsedCall,
				Params:     parsedCall.Params,
				Service:    parsedCall.CallerTypeName.GetName(),
				Method:     parsedCall.Method.String(),
				DbInstance: parsedCall.DbInstance,
				Subscriber: rootIsQueueHandler,
			}
			rootParent.AddChild(child)

			if rootIsQueueHandler && !rootQueueHandler.HasQueueReceiver() {
				if !graph.referencePublisherParams(rootQueueHandler, child) {
					graph.referenceServiceCallerParams(rootParent, directParent, child)
				}
			} else {
				graph.referenceServiceCallerParams(rootParent, directParent, child)
			}
		case *service.ServiceParsedCallExpr:
			child := &AbstractServiceCall{
				ParsedCall: parsedCall,
				Caller:     parsedCall.CallerTypeName.GetName(),
				Callee:     parsedCall.CalleeTypeName.GetName(),
				Params:     parsedCall.Params,
				Method:     parsedCall.Method.String(),
			}
			rootParent.AddChild(child)
			graph.referenceServiceCallerParams(rootParent, directParent, child)
		case *service.InternalTempParsedCallExpr:
			tempChild := &AbstractTempInternalCall{
				ParsedCall: parsedCall,
				Service:    parsedCall.ServiceTypeName.GetName(),
				Params:     parsedCall.Params,
				Method:     parsedCall.Method.String(),
			}
			graph.referenceServiceCallerParams(rootParent, directParent, tempChild)
			tempMethod := graph.Services[tempChild.Service].GetInternalMethod(tempChild.ParsedCall.Name)
			graph.appendAbstractEdges(rootParent, tempChild, tempMethod)
		}
	}
}

func (graph *AbstractGraph) appendPublisherQueueHandlers(app *app.App, publisher *AbstractDatabaseCall) {
	instance := publisher.ParsedCall.GetTargetedDatabaseInstance()
	for _, node := range app.Services {
		for _, handlerMethod := range node.GetQueueHandlersForDatabase(instance) {
			logger.Logger.Debugf("[GRAPH - QUEUE] found worker %s on instance '%s'", handlerMethod.String(), instance.GetName())
			abstractHandler := &AbstractQueueHandler{
				AbstractServiceCall: graph.createDummyAbstractServiceCall(node, handlerMethod, publisher),
				DbInstance:          instance,
				Publisher:           publisher,
			}
			for _, p := range handlerMethod.GetParams() {
				abstractHandler.ParsedCall.Params = append(abstractHandler.ParsedCall.Params, &types.GenericVariable{
					VariableInfo: &types.VariableInfo{
						Name: p.GetName(),
						Type: p.GetType(),
					},
				})
			}
			publisher.Children = append(publisher.Children, abstractHandler)
		}
	}
}

func (graph *AbstractGraph) referencePublisherParams(queueHandler *AbstractQueueHandler, child *AbstractDatabaseCall) bool {
	if child.ParsedCall.Method.IsQueueRead() && queueHandler.Publisher.DbInstance == child.ParsedCall.DbInstance {
		pushMethod, ok := queueHandler.Publisher.ParsedCall.Method.(*frameworks.BlueprintBackend)
		if !ok {
			return false
		}
		queueHandler.EnableQueueReceiver()
		for pushParamIdx, popParamIdx := range pushMethod.MatchQueueIdentifiers() {
			pushParam := queueHandler.Publisher.GetParam(pushParamIdx)
			popParam := child.GetParam(popParamIdx)
			popParam = getVariableIfPointer(popParam)

			if addressVar, ok := popParam.(*types.AddressVariable); ok {
				popParam = addressVar.GetAddressOf()
			} else if ptrVar, ok := popParam.(*types.PointerVariable); ok {
				popParam = ptrVar.GetPointerTo()
			}

			popParam.GetVariableInfo().AddReferenceWithID(pushParam, "unknown creator")
			if pushParam.GetVariableInfo().HasReference() {
				popParam.GetVariableInfo().GetReference().Creator = pushParam.GetVariableInfo().GetReference().Creator
			} else {
				popParam.GetVariableInfo().GetReference().Creator = queueHandler.Publisher.ParsedCall.CallerTypeName.GetName()
			}
		}
		return true
	}
	return false
}

func getIndirectParamDeps(v types.Variable) []types.Variable {
	var deps []types.Variable
	for _, d := range v.GetDependencies() {
		deps = append(deps, getIndirectParamDeps(d)...)
	}
	return append(deps, v)
}

func (graph *AbstractGraph) referenceServiceCallerParams(rootParent AbstractNode, directParent AbstractNode, child AbstractNode) {
	for _, childParam := range child.GetParams() {
		for _, dep := range getIndirectParamDeps(childParam) {
			if dep.GetVariableInfo().HasReference() {
				continue
			}
			for callerParamIdx, callerParam := range directParent.GetParams() {
				if dep.GetVariableInfo().IsBlockParameter() && dep.GetVariableInfo().EqualBlockParamIndex(callerParamIdx) {
					if dep.GetVariableInfo().IsUnassigned() {

						if addressVar, ok := dep.(*types.AddressVariable); ok {
							dep = addressVar.GetAddressOf()
						} else if ptrVar, ok := dep.(*types.PointerVariable); ok {
							dep = ptrVar.GetPointerTo()
						}

						if rootParent == directParent {
							dep.GetVariableInfo().AddReferenceWithID(callerParam, child.GetCallerStr())
						} else if callerParam.GetVariableInfo().HasReference() {
							// this can happen with the context variable (e.g. handleMessage called by the workerThread in the NotifyService)
							dep.GetVariableInfo().AddOriginalReferenceWithID(callerParam.GetVariableInfo().GetReference())
						} else {
							dep.GetVariableInfo().AddReferenceWithID(callerParam, child.GetCallerStr())
						}
						break
					}
				}
			}
			if dep.GetVariableInfo().IsUnassigned() {
				dep.GetVariableInfo().AssignID(graph.getAndIncGIndex())
			}
		}
	}
}
