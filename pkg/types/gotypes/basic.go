package gotypes

import "fmt"

type BasicType struct {
	Type  `json:"-"`
	Name  string
	Value string
}

// ------------
// Type Methods
// ------------

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
func (t *BasicType) GetNestedFieldTypes(prefix string) ([]Type, []string) {
	return nil, nil
}

// -------------
// Basic Methods
// -------------
