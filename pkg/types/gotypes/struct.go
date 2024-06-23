package gotypes

import (
	"analyzer/pkg/logger"
)

type StructType struct {
	Type       `json:"-"`
	FieldTypes []*FieldType
	Methods    []string
}

// ------------
// Type Methods
// ------------

func (t *StructType) IsSameType(other Type) bool {
	_, ok := other.(*StructType)
	return ok
}
func (t *StructType) String() string {
	if len(t.FieldTypes) == 0 {
		return "struct {}"
	}
	s := "struct {"
	i := 0
	for _, f := range t.FieldTypes {
		s += f.FieldName + " " + f.String()
		if i < len(t.FieldTypes)-1 {
			s += ", "
		}
		i++
	}
	s += "}"
	return s
}
func (t *StructType) MethodsString() string {
	s := "{"
	for i, m := range t.Methods {
		s += m
		if i < len(t.Methods) {
			s += ", "
		}
	}
	return s + "}"
}
func (t *StructType) LongString() string {
	if len(t.FieldTypes) == 0 {
		return "struct {}"
	}
	s := "struct {"
	i := 0
	for _, f := range t.FieldTypes {
		s += f.FieldName + " " + f.LongString()
		if i < len(t.FieldTypes)-1 {
			s += ", "
		}
		i++
	}
	s += "}"
	return s
}
func (t *StructType) GetName() string {
	return t.String()
}
func (t *StructType) GetBasicValue() string {
	logger.Logger.Fatalf("[TYPES STRUCT] unable to get value for struct type %s", t.String())
	return ""
}
func (t *StructType) AddValue(value string) {
	logger.Logger.Fatalf("[TYPES STRUCT] unable to add value for struct type %s", t.String())
}
func (t *StructType) GetNestedFieldTypes(prefix string) ([]Type, []string) {
	var nestedTypes []Type
	var nestedIDs []string

	for _, f := range t.FieldTypes {
		nestedFieldTypes, nestedFieldIDs := f.GetNestedFieldTypes(prefix)
		nestedTypes = append(nestedTypes, nestedFieldTypes...)
		nestedIDs = append(nestedIDs, nestedFieldIDs...)
	}
	return nestedTypes, nestedIDs
}

// --------------
// Struct Methods
// --------------

func (t *StructType) GetFieldTypeByName(name string) *FieldType {
	for _, f := range t.FieldTypes {
		if f.FieldName == name {
			return f
		}
	}
	logger.Logger.Fatalf("[TYPES STRUCT] field %s not found for struct type %s", name, t.String())
	return nil
}

func (t *StructType) GetFieldTypeByNameIfExists(name string) *FieldType {
	for _, f := range t.FieldTypes {
		if f.FieldName == name {
			return f
		}
	}
	logger.Logger.Fatalf("[TYPES STRUCT] field %s not found for struct type %s", name, t.String())
	return nil
}

func (t *StructType) GetFieldTypeAt(index int) *FieldType {
	if index > len(t.FieldTypes)-1 {
		logger.Logger.Fatalf("[TYPES STRUCT] field at index %d not found for struct type %s", index, t.String())
	}
	return t.FieldTypes[index]
}

func (t *StructType) AddFieldType(field *FieldType) {
	t.FieldTypes = append(t.FieldTypes, field)
}

func (t *StructType) AddMethod(name string) {
	t.Methods = append(t.Methods, name)
}
