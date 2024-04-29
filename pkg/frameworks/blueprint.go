package frameworks

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/analyzer"
	"fmt"
	"reflect"

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
	NumParams 	int
}

func (b *BlueprintBackend) String() string {
	return b.Name
}

func (b *BlueprintBackend) GetNumParams() int {
	return b.NumParams
}


func GetBackendMethod(name string) *BlueprintBackend {
	if name == "Cache.Put" {
		return &BlueprintBackend {
			Name: name,
			NumParams: 3,
		}
	}
	if name == "Cache.Get" {
		return &BlueprintBackend {
			Name: name,
			NumParams: 2,
		}
	}
	return nil
}
