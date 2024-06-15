package types

import (
	"fmt"
	"strings"
)

type Type interface {
	String() string
	FullString() string
	GetName() string
	// only fore UserType, ServiceType, and DatastoreType
	GetPackage() string
}

// NOTE: package is always the real package path

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
type FuncType struct {
	Type     `json:"-"`
	Name 		string
	Package 	string
	SignatureType *SignatureType
}
type SignatureType struct {
	Type     `json:"-"`
	ReturnTypes []Type
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
type TupleType struct {
	Type `json:"-"`
	Types []Type
}
type InterfaceType struct {
	Type `json:"-"`
	Content string
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
func (t *ServiceType) FullString() string {
	return t.String()
}
func (t *ServiceType) GetName() string {
	return t.Name
}
func (t *ServiceType) GetPackage() string {
	return t.Package
}
// User
func (t *UserType) String() string {
	if t.UserType != nil {
		return fmt.Sprintf("%s.%s %s", packageAlias(t.Package), t.Name, t.UserType.String())
	}
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *UserType) FullString() string {
	if t.UserType != nil {
		return fmt.Sprintf("%s.%s %s", packageAlias(t.Package), t.Name, t.UserType.FullString())
	}
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *UserType) GetName() string {
	return t.Name
}
func (t *UserType) GetPackage() string {
	return t.Package
}
// FuncType
func (t *FuncType) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *FuncType) FullString() string {
	return fmt.Sprintf("%s.%s (...) %s", packageAlias(t.Package), t.Name, t.SignatureType.String())
}
func (t *FuncType) GetName() string {
	return t.Name
}
func (t *FuncType) GetPackage() string {
	return t.Package
}
// SignatureType
func (t *SignatureType) String() string {
	if len(t.ReturnTypes) == 0 {
		return ""
	}
	if len(t.ReturnTypes) == 1 {
		return t.ReturnTypes[0].FullString()
	}
	s := "( "
	for i, ft := range t.ReturnTypes {
		s += ft.FullString()
		if i < len(t.ReturnTypes) - 1 {
			s += ", "
		}
	}
	s += " )"
	return s
}
func (t *SignatureType) FullString() string {
	return t.String()
}
func (t *SignatureType) GetName() string {
	return ""
}
func (t *SignatureType) GetPackage() string {
	return ""
}
func (t *SignatureType) GetReturns() []Type {
	return t.ReturnTypes
}
// Imported
func (t *ImportedType) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *ImportedType) FullString() string {
	return t.String()
}
func (t *ImportedType) GetName() string {
	return t.Name
}
// Pointer
func (t *PointerType) String() string {
	return fmt.Sprintf("*%s", t.PointerTo.String())
}
func (t *PointerType) FullString() string {
	return fmt.Sprintf("*%s", t.PointerTo.FullString())
}
func (t *PointerType) GetName() string {
	return t.String()
}
// Address
func (t *AddressType) String() string {
	return fmt.Sprintf("&%s", t.AddressOf.String())
}
func (t *AddressType) FullString() string {
	return fmt.Sprintf("&%s", t.AddressOf.FullString())
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
func (t *BasicType) FullString() string {
	return t.String()
}
func (t *BasicType) GetName() string {
	return t.Value
}
// Tuple
func (t *TupleType) String() string {
	return ""
}
func (t *TupleType) FullString() string {
	return ""
}
func (t *TupleType) GetName() string {
	return ""
}
func (t *TupleType) GetTypes() []Type {
	return t.Types
}
// Array
func (t *ArrayType) String() string {
	return "[]" + t.ElementsType.String()
}
func (t *ArrayType) FullString() string {
	return "[]" + t.ElementsType.FullString()
}
func (t *ArrayType) GetName() string {
	return t.String()
}
// Map
func (t *MapType) String() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.String(), t.ValueType.String())
}
func (t *MapType) FullString() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.FullString(), t.ValueType.FullString())
}
func (t *MapType) GetName() string {
	return t.String()
}
// Chan
func (t *ChanType) String() string {
	return fmt.Sprintf("chan %s", t.ChanType.String())
}
func (t *ChanType) FullString() string {
	return fmt.Sprintf("chan %s", t.ChanType.FullString())
}
func (t *ChanType) GetName() string {
	return t.String()
}
// Struct
func (t *StructType) String() string {
	return "struct"
}
func (t *StructType) FullString() string {
	s := "struct { "
	i := 0
	for name, ft := range t.FieldTypes {
		s += name + " " + ft.FullString()
		if i < len(t.FieldTypes) - 1 {
			s += ", "
		}
		i++
	}
	s += " }"
	return s
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
func (t *GenericType) FullString() string {
	return t.String()
}
func (t *GenericType) GetName() string {
	return t.String()
}
// Interface
func (t *InterfaceType) String() string {
	if t.Content != "" {
		return fmt.Sprintf("interface{ %s }", t.Content)
	}
	return "interface{}"
}
func (t *InterfaceType) FullString() string {
	return t.String()
}
func (t *InterfaceType) GetName() string {
	return t.String()
}
