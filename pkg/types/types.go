package types

import (
	"fmt"
	"strings"

	"analyzer/pkg/logger"
)

type Type interface {
	String() string
	FullString() string
	GetName() string
	// only fore UserType, ServiceType, and DatastoreType
	GetPackage() string
	GetBasicValue() string
	AddValue(value string)
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
	Package  string
	Name     string
}
type SignatureType struct {
	Type        `json:"-"`
	ReturnTypes []Type
}
type StructType struct {
	Type       `json:"-"`
	FieldTypes map[string]Type

	// order fields by index
	// FIXME: in the future, this should not be necessary if we have a new FieldType (also with annotations e.g. for json parsing)
	FieldNames []string
}
type MapType struct {
	Type      `json:"-"`
	KeyType   Type
	ValueType Type
}
type ChanType struct {
	Type     `json:"-"`
	ChanType Type
}
type ArrayType struct {
	Type         `json:"-"`
	ElementsType Type
}
type BasicType struct {
	Type  `json:"-"`
	Name  string
	Value string
}
type TupleType struct {
	Type  `json:"-"`
	Types []Type
}
type InterfaceType struct {
	Type    `json:"-"`
	Content string
}
type GenericType struct {
	Type `json:"-"`
	Name string
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

// -------
// Service
// -------
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
func (t *ServiceType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for service type %s", t.String())
	return ""
}
func (t *ServiceType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for service type %s", t.String())
}

// ----
// User
// ----
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
func (t *UserType) GetBasicValue() string {
	return t.UserType.GetBasicValue()
}

// -------------
// SignatureType
// -------------
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
		if i < len(t.ReturnTypes)-1 {
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
func (t *SignatureType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for signature type %s", t.String())
	return ""
}
func (t *SignatureType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for signature type %s", t.String())
}

// -------
// Pointer
// -------
func (t *PointerType) String() string {
	return fmt.Sprintf("*%s", t.PointerTo.String())
}
func (t *PointerType) FullString() string {
	return fmt.Sprintf("*%s", t.PointerTo.FullString())
}
func (t *PointerType) GetName() string {
	return t.String()
}
func (t *PointerType) GetBasicValue() string {
	return t.PointerTo.GetBasicValue()
}
func (t *PointerType) AddValue(value string) {
	t.PointerTo.AddValue(value)
}

// -------
// Address
// -------
func (t *AddressType) String() string {
	return fmt.Sprintf("&%s", t.AddressOf.String())
}
func (t *AddressType) FullString() string {
	return fmt.Sprintf("&%s", t.AddressOf.FullString())
}
func (t *AddressType) GetName() string {
	return t.String()
}
func (t *AddressType) GetBasicValue() string {
	return t.AddressOf.GetBasicValue()
}
func (t *AddressType) AddValue(value string) {
	t.AddressOf.AddValue(value)
}

// -----
// Basic
// -----
func (t *BasicType) String() string {
	if t.Value != "" {
		return fmt.Sprintf("%s %s", t.Value, t.Name)
	}
	return t.Name
}
func (t *BasicType) FullString() string {
	return t.String()
}
func (t *BasicType) GetName() string {
	return t.String()
}
func (t *BasicType) GetBasicValue() string {
	return t.Value
}
func (t *BasicType) AddValue(value string) {
	t.Value = value
}

// -----
// Tuple
// -----
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
func (t *TupleType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for tuple type %s", t.String())
	return ""
}
func (t *TupleType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for tuple type %s", t.String())
}

// -----
// Array
// -----
func (t *ArrayType) String() string {
	return "[]" + t.ElementsType.String()
}
func (t *ArrayType) FullString() string {
	return "[]" + t.ElementsType.FullString()
}
func (t *ArrayType) GetName() string {
	return t.String()
}
func (t *ArrayType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for array type %s", t.String())
	return ""
}
func (t *ArrayType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for array type %s", t.String())
}

// ---
// Map
// ---
func (t *MapType) String() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.String(), t.ValueType.String())
}
func (t *MapType) FullString() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.FullString(), t.ValueType.FullString())
}
func (t *MapType) GetName() string {
	return t.String()
}
func (t *MapType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for map type %s", t.String())
	return ""
}
func (t *MapType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for map type %s", t.String())
}

// ----
// Chan
// ----
func (t *ChanType) String() string {
	return fmt.Sprintf("chan %s", t.ChanType.String())
}
func (t *ChanType) FullString() string {
	return fmt.Sprintf("chan %s", t.ChanType.FullString())
}
func (t *ChanType) GetName() string {
	return t.String()
}
func (t *ChanType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for chan type %s", t.String())
	return ""
}
func (t *ChanType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for chan type %s", t.String())
}

// ------
// Struct
// ------
func (t *StructType) String() string {
	return "struct"
}
func (t *StructType) FullString() string {
	if len(t.FieldNames) == 0 {
		return "struct {}"
	}
	s := "struct { "
	i := 0
	// get by index order
	for _, name := range t.FieldNames {
		field := t.FieldTypes[name]
		if field == nil {
			logger.Logger.Warnf("unexpected nil field %s for structure with types list %v and field names %v", name, t.FieldTypes, t.FieldNames)
			continue
		}
		s += name + " " + field.FullString()
		if i < len(t.FieldTypes)-1 {
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
func (t *StructType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for struct type %s", t.String())
	return ""
}
func (t *StructType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for struct type %s", t.String())
}

// -------
// Generic
// -------
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
func (t *GenericType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for generic type %s", t.String())
	return ""
}
func (t *GenericType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for generic type %s", t.String())
}

// ---------
// Interface
// ---------
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
func (t *InterfaceType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for interface type %s", t.String())
	return ""
}
func (t *InterfaceType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for interface type %s", t.String())
}
