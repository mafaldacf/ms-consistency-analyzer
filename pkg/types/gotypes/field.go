package gotypes

import (
	"fmt"
	"regexp"

	"analyzer/pkg/logger"
)

// A FieldType represents a function parameter and results, and struct fields
type FieldType struct {
	Type          `json:"-"`
	Origin        Type
	SubType       Type
	StructField   bool
	Embedded      bool   // if set, the SubType is an embedded struct field
	FieldName     string // set if is struct field
	FieldLongName string
	FieldTag      string // set if is struct field
}

// ------------
// Type Methods
// ------------

func (t *FieldType) String() string {
	return t.SubType.String()
}
func (t *FieldType) FullString() string {
	return t.SubType.FullString()
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
func (t *FieldType) GetNestedFieldTypes(prefix string) ([]Type, []string) {
	/* if tag := t.GetTagJSON(); tag != "" {
		prefix = prefix + "." + tag
	} else {
		prefix = prefix + "." + t.FieldName
	} */
	prefix = prefix + "." + t.FieldName
	nestedTypes := []Type{t}
	nestedNames := []string{prefix}
	nestedFieldTypes, nestedFieldNames := t.SubType.GetNestedFieldTypes(prefix)
	nestedTypes = append(nestedTypes, nestedFieldTypes...)
	nestedNames = append(nestedNames, nestedFieldNames...)
	return nestedTypes, nestedNames
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
func (t *FieldType) SetEmbedded() {
	t.Embedded = true
}
func (t *FieldType) GetFieldName() string {
	return t.FieldName
}
func (t *FieldType) GetTagValue(key string) string {
	pattern := fmt.Sprintf(`%s:"([^"]+)"`, key)
	re := regexp.MustCompile(pattern)
	matches := re.FindStringSubmatch(t.FieldName)
	if len(matches) >= 2 {
		return matches[1]
	}
	return ""
}
func (t *FieldType) GetTagJSON() string {
	return t.GetTagValue("json")
}
