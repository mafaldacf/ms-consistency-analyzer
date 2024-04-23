package parser

import (
)

type AbstractNode struct {
	// representation of the node (e.g. storageService.StorePost)
	Repr 			string 				`json:"repr"`
	CallerParams    []*Variable 		`json:"caller_params"`
	CalleeParams    []*Variable 		`json:"-"`
	NodeType 		NodeKind 			`json:"kind"` 		// omit from json
	ParsedCall 		*ParsedCallExpr 	`json:"-"` 			// omit from json
	ParsedFuncDecl 	*ParsedFuncDecl 	`json:"-"` 			// omit from json
	Children 		[]*AbstractNode 	`json:"children"`
}

type AbstractGraph struct {
	Nodes []*AbstractNode
}
