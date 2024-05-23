package types

import (
	"fmt"
	"strings"
)

type Type interface {
	String() string
	GetName() string
}

type Service struct {
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
type StructType struct {
	Type   `json:"-"`
	Name   string
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
func (t *Service) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *Service) GetName() string {
	return t.Name
}
// User
func (t *UserType) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *UserType) GetName() string {
	return t.Name
}
// Pointer
func (t *PointerType) String() string {
	return fmt.Sprintf("*%s", t.PointerTo)
}
// Address
func (t *AddressType) String() string {
	return fmt.Sprintf("&%s", t.AddressOf)
}
// Basic
func (t *BasicType) String() string {
	if t.Value != "" {
		return fmt.Sprintf("%s (%s)", t.Name, t.Value)
	}
	return t.Name
}
// Array
func (t *ArrayType) String() string {
	return "[]" + t.ElementsType.String()
}
// Map
func (t *MapType) String() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.String(), t.ValueType.String())
}
// Chan
func (t *ChanType) String() string {
	return fmt.Sprintf("chan %s", t.ChanType.String())
}
// Struct
func (t *StructType) String() string {
	if t.Name != "" {
		return fmt.Sprintf("struct (%s)", t.Name)
	}
	return "struct"
}
// Generic
func (t *GenericType) String() string {
	if t.Name != "" {
		return fmt.Sprintf("generic (%s)", t.Name)
	}
	return "undefined"
}
// Interface
func (t *InterfaceType) String() string {
	return "interface{}"
}
