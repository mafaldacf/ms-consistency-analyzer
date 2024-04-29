package utils

import (
	"go/ast"
	"reflect"
)

func GetNodeType(node ast.Node) string {
	return reflect.TypeOf(node).Elem().Name()
}
