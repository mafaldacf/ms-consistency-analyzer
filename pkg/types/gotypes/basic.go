package gotypes

import (
	"fmt"
	"strings"
)

type BasicType struct {
	Type  `json:"-"`
	Name  string
	Value string
}

// ------------
// Type Methods
// ------------

func (t *BasicType) IsSameType(other Type) bool {
	_, ok := other.(*BasicType)
	return ok
}
func (t *BasicType) String() string {
	if t.Value != "" {
		return fmt.Sprintf("%s %s", t.Value, t.Name)
	}
	return t.Name
}
func (t *BasicType) LongString() string {
	return t.String()
}
func (t *BasicType) GetName() string {
	return t.Name
}
func (t *BasicType) GetBasicValue() string {
	// remove double quotes " " if they exist
	value := t.Value
	if strings.HasPrefix(value, "\"") && strings.HasSuffix(value, "\"") {
		value = value[1 : len(value)-1]
	}
	return value
}

func (t *BasicType) AddValue(value string) {
	if t.Value == "" {
		t.Value = value
	} else {
		t.Value += value
	}
}
func (t *BasicType) GetNestedFieldTypes(prefix string) ([]Type, []string) {
	return nil, nil
}

// -------------
// Basic Methods
// -------------
