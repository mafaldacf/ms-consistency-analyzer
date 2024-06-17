package gotypes

import (
	"regexp"

	"analyzer/pkg/logger"
)

type StructType struct {
	Type       `json:"-"`
	FieldTypes map[string]Type
	FieldTags  map[string]string

	// order fields by index
	// FIXME: in the future, this should not be necessary if we have a new FieldType (also with annotations e.g. for json parsing)
	FieldNames []string
}

// ------------
// Type Methods
// ------------

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
func (t *StructType) getFieldJsonTag(field string) string {
	if tag, ok := t.FieldTags[field]; ok {
		re := regexp.MustCompile(`json:"([^"]+)"`)
		matches := re.FindStringSubmatch(tag)
		if len(matches) >= 2 {
			return matches[1]
		}
	}
	return ""
}
func (t *StructType) GetNestedTypes(prefix string) ([]Type, []string) {
	var types []Type
	var ids []string

	for _, name := range t.FieldNames {
		field := t.FieldTypes[name]

		fieldPrefix := prefix + "." + name
		if tag := t.getFieldJsonTag(name); tag != "" {
			fieldPrefix = prefix + "." + tag
		}

		ids = append(ids, fieldPrefix)
		types = append(types, field)

		r1, r2 := field.GetNestedTypes(fieldPrefix)
		types = append(types, r1...)
		ids = append(ids, r2...)
	}
	return types, ids
}

// --------------
// Struct Methods
// --------------
