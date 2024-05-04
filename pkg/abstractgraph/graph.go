package abstractgraph

import (
	"analyzer/pkg/app"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"encoding/json"
	"fmt"
	"go/token"
	"os"
	"sort"
	"strings"
)

type AbstractNode interface {
	GetParams() []*types.Variable
	String() string
}

type AbstractServiceCall struct {
	AbstractNode `json:"-"` // omit from json
	Call         string     `json:"call,omitempty"`
	Method       string     `json:"method,omitempty"`
	// name of the service calling e.g. StorageService
	Caller     string                  `json:"caller,omitempty"`
	Params     []*types.Variable       `json:"params,omitempty"`
	ParsedCall *service.ParsedCallExpr `json:"-"` // omit from json
	// nodes representing database calls cannot contain children as well
	Children []AbstractNode `json:"edges,omitempty"` // omit from json
	Parent   AbstractNode   `json:"-"`                  // omit from json
}

func (svc *AbstractServiceCall) GetParams() []*types.Variable {
	return svc.Params
}

func (svc *AbstractServiceCall) String() string {
	return svc.ParsedCall.SimpleString()
}

type AbstractDatabaseCall struct {
	AbstractNode `json:"-"`              // omit from json
	Call         string                  `json:"call,omitempty"`
	Method       string                  `json:"method,omitempty"`
	Params       []*types.Variable       `json:"params,omitempty"`
	ParsedCall   *service.ParsedCallExpr `json:"-"` // omit from json
	Parent       AbstractNode            `json:"-"` // omit from json
}

func (db *AbstractDatabaseCall) GetParams() []*types.Variable {
	return db.Params
}

func (db *AbstractDatabaseCall) String() string {
	return db.ParsedCall.SimpleString()
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
			abstractGraph.startBuild(&abstractGraph, app.Services[serviceName], method)
			abstractGraph.matchVarsIdentifiers()
		}
	}
	return &abstractGraph
}

// MatchVarsIdentifiers uses DFS search

// FIXME: do for multiple levels of children
func (ag *AbstractGraph) matchVarsIdentifiers() {
	// cannot be 0 otherwise because default value in
	// variable id parameter is 0 when not previously set
	ag.globalIdx = 1
	ag.visitedNodes = make(map[AbstractNode]bool, 0)
	ag.nodesBlockParams = make(map[AbstractNode][]*types.Variable, 0)

	//FIXME: root node (e.g. UploadPost) must have callerParam args aswell
	ag.matchVarsIdentifiersHelper(ag.Nodes[0])
}

func (ag *AbstractGraph) matchVarsIdentifiersHelper(node AbstractNode) {
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
			ag.matchVarsIdentifiersHelper(childNode)
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
	file, err := os.Create("assets/abstract_graph.json")
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

func (ag *AbstractGraph) startBuild(abstractGraph *AbstractGraph, serviceNode *service.ServiceNode, targetMethod *service.ParsedFuncDecl) {
	linenos := make([]token.Pos, 0, len(targetMethod.DatabaseCalls))
	for k := range targetMethod.DatabaseCalls {
		linenos = append(linenos, k)
	}
	for k := range targetMethod.ServiceCalls {
		linenos = append(linenos, k)
	}
	// order by lineno
	sort.Slice(linenos, func(i, j int) bool {
		return linenos[i] < linenos[j]
	})

	abstractGraph.Nodes = append(abstractGraph.Nodes, &AbstractServiceCall{
		ParsedCall: &service.ParsedCallExpr{
			TargetField: serviceNode.Name,
			Name:        targetMethod.Name,
		},
		Caller: "Client",
		Method: targetMethod.String(),
	})
	abstractService := abstractGraph.Nodes[0].(*AbstractServiceCall)

	//FIXME: this is hardcoded but should be automated later
	entryMethod := serviceNode.ExposedMethods[targetMethod.Name]
	for _, p := range entryMethod.Params {
		abstractService.Params = append(abstractService.Params, &types.Variable{
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

	for _, lineno := range linenos {
		if targetMethod.DatabaseCalls[lineno] != nil {
			dbCall := targetMethod.DatabaseCalls[lineno]
			abstractService.Children = append(abstractService.Children, &AbstractDatabaseCall{
				ParsedCall: dbCall,
				Params:     dbCall.Params,
				Call:       dbCall.SimpleString(),
				Method:     dbCall.Method.String(),
			})
		} else if targetMethod.ServiceCalls[lineno] != nil {
			svcCall := targetMethod.ServiceCalls[lineno]
			abstractService.Children = append(abstractService.Children, &AbstractServiceCall{
				ParsedCall: svcCall,
				Caller:     strings.Split(svcCall.SrcType.String(), ".")[1],
				Params:     svcCall.Params,
				Call:       svcCall.SimpleString(),
				Method:     svcCall.Method.String(),
			})
		}
	}

	// FIXME: is it really necessary that we only have one node?
	// should these always be the entry nodes?
	ag.recurseBuild(abstractService)
}

func (ag *AbstractGraph) recurseBuild(parentNode *AbstractServiceCall) {
	for _, node := range parentNode.Children {
		// we need to unfold the service blocks from each service call
		if abstractService, ok := node.(*AbstractServiceCall); ok {
			serviceNode := ag.AppServiceNodes[service.GetShortServiceTypeStr(abstractService.ParsedCall.DestType)]
			methodName := abstractService.ParsedCall.Name
			targetMethod := serviceNode.ExposedMethods[methodName]

			linenos := make([]token.Pos, 0, len(targetMethod.DatabaseCalls))

			for k := range targetMethod.DatabaseCalls {
				linenos = append(linenos, k)
			}
			for k := range targetMethod.ServiceCalls {
				linenos = append(linenos, k)
			}
			// order by lineno
			sort.Slice(linenos, func(i, j int) bool {
				return linenos[i] < linenos[j]
			})
			for _, lineno := range linenos {
				if targetMethod.DatabaseCalls[lineno] != nil {
					dbCall := targetMethod.DatabaseCalls[lineno]
					abstractService.Children = append(abstractService.Children, &AbstractDatabaseCall{
						ParsedCall: dbCall,
						Params:     dbCall.Params,
						Call:       dbCall.SimpleString(),
						Method:     dbCall.Method.String(),
						Parent:     abstractService,
					})
				} else if targetMethod.ServiceCalls[lineno] != nil {
					svcCall := targetMethod.ServiceCalls[lineno]
					abstractService.Children = append(abstractService.Children, &AbstractServiceCall{
						ParsedCall: svcCall,
						Caller:     strings.Split(svcCall.SrcType.String(), ".")[1],
						Params:     svcCall.Params,
						Call:       svcCall.SimpleString(),
						Method:     svcCall.Method.String(),
						Parent:     abstractService,
					})
				}
			}
			ag.recurseBuild(abstractService)
		}
	}
}
