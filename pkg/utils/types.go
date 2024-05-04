package utils

import (
	"go/ast"
	"reflect"
	"slices"
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
