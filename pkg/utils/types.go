package utils

import (
	"go/ast"
	"reflect"
	"slices"
	"strings"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

var basicTypes = []string {
	"bool",
	"string",
	"int", "int8", "int16", "int32", "int64",
	"uint", "uint8", "uint16", "uint32", "uint64",
	"byte",
	"rune",
	"float32", "float64",
	"complex64", "complex128",
	"error",
}

func GetNodeType(node ast.Node) string {
	return reflect.TypeOf(node).Elem().Name()
}

func IsBasicType(t string) bool {
	return slices.Contains(basicTypes, t)
}

// GetShortTypeStr removes the package (e.g. backend.) from the type
func GetShortTypeStr(typeName gocode.TypeName) string {
	typeNameStr := typeName.String()
	splits := strings.Split(typeNameStr, ".")
	if len(splits) > 0 {
		return splits[len(splits)-1]
	}
	return typeNameStr
}
