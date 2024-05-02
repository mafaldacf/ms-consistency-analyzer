package frameworks

import (
	"analyzer/pkg/analyzer"
	"analyzer/pkg/logger"
	"fmt"
	"reflect"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"
)

func GetBlueprintServiceSpec[T any]() (*workflowspec.Service, error) {
	t := reflect.TypeOf(new(T)).Elem()
	serviceSpec, err := workflowspec.GetService[T]()
	if err != nil {
		logger.Logger.Error(fmt.Sprintf("error getting service %s from workflow spec %s", t, err.Error()))
		return nil, err
	}
	if serviceSpec == nil {
		msg := fmt.Sprintf("workflow spec of service %s is nil", t)
		logger.Logger.Error(msg)
		return nil, fmt.Errorf(msg)
	}
	return serviceSpec, nil
}

type BlueprintBackend struct {
	analyzer.Method
	Name      	string
	Params 		[]*analyzer.FunctionField
	Returns 	[]*analyzer.FunctionField
}

func (b *BlueprintBackend) String() string {
	repr := fmt.Sprintf("%s(", b.Name)
	for i, param := range b.Params {
		repr += param.GetName()
		if i < len(b.Params) - 1 {
			repr += ", "
		}
	}
	repr += ")"
	return repr
}

func (b *BlueprintBackend) GetParams() []*analyzer.FunctionField {
	return b.Params
}

func (b *BlueprintBackend) GetReturns() []*analyzer.FunctionField {
	return b.Returns
}

func GetBackendMethod(name string) *BlueprintBackend {
	if name == "Cache.Put" {
		return &BlueprintBackend {
			Name: name,
			Params: []*analyzer.FunctionField{
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
						Type: &gocode.InterfaceType{
						},
					},
					Lineno: 0,
					Ast:    nil,
				},
			},
		}
	}
	if name == "Cache.Get" {
		return &BlueprintBackend {
			Name: name,
			Params: []*analyzer.FunctionField{
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
						Type: &gocode.InterfaceType{
						},
					},
					Lineno: 0,
					Ast:    nil,
				},
			},
		}
	}
	return nil
}
