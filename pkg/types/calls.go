package types

import (
	"fmt"
	"go/ast"
	"go/token"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type Call interface {
	String() string
	GetName() string
	GetMethod() Method
	SimpleString() string
	IsAtPos(token.Pos) bool
	AddParam(param Variable)
	AddReturn(ret Variable)
	GetParams() []Variable
}

type ParsedCall struct {
	Ast  *ast.CallExpr
	Name string

	// represents the name of the field for the interface
	// that the method is implementing e.g. f in 'f.storageService.StorePost(...)'
	Receiver    string
	TargetField string

	Pos     token.Pos
	Params  []Variable
	Returns []Variable
	Method  Method
}

func (call ParsedCall) GetArgument(i int) Variable {
	if i > len(call.Params) {
		logger.Logger.Fatalf("invalid argument index %d for length %d in params: %v", i, (call.Params), call.Params)
	}
	return call.Params[i]
}

func (call *ParsedCall) String() string {
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

func (call *ParsedCall) SimpleString() string {
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

func (svcCall *ParsedServiceCall) AddParam(param Variable) {
	svcCall.Params = append(svcCall.Params, param)
}

func (svcCall *ParsedServiceCall) AddReturn(ret Variable) {
	svcCall.Returns = append(svcCall.Returns, ret)
}

func (svcCall *ParsedServiceCall) GetParams() []Variable {
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

func (dbCall *ParsedDatabaseCall) AddParam(param Variable) {
	dbCall.Params = append(dbCall.Params, param)
}

func (dbCall *ParsedDatabaseCall) AddReturn(ret Variable) {
	dbCall.Returns = append(dbCall.Returns, ret)
}

func (dbCall *ParsedDatabaseCall) GetParams() []Variable {
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

func (internalCall *ParsedInternalCall) AddParam(param Variable) {
	internalCall.Params = append(internalCall.Params, param)
}

func (internalCall *ParsedInternalCall) AddReturn(ret Variable) {
	internalCall.Returns = append(internalCall.Returns, ret)
}

func (internalCall *ParsedInternalCall) GetParams() []Variable {
	return internalCall.Params
}

func (internalCall *ParsedInternalCall) GetMethod() Method {
	return internalCall.Method
}
