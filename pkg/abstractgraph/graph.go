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
	"go/token"
	"os"
	"slices"
	"sort"
)

type AbstractNode interface {
	GetParams() []*types.Variable
	String() string
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
	Method       string     `json:"method,omitempty"`

	Caller string `json:"caller,omitempty"`
	Callee string `json:"callee,omitempty"`

	Params     []*types.Variable       `json:"params,omitempty"`
	ParsedCall *service.ParsedCallExpr `json:"-"` // omit from json

	// nodes representing database calls cannot contain children as well
	Children []AbstractNode `json:"edges,omitempty"`
	Parent   AbstractNode   `json:"-"` // omit from json
}

type AbstractQueueHandler struct {
	AbstractServiceCall `json:"handler"`
	DbInstance          types.DatabaseInstance `json:"db_instance"`
}

func (call *AbstractServiceCall) GetParams() []*types.Variable {
	return call.Params
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
	AbstractNode `json:"-"`              // omit from json
	Visited      bool                    `json:"-"` // omit from json
	Call         string                  `json:"call,omitempty"`
	Method       string                  `json:"method,omitempty"`
	Caller       string                  `json:"caller,omitempty"`
	Params       []*types.Variable       `json:"params,omitempty"`
	ParsedCall   *service.ParsedCallExpr `json:"-"` // omit from json
	Parent       AbstractNode            `json:"-"` // omit from json
	Children     []AbstractNode          `json:"queue_handlers,omitempty"`
	DbInstance   types.DatabaseInstance  `json:"db_instance"`
}

func (call *AbstractDatabaseCall) GetParams() []*types.Variable {
	return call.Params
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

func getAllChildDeps(node AbstractNode) map[AbstractNode][]*types.Variable {
	allChildDeps := make(map[AbstractNode][]*types.Variable)
	for _, child := range node.GetChildren() {
		// if it is visited then it already has IDs assigned
		if !child.IsVisited() {
			logger.Logger.Warnf("\t getting all deps for child %s", child.String())
			// get all dependencies recursively within children
			childDeps := make(map[*types.Variable]bool)
			for _, param := range child.GetParams() {
				for _, paramDep := range getParamDeps(param) {
					if exists := childDeps[paramDep]; !exists {
						allChildDeps[child] = append(allChildDeps[child], paramDep)
						childDeps[paramDep] = true
					}
				}
			}
		}
	}
	return allChildDeps
}

// getChildBlockParams filters the block parameters for each child
// block parameters are a subset of deps and correspond to the CFG block parameter
func getChildBlockParams(node AbstractNode) map[AbstractNode][]*types.Variable {
	childBlockParams := make(map[AbstractNode][]*types.Variable)
	for child, childDeps := range getAllChildDeps(node) {
		for _, childDep := range childDeps {
			if childDep.IsBlockParam {
				childBlockParams[child] = append(childBlockParams[child], childDep)
			}
		}
	}
	return childBlockParams
}

func (graph *AbstractGraph) matchIdentifiers(node AbstractNode) {
	if node.IsVisited() {
		return
	}
	logger.Logger.Warnf("matching identifiers for node %s (params = %v)", node.String(), node.GetParams())
	node.SetVisited(true)
	graph.matchCallerToChildParams(node)
	logger.Logger.Warn()
	for _, child := range node.GetChildren() {
		graph.matchIdentifiers(child)
	}
}

func (graph *AbstractGraph) matchCallerToChildParams(node AbstractNode) {
	for callerParamIdx, callerParam := range node.GetParams() {
		if !callerParam.HasAssignedID() {
			callerParam.Id = graph.getAndIncGlobalIndex()
			logger.Logger.Warnf("\t caller param #%d: %s (new id = %d)", callerParamIdx, callerParam.Name, callerParam.Id)
		} else {
			logger.Logger.Warnf("\t caller param #%d: %s (id = %d)", callerParamIdx, callerParam.Name, callerParam.Id)
		}

		for child, childBlockParams := range getChildBlockParams(node) {
			for _, childBlockParam := range childBlockParams {
				if !childBlockParam.HasAssignedID() && childBlockParam.EqualBlockParamIndex(callerParamIdx) {
					logger.Logger.Warnf("\t\t matching child (%s) param '%s' with parent (%s) param '%s' for id %d", child.String(), childBlockParam.Name, node.String(), callerParam.Name, callerParam.Id)
					childBlockParam.AssignID(callerParam.Id)
					childBlockParam.AddReference(&types.Ref{
						Name:     callerParam.Name,
						Id:       callerParam.Id,
						Creator:  node.GetCallerStr(),
						Variable: callerParam,
					})
				}
			}
		}
	}
}

func getParamDeps(v *types.Variable) []*types.Variable {
	var deps []*types.Variable
	for _, d := range v.Deps {
		deps = append(deps, getParamDeps(d)...)
	}
	return append(deps, v)
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

func getMethodCallsLinenosByOrder(method *service.ParsedFuncDecl) []token.Pos {
	var linenos []token.Pos
	for k := range method.DatabaseCalls {
		linenos = append(linenos, k)
	}
	for k := range method.ServiceCalls {
		linenos = append(linenos, k)
	}
	// order by lineno
	sort.Slice(linenos, func(i, j int) bool {
		return linenos[i] < linenos[j]
	})
	return linenos
}

func (graph *AbstractGraph) initBuild(app *app.App, serviceNode *service.ServiceNode, targetMethod *service.ParsedFuncDecl) {
	graph.addEntry(serviceNode, targetMethod)
	for _, abstractEntry := range graph.Nodes {
		if abstractServiceEntry, ok := abstractEntry.(*AbstractServiceCall); ok { // sanity check
			graph.recurseBuild(app, abstractServiceEntry)
		}
	}
}

func createDummyAbstractServiceCall(node *service.ServiceNode, method *service.ParsedFuncDecl, caller string) AbstractServiceCall {
	logger.Logger.Warnf("[GRAPH - DUMMY] create dummy abstract service call for node %s and method %s", node.Name, method.Name)
	call := AbstractServiceCall{
		ParsedCall: &service.ParsedCallExpr{
			TargetField: node.Name,
			Name:        method.Name,
			Method:      method,
		},
		Caller: caller,
		Callee: node.Name,
		Method: method.String(),
	}
	for _, p := range method.GetParams() {
		call.ParsedCall.Params = append(call.ParsedCall.Params, &types.Variable{
			Name: p.Name,
			Type: p.Type,
		})
	}
	return call
}

func (graph *AbstractGraph) addEntry(node *service.ServiceNode, method *service.ParsedFuncDecl) {
	// add entry node to graph
	entryCall := createDummyAbstractServiceCall(node, method, "Client")
	graph.Nodes = append(graph.Nodes, &entryCall)
	// build entry node
	entryMethod := node.ExposedMethods[method.Name]
	for _, p := range entryMethod.Params {
		entryCall.Params = append(entryCall.Params, &types.Variable{
			Name: p.Name,
			Type: p.Type,
			Id:   types.VARIABLE_UNASSIGNED_ID,
			Ref: &types.Ref{
				Creator: "Client",
				Name:    p.Name,
				Id:      types.VARIABLE_UNASSIGNED_ID,
			},
		})
	}
}

func (graph *AbstractGraph) recurseBuild(app *app.App, abstractNode AbstractNode) {
	if abstractNode.IsVisited() {
		return
	}
	abstractNode.SetVisited(true)

	switch node := abstractNode.(type) {
	case *AbstractServiceCall:
		logger.Logger.Debugf("Doing recurse build on service call %s", node.String())
		targetMethod := graph.AppServiceNodes[node.Callee].ExposedMethods[node.ParsedCall.Name]
		graph.appendAbstractEdges(node, targetMethod)
	case *AbstractDatabaseCall:
		logger.Logger.Debugf("Doing recurse build on database call %s", node.String())
		if dbInstance := node.ParsedCall.GetTargetedDatabaseInstance(); dbInstance != nil && dbInstance.IsQueue() {
			if method, ok := node.ParsedCall.Method.(*frameworks.BlueprintBackend); ok && method.IsWrite() {
				queueHandlers := graph.findQueueHandlers(app, dbInstance, node)
				for _, handler := range queueHandlers {
					node.Children = append(node.Children, handler)
				}
			}
		}
	case *AbstractQueueHandler:
		logger.Logger.Debugf("Doing recurse build on queue handler %s", node.String())
		targetMethod := graph.AppServiceNodes[node.Callee].QueueHandlerMethods[node.ParsedCall.Name]
		graph.appendAbstractEdges(node, targetMethod)
	default:
		logger.Logger.Debugf("Error recursing build for %s", node)
		return
	}
	for _, edge := range abstractNode.GetChildren() {
		graph.recurseBuild(app, edge)
	}
}

func (graph *AbstractGraph) findQueueHandlers(app *app.App, instance types.DatabaseInstance, publisher *AbstractDatabaseCall) []*AbstractQueueHandler {
	var queueHandlers []*AbstractQueueHandler
	for _, node := range app.Services {
		if _, ok := node.Databases[instance.GetName()]; ok {
			if _, ok := node.Databases[instance.GetName()]; ok {
				for _, queueHandler := range node.QueueHandlerMethods {
					if slices.Contains(queueHandler.DbInstances, instance) {
						logger.Logger.Warnf("[GRAPH - QUEUE] found worker %s on instance '%s'", queueHandler.String(), instance.GetName())
						queueHandler := &AbstractQueueHandler{
							AbstractServiceCall: createDummyAbstractServiceCall(node, queueHandler, utils.GetShortTypeStr(publisher.ParsedCall.CallerTypeName)),
							DbInstance:          instance,
						}
						for _, p := range queueHandler.GetParams() {
							queueHandler.ParsedCall.Params = append(queueHandler.ParsedCall.Params, &types.Variable{
								Name: p.Name,
								Type: p.Type,
							})
						}
						queueHandlers = append(queueHandlers, queueHandler)
					}
				}
			}
		}
	}
	return queueHandlers
}

func (graph *AbstractGraph) appendAbstractEdges(parentCall AbstractNode, targetMethod *service.ParsedFuncDecl) {
	linenos := getMethodCallsLinenosByOrder(targetMethod)
	for _, lineno := range linenos {
		if targetMethod.DatabaseCalls[lineno] != nil {
			call := targetMethod.DatabaseCalls[lineno]
			abstractDbCall := &AbstractDatabaseCall{
				ParsedCall: call,
				Params:     call.Params,
				Call:       call.SimpleString(),
				Caller:     utils.GetShortTypeStr(call.CallerTypeName),
				Method:     call.Method.String(),
				DbInstance: call.DbInstance,
			}
			logger.Logger.Warnf("[GRAPH - EDGES] appending edge of abstract database call %s", call.SimpleString())
			parentCall.AddChild(abstractDbCall)
			if dbInstance := call.GetTargetedDatabaseInstance(); dbInstance != nil && dbInstance.IsQueue() {
				if method, ok := call.Method.(*frameworks.BlueprintBackend); ok && method.IsWrite() {
					logger.Logger.Warnf("[GRAPH - QUEUE] found queue push call in %s: %s on instance '%s'", parentCall.(*AbstractServiceCall).Callee, call.String(), dbInstance.GetName())
				}
			}
		} else if targetMethod.ServiceCalls[lineno] != nil {
			call := targetMethod.ServiceCalls[lineno]
			logger.Logger.Warnf("[GRAPH - EDGES] appending edge of abstract service call %s with params %v", call.SimpleString(), call.Params)
			parentCall.AddChild(&AbstractServiceCall{
				ParsedCall: call,
				Caller:     utils.GetShortTypeStr(call.CallerTypeName),
				Callee:     utils.GetShortTypeStr(call.CalleeTypeName),
				Params:     call.Params,
				Call:       call.SimpleString(),
				Method:     call.Method.String(),
			})
		}
	}
}
