package types

import (
	"fmt"
	"go/ast"
	"go/token"
	"slices"

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

func (block *Block) Yaml() []string {
	data := []string{}
	for _, v := range block.Vars {
		dfs := append(v.GetVariableInfo().Dataflows, v.GetVariableInfo().IndirectDataflows...)
		if len(dfs) > 0 {
			var dbs []string
			str := ""
			for _, df := range dfs {
				if !slices.Contains(dbs, df.Field.GetFullName()) {
					dbs = append(dbs, df.Field.GetFullName())
				}
			}
			for i, db := range dbs {
				str += db
				if i < len(dbs)-1 {
					str += ", "
				}
			}
			data = append(data, fmt.Sprintf("%s (%s) ----> (TAINTED @ %s)", v.String(), variables.GetVariableTypeAndTypeString(v), str))
		} else {
			data = append(data, fmt.Sprintf("%s (%s)", v.String(), variables.GetVariableTypeAndTypeString(v)))
		}
	}
	return data
}

type BlockInfo struct {
	Gen []variables.Variable
	In  []variables.Variable
	Out []variables.Variable
}

func (block *Block) GetVariables() []variables.Variable {
	return block.Vars
}

func (block *Block) GetLastestVariable(name string) variables.Variable {
	for i := len(block.Vars) - 1; i >= 0; i-- {
		v := block.Vars[i]
		if name == v.GetVariableInfo().GetName() {
			return v
		}
	}
	logger.Logger.Warnf("variable '%s' not found in declared block: %v", name, block.Vars)
	return nil
}

func (block *Block) AddVariables(variables []variables.Variable) {
	logger.Logger.Warnf("added variables to block: %s", variables)
	block.Vars = append(block.Vars, variables...)
}

func (block *Block) AddVariable(variable variables.Variable) {
	if block.Vars[len(block.Vars)-1] != variable {
		logger.Logger.Infof("added %s (%s) to block", variable.String(), utils.GetType(variable))
		block.Vars = append(block.Vars, variable)
	} else {
		logger.Logger.Warnf("%s (%s) already exists in block", variable.String(), utils.GetType(variable))
	}
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
