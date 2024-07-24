package utils

import (
	"reflect"
	"runtime"
	"slices"

	"analyzer/pkg/logger"
)

var builtInTypes = []string{
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

var builtInConsts = []string{"true", "false"}
var builtInFuncs = []string{"make", "println", "append", "len"}

func GetType(node interface{}) string {
	if node == nil {
		pc, file, line, ok := runtime.Caller(1)
		if !ok {
			logger.Logger.Fatal("[UTILS TYPE] INVALID TYPE FOR <nil> and unable to retrieve caller information")
		}
		callerFunc := runtime.FuncForPC(pc).Name()
		logger.Logger.Fatalf("[UTILS TYPE] INVALID TYPE FOR <nil> (caller: %s) \n\t\t\t\t\t %s:%d", callerFunc, file, line)
	}
	return reflect.TypeOf(node).Elem().Name()
}

func IsType[T any](obj interface{}) bool {
	_, ok := obj.(T)
	return ok
}

func IsBuiltInGoTypeOrFunc(name string) bool {
	return IsBuiltInGoFunc(name) || IsBuiltInGoType(name)
}

func IsBuiltInGoFunc(name string) bool {
	return slices.Contains(builtInFuncs, name)
}

func IsBuiltInGoType(name string) bool {
	return slices.Contains(builtInTypes, name)
}

func IsBuiltInConstValue(name string) bool {
	return slices.Contains(builtInConsts, name)
}

func GetBuiltInConstTypeName(name string) string {
	switch name {
	case "true":
		return "bool"
	case "false":
		return "bool"
	default:
		logger.Logger.Fatalf("[UTILS] unknown built in const type/value for name (%s)", name)
	}
	return ""
}
