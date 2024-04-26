package frameworks

import (
	"fmt"
	"analyzer/pkg/logger"	
	"reflect"

	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"
)

func GetBlueprintServiceSpec[T any]() (*workflowspec.Service, error) {
	t := reflect.TypeOf(new(T)).Elem()
	serviceSpec, err := workflowspec.GetService[T]()
	if err != nil {
		log.Logger.Error(fmt.Sprintf("error getting service %s from workflow spec %s", t, err.Error()))
		return nil, err
	}
	if serviceSpec == nil {
		msg := fmt.Sprintf("workflow spec of service %s is nil", t)
		log.Logger.Error(msg)
		return nil, fmt.Errorf(msg)
	}
	return serviceSpec, nil
}
