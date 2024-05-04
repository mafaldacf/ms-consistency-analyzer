package service

import (
	"analyzer/pkg/types"
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
	types.Method
	Ast           *ast.FuncDecl                 `json:"-"`    // omit from json
	Name          string                        `json:"name"` // omit from json
	Recv          *ast.Ident                    `json:"-"`    // omit from json
	DatabaseCalls map[token.Pos]*ParsedCallExpr `json:"-"`    // omit from json
	ServiceCalls  map[token.Pos]*ParsedCallExpr `json:"-"`    // omit from json
	Service       string                        `json:"-"`
	// used to fetch the params when generating the basic cfg
	// to store in the variables array of the function
	Params  []*types.FunctionField
	Returns []*types.FunctionField
}

func (p *ParsedFuncDecl) String() string {
	repr := fmt.Sprintf("%s.%s(", p.Service, p.Name)
	for i, arg := range p.Params {
		repr += arg.GetName()
		if i < len(p.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	return repr
}

func (p *ParsedFuncDecl) GetParams() []*types.FunctionField {
	return p.Params
}

func (p *ParsedFuncDecl) GetReturns() []*types.FunctionField {
	return p.Returns
}

type ParsedImportSpec struct {
	Ast                *ast.ImportSpec
	Alias              string
	Path               string
	Package            string
	IsBlueprintBackend bool
}

type ParsedCallExpr struct {
	Ast  *ast.CallExpr
	Name string

	// represents the name of the field for the interface
	// that the method is implementing e.g. f in 'f.storageService.StorePost(...)'
	Receiver    string
	TargetField string

	// type of service calling (src) and being called (dest)
	SrcType  gocode.TypeName
	DestType gocode.TypeName

	Pos    token.Pos
	Params []*types.Variable

	Method types.Method
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
	for i, arg := range call.Params {
		funcCallStr += arg.String()
		if i < len(call.Ast.Args)-2 {
			funcCallStr += ", "
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
	Fields   map[string]types.Field
	Imports  map[string]*ParsedImportSpec
	// the map key is the service type (e.g. StorageService in 'storageService StorageService')
	Services 	map[string]*ServiceNode
	Databases 	map[string]types.DatabaseInstance
	// safe because methods are unique since Golang does not allow overloading
	// also this captures all exposed methods because they must be defined within the service struct file
	ExposedMethods  map[string]*ParsedFuncDecl
	WorkerMethods   map[string]*ParsedFuncDecl
	InternalMethods map[string]*ParsedFuncDecl

	ParsedCFGs      map[string]*types.ParsedCFG
	ImplementsQueue bool
}

func (n *ServiceNode) String() string {
	repr := fmt.Sprintf("%s ----> Services: { ", n.Name)
	i := 0
	for name := range n.Services {
		repr += name
		if i < len(n.Services) - 1 {
			repr += ", "
		}
		i++
	}
	repr += " }, Databases: { "
	i = 0
	for _, t := range n.Databases {
		repr += t.String()
		if i < len(n.Databases) - 1 {
			repr += ", "
		}
		i++
	}
	return repr + " }"
}
