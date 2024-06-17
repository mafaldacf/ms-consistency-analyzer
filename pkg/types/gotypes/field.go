package gotypes

import (
	"fmt"

	"analyzer/pkg/logger"
)

// A FieldType represents a function parameter and results, and struct fields
type FieldType struct {
	Type        `json:"-"`
	Origin      Type
	SubType     Type
	StructField bool
	Embedded    bool   // if set, the SubType is an embedded struct field
	FieldName   string // set if is struct field
	FieldTag    string // set if is struct field
}

// ------------
// Type Methods
// ------------

func (t *FieldType) String() string {
	return t.SubType.String()
}
func (t *FieldType) FullString() string {
    if t.FieldName != "" {
        return fmt.Sprintf("%s %s", t.FieldName, t.SubType.String())
    }
    return t.SubType.String()
}
func (t *FieldType) GetName() string {
	return t.SubType.GetName()
}
func (t *FieldType) GetPackage() string {
	logger.Logger.Fatalf("unable to get package for field type %s", t.String())
	return ""
}
func (t *FieldType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for field type %s", t.String())
	return ""
}
func (t *FieldType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for field type %s", t.String())
}

// -------------
// Field Methods
// -------------

func (t *FieldType) GetOrigin() Type {
	return t.Origin
}
func (t *FieldType) GetSubType() Type {
	return t.SubType
}
func (t *FieldType) IsStructField() bool {
	return t.StructField
}
func (t *FieldType) IsEmbedded() bool {
	return t.Embedded
}
func (t *FieldType) GetFieldName() string {
	return t.FieldName
}
func (t *FieldType) GetFieldTag() string {
	return t.FieldTag
}
