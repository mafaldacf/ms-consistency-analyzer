package types

import (
	"analyzer/pkg/datastores"
	"fmt"
	"go/ast"
)

type Field interface {
	String() string
	GetName() string
	GetType() Type
	SetType(t Type)
	GetTypeString() string
	GetTypeName() string
	GetIndex() int
}

type FieldInfo struct {
	Ast  *ast.Field
	Name string
	Type Type
}

type FunctionParameter struct {
	Field
	FieldInfo FieldInfo
}
type GenericField struct {
	Field
	Idx       int
	FieldInfo FieldInfo
}
type ServiceField struct {
	Field
	FieldInfo FieldInfo
	Idx       int
}
type DatabaseField struct {
	Field
	FieldInfo  FieldInfo
	IsQueue    bool
	DbInstance datastores.DatabaseInstance
	Idx        int
}

// -------------
// GENERIC FIELD
// -------------
func (f *GenericField) String() string {
	return fmt.Sprintf("%s %s", f.FieldInfo.Name, f.FieldInfo.Type.String())
}
func (f *GenericField) GetTypeString() string {
	return f.FieldInfo.Type.String()
}
func (f *GenericField) GetIndex() int {
	return f.Idx
}
func (f *GenericField) GetName() string {
	return f.FieldInfo.Name
}
func (f *GenericField) GetType() Type {
	return f.FieldInfo.Type
}
func (f *GenericField) GetTypeName() string {
	return f.FieldInfo.Type.GetName()
}
func (f *GenericField) SetType(t Type) {
	f.FieldInfo.Type = t
}

// -------------
// SERVICE FIELD
// -------------
func (f *ServiceField) String() string {
	return fmt.Sprintf("%s %s", f.FieldInfo.Name, f.FieldInfo.Type.String())
}
func (f *ServiceField) GetTypeString() string {
	return f.FieldInfo.Type.String()
}
func (f *ServiceField) GetTypeName() string {
	return f.FieldInfo.Type.GetName()
}
func (f *ServiceField) GetIndex() int {
	return f.Idx
}
func (f *ServiceField) GetName() string {
	return f.FieldInfo.Name
}
func (f *ServiceField) GetType() Type {
	return f.FieldInfo.Type
}
func (f *ServiceField) SetType(t Type) {
	f.FieldInfo.Type = t
}

// --------------
// DATABASE FIELD
// --------------
func (f *DatabaseField) String() string {
	return fmt.Sprintf("%s %s", f.FieldInfo.Name, f.FieldInfo.Type.String())
}
func (f *DatabaseField) GetTypeString() string {
	return f.FieldInfo.Type.String()
}
func (f *DatabaseField) GetTypeName() string {
	return f.FieldInfo.Type.GetName()
}
func (f *DatabaseField) GetIndex() int {
	return f.Idx
}
func (f *DatabaseField) GetName() string {
	return f.FieldInfo.Name
}
func (f *DatabaseField) GetType() Type {
	return f.FieldInfo.Type
}
func (f *DatabaseField) SetType(t Type) {
	f.FieldInfo.Type = t
}

// ------------------
// FUNCTION PARAMETER
// ------------------
func (f *FunctionParameter) String() string {
	return fmt.Sprintf("%s %s", f.FieldInfo.Name, f.FieldInfo.Type.String())
}
func (f *FunctionParameter) GetTypeString() string {
	return f.FieldInfo.Type.String()
}
func (f *FunctionParameter) GetTypeName() string {
	return f.FieldInfo.Type.GetName()
}
func (f *FunctionParameter) GetIndex() int {
	return -1
}
func (f *FunctionParameter) GetName() string {
	return f.FieldInfo.Name
}
func (f *FunctionParameter) GetType() Type {
	return f.FieldInfo.Type
}
func (f *FunctionParameter) SetType(t Type) {
	f.FieldInfo.Type = t
}
