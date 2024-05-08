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
	GetParams() 	[]*types.Variable
	String() 		string
	GetChildren() 	[]AbstractNode
	AddChild(AbstractNode)
	SetVisited(bool)
	IsVisited() bool
}

type AbstractServiceCall struct {
	AbstractNode 						`json:"-"` 					// omit from json
	Visited      bool     				`json:"-"` 					// omit from json
	Call         string     			`json:"call,omitempty"`
	Method       string     			`json:"method,omitempty"`

	Caller 		string 					`json:"caller,omitempty"`
	Callee 		string 					`json:"callee,omitempty"`

	Params     	[]*types.Variable       `json:"params,omitempty"`
	ParsedCall 	*service.ParsedCallExpr `json:"-"` 					// omit from json

	// nodes representing database calls cannot contain children as well
	Children 	[]AbstractNode 			`json:"edges,omitempty"`
	Parent   	AbstractNode  			`json:"-"`              	// omit from json
}

type AbstractQueueHandler struct {
	AbstractServiceCall 				  			`json:"handler"`
	DbInstance   			types.DatabaseInstance  `json:"db_instance"`
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

type AbstractDatabaseCall struct {
	AbstractNode 						 `json:"-"`              	// omit from json
	Visited      bool     			     `json:"-"` 				// omit from json
	Call         string                  `json:"call,omitempty"`
	Method       string                  `json:"method,omitempty"`
	Caller       string                  `json:"caller,omitempty"`
	Params       []*types.Variable       `json:"params,omitempty"`
	ParsedCall   *service.ParsedCallExpr `json:"-"` 				// omit from json
	Parent       AbstractNode            `json:"-"` 				// omit from json
	Children 	 []AbstractNode 		 `json:"queue_handlers,omitempty"`
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

type AbstractGraph struct {
	Nodes           []AbstractNode
	AppServiceNodes map[string]*service.ServiceNode

	// helpers
	globalIdx        int64
	nodesBlockParams map[AbstractNode][]*types.Variable
}

func Build(app *app.App, entryPoints []string) *AbstractGraph {
	ag := &AbstractGraph{
		Nodes:           make([]AbstractNode, 0),
		AppServiceNodes: app.Services,
	}
	for _, serviceName := range entryPoints {
		service := app.Services[serviceName]
		for _, method := range service.ExposedMethods {
			ag.initBuild(app, app.Services[serviceName], method)
		}
	}
	
	for _, node := range ag.Nodes {
		ag.cleanVisited(node)
	}
	ag.globalIdx = 1
	ag.nodesBlockParams = make(map[AbstractNode][]*types.Variable, 0)
	for _, abstractEntry := range ag.Nodes {
		ag.matchIdentifiers(abstractEntry)
	}
	return ag
}

func (ag *AbstractGraph) cleanVisited(node AbstractNode) {
	node.SetVisited(false)
	for _, edge := range node.GetChildren() {
		ag.cleanVisited(edge)
	}
}

func (ag *AbstractGraph) matchIdentifiers(node AbstractNode) {
	logger.Logger.Warnf("matching identifiers for node %s", node.String())
	for callerParamIdx, callerParam := range node.GetParams() {
		logger.Logger.Debugf("> caller %s for param %s", node.String(), callerParam.Name)
		// assign id if not yet assigned (act as root variable for other child dependencies)
		if callerParam.Id == -1 {
			logger.Logger.Debugf("(1/2) assigning id %d to caller param %s", ag.globalIdx, callerParam.Name)
			callerParam.Id = ag.globalIdx
			ag.globalIdx++
		}

		if abstractService, ok := node.(*AbstractServiceCall); ok {
			for _, childNode := range abstractService.Children {
				if !node.IsVisited() {
					// get all dependencies recursively within children
					// (i think it is safe to have duplicates)
					var deps []*types.Variable
					for _, param := range childNode.GetParams() {
						deps = append(deps, getAllVariableDeps(param)...)
					}

					// block params is a subset of deps when a variable originates from
					// the block parameter i.e. the (remote) method parameter
					for _, dep := range deps {
						if dep.IsBlockParam {
							ag.nodesBlockParams[childNode] = append(ag.nodesBlockParams[childNode], dep)
						} else if dep.Id == -1 {
							logger.Logger.Debugf("(2/2) assigning id %d to dep param %s", ag.globalIdx, dep.Name)
							callerParam.Id = ag.globalIdx
							ag.globalIdx++
						}
					}
					node.SetVisited(true)
				}
				// match the child parameter id to the caller parameter id
				// if they correspond to the same index in the func call and func definition, resp.
				for _, childParam := range ag.nodesBlockParams[childNode] {
					if childParam.BlockParamIdx == callerParamIdx &&
						// ^ sanity check (-1 is when it was not yet set)
						childParam.Id == -1 {

						logger.Logger.Debugf("\t matching child (%s) param '%s' with parent (%s) param '%s' for id %d", childNode.String(), childParam.Name, node.String(), callerParam.Name, callerParam.Id)

						childParam.Id = callerParam.Id
						// add reference
						//TODO: add more stuff later
						childParam.Ref = &types.Ref{
							Name:     callerParam.Name,
							Id:       callerParam.Id,
							Creator:  abstractService.Caller,
							Variable: callerParam,
						}
					}
					logger.Logger.Debug()
				}
				logger.Logger.Debug()
			}
		}
		logger.Logger.Debug()
	}
	if abstractService, ok := node.(*AbstractServiceCall); ok {
		for _, childNode := range abstractService.Children {
			ag.matchIdentifiers(childNode)
		}
	}
}

func getAllVariableDeps(v *types.Variable) []*types.Variable {
	var deps []*types.Variable
	for _, d := range v.Deps {
		deps = append(deps, getAllVariableDeps(d)...)
	}
	return append(deps, v)
}

func (ag *AbstractGraph) Save() {
	// print in JSON format
	// https://omute.net/editor
	file, err := os.Create("assets/abstractgraph.json")
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()
	for _, node := range ag.Nodes {
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

func (ag *AbstractGraph) initBuild(app *app.App, serviceNode *service.ServiceNode, targetMethod *service.ParsedFuncDecl) {
	ag.addEntry(serviceNode, targetMethod)
	for _, abstractEntry := range ag.Nodes {
		if abstractServiceEntry, ok := abstractEntry.(*AbstractServiceCall); ok { // sanity check
			ag.recurseBuild(app, abstractServiceEntry)
		}
	}
}

func createDummyAbstractServiceCall(node *service.ServiceNode, method *service.ParsedFuncDecl, caller string) AbstractServiceCall{
	call := AbstractServiceCall{
		ParsedCall: &service.ParsedCallExpr{
			TargetField: node.Name,
			Name:        method.Name,
			Method: 	 method,
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

func (ag *AbstractGraph) addEntry(node *service.ServiceNode, method *service.ParsedFuncDecl) {
	// add entry node to graph
	entryCall := createDummyAbstractServiceCall(node, method, "Client")
	ag.Nodes = append(ag.Nodes, &entryCall)
	// build entry node
	entryMethod := node.ExposedMethods[method.Name]
	for _, p := range entryMethod.Params {
		entryCall.Params = append(entryCall.Params, &types.Variable{
			Name: p.Name,
			Type: p.Type,
			Id:   -1,
			Ref: &types.Ref{
				Creator: "Client",
				Name:    p.Name,
				Id:      -1,
			},
		})
	}
}

func (ag *AbstractGraph) recurseBuild(app *app.App, abstractNode AbstractNode) {
	if abstractNode.IsVisited() {
		return
	}
	switch node := abstractNode.(type) {
		case *AbstractServiceCall:
			logger.Logger.Debugf("Doing recurse build on service call %s", node.String())
			targetMethod := ag.AppServiceNodes[node.Callee].ExposedMethods[node.ParsedCall.Name]
			ag.appendAbstractEdges(node, targetMethod)
		case *AbstractDatabaseCall:
			logger.Logger.Debugf("Doing recurse build on database call %s", node.String())
			if dbInstance := node.ParsedCall.GetTargetedDatabaseInstance(); dbInstance != nil && dbInstance.IsQueue() {
				if method, ok := node.ParsedCall.Method.(*frameworks.BlueprintBackend); ok && method.IsWrite() {
					queueHandlers := ag.findQueueHandlers(app, dbInstance, node)
					for _, handler := range queueHandlers {
						node.Children = append(node.Children, handler)
					}
				}
			}
		case *AbstractQueueHandler:
			logger.Logger.Debugf("Doing recurse build on queue handler %s", node.String())
			targetMethod := ag.AppServiceNodes[node.Callee].QueueHandlerMethods[node.ParsedCall.Name]
			ag.appendAbstractEdges(node, targetMethod)
		default:
			logger.Logger.Debugf("Error recursing build for %s", node)
			return
	}
	abstractNode.SetVisited(true)
	for _, edge := range abstractNode.GetChildren(){
		ag.recurseBuild(app, edge)
	}
}

func (ag *AbstractGraph) findQueueHandlers(app *app.App, instance types.DatabaseInstance, publisher *AbstractDatabaseCall) []*AbstractQueueHandler {
	var queueHandlers []*AbstractQueueHandler
	for _, node := range app.Services {
		if _, ok := node.Databases[instance.GetName()]; ok {
			if _, ok := node.Databases[instance.GetName()]; ok {
				for _, queueHandler := range node.QueueHandlerMethods {
					if slices.Contains(queueHandler.DbInstances, instance) {
						logger.Logger.Warnf("[GRAPH] found worker %s on instance '%s'", queueHandler.String(), instance.GetName())
						queueHandler := &AbstractQueueHandler{
							AbstractServiceCall: createDummyAbstractServiceCall(node, queueHandler, utils.GetShortTypeStr(publisher.ParsedCall.CallerTypeName),),
							DbInstance: instance,
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

func (ag *AbstractGraph) appendAbstractEdges(abstractCall AbstractNode, targetMethod *service.ParsedFuncDecl) {
	linenos := getMethodCallsLinenosByOrder(targetMethod)
	for _, lineno := range linenos {
		if targetMethod.DatabaseCalls[lineno] != nil {
			dbCall := targetMethod.DatabaseCalls[lineno]
			abstractDbCall := &AbstractDatabaseCall{
				ParsedCall: dbCall,
				Params:     dbCall.Params,
				Call:       dbCall.SimpleString(),
				Caller:     utils.GetShortTypeStr(dbCall.CallerTypeName),
				Method:     dbCall.Method.String(),
				DbInstance: dbCall.DbInstance,
			}
			abstractCall.AddChild(abstractDbCall)
			if dbInstance := dbCall.GetTargetedDatabaseInstance(); dbInstance != nil && dbInstance.IsQueue() {
				if method, ok := dbCall.Method.(*frameworks.BlueprintBackend); ok && method.IsWrite() {
					logger.Logger.Warnf("[GRAPH] found queue push call in %s: %s on instance '%s'", abstractCall.(*AbstractServiceCall).Callee, dbCall.String(), dbInstance.GetName())
				}
			}
		} else if targetMethod.ServiceCalls[lineno] != nil {
			svcCall := targetMethod.ServiceCalls[lineno]
			logger.Logger.Warnf("[GRAPH] appending edge of abstract service call %s", svcCall.SimpleString())
			abstractCall.AddChild(&AbstractServiceCall{
				ParsedCall: svcCall,
				Caller:     utils.GetShortTypeStr(svcCall.CallerTypeName),
				Callee:     utils.GetShortTypeStr(svcCall.CalleeTypeName),
				Params:     svcCall.Params,
				Call:       svcCall.SimpleString(),
				Method:     svcCall.Method.String(),
			})
		}
	}
}
