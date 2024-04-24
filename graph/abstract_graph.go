package graph

import (
	"encoding/json"
	"fmt"
	"go/token"
	"os"
	"sort"
	"static_analyzer/logger"
	"static_analyzer/models"
	"strings"
)

type AbstractNode struct {
	// representation of the node (e.g. storageService.StorePost)
	Repr           string                 `json:"repr"`
	CallerParams   []*models.Variable     `json:"caller_params,omitempty"`
	CalleeParams   []*models.Variable     `json:"-"` // omit from json
	Kind           models.NodeKind        `json:"-"` // omit from json
	ParsedCall     *models.ParsedCallExpr `json:"-"` // omit from json
	ParsedFuncDecl *models.ParsedFuncDecl `json:"-"` // omit from json
	// nodes representing database calls cannot contain children as well
	Children       []*AbstractNode        `json:"children,omitempty"` // omit from json
}

type AbstractGraph struct {
	Nodes           []*AbstractNode
	AppServiceNodes map[string]*models.ServiceNode

	// helpers
	globalIdx 			int64
	visitedNodes 		map[*AbstractNode]bool
	nodesBlockParams 	map[*AbstractNode][]*models.Variable
}

func Build(serviceNode *models.ServiceNode, targetMethodName string, appServiceNodes map[string]*models.ServiceNode) *AbstractGraph {
	abstractGraph := AbstractGraph{
		Nodes:           make([]*AbstractNode, 0),
		AppServiceNodes: appServiceNodes,
	}
	abstractGraph.startBuild(&abstractGraph, serviceNode, targetMethodName)
	abstractGraph.MatchVarsIdentifiers()
	return &abstractGraph
}

// MatchVarsIdentifiers uses DFS search

// FIXME: do for multiple levels of children
func (ag *AbstractGraph) MatchVarsIdentifiers() {
	// cannot be 0 otherwise because default value in
	// variable id parameter is 0 when not previously set
	ag.globalIdx = 0
	ag.visitedNodes = make(map[*AbstractNode]bool, 0)
	ag.nodesBlockParams = make(map[*AbstractNode][]*models.Variable, 0)

	//FIXME: root node (e.g. UploadPost) must have callerParam args aswell
	ag.matchVarsIdentifiersHelper(ag.Nodes[0])
}

func (ag *AbstractGraph) matchVarsIdentifiersHelper(node *AbstractNode) {
	// REMINDER: is it really necessary that we only have one node?
	// should these always be the entry nodes????
	for callerParamIdx, callerParam := range node.CallerParams {
		logger.Logger.Debugf("> caller %s", node.Repr)
		// assign id if not yet assigned (act as root variable for other child dependencies)
		if callerParam.Id == -1 {
			logger.Logger.Debug("assigning id ", ag.globalIdx, " to caller param ", callerParam.Name, " :", callerParam.Lineno)
			callerParam.Id = ag.globalIdx
			ag.globalIdx++
		}

		// iterate every child and if not yet visited then we extract
		// all the variables (even from the dependencies) that correspond to
		// a parameter of the block i.e. the (remote) method parameter
		// FIXME: FOR NOW BECAUSE WE ONLY SUPPORT 1 BLOCK PER REMOTE METHOD
		for _, childNode := range node.Children {
			logger.Logger.Debug("visiting child node ", childNode.Repr)
			if !ag.visitedNodes[childNode] {
				// get all dependencies recursively within children
				// (i think it is safe to have duplicates)
				var deps []*models.Variable
				for _, param := range childNode.CallerParams {
					deps = append(deps, getAllCallerParamDeps(param)...)
				}

				// block params is a subset of deps when a variable originates from
				// the block parameter i.e. the (remote) method parameter
				// FIXME: FOR NOW BECAUSE WE ONLY SUPPORT 1 BLOCK PER REMOTE METHOD
				for _, dep := range deps {
					if dep.IsBlockParam {
						ag.nodesBlockParams[childNode] = append(ag.nodesBlockParams[childNode], dep)
					} else if dep.Id == -1 {
						logger.Logger.Debug("assigning id ", ag.globalIdx, " to dep param ", callerParam.Name, " :", callerParam.Lineno)
						callerParam.Id = ag.globalIdx
						ag.globalIdx++
					}
				}
				ag.visitedNodes[childNode] = true
			}
			// match the child parameter id to the caller parameter id
			// if they correspond to the same index in the func call and func definition, resp.
			for _, childParam := range ag.nodesBlockParams[childNode] {
				logger.Logger.Debugf("\t matching child (idx=%d) param %s:%d with caller (idx=%d) param %s:%d", childParam.BlockParamIdx, childParam.Name, childParam.Lineno, callerParamIdx+1, callerParam.Name, callerParam.Lineno)
				if childParam.BlockParamIdx == callerParamIdx + 1 &&
					// ^ sanity check (-1 is when it was not yet set)
					childParam.Id == -1 {

					childParam.Id = callerParam.Id
					// add reference
					//TODO: add more stuff later
					childParam.Ref = &models.Ref{
						Name: 		callerParam.Name,
						Id: 		callerParam.Id,
						Parent: 	strings.Split(node.Repr, ".")[0], //CAUTION, this is hard coded
						Variable: 	callerParam,
					}
				}
			}
			logger.Logger.Debug()
		}
		logger.Logger.Debug()
	}
	for _, childNode := range node.Children {
		ag.matchVarsIdentifiersHelper(childNode)
	}
}

func getAllCallerParamDeps(v *models.Variable) []*models.Variable {
	var deps []*models.Variable
	for _, d := range v.Deps {
		deps = append(deps, getAllCallerParamDeps(d)...)
	}
	return append(deps, v)
}

func (ag *AbstractGraph) Save() {
	// print in JSON format
	// https://omute.net/editor
	file, err := os.Create("abstract_graph.json")
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
		//fmt.Println(string(data))
	}
}

func (ag *AbstractGraph) startBuild(abstractGraph *AbstractGraph, serviceNode *models.ServiceNode, targetMethodName string) {
	targetMethod := serviceNode.Methods[targetMethodName]

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

	abstractGraph.Nodes = append(abstractGraph.Nodes, &AbstractNode{
		Kind: models.KIND_ROOT,
		Repr: fmt.Sprintf("%s.%s", serviceNode.Name, targetMethodName),
	})

	for _, lineno := range linenos {
		if targetMethod.DatabaseCalls[lineno] != nil {
			dbCall := targetMethod.DatabaseCalls[lineno]
			repr := fmt.Sprintf("%s.%s (", dbCall.Type, dbCall.MethodName)
			for _, param := range dbCall.Deps {
				repr = repr + fmt.Sprintf("%s, ", param.Name)
			}
			repr = repr + ")"
			abstractGraph.Nodes[0].Children = append(abstractGraph.Nodes[0].Children, &AbstractNode{
				ParsedCall:   dbCall,
				CallerParams: dbCall.Deps,
				Kind:         models.KIND_DATABASE_CALL,
				Repr:         repr,
			})
		} else if targetMethod.ServiceCalls[lineno] != nil {
			svcCall := targetMethod.ServiceCalls[lineno]
			repr := fmt.Sprintf("%s.%s (", svcCall.Type, svcCall.MethodName)
			for _, param := range svcCall.Deps {
				repr = repr + fmt.Sprintf("%s, ", param.Name)
			}
			repr = repr + ")"
			abstractGraph.Nodes[0].Children = append(abstractGraph.Nodes[0].Children, &AbstractNode{
				ParsedCall:   svcCall,
				CallerParams: svcCall.Deps,
				//CalleeParams: 	svcFuncDecl,
				Kind: models.KIND_SERVICE_CALL,
				Repr: repr,
			})
		}
	}
	// FIXME: is it really necessary that we only have one node?
	// should these always be the entry nodes?
	ag.recurseBuild(abstractGraph.Nodes[0])
}

func (ag *AbstractGraph) recurseBuild(parentNode *AbstractNode) {
	for _, node := range parentNode.Children {
		// we need to unfold the service blocks from each service call
		if node.Kind == models.KIND_SERVICE_CALL {
			serviceNode := ag.AppServiceNodes[node.ParsedCall.Type]
			methodName := node.ParsedCall.MethodName
			targetMethod := serviceNode.Methods[methodName]

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
					repr := fmt.Sprintf("%s.%s (", dbCall.Type, dbCall.MethodName)
					for _, param := range dbCall.Deps {
						repr = repr + fmt.Sprintf("%s, ", param.Name)
					}
					repr = repr + ")"
					node.Children = append(node.Children, &AbstractNode{
						ParsedCall:   dbCall,
						CallerParams: dbCall.Deps,
						Kind:         models.KIND_DATABASE_CALL,
						Repr:         repr,
					})
				} else if targetMethod.ServiceCalls[lineno] != nil {
					svcCall := targetMethod.ServiceCalls[lineno]
					repr := fmt.Sprintf("%s.%s (", svcCall.Type, svcCall.MethodName)
					for _, param := range svcCall.Deps {
						repr = repr + fmt.Sprintf("%s, ", param.Name)
					}
					repr = repr + ")"
					node.Children = append(node.Children, &AbstractNode{
						ParsedCall:   svcCall,
						CallerParams: svcCall.Deps,
						Kind:         models.KIND_SERVICE_CALL,
						Repr:         repr,
					})
				}
			}
			ag.recurseBuild(node)
		}
	}
}
