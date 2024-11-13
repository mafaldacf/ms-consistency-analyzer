package types

import (
	"go/ast"

	"golang.org/x/tools/go/cfg"

	"analyzer/pkg/types/objects"
)

type Block struct {
	block   *cfg.Block
	index   int
	succs   []*Block
	vars    []objects.Variable
	in      []objects.Variable // initial vars
	out     []objects.Variable // last vars
	visited bool
}

func NewBlock(block *cfg.Block, index int) *Block {
	return &Block{
		block: block,
		index: index,
	}
}

func (block *Block) Block() *cfg.Block {
	return block.block
}

func (block *Block) BlockIsBody() bool {
	return block.block.Kind == cfg.KindBody
}

func (block *Block) BlockIsIfThen() bool {
	return block.block.Kind == cfg.KindIfThen
}

func (block *Block) BlockNodes() []ast.Node {
	return block.block.Nodes
}

func (block *Block) Index() int {
	return block.index
}

func (block *Block) Visited() bool {
	return block.visited
}

func (block *Block) SetVisited() {
	block.visited = true
}

func (block *Block) ResetVisited() {
	block.visited = false
}

func (block *Block) Succs() []*Block {
	return block.succs
}

func (block *Block) SetVars(vars []objects.Variable) {
	// append because if we just assigned we would not be affecting the original block.vars and block.in
	block.vars = append(block.vars, vars...)
	block.in = append(block.vars, vars...)
}

func (block *Block) SetOut(vars []objects.Variable) {
	// append because if we just assigned we would not be affecting the original block.out
	block.out = append(block.out, vars...)
}

func (block *Block) In() []objects.Variable {
	return block.in
}

func (block *Block) Out() []objects.Variable {
	return block.out
}

func (block *Block) Vars() []objects.Variable {
	return block.vars
}

func (block *Block) AddSuccessor(next *Block) {
	block.succs = append(block.succs, next)
}
