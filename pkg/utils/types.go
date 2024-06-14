package utils

import (
	"reflect"
	"slices"
)

var basicTypes = []string{
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

func GetType(node interface{}) string {
	if node == nil {
		return "INVALID TYPE FOR <nil>"
	}
	return reflect.TypeOf(node).Elem().Name()
}

func IsBasicType(t string) bool {
	return slices.Contains(basicTypes, t)
}

func IsType[T any](obj interface{}) bool {
	_, ok := obj.(T)
	return ok
}
