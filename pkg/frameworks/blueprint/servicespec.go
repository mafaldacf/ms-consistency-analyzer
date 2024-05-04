package frameworks

import (
	"analyzer/pkg/logger"
	"fmt"
	"reflect"

	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"
)

// GetBlueprintServiceSpec is deprecated
// Usage:
// storageServiceSpec, err0 := frameworks.GetBlueprintServiceSpec[postnotification.StorageService]()
// notifyServiceSpec, err1 := frameworks.GetBlueprintServiceSpec[postnotification.NotifyService]()
// uploadServiceSpec, err2 := frameworks.GetBlueprintServiceSpec[postnotification.UploadService]()
// app.RegisterSimpleServiceNode(storageServiceSpec)
// app.RegisterSimpleServiceNode(notifyServiceSpec, storageServiceSpec)
// app.RegisterSimpleServiceNode(uploadServiceSpec, storageServiceSpec, notifyServiceSpec)
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
