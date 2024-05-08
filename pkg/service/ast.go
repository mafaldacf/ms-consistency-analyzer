package service

import (
	"analyzer/pkg/types"
	"encoding/json"
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

type ParsedFuncDecl struct {
	types.Method
	Ast           *ast.FuncDecl                 `json:"-"`
	Name          string                        `json:"name"`
	Recv          *ast.Ident                    `json:"-"`
	DatabaseCalls map[token.Pos]*ParsedCallExpr `json:"-"`
	ServiceCalls  map[token.Pos]*ParsedCallExpr `json:"-"`
	Service       string                        `json:"-"`

	DbInstances []types.DatabaseInstance `json:"-"`

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
	CallerTypeName gocode.TypeName
	CalleeTypeName gocode.TypeName

	Pos    token.Pos
	Params []*types.Variable

	DbInstance types.DatabaseInstance
	Method     types.Method
}

func (call *ParsedCallExpr) GetTargetedDatabaseInstance() types.DatabaseInstance {
	return call.DbInstance
}

func (call *ParsedCallExpr) String() string {
	var funcCallStr string
	if call.Receiver != "" {
		funcCallStr = fmt.Sprintf("%s.%s.%s(", call.Receiver, call.TargetField, call.Name)
	} else {
		funcCallStr = fmt.Sprintf("%s.%s(", call.TargetField, call.Name)
	}
	for i, arg := range call.Ast.Args {
		switch e := arg.(type) {
		case *ast.Ident:
			funcCallStr += e.Name
		case *ast.UnaryExpr:
			if ident, ok := e.X.(*ast.Ident); ok {
				funcCallStr += "&" + ident.Name
			}
		}
		if i < len(call.Ast.Args)-1 {
			funcCallStr += ", "
		}
	}
	funcCallStr += ")"
	return funcCallStr
}

func (call *ParsedCallExpr) SimpleString() string {
	funcCallStr := fmt.Sprintf("%s.%s(", call.TargetField, call.Name)
	for i, arg := range call.Params {
		funcCallStr += arg.String()
		if i < len(call.Ast.Args)-1 {
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
	Services  map[string]*ServiceNode
	Databases map[string]types.DatabaseInstance
	// safe because methods are unique since Golang does not allow overloading
	// also this captures all exposed methods because they must be defined within the service struct file
	ExposedMethods      map[string]*ParsedFuncDecl
	QueueHandlerMethods map[string]*ParsedFuncDecl
	InternalMethods     map[string]*ParsedFuncDecl
	Constructor         *ParsedFuncDecl

	ParsedCFGs      map[string]*types.ParsedCFG
	ImplementsQueue bool
}

// MarshalJSON is used by app.Save()
func (s *ServiceNode) MarshalJSON() ([]byte, error) {
	var serviceKeys []string
	for k := range s.Services {
		serviceKeys = append(serviceKeys, k)
	}
	var databaseKeys []string
	for k := range s.Databases {
		databaseKeys = append(databaseKeys, k)
	}
	fieldTypes := make(map[string]string)
	for name, field := range s.Fields {
		fieldTypes[name] = field.GetTypeName()
	}
	return json.MarshalIndent(&struct {
		Fields    map[string]string `json:"fields,omitempty"`
		Services  []string          `json:"services,omitempty"`
		Databases []string          `json:"databases,omitempty"`
	}{
		Fields:    fieldTypes,
		Services:  serviceKeys,
		Databases: databaseKeys,
	}, "", " ")
}

func (n *ServiceNode) String() string {
	str, _ := n.MarshalJSON()
	return string(str)
}
