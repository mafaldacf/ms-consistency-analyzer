package models

import (
	"golang.org/x/tools/go/cfg"
	"analyzer/pkg/analyzer"
)

// -------------------------
//
//	CFG
//
// ------------------------
type ParsedCFG struct {
	Cfg        	*cfg.CFG
	Package     string
	BlocksInfo 	[]*BlockInfo
	FileHash 	string 		 `json:"file_hash,omitempty"`
	// FIXME: this should actually belong to the (first) block of the CFG
	Vars 		[]*analyzer.Variable
}
type BlockInfo struct {
	Gen []*analyzer.Variable
	In  []*analyzer.Variable
	Out []*analyzer.Variable
}
