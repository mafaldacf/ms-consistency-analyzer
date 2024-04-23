package parser

import (
	"go/ast"
)

type ParsedCallExpr struct {
	Ast        *ast.CallExpr
	Selected   string
	MethodName string
}

type ParsedFuncDecl struct {
	Ast           *ast.FuncDecl
	Name          string
	Recv          *ast.Ident
	DatabaseCalls []*ParsedCallExpr
	ServiceCalls  []*ParsedCallExpr
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
