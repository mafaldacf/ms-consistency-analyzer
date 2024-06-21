package gotypes

import (
	"analyzer/pkg/logger"
)

type StructType struct {
	Type       `json:"-"`
	FieldTypes []*FieldType
}

// ------------
// Type Methods
// ------------

func (t *StructType) String() string {
	return "struct"
}
func (t *StructType) LongString() string {
	if len(t.FieldTypes) == 0 {
		return "struct {}"
	}
	s := "struct { "
	i := 0
	// get by index order
	for _, f := range t.FieldTypes {
		s += f.FieldName + " " + f.LongString()
		/* if tag, ok := t.FieldTags[name]; ok {
			s += " `" + tag + "`"
		} */
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
	logger.Logger.Fatalf("field %s not found for struct type %s", name, t.String())
	return nil
}

func (t *StructType) GetFieldTypeAt(index int) *FieldType {
	if index > len(t.FieldTypes)-1 {
		logger.Logger.Fatalf("field at index %d not found for struct type %s", index, t.String())
	}
	return t.FieldTypes[index]
}

func (t *StructType) AddFieldType(field *FieldType) {
	t.FieldTypes = append(t.FieldTypes, field)
}
