package gotypes

import "strings"

type Type interface {
	String() string
	LongString() string
	GetName() string
	GetLongName() string
	GetPackage() string // package is always the real package path
	GetBasicValue() string
	AddValue(value string)
	GetNestedFieldTypes(prefix string) ([]Type, []string)
	GetLongFieldName() string
	GetParentUserType() *UserType
	SetParentUserType(userType *UserType)
	IsSameType(t Type) bool
}

func packageAlias(pkg string) string {
	splits := strings.Split(pkg, "/")
	return splits[len(splits)-1]
}
