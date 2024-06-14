package service

import (
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
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

	DbInstances []datastores.DatabaseInstance `json:"-"`

	// used to fetch the params when generating the basic cfg
	// to store in the variables array of the function
	Params  []*types.FunctionField
	Returns []*types.FunctionField
}

func (f *ParsedFuncDecl) Yaml() map[string]interface{} {
	data := make(map[string]interface{})
	data["Parsed CFG"] = f.ParsedCfg.Yaml()
	return data
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
func (*ParsedFuncDecl) IsQueueRead() bool {
	return false
}

func (p *ParsedFuncDecl) String() string {
	repr := fmt.Sprintf("%s.%s(", p.Service, p.Name)
	for i, arg := range p.Params {
		repr += arg.String()
		if i < len(p.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	return repr
}

// TODO: missing returns!!
func (p *ParsedFuncDecl) Signature() string {
	repr := fmt.Sprintf("%s(", p.Name)
	for i, arg := range p.Params {
		repr += arg.String()
		if i < len(p.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	if len(p.Returns) == 0 {
		return repr
	}
	if len(p.Returns) == 1 {
		return repr + " " + p.Returns[0].String()
	}

	repr += " ("
	for i, arg := range p.Returns {
		repr += arg.String()
		if i < len(p.Returns)-1 {
			repr += ", "
		}
	}
	return repr + ")"
}

func (p *ParsedFuncDecl) GetParams() []*types.FunctionField {
	return p.Params
}
func (p *ParsedFuncDecl) GetReturns() []*types.FunctionField {
	return p.Returns
}

type Call interface {
	String() string
	GetName() string
	GetMethod() types.Method
	SimpleString() string
	IsAtPos(token.Pos) bool
	AddParam(param types.Variable)
	GetParams() []types.Variable
}

type ParsedCallExpr struct {
	Ast  *ast.CallExpr
	Name string

	// represents the name of the field for the interface
	// that the method is implementing e.g. f in 'f.storageService.StorePost(...)'
	Receiver    string
	TargetField string

	Pos    token.Pos
	Params []types.Variable
	Method types.Method
}

func (call ParsedCallExpr) GetArgument(i int) types.Variable {
	if i > len(call.Params) {
		logger.Logger.Fatalf("invalid argument index %d for length %d in params: %v", i, (call.Params), call.Params)
	}
	return call.Params[i]
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
	for i, arg := range call.Params {
		funcCallStr += arg.String()
		if i < len(call.Params)-1 {
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
		if i < len(call.Params)-1 {
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

func (svcCall *ServiceParsedCallExpr) AddParam(param types.Variable) {
	svcCall.Params = append(svcCall.Params, param)
}

func (svcCall *ServiceParsedCallExpr) GetParams() []types.Variable {
	return svcCall.Params
}

func (svcCall *ServiceParsedCallExpr) GetMethod() types.Method {
	return svcCall.Method
}

type DatabaseParsedCallExpr struct {
	Call
	ParsedCallExpr
	DbInstance     datastores.DatabaseInstance
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

func (dbCall *DatabaseParsedCallExpr) GetTargetedDatabaseInstance() datastores.DatabaseInstance {
	return dbCall.DbInstance
}

func (dbCall *DatabaseParsedCallExpr) GetName() string {
	return dbCall.Name
}

func (dbCall *DatabaseParsedCallExpr) AddParam(param types.Variable) {
	dbCall.Params = append(dbCall.Params, param)
}

func (dbCall *DatabaseParsedCallExpr) GetParams() []types.Variable {
	return dbCall.Params
}

func (dbCall *DatabaseParsedCallExpr) GetMethod() types.Method {
	return dbCall.Method
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

func (internalCall *InternalTempParsedCallExpr) AddParam(param types.Variable) {
	internalCall.Params = append(internalCall.Params, param)
}

func (internalCall *InternalTempParsedCallExpr) GetParams() []types.Variable {
	return internalCall.Params
}

func (internalCall *InternalTempParsedCallExpr) GetMethod() types.Method {
	return internalCall.Method
}

type ServiceNode struct {
	Name            string
	ImplName        string
	ConstructorName string

	File   *types.File
	Fields map[string]types.Field
	// the map key is the service type (e.g. StorageService in 'storageService StorageService')
	Services  map[string]*ServiceNode
	Databases map[string]datastores.DatabaseInstance
	// safe because methods are unique since Golang does not allow overloading
	// also this captures all exposed methods because they must be defined within the service struct file
	ExposedMethods      map[string]*ParsedFuncDecl
	QueueHandlerMethods map[string]*ParsedFuncDecl
	InternalMethods     map[string]*ParsedFuncDecl
	Constructor         *ParsedFuncDecl

	ImplementsQueue bool
}

func (node *ServiceNode) Yaml() map[string]interface{} {
	data := make(map[string]interface{})
	// exposed methods
	exposedMethods := make(map[string]interface{})
	for _, method := range node.ExposedMethods {
		exposedMethods[method.Signature()] = method.Yaml()
	}
	data["Exposed Methods"] = exposedMethods
	// queue handler methods COMMENTED
	queueHandlerMethods := make(map[string]interface{})
	/* for _, method := range node.QueueHandlerMethods {
		queueHandlerMethods[method.Signature()] = method.Yaml()
	} */
	data["Queue Handler Methods"] = queueHandlerMethods
	// exposed methods COMMENTED
	internalMethods := make(map[string]interface{})
	/* for _, method := range node.InternalMethods {
		internalMethods[method.Signature()] = method.Yaml()
	} */
	data["Internal Methods"] = internalMethods
	return data
}

func (node *ServiceNode) GetPackage() *types.Package {
	return node.File.Package
}
func (node *ServiceNode) GetPackageName() string {
	return node.File.Package.Name
}

func (node *ServiceNode) GetQueueHandlersForDatabase(database datastores.DatabaseInstance) []*ParsedFuncDecl {
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
