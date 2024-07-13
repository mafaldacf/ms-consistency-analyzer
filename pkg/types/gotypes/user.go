package gotypes

import (
	"fmt"
	"slices"

	"analyzer/pkg/logger"
)

type UserType struct {
	Type     `json:"-"`
	UserType Type
	Package  string
	Name     string
}

func (t *UserType) skipUnderlyingTypeString() bool {
	var packagesToSkip = []string{
		"", // built-in
		"context", 
		"sync", 
		"sync/atomic", 
		"go.mongodb.org/mongo-driver/bson/primitive",

	}
	// skip long strings for built-in or other package types otherwise it gets too complex
	return slices.Contains(packagesToSkip, t.Package)
}

func (t *UserType) IsSameType(other Type) bool {
	_, ok := other.(*UserType)
	return ok
}
func (t *UserType) String() string {
	if t.UserType != nil && !t.skipUnderlyingTypeString() {
		return fmt.Sprintf("%s.%s %s", packageAlias(t.Package), t.Name, t.UserType.String())
	}
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}

func (t *UserType) LongString() string {
	if t.UserType != nil && !t.skipUnderlyingTypeString() {
		return fmt.Sprintf("%s.%s %s", packageAlias(t.Package), t.Name, t.UserType.LongString())
	}
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *UserType) GetName() string {
	return t.Name
}
func (t *UserType) GetLongName() string {
	return t.Package + "." + t.Name
}
func (t *UserType) GetPackage() string {
	return t.Package
}
func (t *UserType) GetBasicValue() string {
	return t.UserType.GetBasicValue()
}
func (t *UserType) GetNestedFieldTypes(prefix string) ([]Type, []string) {
	if t.UserType == nil {
		logger.Logger.Fatalf("[TYPES USER] unexpected nil underlying type for User Type %s.%s", t.Package, t.Name)
	}
	return t.UserType.GetNestedFieldTypes(prefix)
}

// ------------
// Type Methods
// ------------

// ------------
// User Methods
// ------------
