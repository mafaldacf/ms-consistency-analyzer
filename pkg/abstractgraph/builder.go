package abstractgraph

import (
	"fmt"

	"analyzer/pkg/app"
	"analyzer/pkg/controlflow"
	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
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

func (graph *AbstractGraph) createDummyAbstractServiceCall(node *service.Service, method *types.ParsedMethod, parent *AbstractDatabaseCall) AbstractServiceCall {
	logger.Logger.Debugf("[GRAPH - DUMMY] create dummy abstract service call for node %s and method %s with params %v", node.Name, method.Name, method.GetParams())

	var callerStr = "Client"
	if parent != nil {
		callerStr = parent.ParsedCall.CallerTypeName.GetName()
	}

	call := AbstractServiceCall{
		ParsedCall: &types.ParsedServiceCall{
			ParsedCall: types.ParsedCall{
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
		v := controlflow.CreateVariableFromType(node, p.GetName(), p.GetType())
		call.ParsedCall.Params = append(call.ParsedCall.Params, v)
		logger.Logger.Debugf("created variable %s (%s)", v.String(), utils.GetType(v))
	}
	call.Params = call.ParsedCall.Params
	return call
}

func (graph *AbstractGraph) addEntry(node *service.Service, method *types.ParsedMethod) {
	// add entry node to graph
	entryCall := graph.createDummyAbstractServiceCall(node, method, nil)
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
		targetMethod := graph.Services[node.Callee].GetExposedMethod(node.ParsedCall.Name)
		logger.Logger.Debugf("[GRAPH] visiting abstract service call (%d calls): %s", len(targetMethod.Calls), node.String())
		graph.appendAbstractEdges(node, node, targetMethod)
	case *AbstractDatabaseCall:
		if node.ParsedCall.Method.IsQueueWrite() {
			logger.Logger.Debugf("[GRAPH] visiting abstract database call: %s", node.String())
			graph.appendPublisherQueueHandlers(app, node)
		}
	case *AbstractQueueHandler:
		targetMethod := graph.Services[node.Callee].GetQueueHandlerMethod(node.ParsedCall.Name)
		logger.Logger.Debugf("[GRAPH] visiting abstract queue handler (%d calls): %s", len(targetMethod.Calls), node.String())
		graph.appendAbstractEdges(node, node, targetMethod)
	default:
		logger.Logger.Fatalf("Error recursing build for %s\nUnknown node type: %s", node, utils.GetType(node))
	}
	for _, edge := range abstractNode.GetChildren() {
		graph.recurseBuild(app, edge)
	}
}

func (graph *AbstractGraph) appendAbstractEdges(rootParent AbstractNode, directParent AbstractNode, targetMethod *types.ParsedMethod) {
	for _, call := range targetMethod.Calls {
		rootQueueHandler, rootIsQueueHandler := rootParent.(*AbstractQueueHandler)
		switch parsedCall := call.(type) {
		case *types.ParsedDatabaseCall:
			child := &AbstractDatabaseCall{
				ParsedCall: parsedCall,
				Params:     parsedCall.Params,
				Returns:    parsedCall.Returns,
				Service:    parsedCall.CallerTypeName.GetName(),
				Method:     parsedCall.Method.String(),
				DbInstance: parsedCall.DbInstance,
				Subscriber: rootIsQueueHandler,
			}
			rootParent.AddChild(child)
			logger.Logger.Debugf("[GRAPH] added node for abstract database call: %s", child.String())

			if rootIsQueueHandler && !rootQueueHandler.HasQueueReceiver() {
				if !graph.referencePublisherParams(rootQueueHandler, child) {
					graph.referenceServiceCallerParams(rootParent, directParent, child)
				}
			} else {
				graph.referenceServiceCallerParams(rootParent, directParent, child)
			}
		case *types.ParsedServiceCall:
			child := &AbstractServiceCall{
				ParsedCall: parsedCall,
				Caller:     parsedCall.CallerTypeName.GetName(),
				Callee:     parsedCall.CalleeTypeName.GetName(),
				Params:     parsedCall.Params,
				Returns:    parsedCall.Returns,
				Method:     parsedCall.Method.String(),
			}
			rootParent.AddChild(child)
			logger.Logger.Debugf("[GRAPH] added node for abstract service call: %s", child.String())
			graph.referenceServiceCallerParams(rootParent, directParent, child)
		case *types.ParsedInternalCall:
			tempChild := &AbstractTempInternalCall{
				ParsedCall: parsedCall,
				Service:    parsedCall.ServiceTypeName.GetName(),
				Params:     parsedCall.Params,
				Returns:    parsedCall.Returns,
				Method:     parsedCall.Method.String(),
			}
			graph.referenceServiceCallerParams(rootParent, directParent, tempChild)
			tempMethod := graph.Services[tempChild.Service].GetInternalMethod(tempChild.ParsedCall.Name)
			graph.appendAbstractEdges(rootParent, tempChild, tempMethod)
			logger.Logger.Debugf("[GRAPH] added temporary node for abstract service call: %s", tempChild.String())
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

func (graph *AbstractGraph) referencePublisherParams(queueHandler *AbstractQueueHandler, child *AbstractDatabaseCall) bool {
	if child.ParsedCall.Method.IsQueueRead() && queueHandler.Publisher.DbInstance == child.ParsedCall.DbInstance {
		pushMethod, ok := queueHandler.Publisher.ParsedCall.Method.(*blueprint.BackendMethod)
		if !ok {
			return false
		}
		queueHandler.EnableQueueReceiver()
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
	return false
}

func getDependencies(first bool, v variables.Variable) []variables.Variable {
	indirectDeps := []variables.Variable{}
	if !first {
		indirectDeps = append(indirectDeps, v)
	}

	// indirect dependencySets from potential reference
	if v.GetVariableInfo().HasReference() {
		indirectDeps = append(indirectDeps, getDependencies(false, v.GetVariableInfo().GetReference())...)
	}
	// direct dependencySets
	for _, dep := range v.GetDependencies() {
		indirectDeps = append(indirectDeps, getDependencies(false, dep)...)
	}

	return indirectDeps
}

func (graph *AbstractGraph) referenceServiceCallerParams(parent AbstractNode, caller AbstractNode, child AbstractNode) {
	fmt.Println()
	logger.Logger.Infof("[REF] visiting %s (caller = %s, parent = %s)", child.String(), caller.GetName(), parent.GetName())

	/* _, parentIsService := parent.(*AbstractServiceCall)
	_, childIsDatastore := child.(*AbstractDatabaseCall)
	// ignore when child is a datastore, unless the parent is also a datastore
	// (e.g. queue.Push and the corresponding queue.Pop)
	if parentIsService && childIsDatastore {
		for i, childParam := range child.GetParams() {
			callArg := child.GetParsedCall().GetArgument(i)
			if callArg.GetVariableInfo().IsUnassigned() {
				unassaignedVariables := callArg.GetUnassaignedVariables()
				for _, v := range unassaignedVariables {
					v.GetVariableInfo().AssignID(graph.getAndIncGIndex())
					logger.Logger.Warnf("\t\t\t[GID] assigned gid %s (%d)", v.String(), v.GetId())
				}
			}
			if parent == caller {
				childParam.AddReferenceWithID(callArg, child.GetCallerStr())
			}
			if childParam.GetVariableInfo().IsUnassigned() {
				childParam.GetVariableInfo().AssignID(graph.getAndIncGIndex())
			}
		}
		logger.Logger.Warnf("ignoring references between parent service (%s) and child datastore (%s)", parent.GetName(), child.GetName())
		return
	} */

	for _, childParam := range child.GetParams() {
		deps := getDependencies(false, childParam)
		logger.Logger.Infof("\t\t[REF] %s: referencing %v (deps = %v)", child.GetName(), childParam, deps)
		/* callArg := child.GetParsedCall().GetArgument(i)

		if callArg.GetVariableInfo().IsUnassigned() {
			unassaignedVariables := callArg.GetUnassaignedVariables()
			for _, v := range unassaignedVariables {
				v.GetVariableInfo().AssignID(graph.getAndIncGIndex())
				logger.Logger.Warnf("\t\t\t[GID] assigned gid %s (%d)", v.String(), v.GetId())
			}
		}

		if childParam.GetVariableInfo().HasReference() {
			continue
		}

		if parent == caller {
			childParam.AddReferenceWithID(callArg, child.GetCallerStr())
		}

		if childParam.GetVariableInfo().IsUnassigned() {
			childParam.GetVariableInfo().AssignID(graph.getAndIncGIndex())
		} */

		for _, dep := range deps {
			logger.Logger.Infof("\t\t[REF] got dep %s (%v) caller params", dep.String(), caller.GetParams())
			if dep.GetVariableInfo().HasReference() {
				continue
			}
			for callerParamIdx, callerParam := range caller.GetParams() {
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
									logger.Logger.Warnf("\t\t\t[GID] assigned gid %s (%d)", v.String(), v.GetId())
								}
							}
							//dep = callerParam.DeepCopy()
							dep.AddReferenceWithID(callerParam, child.GetCallerStr())

							// FIXME: THIS IS HARD CODED
							if structVariable, ok := childParam.(*variables.StructVariable); ok {
								if structParentVariable, ok := callerParam.(*variables.StructVariable); ok {
									structVariable.CopyFrom(structParentVariable)
								} else {
									logger.Logger.Fatalf("%s (%s) vs %s (%s)", childParam.String(), child.GetName(), callerParam.String(), parent.GetName())
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

	/* for _, dep := range getIndirectParamDeps(childParam) {
		if dep.GetVariableInfo().HasReference() {
			continue
		}
		for callerParamIdx, callerParam := range caller.GetParams() {
			if dep.GetVariableInfo().IsBlockParameter() && dep.GetVariableInfo().EqualBlockParamIndex(callerParamIdx) {
				if dep.GetVariableInfo().IsUnassigned() {

					if addressVar, ok := dep.(*types.AddressVariable); ok {
						dep = addressVar.GetAddressOf()
					} else if ptrVar, ok := dep.(*types.PointerVariable); ok {
						dep = ptrVar.GetPointerTo()
					}

					// we are in the remote service method
					// that was called by the parent service
					// otherwise, parent funcion corresponds to the caller function within the service
					if parent == caller {
						logger.Logger.Infof("---- ADDING REFERENCE FOR PARAM %v WITH CHILD %s and CALLER %s", callerParam, child.String(), caller.String())
						dep.GetVariableInfo().AddReferenceWithID(callerParam, child.GetCallerStr())
					} else if callerParam.GetVariableInfo().HasReference() {
						// this can happen with the context variable (e.g. handleMessage called by the workerThread in the NotifyService)
						dep.GetVariableInfo().AddOriginalReferenceWithID(callerParam.GetVariableInfo().GetReference())
					} else {
						dep.GetVariableInfo().AddReferenceWithID(callerParam, parent.GetName())
					}
					break
				}
			}
		}
		if dep.GetVariableInfo().IsUnassigned() {
			dep.GetVariableInfo().AssignID(graph.getAndIncGIndex())
		}
	} */
}
