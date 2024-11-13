package types

import (
	"go/ast"

	"golang.org/x/tools/go/cfg"
)

type ControlFlow struct {
	cfg    *cfg.CFG
	blocks []*Block
}

func NewControlFlow(blockStmt *ast.BlockStmt) *ControlFlow {
	cfg := cfg.New(blockStmt, mayReturn)
	var blocks []*Block

	for i, block := range cfg.Blocks {
		blocks = append(blocks, NewBlock(block, i))
	}

	for _, block := range blocks {
		for _, succ := range block.Block().Succs {
			block.AddSuccessor(blocks[succ.Index])
		}
	}

	return &ControlFlow{
		blocks: blocks,
		cfg:    cfg,
	}
}

func mayReturn(call *ast.CallExpr) bool {
	switch fun := call.Fun.(type) {
	case *ast.Ident:
		return fun.Name != "panic"
	case *ast.SelectorExpr:
		return fun.Sel.Name != "Fatal"
	}
	return true
}

func (cfg *ControlFlow) Cfg() *cfg.CFG {
	return cfg.cfg
}

func (cfg *ControlFlow) Blocks() []*Block {
	return cfg.blocks
}

func (cfg *ControlFlow) EntryBlock() *Block {
	return cfg.blocks[0]
}

func (cfg *ControlFlow) BlockAt(index int) *Block {
	return cfg.blocks[index]
}
