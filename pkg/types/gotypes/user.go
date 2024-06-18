package gotypes

import (
	"fmt"
)

type UserType struct {
	Type     `json:"-"`
	UserType Type
	Package  string
	Name     string
}

func (t *UserType) String() string {
	if t.UserType != nil {
		return fmt.Sprintf("%s.%s %s", packageAlias(t.Package), t.Name, t.UserType.String())
	}
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *UserType) FullString() string {
	if t.UserType != nil {
		return fmt.Sprintf("%s.%s %s", packageAlias(t.Package), t.Name, t.UserType.FullString())
	}
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *UserType) GetName() string {
	return t.Name
}
func (t *UserType) GetPackage() string {
	return t.Package
}
func (t *UserType) GetBasicValue() string {
	return t.UserType.GetBasicValue()
}
func (t *UserType) GetNestedFieldTypes(prefix string) ([]Type, []string) {
	return t.UserType.GetNestedFieldTypes(prefix)
}

// ------------
// Type Methods
// ------------

// ------------
// User Methods
// ------------
