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
	Params  []variables.Variable
	Returns []variables.Variable
	Method  Method
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
	deepCopy := param.DeepCopy()
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

func (svcCall *ParsedServiceCall) GetMethod() Method {
	return svcCall.Method
}

type ParsedDatabaseCall struct {
	Call
	ParsedCall
	DbInstance     datastores.DatabaseInstance
	CallerTypeName gotypes.Type
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
	deepCopy := param.DeepCopy()
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

func (dbCall *ParsedDatabaseCall) GetMethod() Method {
	return dbCall.Method
}

type ParsedInternalCall struct {
	Call
	ParsedCall
	ServiceTypeName gotypes.Type
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
