package parser

import (
)

type NodeType int

const (
	DATABASE_CALL NodeType = iota
	SERVICE_CALL
)

type AbstractNode struct {
	ParsedCall 		*ParsedCallExpr
	ParsedFuncDecl 	*ParsedFuncDecl
	NodeType 		NodeType
	Children 		[]*AbstractNode
}

type AbstractGraph struct {
	Nodes []*AbstractNode
}
