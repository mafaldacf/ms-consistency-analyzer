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

func GetBackendMethod(name string) *BlueprintBackend {
	if name == "Cache.Put" {
		return &BlueprintBackend{
			Name: name,
			Params: []*types.FunctionField{
				{
					Variable: gocode.Variable{
						Name: "key",
						Type: &gocode.BasicType{
							Name: "string",
						},
					},
					Lineno: 0,
					Ast:    nil,
				},
				{
					Variable: gocode.Variable{
						Name: "value",
						Type: &gocode.InterfaceType{},
					},
					Lineno: 0,
					Ast:    nil,
				},
			},
		}
	}
	if name == "Cache.Get" {
		return &BlueprintBackend{
			Name: name,
			Params: []*types.FunctionField{
				{
					Variable: gocode.Variable{
						Name: "key",
						Type: &gocode.BasicType{
							Name: "string",
						},
					},
					Lineno: 0,
					Ast:    nil,
				},
				{
					Variable: gocode.Variable{
						Name: "val",
						Type: &gocode.InterfaceType{},
					},
					Lineno: 0,
					Ast:    nil,
				},
			},
		}
	}
	return nil
}
