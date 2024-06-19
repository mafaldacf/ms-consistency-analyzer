package types

import (
	"fmt"

	"golang.org/x/tools/go/cfg"
)

type CFG struct {
	Cfg          *cfg.CFG
	ParsedBlocks []*Block
	Package      string
	FileHash     string
	FullMethod   string
}

func InitParsedCFG(cfg *cfg.CFG, fullMethod string) *CFG {
	parsedCfg := &CFG{
		Cfg:        cfg,
		FullMethod: fullMethod,
	}
	for _, block := range cfg.Blocks {
		parsedCfg.ParsedBlocks = append(parsedCfg.ParsedBlocks, &Block{Block: block})
	}
	return parsedCfg
}

func (cfg *CFG) Yaml() map[string]interface{} {
	data := make(map[string]interface{})
	for _, block := range cfg.ParsedBlocks {
		data[block.Block.String()] = block.Yaml()
	}
	return data
}

func (cfg *CFG) String() string {
	str := fmt.Sprintf("%s: ", cfg.FullMethod)
	for i, block := range cfg.ParsedBlocks {
		str += block.String()
		if i < len(cfg.ParsedBlocks)-1 {
			str += ", "
		}
	}
	return str + "\n"
}

func (cfg *CFG) FullString() string {
	str := "\n"
	for _, block := range cfg.ParsedBlocks {
		str += block.FullString()
	}
	return str + "\n"
}

func (cfg *CFG) GetEntryParsedBlock() *Block {
	if len(cfg.ParsedBlocks) > 0 {
		return cfg.ParsedBlocks[0]
	}
	return nil
}

func (cfg *CFG) GetParsedBlocks() []*Block {
	return cfg.ParsedBlocks
}

func (cfg *CFG) GetParsedBlockAtIndex(index int32) *Block {
	if len(cfg.ParsedBlocks) > int(index) {
		return cfg.ParsedBlocks[index]
	}
	return nil
}
