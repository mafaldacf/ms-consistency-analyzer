package abstractgraph

import (
	"analyzer/pkg/app"
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	"encoding/json"
	"fmt"
	"os"
)

type AbstractGraph struct {
	AppName  string
	Nodes    []AbstractNode
	Services map[string]*service.ServiceNode
	GIndex   int64
}

func (graph *AbstractGraph) getAndIncGIndex() int64 {
	prev := graph.GIndex
	graph.GIndex++
	return prev
}

type AbstractNode interface {
	GetParams() []*types.Variable
	GetParam(int) *types.Variable
	String() string
	GetName() string
	GetChildren() []AbstractNode
	AddChild(AbstractNode)
	SetVisited(bool)
	IsVisited() bool
	GetCallerStr() string
	GetCallee() string
}

type AbstractServiceCall struct {
	AbstractNode `json:"-"` // omit from json
	Visited      bool       `json:"-"` // omit from json
	Call         string     `json:"call,omitempty"`
	Method       string     `json:"method"`

	Caller string `json:"caller"`
	Callee string `json:"callee"`

	Params     []*types.Variable              `json:"params"`
	ParsedCall *service.ServiceParsedCallExpr `json:"-"` // omit from json

	// nodes representing database calls cannot contain children as well
	Children []AbstractNode `json:"edges"`
}

func (call *AbstractServiceCall) GetParams() []*types.Variable {
	return call.Params
}

func (call *AbstractServiceCall) GetParam(index int) *types.Variable {
	return call.Params[index]
}

func (call *AbstractServiceCall) GetName() string {
	return call.ParsedCall.Name
}

func (call *AbstractServiceCall) GetCallee() string {
	return call.Callee
}

func (call *AbstractServiceCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractServiceCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractServiceCall) AddChild(child AbstractNode) {
	logger.Logger.Debugf("adding child %s (%s) > %s (%s)", call.GetName(), utils.GetType(call), child.GetName(), utils.GetType(child))
	call.Children = append(call.Children, child)
}

func (call *AbstractServiceCall) SetVisited(v bool) {
	call.Visited = v
}

func (call *AbstractServiceCall) IsVisited() bool {
	return call.Visited
}

func (call *AbstractServiceCall) GetCallerStr() string {
	return call.Caller
}

type AbstractTempInternalCall struct {
	AbstractNode `json:"-"`
	Visited      bool                                `json:"-"`
	Call         string                              `json:"call,omitempty"`
	Method       string                              `json:"method"`
	Service      string                              `json:"service"`
	Params       []*types.Variable                   `json:"params"`
	ParsedCall   *service.InternalTempParsedCallExpr `json:"-"`
	Children     []AbstractNode                      `json:"edges"`
}

func (call *AbstractTempInternalCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractTempInternalCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractTempInternalCall) GetParams() []*types.Variable {
	return call.Params
}

func (call *AbstractTempInternalCall) GetParam(index int) *types.Variable {
	return call.Params[index]
}

func (call *AbstractTempInternalCall) GetName() string {
	return call.ParsedCall.Name
}

func (call *AbstractTempInternalCall) IsVisited() bool {
	return call.Visited
}

func (call *AbstractTempInternalCall) SetVisited(v bool) {
	call.Visited = v
}

func (call *AbstractTempInternalCall) GetCallerStr() string {
	return call.Service
}

type AbstractDatabaseCall struct {
	AbstractNode `json:"-"`                      // omit from json
	Visited      bool                            `json:"-"` // omit from json
	Call         string                          `json:"call"`
	Method       string                          `json:"method"`
	Service      string                          `json:"caller"`
	Params       []*types.Variable               `json:"params"`
	ParsedCall   *service.DatabaseParsedCallExpr `json:"-"` // omit from json
	Children     []AbstractNode                  `json:"queue_handlers,omitempty"`
	DbInstance   types.DatabaseInstance          `json:"db_instance"`
}

type AbstractQueueHandler struct {
	AbstractServiceCall `json:"handler"`
	DbInstance          types.DatabaseInstance `json:"db_instance"`
	Publisher           *AbstractDatabaseCall  `json:"-"`
	Receiver            bool                   `json:"-"`
}

func (call *AbstractQueueHandler) HasQueueReceiver() bool {
	return call.Receiver
}

func (call *AbstractQueueHandler) EnableQueueReceiver() {
	call.Receiver = true
}

func (call *AbstractDatabaseCall) GetParams() []*types.Variable {
	return call.Params
}

func (call *AbstractDatabaseCall) GetParam(index int) *types.Variable {
	if index > 0 && index < len(call.Params) {
		return call.Params[index]
	}
	logger.Logger.Warnf("did not find parameter of index %d for call %s", index, call.String())
	return nil
}

func (call *AbstractDatabaseCall) GetName() string {
	return call.ParsedCall.Name
}

func (call *AbstractDatabaseCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractDatabaseCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractDatabaseCall) AddChild(child AbstractNode) {
	logger.Logger.Debugf("adding child %s (%s) > %s (%s)", call.GetName(), utils.GetType(call), child.GetName(), utils.GetType(child))
	call.Children = append(call.Children, child)
}

func (call *AbstractDatabaseCall) SetVisited(v bool) {
	call.Visited = v
}

func (call *AbstractDatabaseCall) IsVisited() bool {
	return call.Visited
}

func (call *AbstractDatabaseCall) GetCallerStr() string {
	return call.Service
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
func getVariableIfPointer(variable *types.Variable) *types.Variable {
	value := variable
	if _, ok := value.Type.(*types.Pointer); ok {
		value = value.Deps[0]
	}
	return value
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
		call.ParsedCall.Params = append(call.ParsedCall.Params, &types.Variable{
			Name: p.GetName(),
			Type: p.GetType(),
			Id:   graph.getAndIncGIndex(),
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
		param.Ref = &types.Ref{
			Creator: "Client",
			Variable: &types.Variable{
				Name: param.Name,
				Id:   0,
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
				Call:       parsedCall.SimpleString(),
				Service:    parsedCall.CallerTypeName.GetName(),
				Method:     parsedCall.Method.String(),
				DbInstance: parsedCall.DbInstance,
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
				Call:       parsedCall.SimpleString(),
				Method:     parsedCall.Method.String(),
			}
			rootParent.AddChild(child)
			graph.referenceServiceCallerParams(rootParent, directParent, child)
		case *service.InternalTempParsedCallExpr:
			tempChild := &AbstractTempInternalCall{
				ParsedCall: parsedCall,
				Service:    parsedCall.ServiceTypeName.GetName(),
				Params:     parsedCall.Params,
				Call:       parsedCall.SimpleString(),
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
				abstractHandler.ParsedCall.Params = append(abstractHandler.ParsedCall.Params, &types.Variable{
					Name: p.GetName(),
					Type: p.GetType(),
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
			popParam.AddReferenceWithID(pushParam, "unknown creator")
			if pushParam.Ref != nil {
				popParam.Ref.Creator = pushParam.Ref.Creator
			} else {
				popParam.Ref.Creator = queueHandler.Publisher.ParsedCall.CallerTypeName.GetName()
			}
		}
		return true
	}
	return false
}

func getIndirectParamDeps(v *types.Variable) []*types.Variable {
	var deps []*types.Variable
	for _, d := range v.Deps {
		deps = append(deps, getIndirectParamDeps(d)...)
	}
	return append(deps, v)
}

func (graph *AbstractGraph) referenceServiceCallerParams(rootParent AbstractNode, directParent AbstractNode, child AbstractNode) {
	for _, childParam := range child.GetParams() {
		for _, dep := range getIndirectParamDeps(childParam) {
			if dep.HasReference() {
				continue
			}
			for callerParamIdx, callerParam := range directParent.GetParams() {
				if dep.IsBlockParameter() && dep.EqualBlockParamIndex(callerParamIdx) {
					if dep.IsUnassigned() {
						if rootParent == directParent {
							dep.AddReferenceWithID(callerParam, child.GetCallerStr())
						} else {
							if len(callerParam.Deps) > 0 {
								dep.AssignID(graph.getAndIncGIndex())
								dep.AddDependencies(callerParam.Deps)
							} else if callerParam.HasReference() {
								// this can happen with the context variable (e.g. handleMessage called by the workerThread in the NotifyService)
								dep.AddOriginalReferenceWithID(callerParam.Ref)
							} else {
								dep.AddReferenceWithID(callerParam, child.GetCallerStr())
							}
						}
						break
					}
				}
			}
			if dep.IsUnassigned() {
				dep.AssignID(graph.getAndIncGIndex())
			}
		}
	}
}
