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
	WrappedType   Type
	StructField   bool
	Embedded      bool   // if set, the WrappedType is an embedded struct field
	FieldName     string // set if is struct field
	FieldLongName string
	FieldTag      string // set if is struct field
}

// ------------
// Type Methods
// ------------

func (t *FieldType) IsSameType(other Type) bool {
	_, ok := other.(*FieldType)
	return ok
}
func (t *FieldType) SetOrigin(origin Type) {
	t.Origin = origin
}
func (t *FieldType) EnableStructField() {
	t.StructField = true
}
func (t *FieldType) EnableEmbedded() {
	t.Embedded = true
}
func (t *FieldType) String() string {
	if t.WrappedType == nil {
		logger.Logger.Fatalf("[TYPES FIELD] unexpected nil underlying type for Field Type %s", t.FieldName)
	}
	return t.WrappedType.String()
}
func (t *FieldType) LongString() string {
	if t.WrappedType == nil {
		logger.Logger.Fatalf("[TYPES FIELD] unexpected nil underlying type for Field Type %s", t.FieldName)
	}
	return t.WrappedType.LongString()
}
func (t *FieldType) GetName() string {
	if t.WrappedType == nil {
		logger.Logger.Fatalf("[TYPES FIELD] unexpected nil underlying type for Field Type %s", t.FieldName)
	}
	if t.StructField {
		return t.FieldName
	}
	return t.WrappedType.GetName()
}
func (t *FieldType) GetPackage() string {
	logger.Logger.Fatalf("unable to get package for field type %s", t.String())
	return ""
}
func (t *FieldType) GetBasicValue() string {
	return t.WrappedType.GetBasicValue()
}
func (t *FieldType) AddValue(value string) {
	t.WrappedType.AddValue(value)
}
func (t *FieldType) GetNestedFieldTypes(prefix string) ([]Type, []string) {
	if t.WrappedType == nil {
		logger.Logger.Fatalf("[TYPES FIELD] unexpected nil underlying type for Field Type %s", t.FieldName)
	}

	/* if tag := t.GetTagJSON(); tag != "" {
		prefix = prefix + "." + tag
	} else {
		prefix = prefix + "." + t.FieldName
	} */
	prefix = prefix + "." + t.FieldName
	nestedTypes := []Type{t}
	nestedNames := []string{prefix}
	nestedFieldTypes, nestedFieldNames := t.WrappedType.GetNestedFieldTypes(prefix)
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
func (t *FieldType) GetWrappedType() Type {
	if t.WrappedType == nil {
		logger.Logger.Fatalf("[TYPES FIELD] unexpected nil underlying type for Field Type %s", t.FieldName)
	}
	return t.WrappedType
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
