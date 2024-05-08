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
	"strings"
)

type AbstractNode interface {
	GetParams() 	[]*types.Variable
	String() 		string
	GetChildren() 	[]AbstractNode
	AddChild(AbstractNode)
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

type AbstractDatabaseCall struct {
	AbstractNode 						 `json:"-"`              	// omit from json
	Visited      bool     			     `json:"-"` 				// omit from json
	Call         string                  `json:"call,omitempty"`
	Method       string                  `json:"method,omitempty"`
	Caller       string                  `json:"caller,omitempty"`
	Params       []*types.Variable       `json:"params,omitempty"`
	ParsedCall   *service.ParsedCallExpr `json:"-"` 				// omit from json
	Parent       AbstractNode            `json:"-"` 				// omit from json
	Children 	 []AbstractNode  `json:"handlers,omitempty"`
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

type AbstractGraph struct {
	Nodes           []AbstractNode
	AppServiceNodes map[string]*service.ServiceNode

	// helpers
	globalIdx        int64
	visitedNodes     map[AbstractNode]bool
	nodesBlockParams map[AbstractNode][]*types.Variable
}

func Build(app *app.App, entryPoints []string) *AbstractGraph {
	abstractGraph := AbstractGraph{
		Nodes:           make([]AbstractNode, 0),
		AppServiceNodes: app.Services,
	}

	//FIXME: this is hardcoded but the graph can have several root nodes with several (root) target methods
	for _, serviceName := range entryPoints {
		service := app.Services[serviceName]
		for _, method := range service.ExposedMethods {
			abstractGraph.initBuild(app, app.Services[serviceName], method)
			abstractGraph.matchIdentifiers()
		}
	}
	return &abstractGraph
}

// matchIdentifiers uses DFS search
func (ag *AbstractGraph) matchIdentifiers() {
	// cannot be 0 otherwise because default value in
	// variable id parameter is 0 when not previously set
	ag.globalIdx = 1
	ag.visitedNodes = make(map[AbstractNode]bool, 0)
	ag.nodesBlockParams = make(map[AbstractNode][]*types.Variable, 0)

	for _, abstractEntry := range ag.Nodes {
		ag.matchIdentifiersHelper(abstractEntry)
	}
}

func (ag *AbstractGraph) matchIdentifiersHelper(node AbstractNode) {
	// REMINDER: is it really necessary that we only have one node?
	// should these always be the entry nodes????
	for callerParamIdx, callerParam := range node.GetParams() {
		logger.Logger.Debugf("> caller %s for param %s", node.String(), callerParam.Name)
		// assign id if not yet assigned (act as root variable for other child dependencies)
		if callerParam.Id == -1 {
			logger.Logger.Debugf("(1/2) assigning id %d to caller param %s", ag.globalIdx, callerParam.Name)
			callerParam.Id = ag.globalIdx
			ag.globalIdx++
		}

		// iterate every child and if not yet visited then we extract
		// all the variables (even from the dependencies) that correspond to
		// a parameter of the block i.e. the (remote) method parameter
		// FIXME: FOR NOW BECAUSE WE ONLY SUPPORT 1 BLOCK PER REMOTE METHOD
		if abstractService, ok := node.(*AbstractServiceCall); ok {
			for _, childNode := range abstractService.Children {
				if !ag.visitedNodes[childNode] {
					// get all dependencies recursively within children
					// (i think it is safe to have duplicates)
					var deps []*types.Variable
					for _, param := range childNode.GetParams() {
						deps = append(deps, getAllVariableDeps(param)...)
					}

					// block params is a subset of deps when a variable originates from
					// the block parameter i.e. the (remote) method parameter
					// FIXME: FOR NOW BECAUSE WE ONLY SUPPORT 1 BLOCK PER REMOTE METHOD
					for _, dep := range deps {
						if dep.IsBlockParam {
							ag.nodesBlockParams[childNode] = append(ag.nodesBlockParams[childNode], dep)
						} else if dep.Id == -1 {
							logger.Logger.Debugf("(2/2) assigning id %d to dep param %s", ag.globalIdx, dep.Name)
							callerParam.Id = ag.globalIdx
							ag.globalIdx++
						}
					}
					ag.visitedNodes[childNode] = true
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
			ag.matchIdentifiersHelper(childNode)
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
	ag.addAndBuildEntry(app, serviceNode, targetMethod)
	for _, abstractEntry := range ag.Nodes {
		if abstractServiceEntry, ok := abstractEntry.(*AbstractServiceCall); ok { // sanity check
			ag.recurseBuild(app, abstractServiceEntry)
		}
	}
}

func (ag *AbstractGraph) appendQueuePopCalls(app *app.App, abstractPushCalls []*AbstractDatabaseCall) []*AbstractDatabaseCall {
	var queueHandlers []*AbstractDatabaseCall
	for _, pushCall := range abstractPushCalls {
		queueInstance := pushCall.DbInstance
		for _, serviceNode := range app.Services {
			// found service node in app that uses this queue
			if _, ok := serviceNode.Databases[queueInstance.GetName()]; ok {
				// check if it implements the pop worker
				for _, queueHandler := range serviceNode.QueueHandlerMethods {
					if slices.Contains(queueHandler.DbInstances, queueInstance) {
						logger.Logger.Warnf("[GRAPH] found worker %s on instance '%s'", queueHandler.String(), queueInstance.GetName())
						queueHandler := &AbstractDatabaseCall{
							ParsedCall: &service.ParsedCallExpr{
								TargetField: serviceNode.Name,
								Name:        queueHandler.Name,
							},
							Caller: 	"Client",
							Method: 	queueHandler.String(),
							DbInstance: pushCall.DbInstance,
						}
						pushCall.Children = append(pushCall.Children, queueHandler)
						queueHandlers = append(queueHandlers, queueHandler)
					}
				}
			}
		}
	}
	return queueHandlers
}

func (ag *AbstractGraph) addAndBuildEntry(app *app.App, serviceNode *service.ServiceNode, targetMethod *service.ParsedFuncDecl) {
	// add entry node to graph
	entryAbstractServiceCall := &AbstractServiceCall{
		ParsedCall: &service.ParsedCallExpr{
			TargetField: serviceNode.Name,
			Name:        targetMethod.Name,
		},
		Caller: "Client",
		Callee: serviceNode.Name,
		Method: targetMethod.String(),
	}
	ag.Nodes = append(ag.Nodes, entryAbstractServiceCall)
	// build entry node
	entryMethod := serviceNode.ExposedMethods[targetMethod.Name]
	for _, p := range entryMethod.Params {
		entryAbstractServiceCall.Params = append(entryAbstractServiceCall.Params, &types.Variable{
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
	entryAbstractServiceCall.Visited = true
	ag.appendAbstractEdges(app, entryAbstractServiceCall, targetMethod)
}

func (ag *AbstractGraph) recurseBuild(app *app.App, abstractNode AbstractNode) {
	for _, node := range abstractNode.GetChildren() {
		// we need to unfold the service blocks from each service call
		if abstractService, ok := node.(*AbstractServiceCall); ok && !abstractService.Visited {
			serviceNode := ag.AppServiceNodes[utils.GetShortTypeStr(abstractService.ParsedCall.CalleeTypeName)]
			methodName := abstractService.ParsedCall.Name
			targetMethod := serviceNode.ExposedMethods[methodName]
			abstractService.Visited = true

			ag.appendAbstractEdges(app, abstractService, targetMethod)
			ag.recurseBuild(app, abstractService)
		}
		if abstractDatabase, ok := node.(*AbstractDatabaseCall); ok && !abstractDatabase.Visited {
			/* ag.appendAbstractEdges(app, abstractDatabase, targetMethod) */
			abstractDatabase.Visited = true
			ag.recurseBuild(app, abstractDatabase)
		}
	}
}

func (ag *AbstractGraph) appendAbstractEdges(app *app.App, abstractCall AbstractNode, targetMethod *service.ParsedFuncDecl) {
	var abstractPushCalls []*AbstractDatabaseCall
	linenos := getMethodCallsLinenosByOrder(targetMethod)
	for _, lineno := range linenos {
		if targetMethod.DatabaseCalls[lineno] != nil {
			dbCall := targetMethod.DatabaseCalls[lineno]
			abstractDbCall := &AbstractDatabaseCall{
				ParsedCall: dbCall,
				Params:     dbCall.Params,
				Call:       dbCall.SimpleString(),
				Caller:     strings.Split(dbCall.CallerTypeName.String(), ".")[1],
				Method:     dbCall.Method.String(),
				DbInstance: dbCall.DbInstance,
			}
			abstractCall.AddChild(abstractDbCall)
			if dbInstance := dbCall.GetTargetedDatabaseInstance(); dbInstance != nil && dbInstance.IsQueue() {
				if method, ok := dbCall.Method.(*frameworks.BlueprintBackend); ok && method.IsWrite() {
					abstractPushCalls = append(abstractPushCalls, abstractDbCall)
					logger.Logger.Warnf("[GRAPH] found queue push call in %s: %s on instance '%s'", abstractCall.(*AbstractServiceCall).Callee, dbCall.String(), dbInstance.GetName())
				}
			}
		} else if targetMethod.ServiceCalls[lineno] != nil {
			svcCall := targetMethod.ServiceCalls[lineno]
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
	ag.appendQueuePopCalls(app, abstractPushCalls)
}
