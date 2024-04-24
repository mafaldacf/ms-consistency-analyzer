package graph

import (
	"encoding/json"
	"fmt"
	"go/token"
	"os"
	"sort"
	"static_analyzer/models"
	"static_analyzer/logger"
)

type AbstractNode struct {
	// representation of the node (e.g. storageService.StorePost)
	Repr 			string 					`json:"repr"`
	CallerParams    []*models.Variable 		`json:"caller_params"`
	CalleeParams    []*models.Variable 		`json:"-"`
	NodeType 		models.NodeKind 		`json:"kind"` 		// omit from json
	ParsedCall 		*models.ParsedCallExpr 	`json:"-"` 			// omit from json
	ParsedFuncDecl 	*models.ParsedFuncDecl 	`json:"-"` 			// omit from json
	Children 		[]*AbstractNode 		`json:"children"`
}

type AbstractGraph struct {
	Nodes 			[]*AbstractNode
	AppServiceNodes map[string]*models.ServiceNode
}

func Build(serviceNode *models.ServiceNode, targetMethodName string, appServiceNodes map[string]*models.ServiceNode) *AbstractGraph {
	abstractGraph := AbstractGraph{
		Nodes: 				make([]*AbstractNode, 0),
		AppServiceNodes: 	appServiceNodes,
	}
	abstractGraph.startBuild(&abstractGraph, serviceNode, targetMethodName)
	return &abstractGraph
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
		NodeType: models.KIND_ROOT,
		Repr:     fmt.Sprintf("%s.%s", serviceNode.Name, targetMethodName),
	})

	for _, lineno := range linenos {
		if targetMethod.DatabaseCalls[lineno] != nil {
			dbCall := targetMethod.DatabaseCalls[lineno]
			repr := fmt.Sprintf("%s.%s", dbCall.Type, dbCall.MethodName)
			abstractGraph.Nodes[0].Children = append(abstractGraph.Nodes[0].Children, &AbstractNode{
				ParsedCall:   dbCall,
				CallerParams: dbCall.Deps,
				NodeType:     models.KIND_DATABASE_CALL,
				Repr:         repr,
			})
		} else if targetMethod.ServiceCalls[lineno] != nil {
			svcCall := targetMethod.ServiceCalls[lineno]
			//svcFuncDecl := allServiceNodes[svcCall.Type].ParsedCFGs[svcCall.MethodName].Vars
			repr := fmt.Sprintf("%s.%s", svcCall.Type, svcCall.MethodName)
			abstractGraph.Nodes[0].Children = append(abstractGraph.Nodes[0].Children, &AbstractNode{
				ParsedCall:   svcCall,
				CallerParams: svcCall.Deps,
				//CalleeParams: 	svcFuncDecl,
				NodeType: models.KIND_SERVICE_CALL,
				Repr:     repr,
			})
		}
	}
	ag.recurseBuild(abstractGraph.Nodes[0])
}

func (ag *AbstractGraph) recurseBuild(parentNode *AbstractNode) {
	for _, node := range parentNode.Children {
		// we need to unfold the service blocks from each service call
		if node.NodeType == models.KIND_SERVICE_CALL {
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
					repr := fmt.Sprintf("%s.%s", dbCall.Type, dbCall.MethodName)
					node.Children = append(node.Children, &AbstractNode{
						ParsedCall:   dbCall,
						CallerParams: dbCall.Deps,
						NodeType:     models.KIND_DATABASE_CALL,
						Repr:         repr,
					})
				} else if targetMethod.ServiceCalls[lineno] != nil {
					svcCall := targetMethod.ServiceCalls[lineno]
					repr := fmt.Sprintf("%s.%s", svcCall.Type, svcCall.MethodName)
					node.Children = append(node.Children, &AbstractNode{
						ParsedCall:   svcCall,
						CallerParams: svcCall.Deps,
						NodeType:     models.KIND_SERVICE_CALL,
						Repr:         repr,
					})
				}
			}
			ag.recurseBuild(node)
		}
	}
}
