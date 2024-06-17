package gotypes

import "strings"

type Type interface {
	String() string
	FullString() string
	GetName() string
	GetPackage() string // package is always the real package path
	GetBasicValue() string
	AddValue(value string)
	GetNestedTypes(prefix string) ([]Type, []string)
}

func packageAlias(pkg string) string {
	splits := strings.Split(pkg, "/")
	return splits[len(splits)-1]
}
