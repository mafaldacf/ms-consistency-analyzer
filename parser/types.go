package parser

import (
	"go/ast"
	"go/token"

	"golang.org/x/tools/go/cfg"
)

type Variable struct {
	Lineno token.Pos
	Name   string
	Deps   []*Variable
}

// -------------------------
//
//	CFG
//
// ------------------------
type ParsedCFG struct {
	Cfg        *cfg.CFG
	BlocksInfo []*BlockInfo
}
type BlockInfo struct {
	Gen []*Variable
	In  []*Variable
	Out []*Variable
}

// -------------------------
//
//	AST
//
// ------------------------
type ParsedCallExpr struct {
	Ast        *ast.CallExpr
	// represents either the service or database being called
	Selected   string
	MethodName string
	Pos        token.Pos
	Deps       []*Variable
}

type ParsedFuncDecl struct {
	Ast           *ast.FuncDecl
	Name          string
	Recv          *ast.Ident
	DatabaseCalls map[token.Pos]*ParsedCallExpr
	ServiceCalls  map[token.Pos]*ParsedCallExpr
	// used to fetch the params when generating the basic cfg
	// to store in the variables array of the function
	Params []string
}

type BlueprintPkg int

const (
	BLUEPRINT_RUNTIME_CORE_BACKEND BlueprintPkg = iota
)

type ParsedImportSpec struct {
	Ast   *ast.ImportSpec
	Alias string
	Path  string
	// e.g.
	Type BlueprintPkg
}

type BlueprintDb int

const (
	BLUEPRINT_DB_NO_SQL_DATABASE BlueprintDb = iota
	BLUEPRINT_DB_CACHE
	BLUEPRINT_DB_QUEUE
)

type DatabaseField struct {
	Kind BlueprintDb
}

type ServiceNode struct {
	Name      string
	Impl      string
	Filepath  string
	File      *ast.File
	Imports   map[string]*ParsedImportSpec
	Databases map[string]*DatabaseField
	Services  map[string]*ServiceNode
	Methods   []*ParsedFuncDecl
}
