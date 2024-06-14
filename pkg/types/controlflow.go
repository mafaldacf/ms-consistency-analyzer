package types

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
	"fmt"
	"go/ast"
	"go/token"

	"golang.org/x/tools/go/cfg"
)

type ParsedCFG struct {
	Cfg          *cfg.CFG
	ParsedBlocks []*ParsedBlock
	Package      string
	FileHash     string
	FullMethod   string
}

func InitParsedCFG(cfg *cfg.CFG, fullMethod string) *ParsedCFG {
	parsedCfg := &ParsedCFG{
		Cfg:        cfg,
		FullMethod: fullMethod,
	}
	for _, block := range cfg.Blocks {
		parsedCfg.ParsedBlocks = append(parsedCfg.ParsedBlocks, &ParsedBlock{Block: block})
	}
	return parsedCfg
}

func (cfg *ParsedCFG) Yaml() map[string][]string {
	data := make(map[string][]string)
	for _, block := range cfg.ParsedBlocks {
		data[block.Block.String()] = block.Yaml()
	}
	return data
}

func (cfg *ParsedCFG) String() string {
	str := fmt.Sprintf("%s: ", cfg.FullMethod)
	for i, block := range cfg.ParsedBlocks {
		str += block.String()
		if i < len(cfg.ParsedBlocks)-1 {
			str += ", "
		}
	}
	return str + "\n"
}

func (cfg *ParsedCFG) FullString() string {
	str := "\n"
	for _, block := range cfg.ParsedBlocks {
		str += block.FullString()
	}
	return str + "\n"
}

func (cfg *ParsedCFG) GetEntryParsedBlock() *ParsedBlock {
	if len(cfg.ParsedBlocks) > 0 {
		return cfg.ParsedBlocks[0]
	}
	return nil
}

func (cfg *ParsedCFG) GetParsedBlocks() []*ParsedBlock {
	return cfg.ParsedBlocks
}

func (cfg *ParsedCFG) GetParsedBlockAtIndex(index int32) *ParsedBlock {
	if len(cfg.ParsedBlocks) > int(index) {
		return cfg.ParsedBlocks[index]
	}
	return nil
}

type ParsedBlock struct {
	Block *cfg.Block
	// blocks can contain inline go routines
	Vars []Variable
	Info BlockInfo
}

func (block *ParsedBlock) Yaml() []string {
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

func (block *ParsedBlock) GetVariables() []Variable {
	return block.Vars
}

func (block *ParsedBlock) GetLastestVariable(name string) Variable {
	for i := len(block.Vars) - 1; i >= 0; i-- {
		v := block.Vars[i]
		if name == v.GetVariableInfo().GetName() {
			return v
		}
	}
	logger.Logger.Warnf("variable '%s' not found in declared block: %v", name, block.Vars)
	return nil
}

func (block *ParsedBlock) AddVariables(variables []Variable) {
	block.Vars = append(block.Vars, variables...)
}

func (block *ParsedBlock) AddVariable(variable Variable) {
	block.Vars = append(block.Vars, variable)
}

func (block *ParsedBlock) GetPosition() token.Pos {
	return block.Block.Stmt.Pos()
}

func (block *ParsedBlock) GetIndex() int32 {
	return block.Block.Index
}

func (block *ParsedBlock) GetNodes() []ast.Node {
	return block.Block.Nodes
}

func (block *ParsedBlock) GetSuccs() []*cfg.Block {
	return block.Block.Succs
}

func (block *ParsedBlock) CopyVarsFromPredecessor(predecessor *ParsedBlock) {
	logger.Logger.Debugf("copying vars %d -> %d: %v -> %v", predecessor.GetIndex(), block.GetIndex(), predecessor.Vars, block.Vars)
	block.Vars = append(predecessor.Vars, block.Vars...)
}

func (block *ParsedBlock) String() string {
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

func (block *ParsedBlock) FullString() string {
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
