package models

import (
	"go/ast"
	"go/token"
	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

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
	Kind 			NodeKind
	// string of the type of service (e.g. PostStorageService) or database (Cache)
	TargetType 		string

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

type ParsedImportSpec struct {
	Ast   	*ast.ImportSpec
	Alias 	string
	Path  	string
	Package string
	IsBlueprintBackend bool
}

type ParsedField interface {
}

type ServiceField struct {
	ParsedField
	gocode.Variable
	Lineno 		token.Pos
	Ast      	*ast.Field
}
type DatabaseField struct {
	ParsedField
	gocode.Variable
	Lineno 		token.Pos
	Ast      	*ast.Field
}

type ServiceNode struct {
	Name      string
	Impl      string
	Filepath  string
	Package 	  string
	File      *ast.File
	Fields 	  map[string]ParsedField
	Imports   map[string]*ParsedImportSpec
	// the map key is the service type (e.g. StorageService in 'storageService StorageService')
	Services  map[string]*ServiceNode
	// safe because methods are unique since Golang does not allow overloading
	Methods   map[string]*ParsedFuncDecl

	ParsedCFGs map[string]*ParsedCFG
}
