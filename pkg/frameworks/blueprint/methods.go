package frameworks

import (
	"analyzer/pkg/types"
	"fmt"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

func IsBlueprintBackend(name string) bool {
	switch name {
	case "Queue", "NoSQLDatabase", "Cache":
		return true
	}
	return false
}

func IsBlueprintBackendQueue(name string) bool {
	return name == "Queue"
}

type BlueprintBackend struct {
	types.Method
	Name    string 
	Params  []*types.FunctionField
	Returns []*types.FunctionField
	Write 	 bool
}

func (b *BlueprintBackend) String() string {
	repr := fmt.Sprintf("%s(", b.Name)
	for i, param := range b.Params {
		repr += param.GetName()
		if i < len(b.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	return repr
}

func (b *BlueprintBackend) GetParams() []*types.FunctionField {
	return b.Params
}

func (b *BlueprintBackend) GetReturns() []*types.FunctionField {
	return b.Returns
}

func (b *BlueprintBackend) IsWrite() bool {
	return b.Write
}

func (b *BlueprintBackend) IsQueuePop() bool {
	return !b.Write && b.Name == "Queue.Pop"
}

func (b *BlueprintBackend) IsQueuePush() bool {
	return b.Write && b.Name == "Queue.Push"
}

func GetBackendMethod(name string) *BlueprintBackend {
	switch name {
		case "Cache.Put":
			return &BlueprintBackend{Name: name, Write: true, Params:[]*types.FunctionField{&ctxParam, &keyParam, &valueParam}}
		case "Cache.Get":
			return &BlueprintBackend{Name: name, Write: false, Params:[]*types.FunctionField{&ctxParam, &keyParam, &valueParam}}
		case "Queue.Push":
			return &BlueprintBackend{Name: name, Write: true, Params:[]*types.FunctionField{&ctxParam, &itemParam}}
		case "Queue.Pop":
			return &BlueprintBackend{Name: name, Write: false, Params:[]*types.FunctionField{&ctxParam, &itemParam}}
	}
	return nil
}

var ctxParam = types.FunctionField {
	Variable: gocode.Variable{
		Name: "ctx",
		Type: &gocode.UserType{
			Name: "Context",
			Package: "context",
		},
	},
	Lineno: 0,
	Ast:    nil,
}

var keyParam = types.FunctionField {
	Variable: gocode.Variable{
		Name: "key",
		Type: &gocode.BasicType{
			Name: "string",
		},
	},
	Lineno: 0,
	Ast:    nil,
}

var valueParam = types.FunctionField {
	Variable: gocode.Variable{
		Name: "value",
		Type: &gocode.InterfaceType{},
	},
	Lineno: 0,
	Ast:    nil,
}

var itemParam = types.FunctionField {
	Variable: gocode.Variable{
		Name: "item",
		Type: &gocode.InterfaceType{},
	},
	Lineno: 0,
	Ast:    nil,
}
