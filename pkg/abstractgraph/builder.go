package abstractgraph

import (
	"fmt"

	"analyzer/pkg/app"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/lookup"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

func (graph *AbstractGraph) getAndIncGIndex() int64 {
	prev := graph.GIndex
	graph.GIndex++
	return prev
}

func Build(app *app.App, frontends []string) *AbstractGraph {
	graph := &AbstractGraph{
		AppName:  app.Name,
		Nodes:    make([]AbstractNode, 0),
		Services: app.Services,
		GIndex:   1,
	}
	for _, frontend := range frontends {
		service := app.Services[frontend]
		for _, method := range service.ExportedMethods {
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
	logger.Logger.Tracef("matching identifiers for node %s (params = %v)", node.String(), node.GetParams())
	node.SetVisited(true)
	/* graph.referenceCallerServiceParamss(node) */
	/* graph.matchQueuePublishersToReceiversParams(node) */
	for _, child := range node.GetChildren() {
		graph.matchIdentifiers(child)
	}
}

// FIXME: this should be recursive!!
func getVariableIfPointer(variable variables.Variable) variables.Variable {
	if variable.GetVariableInfo() == nil {
		logger.Logger.Fatalf("missing info for variable %v", variable)
	}
	if variable.GetType() == nil {
		logger.Logger.Fatalf("missing type for variable %v", variable)
	}

	if _, ok := variable.GetType().(*gotypes.PointerType); ok {
		return variable.GetDependencies()[0]
	}
	return variable
}

func (graph *AbstractGraph) initBuild(app *app.App, serviceNode *service.Service, targetMethod *types.ParsedMethod) {
	graph.addEntry(serviceNode, targetMethod)
	for _, abstractEntry := range graph.Nodes {
		if abstractServiceEntry, ok := abstractEntry.(*AbstractServiceCall); ok { // sanity check
			graph.recurseBuild(app, abstractServiceEntry)
		}
	}
}

func (graph *AbstractGraph) createDummyAbstractServiceCall(node *service.Service, method *types.ParsedMethod, parent *AbstractDatabaseCall, depth int) AbstractServiceCall {
	logger.Logger.Debugf("[GRAPH - DUMMY] create dummy abstract service call for node %s and method %s with params %v", node.Name, method.Name, method.GetParams())

	var callerStr = "Client"
	if parent != nil {
		callerStr = parent.DbInstance.String()
	}

	call := AbstractServiceCall{
		ParsedCall: &types.ParsedServiceCall{
			ParsedCall: types.ParsedCall{
				Name:    method.Name,
				CallStr: node.Name,
				Method:  method,
			},
		},
		Caller: callerStr,
		Callee: node.Name,
		Method: method,
		Depth:  depth,
	}
	for _, p := range method.GetParams() {
		v := lookup.CreateVariableFromType(p.GetName(), p.GetType())
		call.ParsedCall.Params = append(call.ParsedCall.Params, v)
		logger.Logger.Debugf("[GRAPH - DUMMY] created variable %s (%s)", v.String(), utils.GetType(v))
	}
	call.Params = call.ParsedCall.Params
	return call
}

func (graph *AbstractGraph) addEntry(node *service.Service, method *types.ParsedMethod) {
	// add entry node to graph
	entryCall := graph.createDummyAbstractServiceCall(node, method, nil, 0)
	graph.Nodes = append(graph.Nodes, &entryCall)
	// build entry node
	/* for _, param := range entryCall.Params {
		v := controlflow.CreateVariableFromType(node, param.GetVariableInfo().GetName(), param.GetType())
		v.GetId() = graph.getAndIncGIndex()
		param.GetVariableInfo().Reference = &types.Reference{
			Creator:  "Client",
			Variable: v,
		}
	} */
}

func (graph *AbstractGraph) recurseBuild(app *app.App, abstractNode AbstractNode) {
	if abstractNode.IsVisited() {
		return
	}
	abstractNode.SetVisited(true)

	switch node := abstractNode.(type) {
	case *AbstractServiceCall:
		targetMethod := graph.Services[node.Callee].GetExportedMethod(node.ParsedCall.Name)
		if targetMethod == nil {
			logger.Logger.Fatalf("unexpected nil target method for call (%s) in node (%s)", node.ParsedCall.Name, node.Callee)
		}
		fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------")
		logger.Logger.Infof("[ABSTRACT SERVICE CALL (%d) calls] %s", len(targetMethod.Calls), node.String())
		for _, c := range targetMethod.Calls {
			logger.Logger.Debugf("\t\t- call: %v", c.String())
		}
		fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------")
		graph.appendAbstractEdges(node, node, targetMethod)
		fmt.Println()
	case *AbstractDatabaseCall:
		if node.ParsedCall.Method.IsQueueWrite() {
			fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------")
			logger.Logger.Infof("[ABSTRACT DATABASE CALL] %s", node.String())
			fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------")
			graph.appendPublisherQueueHandlers(app, node)
		}
		fmt.Println()
	case *AbstractQueueHandler:
		targetMethod := graph.Services[node.Callee].GetQueueHandlerMethod(node.ParsedCall.Name)
		if targetMethod == nil {
			logger.Logger.Fatalf("unexpected nil target method for call (%s) in node (%s)", node.ParsedCall.Name, node.Callee)
		}
		fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------")
		logger.Logger.Infof("[ABSTRACT QUEUE HANDLER (%d calls)] %s", len(targetMethod.Calls), node.String())
		for _, c := range targetMethod.Calls {
			logger.Logger.Debugf("\t\t- call: %v", c.String())
		}
		fmt.Println("------------------------------------------------------------------------------------------------------------------------------------------------")
		graph.appendAbstractEdges(node, node, targetMethod)
		fmt.Println()
	default:
		logger.Logger.Fatalf("Error recursing build for %s\nUnknown node type: %s", node, utils.GetType(node))
	}
	for _, edge := range abstractNode.GetChildren() {
		graph.recurseBuild(app, edge)
	}
}

func getPushMethodIfPublisherChild(rootParent AbstractNode, child *AbstractDatabaseCall) *blueprint.BackendMethod {
	if queueHandler, ok := rootParent.(*AbstractQueueHandler); ok && !queueHandler.IsEnabled() {
		if child.ParsedCall.Method.IsQueueRead() && queueHandler.Publisher.DbInstance == child.ParsedCall.DbInstance {
			pushMethod, ok := queueHandler.Publisher.ParsedCall.Method.(*blueprint.BackendMethod)
			if !ok {
				return nil
			}
			return pushMethod
		}
	}
	return nil
}

func (graph *AbstractGraph) referencePublisherParams(queueHandler *AbstractQueueHandler, child *AbstractDatabaseCall) bool {
	pushMethod := getPushMethodIfPublisherChild(queueHandler, child)
	if pushMethod == nil {
		return false
	}
	queueHandler.Enable()
	for pushParamIdx, popParamIdx := range pushMethod.MatchQueueIdentifiers() {
		pushParam := queueHandler.Publisher.GetParam(pushParamIdx)
		popParam := child.GetParam(popParamIdx)
		popParam = getVariableIfPointer(popParam)

		if addressVar, ok := popParam.(*variables.AddressVariable); ok {
			popParam = addressVar.GetAddressOf()
		} else if ptrVar, ok := popParam.(*variables.PointerVariable); ok {
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

// FIXME: we should actually create a new deep copy for the CFG
// to avoid changing it if we have another abstract node that will use the same parsed method
func (graph *AbstractGraph) referenceMethodBlockVars(parsedCall types.Call, child AbstractNode) {
	entryBlock := parsedCall.GetMethod().(*types.ParsedMethod).GetParsedCfg().GetEntryParsedBlock()
	for i, param := range parsedCall.GetParams() {
		// variable at block index 0 is the receiver so we need to skip that one
		blockVar := entryBlock.GetVariableAt(i + 1)
		blockVar.AddReferenceWithID(param, child.GetCallerStr())
		logger.Logger.Infof("\t\t[REF BLOCK VAR] added reference (%d) from creator (%s): (%s) -> (%s)", blockVar.GetId(), child.GetCallerStr(), blockVar.GetType().GetName(), param.GetVariableInfo().GetName())
		for _, dep := range variables.GetIndirectDependenciesWithCurrent(param) {
			if dep.GetVariableInfo().IsUnassigned() {
				dep.GetVariableInfo().AssignID(graph.getAndIncGIndex())
				logger.Logger.Debugf("\t\t\t[GID DEP] assigned new gid (%d) to (%s)", dep.GetId(), dep.String())
			}
		}
	}
}

func (graph *AbstractGraph) referenceQueuePopMethodBlockVars(queueHandler *AbstractQueueHandler, queuePopCall *AbstractDatabaseCall) {
	queuePushMethod := getPushMethodIfPublisherChild(queueHandler, queuePopCall)
	if queuePushMethod == nil {
		logger.Logger.Warnf("[GRAPH] nil queue push method for queue handler (%s) and queue pop call (%s)", queueHandler.GetName(), queuePopCall.GetName())
		return
	}

	for pushParamIdx, popParamIdx := range queuePushMethod.MatchQueueIdentifiers() {
		pushParam := queueHandler.Publisher.GetParam(pushParamIdx)
		popParam := queuePopCall.GetParam(popParamIdx)
		popParam = getVariableIfPointer(popParam)

		if addressVar, ok := popParam.(*variables.AddressVariable); ok {
			popParam = addressVar.GetAddressOf()
		} else if ptrVar, ok := popParam.(*variables.PointerVariable); ok {
			popParam = ptrVar.GetPointerTo()
		}

		popParam.AddReferenceWithID(pushParam, queuePopCall.GetCallerStr())
		logger.Logger.Infof("\t\t[QUEUE POP - REF BLOCK VAR] added reference (%d) from creator (%s): (%s) -> (%s)", popParam.GetId(), queuePopCall.GetCallerStr(), popParam.GetType().GetName(), popParam.GetVariableInfo().GetName())
		for _, dep := range variables.GetIndirectDependenciesWithCurrent(pushParam) {
			if dep.GetVariableInfo().IsUnassigned() {
				dep.GetVariableInfo().AssignID(graph.getAndIncGIndex())
				logger.Logger.Debugf("\t\t\t[QUEUE POP - GID DEP] assigned new gid (%d) to (%s)", dep.GetId(), dep.String())
			}
		}
	}
}

func (graph *AbstractGraph) appendAbstractEdges(rootParent AbstractNode, directParent AbstractNode, targetMethod *types.ParsedMethod) {
	for _, call := range targetMethod.Calls {
		_, rootIsQueueHandler := rootParent.(*AbstractQueueHandler)
		switch parsedCall := call.(type) {
		case *types.ParsedDatabaseCall:
			child := &AbstractDatabaseCall{
				ParsedCall: parsedCall,
				Params:     parsedCall.Params,
				Returns:    parsedCall.Returns,
				Service:    parsedCall.CallerTypeName.GetName(),
				Method:     parsedCall.Method,
				DbInstance: parsedCall.DbInstance,
				Subscriber: rootIsQueueHandler,
				Depth:      rootParent.GetNextDepth(),
			}
			rootParent.AddChild(child)
			logger.Logger.Infof("[GRAPH] added node for abstract database call with parent (%s): %s", child.GetCallerStr(), child.String())

			// if root parent is a queue handler (e.g. workerThread) and child is queue pop call
			if queueHandler, ok := rootParent.(*AbstractQueueHandler); ok && !queueHandler.IsEnabled() {
				graph.referenceQueuePopMethodBlockVars(queueHandler, child)
				queueHandler.Enable()
			}

			//graph.referenceMethodBlockVars(parsedCall, child)

			/* if rootIsQueueHandler && !rootQueueHandler.IsEnabled() {
				if !graph.referencePublisherParams(rootQueueHandler, child) {
					graph.referenceServiceCallerParams(rootParent, directParent, child)
				}
			} else {
				graph.referenceServiceCallerParams(rootParent, directParent, child)
			} */

		case *types.ParsedServiceCall:
			child := &AbstractServiceCall{
				ParsedCall: parsedCall,
				Caller:     parsedCall.CallerTypeName.GetName(),
				Callee:     parsedCall.CalleeTypeName.GetName(),
				Params:     parsedCall.Params,
				Returns:    parsedCall.Returns,
				Method:     parsedCall.Method,
				Depth:      rootParent.GetNextDepth(),
			}
			rootParent.AddChild(child)
			logger.Logger.Infof("[GRAPH] added node for abstract service call: %s", child.String())
			graph.referenceMethodBlockVars(parsedCall, child)

		case *types.ParsedInternalCall:
			tempChild := &AbstractTempInternalCall{
				ParsedCall: parsedCall,
				Service:    parsedCall.ServiceTypeName.GetName(),
				Params:     parsedCall.Params,
				Returns:    parsedCall.Returns,
				Method:     parsedCall.Method,
				Depth:      rootParent.GetNextDepth(),
			}
			
			//graph.referenceServiceCallerParams(rootParent, directParent, tempChild)
			tempMethod := graph.Services[tempChild.Service].GetInternalOrPackageMethod(tempChild.ParsedCall.Name)
			graph.appendAbstractEdges(rootParent, tempChild, tempMethod)

			logger.Logger.Infof("[GRAPH] added temporary node for abstract service call: %s", tempChild.String())
			graph.referenceMethodBlockVars(parsedCall, tempChild)
		}
	}
}

func (graph *AbstractGraph) appendPublisherQueueHandlers(app *app.App, publisher *AbstractDatabaseCall) {
	instance := publisher.ParsedCall.GetTargetedDatabaseInstance()
	if instance == nil {
		logger.Logger.Fatalf("received unexpected nil database for queue publisher parsed call: %s", publisher.ParsedCall.String())
	}
	for _, node := range app.Services {
		for _, handlerMethod := range node.GetQueueHandlersForDatabase(instance) {
			logger.Logger.Debugf("[GRAPH - QUEUE] found worker %s on instance '%s'", handlerMethod.String(), instance.GetName())
			abstractHandler := &AbstractQueueHandler{
				AbstractServiceCall: graph.createDummyAbstractServiceCall(node, handlerMethod, publisher, publisher.GetNextDepth()),
				DbInstance:          instance,
				Publisher:           publisher,
			}
			for _, p := range handlerMethod.GetParams() {
				abstractHandler.ParsedCall.Params = append(abstractHandler.ParsedCall.Params, &variables.CompositeVariable{
					VariableInfo: &variables.VariableInfo{
						Name: p.GetName(),
						Type: p.GetType(),
					},
				})
			}
			publisher.Children = append(publisher.Children, abstractHandler)
		}
	}
}

func getDependencies(v variables.Variable) []variables.Variable {
	indirectDeps := []variables.Variable{v}

	// indirect dependencySets from potential reference
	if v.GetVariableInfo().HasReference() {
		indirectDeps = append(indirectDeps, getDependencies(v.GetVariableInfo().GetReference())...)
	}
	// direct dependencySets
	for _, dep := range v.GetDependencies() {
		indirectDeps = append(indirectDeps, getDependencies(dep)...)
	}

	return indirectDeps
}

func (graph *AbstractGraph) referenceServiceCallerParams(parent AbstractNode, caller AbstractNode, child AbstractNode) {
	fmt.Println()
	if caller == parent {
		logger.Logger.Infof("[REF] reference caller (%s) to callee (%s.%s)", caller.GetName(), child.GetCallee(), child.GetName())
	} else {
		logger.Logger.Infof("[REF] reference caller (%s) from parent (%s) to callee (%s.%s)", caller.GetName(), parent.GetName(), child.GetCallee(), child.GetName())
	}

	for _, childParam := range child.GetParams() {
		deps := getDependencies(childParam)
		logger.Logger.Infof("\t[REF CHILD PARAM] visit (%s)", childParam.String())

		for _, dep := range deps {
			logger.Logger.Debugf("\t\t[REF CHILD PARAM DEP] visit dep (%s)", dep.String())
			if dep.GetVariableInfo().HasReference() {
				continue
			}
			for callerParamIdx, callerParam := range caller.GetParams() {
				logger.Logger.Tracef("\t[REF CALLER PARAM] visit (%s)", callerParam.String())
				if dep.GetVariableInfo().IsBlockParameter() && dep.GetVariableInfo().EqualBlockParamIndex(callerParamIdx) {
					if dep.GetVariableInfo().IsUnassigned() {
						if parent != caller && callerParam.GetVariableInfo().HasReference() {
							// this can happen with the context variable (e.g. handleMessage called by the workerThread in the NotifyService)
							dep.GetVariableInfo().AddOriginalReferenceWithID(callerParam.GetVariableInfo().GetReference())
							//dep = callerParam.DeepCopy()
						} else {
							if callerParam.GetVariableInfo().IsUnassigned() {
								unassaignedVariables := callerParam.GetUnassaignedVariables()
								for _, v := range unassaignedVariables {
									v.GetVariableInfo().AssignID(graph.getAndIncGIndex())
									logger.Logger.Warnf("\t\t\t[NEW GID] assigned new gid (%d) to (%s)", v.GetId(), v.String())
								}
							}
							//dep = callerParam.DeepCopy()
							logger.Logger.Warnf("\t\t\t[VARIABLE] added reference (%d) from creator (%s): (%s) -> (%s)", dep.GetId(), child.GetCallerStr(), dep.GetType().GetName(), callerParam.GetVariableInfo().GetName())
							dep.AddReferenceWithID(callerParam, child.GetCallerStr())

							// FIXME: THIS IS HARD CODED
							if structVariable, ok := childParam.(*variables.StructVariable); ok {
								if structParentVariable, ok := callerParam.(*variables.StructVariable); ok {
									structVariable.CopyFrom(structParentVariable)
								} else {
									logger.Logger.Warnf("FIXMEEEEEEEEE %s (%s) vs %s (%s)", childParam.String(), child.GetName(), callerParam.String(), parent.GetName())
								}
							}
						}
					}
					if dep.GetVariableInfo().IsUnassigned() {
						dep.GetVariableInfo().AssignID(graph.getAndIncGIndex())
					}
				}
			}
		}
	}
}
