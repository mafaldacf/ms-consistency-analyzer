package service

import (
	"analyzer/pkg/analyzer"
	"analyzer/pkg/models"
	"fmt"
	"go/ast"
	"go/token"
	"strings"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

type ServiceType struct {
	gocode.TypeName
	Package string
	Name    string
}

func (t *ServiceType) String() string {
	splits := strings.Split(t.Package, "/")
	return fmt.Sprintf("%s.%s", splits[len(splits)-1], t.Name)
}

func (t *ServiceType) Equals(other gocode.TypeName) bool {
	if t == nil || other == nil {
		return false
	}
	t2, isSameType := other.(*ServiceType)
	if !isSameType {
		return false
	}
	return t.Name == t2.Name
}

func (st *ServiceType) IsTypeName() {}

func GetShortServiceTypeStr(typeName gocode.TypeName) string {
	splits := strings.Split(typeName.String(), ".")
	return splits[len(splits)-1]
}

type ParsedFuncDecl struct {
	analyzer.Method
	Ast           *ast.FuncDecl
	Name          string
	Recv          *ast.Ident
	DatabaseCalls map[token.Pos]*ParsedCallExpr
	ServiceCalls  map[token.Pos]*ParsedCallExpr
	// used to fetch the params when generating the basic cfg
	// to store in the variables array of the function
	Params []string
}

func (p *ParsedFuncDecl) String() string {
	return p.Name
}

func (p *ParsedFuncDecl) GetNumParams() int {
	return len(p.Params)
}

type ParsedImportSpec struct {
	Ast                *ast.ImportSpec
	Alias              string
	Path               string
	Package            string
	IsBlueprintBackend bool
}

type ParsedField interface {
}

type ServiceField struct {
	ParsedField
	gocode.Variable
	Lineno token.Pos
	Ast    *ast.Field
}
type DatabaseField struct {
	ParsedField
	gocode.Variable
	Lineno token.Pos
	Ast    *ast.Field
}

type ParsedCallExpr struct {
	Ast *ast.CallExpr
	Name string

	// represents the name of the field for the interface
	// that the method is implementing e.g. f in 'f.storageService.StorePost(...)'
	Receiver string
	TargetField string

	// type of service calling (src) and being called (dest)
	SrcType  gocode.TypeName
	DestType gocode.TypeName

	Pos  token.Pos
	Deps []*analyzer.Variable

	Method analyzer.Method
}

func (call *ParsedCallExpr) String() string {
	var funcCallStr string
	if call.Receiver != "" {
		funcCallStr = fmt.Sprintf("%s.%s.%s(", call.Receiver, call.TargetField, call.Name)
	} else {
		funcCallStr = fmt.Sprintf("%s.%s(", call.TargetField, call.Name)
	}
	for i, arg := range call.Ast.Args {
		if ident, ok := arg.(*ast.Ident); ok {
			funcCallStr += ident.Name
			if i < len(call.Ast.Args)-1 {
				funcCallStr += ", "
			}
		}
	}
	funcCallStr += ")"
	return funcCallStr
}

func (call *ParsedCallExpr) SimpleString() string {
	funcCallStr := fmt.Sprintf("%s.%s(", call.TargetField, call.Name)
	for i, arg := range call.Ast.Args {
		if ident, ok := arg.(*ast.Ident); ok {
			funcCallStr += ident.Name
			if i < len(call.Ast.Args)-1 {
				funcCallStr += ", "
			}
		}
	}
	funcCallStr += ")"
	return funcCallStr
}

type ServiceNode struct {
	Name     string
	Impl     string
	Filepath string
	Package  string
	File     *ast.File
	Fields   map[string]ParsedField
	Imports  map[string]*ParsedImportSpec
	// the map key is the service type (e.g. StorageService in 'storageService StorageService')
	Services map[string]*ServiceNode
	// safe because methods are unique since Golang does not allow overloading
	// also this captures all exposed methods because they must be defined within the service struct file
	ExposedMethods map[string]*ParsedFuncDecl
	// FIXME: this does not capture all exposed methods
	// advised to include the file of origin in the ParsedFuncDecl type for this
	InternalMethods map[string]*ParsedFuncDecl

	ParsedCFGs map[string]*models.ParsedCFG
}
