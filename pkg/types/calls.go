package types

import (
	"fmt"
	"go/ast"
	"go/token"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

type Call interface {
	String() string
	GetName() string
	GetMethod() Method
	SimpleString() string
	IsAtPos(token.Pos) bool
	AddParam(param variables.Variable)
	AddReturn(ret variables.Variable)
	GetParams() []variables.Variable
}

type ParsedCall struct {
	Ast     *ast.CallExpr
	CallStr string
	Name    string

	Pos     token.Pos
	Method  Method
	Params  []variables.Variable
	Returns []variables.Variable
}

func (call ParsedCall) DeepCopy() ParsedCall {
	// we actually don't need to deep copy the CFG block
	// what we need is to cpy the parsed call's params and returns
	// since they are the ones that are looked up for the references between abstract nodes
	var newParams []variables.Variable
	for _, v := range call.Params {
		newParams = append(newParams, v.DeepCopy())
	}

	newCall := ParsedCall{
		Ast:     call.Ast,
		CallStr: call.CallStr,
		Name:    call.Name,
		Pos:     call.Pos,
		Method:  call.Method,
		Params:  newParams,
		Returns: call.Returns, //TODO: set nil
	}

	return newCall
}

func (call ParsedCall) GetMethod() Method {
	return call.Method
}

func (call ParsedCall) GetParams() []variables.Variable {
	return call.Params
}

func (call ParsedCall) GetReturns() []variables.Variable {
	return call.Returns
}

func (call ParsedCall) GetArgument(i int) variables.Variable {
	if i > len(call.Params) {
		logger.Logger.Fatalf("invalid argument index %d for length %d in params: %v", i, (call.Params), call.Params)
	}
	return call.Params[i]
}

func (call *ParsedCall) String() string {
	funcCallStr := fmt.Sprintf("%s(", call.CallStr)
	for i, arg := range call.Params {
		funcCallStr += arg.String()
		if i < len(call.Params)-1 {
			funcCallStr += ", "
		}
	}
	funcCallStr += ")"
	return funcCallStr
}

func (call *ParsedCall) SimpleString() string {
	funcCallStr := fmt.Sprintf("%s(", call.CallStr)
	for i, arg := range call.Params {
		funcCallStr += arg.String()
		if i < len(call.Params)-1 {
			funcCallStr += ", "
		}
	}
	funcCallStr += ")"
	return funcCallStr
}

type ParsedServiceCall struct {
	Call
	ParsedCall
	CallerTypeName gotypes.Type
	CalleeTypeName gotypes.Type
}

func (svcCall *ParsedServiceCall) DeepCopy() *ParsedServiceCall {
	return &ParsedServiceCall{
		Call:           svcCall.Call,
		ParsedCall:     svcCall.ParsedCall.DeepCopy(),
		CallerTypeName: svcCall.CallerTypeName,
		CalleeTypeName: svcCall.CalleeTypeName,
	}
}

func (svcCall *ParsedServiceCall) GetCallTypeNames() (gotypes.Type, gotypes.Type) {
	return svcCall.CallerTypeName, svcCall.CalleeTypeName
}

func (svcCall *ParsedServiceCall) String() string {
	return svcCall.ParsedCall.String()
}

func (svcCall *ParsedServiceCall) SimpleString() string {
	return svcCall.ParsedCall.SimpleString()
}

func (svcCall *ParsedServiceCall) IsAtPos(pos token.Pos) bool {
	return svcCall.ParsedCall.Pos == pos
}

func (svcCall *ParsedServiceCall) GetName() string {
	return svcCall.Name
}

func (svcCall *ParsedServiceCall) AddParam(param variables.Variable) {
	deepCopy := param.Copy(false)
	logger.Logger.Tracef("[------- DEEP COPY -------] [%s] %v", utils.GetType(deepCopy), deepCopy.String())
	if deepCopy.GetVariableInfo() == nil {
		logger.Logger.Fatalf("[------- DEEP COPY -------] [%s] %v: %v", utils.GetType(deepCopy), deepCopy.String(), deepCopy.GetVariableInfo())
	}
	svcCall.Params = append(svcCall.Params, deepCopy)
}

func (svcCall *ParsedServiceCall) AddReturn(ret variables.Variable) {
	svcCall.Returns = append(svcCall.Returns, ret)
}

func (svcCall *ParsedServiceCall) GetParams() []variables.Variable {
	return svcCall.Params
}

func (svcCall *ParsedServiceCall) GetReturns() []variables.Variable {
	return svcCall.Params
}

func (svcCall *ParsedServiceCall) GetMethod() Method {
	return svcCall.Method
}

type ParsedDatabaseCall struct {
	Call
	ParsedCall
	DbInstance     datastores.DatabaseInstance
	CallerTypeName gotypes.Type
}

func (dbCall *ParsedDatabaseCall) DeepCopy() *ParsedDatabaseCall {
	return &ParsedDatabaseCall{
		Call:           dbCall.Call,
		ParsedCall:     dbCall.ParsedCall.DeepCopy(),
		DbInstance:     dbCall.DbInstance,
		CallerTypeName: dbCall.CallerTypeName,
	}
}

func (dbCall *ParsedDatabaseCall) IsAtPos(pos token.Pos) bool {
	return dbCall.ParsedCall.Pos == pos
}

func (dbCall *ParsedDatabaseCall) String() string {
	return dbCall.ParsedCall.String()
}

func (dbCall *ParsedDatabaseCall) SimpleString() string {
	return dbCall.ParsedCall.SimpleString()
}

func (dbCall *ParsedDatabaseCall) GetTargetedDatabaseInstance() datastores.DatabaseInstance {
	return dbCall.DbInstance
}

func (dbCall *ParsedDatabaseCall) GetName() string {
	return dbCall.Name
}

func (dbCall *ParsedDatabaseCall) AddParam(param variables.Variable) {
	deepCopy := param.Copy(false)
	logger.Logger.Tracef("[------- DEEP COPY -------] [%s] %v", utils.GetType(deepCopy), deepCopy.String())
	if deepCopy.GetVariableInfo() == nil {
		logger.Logger.Fatalf("[------- DEEP COPY -------] [%s] %v: %v", utils.GetType(deepCopy), deepCopy.String(), deepCopy.GetVariableInfo())
	}
	dbCall.Params = append(dbCall.Params, deepCopy)
}

func (dbCall *ParsedDatabaseCall) AddReturn(ret variables.Variable) {
	dbCall.Returns = append(dbCall.Returns, ret)
}

func (dbCall *ParsedDatabaseCall) GetParams() []variables.Variable {
	return dbCall.Params
}

func (dbCall *ParsedDatabaseCall) GetParam(i int) variables.Variable {
	if i >= len(dbCall.Params) {
		logger.Logger.Fatalf("[CALLS] index (%d) out of range for parameters list in database call (%s): %v", i, dbCall.CallStr, dbCall.Params)
	}
	return dbCall.Params[i]
}

func (dbCall *ParsedDatabaseCall) GetReturn(i int) variables.Variable {
	if i >= len(dbCall.Returns) {
		logger.Logger.Fatalf("[CALLS] index (%d) out of range for returns list in database call (%s): %v", i, dbCall.CallStr, dbCall.Returns)
	}
	return dbCall.Returns[i]
}

func (dbCall *ParsedDatabaseCall) GetMethod() Method {
	return dbCall.Method
}

type ParsedInternalCall struct {
	Call
	ParsedCall
	ServiceTypeName gotypes.Type
}

func (internalCall *ParsedInternalCall) DeepCopy() *ParsedInternalCall {
	return &ParsedInternalCall{
		Call:            internalCall.Call,
		ParsedCall:      internalCall.ParsedCall.DeepCopy(),
		ServiceTypeName: internalCall.ServiceTypeName,
	}
}

func (internalCall *ParsedInternalCall) String() string {
	return internalCall.ParsedCall.String()
}

func (internalCall *ParsedInternalCall) SimpleString() string {
	return internalCall.ParsedCall.SimpleString()
}

func (internalCall *ParsedInternalCall) IsAtPos(pos token.Pos) bool {
	return internalCall.ParsedCall.Pos == pos
}

func (internalCall *ParsedInternalCall) GetName() string {
	return internalCall.Name
}

func (internalCall *ParsedInternalCall) AddParam(param variables.Variable) {
	internalCall.Params = append(internalCall.Params, param)
}

func (internalCall *ParsedInternalCall) AddReturn(ret variables.Variable) {
	internalCall.Returns = append(internalCall.Returns, ret)
}

func (internalCall *ParsedInternalCall) GetParams() []variables.Variable {
	return internalCall.Params
}

func (internalCall *ParsedInternalCall) GetMethod() Method {
	return internalCall.Method
}
