package gotypes

import (
	"fmt"

	"analyzer/pkg/logger"
)

type InterfaceType struct {
	Type           `json:"-"`
	Content        string
	ParentUserType *UserType
	Methods        map[string]string // maps method name to package path
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
	i := 0
	for m := range t.Methods {
		s += m
		if i < len(t.Methods) {
			s += ", "
		}
		i++
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
func (t *InterfaceType) GetParentUserType() *UserType {
	return t.ParentUserType
}
func (t *InterfaceType) SetParentUserType(userType *UserType) {
	t.ParentUserType = userType
}

// -----------------
// Interface Methods
// -----------------

func (t *InterfaceType) AddMethod(name string, pkgPath string) {
	t.Methods[name] = pkgPath
}

func (v *InterfaceType) GetMethodPackagePath(method string) string {
	if pkgPath, ok := v.Methods[method]; ok {
		logger.Logger.Debugf("getting method (%s) for pkg path (%s)", method, pkgPath)
		return pkgPath
	}
	logger.Logger.Fatalf("unknown method (%s) for struct type (%s)", method, v.LongString())
	return ""
}
