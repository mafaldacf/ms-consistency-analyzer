package types

import (
	"fmt"
	"go/ast"
	"go/token"

	"golang.org/x/tools/go/cfg"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

type Block struct {
	Block *cfg.Block
	// blocks can contain inline go routines
	Vars []variables.Variable
	Info *BlockInfo
}

func (block *Block) VarsString() string {
	s := "variables = ["
	for i, v := range block.Vars {
		s += v.String()
		if i < len(block.Vars) - 1 {
			s += ", "
		}

	}
	return s + "]"
}

func (block *Block) GetVariableAt(index int) variables.Variable {
	if index >= len(block.Vars) {
		logger.Logger.Fatalf("[BLOCK] received index (%d) but block vars (%s) is length (%d)", index, block.String(), len(block.Vars))
	}
	return block.Vars[index]
}

func (block *Block) LongString() string {
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

type BlockInfo struct {
	Gen []variables.Variable
	In  []variables.Variable
	Out []variables.Variable
}

func (block *Block) GetVariables() []variables.Variable {
	return block.Vars
}

func (block *Block) GetFirstVariable() variables.Variable {
	if len(block.Vars) == 0 {
		logger.Logger.Fatalf("[BLOCKS] unexpected empty CFG block (%v)", block)
	}
	return block.Vars[0]
}

func (block *Block) IsReceiverVariable(v variables.Variable) bool {
	if len(block.Vars) > 0 {
		return block.Vars[0] == v
	}
	return false
}

func (block *Block) GetLastestVariable(name string) variables.Variable {
	for i := len(block.Vars) - 1; i >= 0; i-- {
		v := block.Vars[i]
		if name == v.GetVariableInfo().GetName() {
			return v
		}
	}
	logger.Logger.Fatalf("[BLOCK] variable (%s) not found in block: %s)", name, block.VarsString())
	return nil
}

func (block *Block) GetLastestVariableIfExists(name string) variables.Variable {
	for i := len(block.Vars) - 1; i >= 0; i-- {
		v := block.Vars[i]
		if name == v.GetVariableInfo().GetName() {
			return v
		}
	}
	return nil
}

func (block *Block) AddVariables(variables []variables.Variable) {
	logger.Logger.Tracef("[BLOCK] added variables to block: %s", variables)
	block.Vars = append(block.Vars, variables...)
}

func (block *Block) AddVariable(variable variables.Variable) {
	if variable.GetVariableInfo().Id == variables.VARIABLE_INLINE_ID {
		logger.Logger.Warnf("[BLOCK] skipping addition of new inline variable (%s) to block", variable.String())
		return
	}

	/* if len(block.Vars) == 0 || block.Vars[len(block.Vars)-1] != variable {
		logger.Logger.Tracef("[BLOCK] added %s (%s) to block", variable.String(), utils.GetType(variable))
		block.Vars = append(block.Vars, variable)
	} else {
		lst := ""
		for _, v := range block.Vars {
			lst += fmt.Sprintf("\t\t\t - %s\n", v.String())
		}
		logger.Logger.Fatalf("[BLOCK] %s (%s) already exists in block with vars list:\n%s", variable.String(), utils.GetType(variable), lst)
	} */

	logger.Logger.Debugf("[BLOCK] added %s (%s) to block", variable.String(), utils.GetType(variable))
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
	logger.Logger.Tracef("[BLOCK] copying vars %d -> %d: %v -> %v", predecessor.GetIndex(), block.GetIndex(), predecessor.Vars, block.Vars)
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
