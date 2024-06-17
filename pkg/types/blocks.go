package types

import (
	"fmt"
	"go/ast"
	"go/token"

	"golang.org/x/tools/go/cfg"

	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

type Block struct {
	Block *cfg.Block
	// blocks can contain inline go routines
	Vars []Variable
	Info *BlockInfo
}

func (block *Block) Yaml() []string {
	data := []string{}
	for _, v := range block.Vars {
		data = append(data, v.String())
	}
	return data
}

type BlockInfo struct {
	Gen []Variable
	In  []Variable
	Out []Variable
}

func (block *Block) GetVariables() []Variable {
	return block.Vars
}

func (block *Block) GetLastestVariable(name string) Variable {
	for i := len(block.Vars) - 1; i >= 0; i-- {
		v := block.Vars[i]
		if name == v.GetVariableInfo().GetName() {
			return v
		}
	}
	logger.Logger.Warnf("variable '%s' not found in declared block: %v", name, block.Vars)
	return nil
}

func (block *Block) AddVariables(variables []Variable) {
	logger.Logger.Warnf("added variables to block: %s", variables)
	block.Vars = append(block.Vars, variables...)
}

func (block *Block) AddVariable(variable Variable) {
	logger.Logger.Warnf("added %s to block: %s", utils.GetType(variable), variable.String())
	block.Vars = append(block.Vars, variable)
}

func (block *Block) GetPosition() token.Pos {
	return block.Block.Stmt.Pos()
}

func (block *Block) GetIndex() int32 {
	return block.Block.Index
}

func (block *Block) GetNodes() []ast.Node {
	return block.Block.Nodes
}

func (block *Block) GetSuccs() []*cfg.Block {
	return block.Block.Succs
}

func (block *Block) CopyVarsFromPredecessor(predecessor *Block) {
	logger.Logger.Debugf("copying vars %d -> %d: %v -> %v", predecessor.GetIndex(), block.GetIndex(), predecessor.Vars, block.Vars)
	block.Vars = append(predecessor.Vars, block.Vars...)
}

func (block *Block) String() string {
	str := fmt.Sprintf("Block %d [%s] (", block.Block.Index, block.Block.Kind)
	for i, v := range block.Vars {
		str += v.GetVariableInfo().GetName()
		if i < len(block.Vars)-1 {
			str += ", "
		}
	}
	str += ")"
	return str
}

func (block *Block) FullString() string {
	str := fmt.Sprintf("Block %d", block.Block.Index)
	for i, v := range block.Block.Nodes {
		str += fmt.Sprintf("\t Node %d: %s", i, utils.GetType(v))
	}
	for _, v := range block.Block.Succs {
		str += fmt.Sprintf("\t Succ: %d", v.Index)
	}
	str += "\n"
	return str
}
