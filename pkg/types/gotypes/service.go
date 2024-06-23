package gotypes

import (
	"fmt"

	"analyzer/pkg/logger"
)

type ServiceType struct {
	Type       `json:"-"`
	Package    string
	Name       string
	Methods    []string
}

// ------------
// Type Methods
// ------------

func (t *ServiceType) IsSameType(other Type) bool {
	_, ok := other.(*ServiceType)
	return ok
}
func (t *ServiceType) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *ServiceType) LongString() string {
	return t.String()
}
func (t *ServiceType) GetName() string {
	return t.Name
}
func (t *ServiceType) GetPackage() string {
	return t.Package
}
func (t *ServiceType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for service type %s", t.String())
	return ""
}
func (t *ServiceType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for service type %s", t.String())
}

// ---------------
// Service Methods
// ---------------
