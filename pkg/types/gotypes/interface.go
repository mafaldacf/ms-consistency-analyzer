package gotypes

import (
	"fmt"

	"analyzer/pkg/logger"
)

type InterfaceType struct {
	Type    `json:"-"`
	Content string
}

// ------------
// Type Methods
// ------------

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

// -----------------
// Interface Methods
// -----------------
