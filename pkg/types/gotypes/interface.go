package gotypes

import (
	"fmt"

	"analyzer/pkg/logger"
)


type InterfaceType struct {
	Type    `json:"-"`
	Content string
	Methods []string
}

// ------------
// Type Methods
// ------------

func (t *InterfaceType) IsSameType(other Type) bool {
	_, ok := other.(*InterfaceType)
	return ok
}
func (t *InterfaceType) String() string {
	if t.Content != "" {
		return fmt.Sprintf("interface{ %s }", t.Content)
	}
	return "interface{}"
}
func (t *InterfaceType) LongString() string {
	s := "interface{"
	for i, m := range t.Methods {
		s += m
		if i < len(t.Methods) {
			s += ", "
		}
	}
	return s + "}"
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

// -----------------
// Interface Methods
// -----------------

func (t *InterfaceType) AddMethod(name string) {
	t.Methods = append(t.Methods, name)
}
