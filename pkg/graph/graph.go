package graph

import (
	"analyzer/pkg/abstree"
	"analyzer/pkg/app"
	log "analyzer/pkg/logger"
	"analyzer/pkg/models"
	"encoding/json"
	"fmt"
	"go/token"
	"os"
	"sort"
)

type AbstractNode interface {
	GetCallerParams() []*models.Variable
	String() string
}

type AbstractServiceCall struct {
	AbstractNode `json:"-"` // omit from json
	Repr         string     `json:"repr,omitempty"`
	// name of the service calling e.g. StorageService
	Caller       string                  `json:"caller,omitempty"`
	CallerParams []*models.Variable      `json:"caller_params,omitempty"`
	ParsedCall   *abstree.ParsedCallExpr `json:"-"` // omit from json
	// nodes representing database calls cannot contain children as well
	Children []AbstractNode `json:"children,omitempty"` // omit from json
}

func (svc *AbstractServiceCall) GetCallerParams() []*models.Variable {
	return svc.CallerParams
}

func (svc *AbstractServiceCall) String() string {
	return svc.ParsedCall.SimpleString()
}

type AbstractDatabaseCall struct {
	AbstractNode `json:"-"`              // omit from json
	Repr         string                  `json:"repr"`
	CallerParams []*models.Variable      `json:"caller_params,omitempty"`
	ParsedCall   *abstree.ParsedCallExpr `json:"-"` // omit from json
}

func (db *AbstractDatabaseCall) GetCallerParams() []*models.Variable {
	return db.CallerParams
}

func (db *AbstractDatabaseCall) String() string {
	return db.ParsedCall.SimpleString()
}

type AbstractGraph struct {
	Nodes           []AbstractNode
	AppServiceNodes map[string]*abstree.ServiceNode

	// helpers
	globalIdx        int64
	visitedNodes     map[AbstractNode]bool
	nodesBlockParams map[AbstractNode][]*models.Variable
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
	ag.globalIdx = 0
	ag.visitedNodes = make(map[AbstractNode]bool, 0)
	ag.nodesBlockParams = make(map[AbstractNode][]*models.Variable, 0)

	//FIXME: root node (e.g. UploadPost) must have callerParam args aswell
	ag.matchVarsIdentifiersHelper(ag.Nodes[0])
}

func (ag *AbstractGraph) matchVarsIdentifiersHelper(node AbstractNode) {
	// REMINDER: is it really necessary that we only have one node?
	// should these always be the entry nodes????
	for callerParamIdx, callerParam := range node.GetCallerParams() {
		log.Logger.Debugf("> caller %s", node.String())
		// assign id if not yet assigned (act as root variable for other child dependencies)
		if callerParam.Id == -1 {
			log.Logger.Debug("assigning id ", ag.globalIdx, " to caller param ", callerParam.Name, " :", callerParam.Lineno)
			callerParam.Id = ag.globalIdx
			ag.globalIdx++
		}

		// iterate every child and if not yet visited then we extract
		// all the variables (even from the dependencies) that correspond to
		// a parameter of the block i.e. the (remote) method parameter
		// FIXME: FOR NOW BECAUSE WE ONLY SUPPORT 1 BLOCK PER REMOTE METHOD
		if abstractService, ok := node.(*AbstractServiceCall); ok {
			for _, childNode := range abstractService.Children {
				log.Logger.Debug("visiting child node ", childNode.String())
				if !ag.visitedNodes[childNode] {
					// get all dependencies recursively within children
					// (i think it is safe to have duplicates)
					var deps []*models.Variable
					for _, param := range childNode.GetCallerParams() {
						deps = append(deps, getAllCallerParamDeps(param)...)
					}

					// block params is a subset of deps when a variable originates from
					// the block parameter i.e. the (remote) method parameter
					// FIXME: FOR NOW BECAUSE WE ONLY SUPPORT 1 BLOCK PER REMOTE METHOD
					for _, dep := range deps {
						if dep.IsBlockParam {
							ag.nodesBlockParams[childNode] = append(ag.nodesBlockParams[childNode], dep)
						} else if dep.Id == -1 {
							log.Logger.Debug("assigning id ", ag.globalIdx, " to dep param ", callerParam.Name, " :", callerParam.Lineno)
							callerParam.Id = ag.globalIdx
							ag.globalIdx++
						}
					}
					ag.visitedNodes[childNode] = true
				}
				// match the child parameter id to the caller parameter id
				// if they correspond to the same index in the func call and func definition, resp.
				for _, childParam := range ag.nodesBlockParams[childNode] {
					log.Logger.Debugf("\t matching child (idx=%d) param %s:%d with caller (idx=%d) param %s:%d", childParam.BlockParamIdx, childParam.Name, childParam.Lineno, callerParamIdx+1, callerParam.Name, callerParam.Lineno)
					if childParam.BlockParamIdx == callerParamIdx+1 &&
						// ^ sanity check (-1 is when it was not yet set)
						childParam.Id == -1 {

						childParam.Id = callerParam.Id
						// add reference
						//TODO: add more stuff later
						childParam.Ref = &models.Ref{
							Name:     callerParam.Name,
							Id:       callerParam.Id,
							Origin:   abstractService.Caller,
							Variable: callerParam,
						}
					}
				}
				log.Logger.Debug()
			}
		}
		log.Logger.Debug()
	}
	if abstractService, ok := node.(*AbstractServiceCall); ok {
		for _, childNode := range abstractService.Children {
			ag.matchVarsIdentifiersHelper(childNode)
		}
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
	file, err := os.Create("assets/abstract_graph.json")
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()
	for _, node := range ag.Nodes {
		data, err := json.MarshalIndent(node, "", "  ")
		if err != nil {
			log.Logger.Error("error marshaling json:", err)
			return
		}
		file.Write(data)
		//fmt.Println(string(data))
	}
}

func (ag *AbstractGraph) startBuild(abstractGraph *AbstractGraph, serviceNode *abstree.ServiceNode, targetMethod *abstree.ParsedFuncDecl) {
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
		Repr: fmt.Sprintf("%s.%s", serviceNode.Name, targetMethod.Name),
	})

	if abstractService, ok := abstractGraph.Nodes[0].(*AbstractServiceCall); ok {
		for _, lineno := range linenos {
			if targetMethod.DatabaseCalls[lineno] != nil {
				dbCall := targetMethod.DatabaseCalls[lineno]
				abstractService.Children = append(abstractService.Children, &AbstractDatabaseCall{
					ParsedCall:   dbCall,
					CallerParams: dbCall.Deps,
					Repr:         dbCall.SimpleString(),
				})
			} else if targetMethod.ServiceCalls[lineno] != nil {
				svcCall := targetMethod.ServiceCalls[lineno]
				abstractService.Children = append(abstractService.Children, &AbstractServiceCall{
					ParsedCall:   svcCall,
					Caller:       svcCall.SrcType,
					CallerParams: svcCall.Deps,
					Repr:         svcCall.SimpleString(),
				})
			}
		}
		// FIXME: is it really necessary that we only have one node?
		// should these always be the entry nodes?
		ag.recurseBuild(abstractService)
	}
}

func (ag *AbstractGraph) recurseBuild(parentNode *AbstractServiceCall) {
	for _, node := range parentNode.Children {
		// we need to unfold the service blocks from each service call
		if abstractService, ok := node.(*AbstractServiceCall); ok {
			serviceNode := ag.AppServiceNodes[abstractService.ParsedCall.DestType]
			methodName := abstractService.ParsedCall.MethodName
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
						ParsedCall:   dbCall,
						CallerParams: dbCall.Deps,
						Repr:         dbCall.SimpleString(),
					})
				} else if targetMethod.ServiceCalls[lineno] != nil {
					svcCall := targetMethod.ServiceCalls[lineno]
					abstractService.Children = append(abstractService.Children, &AbstractServiceCall{
						ParsedCall:   svcCall,
						Caller:       svcCall.SrcType,
						CallerParams: svcCall.Deps,
						Repr:         svcCall.SimpleString(),
					})
				}
			}
			ag.recurseBuild(abstractService)
		}
	}
}
