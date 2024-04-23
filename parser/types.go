package parser

import (
	"go/ast"
	"go/token"

	"golang.org/x/tools/go/cfg"
)

type Variable struct {
	Lineno token.Pos 	`json:"lineno"`
	Id 	   int 			`json:"id"`
	Name   string 		`json:"name"`
	Deps   []*Variable 	`json:"deps"`
}

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

// -------------------------
//
//	AST
//
// ------------------------
type NodeKind int

const (
	KIND_ROOT 			NodeKind = iota
	KIND_SERVICE_CALL
	KIND_DATABASE_CALL
)

type ParsedCallExpr struct {
	Ast        		*ast.CallExpr
	// represents either the service or database being called
	Selected   		string
	// string of the type of service (e.g. PostStorageService) or database (Cache)
	Kind 			NodeKind
	Type 			string

	MethodName 		string
	Pos        		token.Pos
	Deps       		[]*Variable
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
type DatabaseField struct {
	Type string
}

type ServiceNode struct {
	Name      string
	Impl      string
	Filepath  string
	File      *ast.File
	Imports   map[string]*ParsedImportSpec
	Databases map[string]*DatabaseField
	Services  map[string]*ServiceNode
	// safe because methods are unique since Golang does not allow overloading
	Methods   map[string]*ParsedFuncDecl

	ParsedCFGs map[string]*ParsedCFG
}
