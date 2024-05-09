package types

import (
	"golang.org/x/tools/go/cfg"
)

// -------------------------
//
//	CFG
//
// ------------------------
type ParsedCFG struct {
	Cfg        *cfg.CFG
	Package    string
	BlocksInfo []*BlockInfo
	FileHash   string `json:"file_hash,omitempty"`
	// FIXME: this should actually belong to the (first) block of the CFG
	Vars []*Variable

	FullMethod  string
}
type BlockInfo struct {
	Gen []*Variable
	In  []*Variable
	Out []*Variable
}
