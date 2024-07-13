package abstractgraph

import (
	"container/list"

	"analyzer/pkg/utils"
)

func (graph *AbstractGraph) Dump() {
	graph.dumpAbstractGraph()
	graph.dumpDiGraph()
}

func (graph *AbstractGraph) dumpAbstractGraph() {
	utils.DumpToJSONFile(graph.Nodes, graph.AppName, "abstractgraph")
}

func (graph *AbstractGraph) dumpDiGraph() {
	type node struct {
		Id   string `json:"id"`
		Type string `json:"type"`
	}
	type edge struct {
		Caller string `json:"caller"`
		Callee string `json:"callee"`
		Call   string `json:"call"`
	}
	type digraph struct {
		Nodes []node `json:"nodes"`
		Edges []edge `json:"edges"`
	}

	nodes := []node{}
	edges := []edge{}
	appendedServiceNodes := make(map[string]bool)

	var abstractNodesToVisit = list.New()
	var visitedAbstractNodes = make(map[AbstractNode]bool)

	for _, n := range graph.Nodes {
		abstractNodesToVisit.PushBack(n)
	}

	nodes = append(nodes, node{Id: "Client", Type: "client"})

	for abstractNodesToVisit.Len() > 0 {
		elem := abstractNodesToVisit.Front()
		n := elem.Value.(AbstractNode)
		abstractNodesToVisit.Remove(elem)

		if _, exists := visitedAbstractNodes[n]; !exists {
			caller := n.GetCallerStr()
			callee := n.GetCallee()
			call := n.GetName()

			if _, exists := appendedServiceNodes[callee]; !exists {
				nodes = append(nodes, node{Id: callee, Type: n.GetNodeType()})
				appendedServiceNodes[callee] = true
			}
			edges = append(edges, edge{Caller: caller, Callee: callee, Call: call})
			visitedAbstractNodes[n] = true

			for _, c := range n.GetChildren() {
				if _, visited := visitedAbstractNodes[c]; !visited {
					abstractNodesToVisit.PushBack(c)
				}
			}
		}
	}

	outputGraph := digraph{Nodes: nodes, Edges: edges}
	utils.DumpToJSONFile(outputGraph, graph.AppName, "digraphs/call_graph")
}
