package models

import (
	"golang.org/x/tools/go/cfg"
)

// -------------------------
//
//	CFG
//
// ------------------------
type ParsedCFG struct {
	Cfg        	*cfg.CFG
	BlocksInfo 	[]*BlockInfo
	// FIXME: this should actually belong to the (first) block of the CFG
	Vars 		[]*Variable
}
type BlockInfo struct {
	Gen []*Variable
	In  []*Variable
	Out []*Variable
}
