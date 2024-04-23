package parser

import (
	"fmt"
	"go/ast"
	"reflect"

	"golang.org/x/tools/go/cfg"
)

type cfgVar struct {
	lineno 			int32
	astAssignStmt 	*ast.AssignStmt
}

type Block struct {
	cfgBlock *cfg.Block
	in 	map[string]bool
	out map[string]bool
	use map[string]bool
	def map[string]bool
}

type CFG struct {
	blocks []*cfg.Block
}

var visited = make(map[int32]bool)

func VisitBasicBlock(block *cfg.Block, serviceNode *ServiceNode) {
	if !visited[block.Index] {
		visited[block.Index] = true
	} else {
		return
	}
	fmt.Println("+ in block", block, "with nodes", block.Nodes)

	for _, node := range block.Nodes {
		isFuncCall(node, serviceNode)
	}


	for _, child := range block.Succs {
		fmt.Println("in child of block", block, ":", child)
		VisitBasicBlock(child, serviceNode)
	}
	fmt.Println("- out block", block)
	fmt.Println()
}

func isFuncCall(node ast.Node, serviceNode *ServiceNode) {
    nodeType := reflect.TypeOf(node).Elem().Name()
    fmt.Printf("Type of node is %s\n", nodeType)

	if expr, ok := node.(*ast.ExprStmt); ok {
		if _, ok := expr.X.(*ast.CallExpr); ok {
			fmt.Println("IS FUNC CALL")
		}
	}
}
