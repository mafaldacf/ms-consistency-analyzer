package types

import (
	"fmt"
	"strings"
)

type Type interface {
	String() string
	GetName() string
}

type ServiceType struct {
	Type    `json:"-"`
	Package string
	Name    string
}
type UserType struct {
	Type     `json:"-"`
	UserType Type
	Package string
	Name    string
}
type ImportedType struct {
	Type     `json:"-"`
	Package string
	Name    string
}
type StructType struct {
	Type   		`json:"-"`
	FieldTypes 	map[string]Type
}
type MapType struct {
	Type   `json:"-"`
	KeyType 	Type
	ValueType 	Type
}
type ChanType struct {
	Type   `json:"-"`
	ChanType   Type
}
type ArrayType struct {
	Type   			`json:"-"`
	ElementsType  	Type
}
type BasicType struct {
	Type `json:"-"`
	Name 	string
	Value 	string
}
type InterfaceType struct {
	Type `json:"-"`
}
type GenericType struct {
	Type `json:"-"`
	Name  string
}
type PointerType struct {
	Type      `json:"-"`
	PointerTo Type
}
type AddressType struct {
	Type      `json:"-"`
	AddressOf Type
}

func packageAlias(pkg string) string {
	splits := strings.Split(pkg, "/")
	return splits[len(splits)-1]
}

// Service
func (t *ServiceType) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *ServiceType) GetName() string {
	return t.Name
}
// User
func (t *UserType) String() string {
	/* if t.UserType != nil {
		return fmt.Sprintf("%s %s.%s", t.UserType.String(), packageAlias(t.Package), t.Name)
	} */
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *UserType) GetName() string {
	return t.Name
}
// Imported
func (t *ImportedType) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *ImportedType) GetName() string {
	return t.Name
}
// Pointer
func (t *PointerType) String() string {
	return fmt.Sprintf("*%s", t.PointerTo)
}
func (t *PointerType) GetName() string {
	return t.String()
}
// Address
func (t *AddressType) String() string {
	return fmt.Sprintf("&%s", t.AddressOf)
}
func (t *AddressType) GetName() string {
	return t.String()
}
// Basic
func (t *BasicType) String() string {
	if t.Value != "" {
		return fmt.Sprintf("%s (%s)", t.Name, t.Value)
	}
	return t.Name
}
func (t *BasicType) GetName() string {
	return t.Value
}
// Array
func (t *ArrayType) String() string {
	return "[]" + t.ElementsType.String()
}
func (t *ArrayType) GetName() string {
	return t.String()
}
// Map
func (t *MapType) String() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.String(), t.ValueType.String())
}
func (t *MapType) GetName() string {
	return t.String()
}
// Chan
func (t *ChanType) String() string {
	return fmt.Sprintf("chan %s", t.ChanType.String())
}
func (t *ChanType) GetName() string {
	return t.String()
}
// Struct
func (t *StructType) String() string {
	return "struct"
}
func (t *StructType) GetName() string {
	return t.String()
}
// Generic
func (t *GenericType) String() string {
	/* if t.Name != "" {
		return t.Name
	} */
	return "undefined"
}
func (t *GenericType) GetName() string {
	return t.String()
}
// Interface
func (t *InterfaceType) String() string {
	return "interface{}"
}
func (t *InterfaceType) GetName() string {
	return t.String()
}
