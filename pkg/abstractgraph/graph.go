package abstractgraph

import (
	"analyzer/pkg/app"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	"encoding/json"
	"fmt"
	"os"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

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

type AbstractQueueHandler struct {
	AbstractServiceCall `json:"handler"`
	DbInstance          types.DatabaseInstance `json:"db_instance"`
	Publisher 			*AbstractDatabaseCall  `json:"-"`
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

func (call *AbstractServiceCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractServiceCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractServiceCall) AddChild(child AbstractNode) {
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

type AbstractDatabaseCall struct {
	AbstractNode `json:"-"`                      // omit from json
	Visited      bool                            `json:"-"` // omit from json
	Call         string                          `json:"call"`
	Method       string                          `json:"method"`
	Caller       string                          `json:"caller"`
	Params       []*types.Variable               `json:"params"`
	ParsedCall   *service.DatabaseParsedCallExpr `json:"-"` // omit from json
	Children     []AbstractNode                  `json:"queue_handlers,omitempty"`
	DbInstance   types.DatabaseInstance          `json:"db_instance"`
}

func (call *AbstractDatabaseCall) GetParams() []*types.Variable {
	return call.Params
}

func (call *AbstractDatabaseCall) GetParam(index int) *types.Variable {
	return call.Params[index]
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
	call.Children = append(call.Children, child)
}

func (call *AbstractDatabaseCall) SetVisited(v bool) {
	call.Visited = v
}

func (call *AbstractDatabaseCall) IsVisited() bool {
	return call.Visited
}

func (call *AbstractDatabaseCall) GetCallerStr() string {
	return call.Caller
}

type AbstractGraph struct {
	Nodes           []AbstractNode
	AppServiceNodes map[string]*service.ServiceNode
	GlobalIndex     int64
}

func (graph *AbstractGraph) getAndIncGlobalIndex() int64 {
	prev := graph.GlobalIndex
	graph.GlobalIndex++
	return prev
}

func Build(app *app.App, entryPoints []string) *AbstractGraph {
	graph := &AbstractGraph{
		Nodes:           make([]AbstractNode, 0),
		AppServiceNodes: app.Services,
		GlobalIndex:     1,
	}
	for _, serviceName := range entryPoints {
		service := app.Services[serviceName]
		for _, method := range service.ExposedMethods {
			graph.initBuild(app, app.Services[serviceName], method)
		}
	}

	for _, node := range graph.Nodes {
		graph.cleanVisited(node)
	}
	graph.GlobalIndex = 1
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
	if _, ok := value.Type.(*gocode.Pointer); ok {
		value = value.Deps[0]
	}
	return value
}

func (graph *AbstractGraph) Save() {
	// print in JSON format
	// https://omute.net/editor
	file, err := os.Create("assets/abstractgraph.json")
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
		callerStr = utils.GetShortTypeStr(parent.ParsedCall.CallerTypeName)
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
			Name: p.Name,
			Type: p.Type,
			Id:   graph.getAndIncGlobalIndex(),
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
		targetMethod := graph.AppServiceNodes[node.Callee].GetExposedMethod(node.ParsedCall.Name)
		graph.appendAbstractEdges(node, targetMethod)
	case *AbstractDatabaseCall:
		if node.ParsedCall.Method.IsQueueWrite() {
			graph.appendPublisherQueueHandlers(app, node)
		}
	case *AbstractQueueHandler:
		targetMethod := graph.AppServiceNodes[node.Callee].GetQueueHandlerMethod(node.ParsedCall.Name)
		graph.appendAbstractEdges(node, targetMethod)
	default:
		logger.Logger.Warnf("Error recursing build for %s", node)
		return
	}
	for _, edge := range abstractNode.GetChildren() {
		graph.recurseBuild(app, edge)
	}
}

func (graph *AbstractGraph) appendAbstractEdges(parent AbstractNode, targetMethod *service.ParsedFuncDecl) {
	for _, call := range targetMethod.Calls {
		switch parsedCall := call.(type) {
		case *service.DatabaseParsedCallExpr:
			child := &AbstractDatabaseCall{
				ParsedCall: parsedCall,
				Params:     parsedCall.Params,
				Call:       parsedCall.SimpleString(),
				Caller:     utils.GetShortTypeStr(parsedCall.CallerTypeName),
				Method:     parsedCall.Method.String(),
				DbInstance: parsedCall.DbInstance,
			}
			parent.AddChild(child)
			if queueHandler, isQueueHandler := parent.(*AbstractQueueHandler); isQueueHandler {
				graph.referencePublisherParams(queueHandler, child)
			} else {
				graph.referenceServiceCallerParams(parent, child)
			}
		case *service.ServiceParsedCallExpr:
			child := &AbstractServiceCall{
				ParsedCall: parsedCall,
				Caller:     utils.GetShortTypeStr(parsedCall.CallerTypeName),
				Callee:     utils.GetShortTypeStr(parsedCall.CalleeTypeName),
				Params:     parsedCall.Params,
				Call:       parsedCall.SimpleString(),
				Method:     parsedCall.Method.String(),
			}
			parent.AddChild(child)
			graph.referenceServiceCallerParams(parent, child)
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
					Name: p.Name,
					Type: p.Type,
				})
			}
			publisher.Children = append(publisher.Children, abstractHandler)
		}
	}
}

func (graph *AbstractGraph) referencePublisherParams(parent *AbstractQueueHandler, child *AbstractDatabaseCall) {
	if child.ParsedCall.Method.IsQueueRead() {
		if parent.Publisher.DbInstance == child.ParsedCall.DbInstance {
			// valid because we have Push(ctx, src) and Pop(ctx, dst)
			// so the parameters indexes match correctly
			for idx, param := range child.ParsedCall.Params {
				parentParam := parent.Publisher.GetParam(idx)
				param := getVariableIfPointer(param)
				param.AddReferenceWithID("unknown creator", parentParam)
				if parentParam.Ref != nil {
					param.Ref.Creator = parentParam.Ref.Creator
				} else {
					param.Ref.Creator = utils.GetShortTypeStr(parent.Publisher.ParsedCall.CallerTypeName)
				}
			}
		}
	}
}


func getIndirectParamDeps(v *types.Variable) []*types.Variable {
	var deps []*types.Variable
	for _, d := range v.Deps {
		deps = append(deps, getIndirectParamDeps(d)...)
	}
	return append(deps, v)
}

func (graph *AbstractGraph) referenceServiceCallerParams(parent AbstractNode, child AbstractNode) {
	for _, childParam := range child.GetParams() {
		for _, dep := range getIndirectParamDeps(childParam) {
			if dep.HasReference() {
				continue
			}
			for callerParamIdx, callerParam := range parent.GetParams() {
				if dep.IsBlockParam && dep.EqualBlockParamIndex(callerParamIdx) {
					dep.AddReferenceWithID(parent.GetCallerStr(), callerParam)
					continue
				}
			}
			dep.AssignID(graph.getAndIncGlobalIndex())
		}
	}
}
