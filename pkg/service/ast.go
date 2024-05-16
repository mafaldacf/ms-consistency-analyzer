package service

import (
	"analyzer/pkg/types"
	"encoding/json"
	"fmt"
	"go/ast"
	"go/token"
	"slices"
)

type ParsedFuncDecl struct {
	types.Method
	Ast       *ast.FuncDecl    `json:"-"`
	Name      string           `json:"name"`
	Recv      *ast.Ident       `json:"-"`
	Calls     []Call           `json:"-"`
	Service   string           `json:"-"`
	ParsedCfg *types.ParsedCFG `json:"-"`

	DbInstances []types.DatabaseInstance `json:"-"`

	// used to fetch the params when generating the basic cfg
	// to store in the variables array of the function
	Params  []*types.FunctionParameter
}

func (f *ParsedFuncDecl) GetAst() *ast.FuncDecl { 
	return f.Ast 
}
func (f *ParsedFuncDecl) GetBody() *ast.BlockStmt { 
	return f.Ast.Body
}
func (f *ParsedFuncDecl) SetParsedCFG(parsedCfg *types.ParsedCFG) {
	f.ParsedCfg = parsedCfg
}
func (*ParsedFuncDecl) IsQueueWrite() bool { 
	return false 
}
func (*ParsedFuncDecl) IsQueueRead() bool  { 
	return false 
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

func (p *ParsedFuncDecl) GetParams() []*types.FunctionParameter {
	return p.Params
}
type ParsedImportSpec struct {
	Ast                *ast.ImportSpec
	Alias              string
	Path               string
	Package            string
	IsBlueprintBackend bool
}

type Call interface {
	String() string
	GetName() string
	SimpleString() string
	IsAtPos(token.Pos) bool
	AddParam(param *types.Variable)
	GetParams() []*types.Variable
}

type ParsedCallExpr struct {
	Ast  *ast.CallExpr
	Name string

	// represents the name of the field for the interface
	// that the method is implementing e.g. f in 'f.storageService.StorePost(...)'
	Receiver    string
	TargetField string

	Pos    token.Pos
	Params []*types.Variable
	Method types.Method
}

func (call *ParsedCallExpr) String() string {
	funcCallStr := ""
	if call.Receiver != "" {
		funcCallStr += fmt.Sprintf("%s.", call.Receiver)
	}
	if call.TargetField != "" {
		funcCallStr += fmt.Sprintf("%s.", call.TargetField)
	}
	funcCallStr += fmt.Sprintf("%s(", call.Name)
	for i, arg := range call.Method.GetParams() {
		funcCallStr += arg.String()
		if i < len(call.Method.GetParams())-1 {
			funcCallStr += ", "
		}
	}
	funcCallStr += ")"
	return funcCallStr
}

func (call *ParsedCallExpr) SimpleString() string {
	funcCallStr := fmt.Sprintf("%s.%s(", call.TargetField, call.Name)
	for i, arg := range call.Method.GetParams() {
		funcCallStr += arg.String()
		if i < len(call.Method.GetParams())-1 {
			funcCallStr += ", "
		}
	}
	funcCallStr += ")"
	return funcCallStr
}

type ServiceParsedCallExpr struct {
	Call
	ParsedCallExpr
	CallerTypeName types.Type
	CalleeTypeName types.Type
}

func (svcCall *ServiceParsedCallExpr) GetCallTypeNames() (types.Type, types.Type) {
	return svcCall.CallerTypeName, svcCall.CalleeTypeName
}

func (svcCall *ServiceParsedCallExpr) String() string {
	return svcCall.ParsedCallExpr.String()
}

func (svcCall *ServiceParsedCallExpr) SimpleString() string {
	return svcCall.ParsedCallExpr.SimpleString()
}

func (svcCall *ServiceParsedCallExpr) IsAtPos(pos token.Pos) bool {
	return svcCall.ParsedCallExpr.Pos == pos
}

func (svcCall *ServiceParsedCallExpr) GetName() string {
	return svcCall.Name
}

func (svcCall *ServiceParsedCallExpr) AddParam(param *types.Variable) {
	svcCall.Params = append(svcCall.Params, param)
}

func (svcCall *ServiceParsedCallExpr) GetParams() []*types.Variable {
	return svcCall.Params
}

type DatabaseParsedCallExpr struct {
	Call
	ParsedCallExpr
	DbInstance     types.DatabaseInstance
	CallerTypeName types.Type
}

func (dbCall *DatabaseParsedCallExpr) IsAtPos(pos token.Pos) bool {
	return dbCall.ParsedCallExpr.Pos == pos
}

func (dbCall *DatabaseParsedCallExpr) String() string {
	return dbCall.ParsedCallExpr.String()
}

func (dbCall *DatabaseParsedCallExpr) SimpleString() string {
	return dbCall.ParsedCallExpr.SimpleString()
}

func (dbCall *DatabaseParsedCallExpr) GetTargetedDatabaseInstance() types.DatabaseInstance {
	return dbCall.DbInstance
}

func (dbCall *DatabaseParsedCallExpr) GetName() string {
	return dbCall.Name
}

func (dbCall *DatabaseParsedCallExpr) AddParam(param *types.Variable) {
	dbCall.Params = append(dbCall.Params, param)
}

func (dbCall *DatabaseParsedCallExpr) GetParams() []*types.Variable {
	return dbCall.Params
}

type InternalTempParsedCallExpr struct {
	Call
	ParsedCallExpr
	ServiceTypeName types.Type
}

func (internalCall *InternalTempParsedCallExpr) String() string {
	return internalCall.ParsedCallExpr.String()
}

func (internalCall *InternalTempParsedCallExpr) SimpleString() string {
	return internalCall.ParsedCallExpr.SimpleString()
}

func (internalCall *InternalTempParsedCallExpr) IsAtPos(pos token.Pos) bool {
	return internalCall.ParsedCallExpr.Pos == pos
}

func (internalCall *InternalTempParsedCallExpr) GetName() string {
	return internalCall.Name
}

func (internalCall *InternalTempParsedCallExpr) AddParam(param *types.Variable) {
	internalCall.Params = append(internalCall.Params, param)
}

func (internalCall *InternalTempParsedCallExpr) GetParams() []*types.Variable {
	return internalCall.Params
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

	ImplementsQueue bool
}

func (node *ServiceNode) GetQueueHandlersForDatabase(database types.DatabaseInstance) []*ParsedFuncDecl {
	if _, ok := node.Databases[database.GetName()]; !ok {
		return nil
	}

	var handlers []*ParsedFuncDecl
	for _, handler := range node.QueueHandlerMethods {
		if slices.Contains(handler.DbInstances, database) {
			handlers = append(handlers, handler)
		}
	}
	return handlers
}

func (node *ServiceNode) GetExposedMethod(name string) *ParsedFuncDecl {
	return node.ExposedMethods[name]
}

func (node *ServiceNode) GetInternalMethod(name string) *ParsedFuncDecl {
	return node.InternalMethods[name]
}

func (node *ServiceNode) GetQueueHandlerMethod(name string) *ParsedFuncDecl {
	return node.QueueHandlerMethods[name]
}

// MarshalJSON is used by app.Save()
func (node *ServiceNode) MarshalJSON() ([]byte, error) {
	var serviceKeys []string
	for k := range node.Services {
		serviceKeys = append(serviceKeys, k)
	}
	var databaseKeys []string
	for k := range node.Databases {
		databaseKeys = append(databaseKeys, k)
	}
	fieldTypes := make(map[string]string)
	for name, field := range node.Fields {
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

func (node *ServiceNode) String() string {
	str, _ := node.MarshalJSON()
	return string(str)
}
