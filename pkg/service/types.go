package service

import (
	"encoding/json"
	"slices"

	"analyzer/pkg/datastores"
	"analyzer/pkg/types"
)

type Service struct {
	Name            string
	ImplName        string
	ConstructorName string

	File   *types.File
	Fields map[string]types.Field
	// the map key is the service type (e.g. StorageService in 'storageService StorageService')
	Services  map[string]*Service
	Databases map[string]datastores.DatabaseInstance
	// safe because methods are unique since Golang does not allow overloading
	// also this captures all exposed methods because they must be defined within the service struct file
	ExposedMethods      map[string]*types.ParsedMethod
	QueueHandlerMethods map[string]*types.ParsedMethod
	InternalMethods     map[string]*types.ParsedMethod
	Constructor         *types.ParsedMethod

	ImplementsQueue bool
}

func (node *Service) Yaml() map[string]interface{} {
	data := make(map[string]interface{})
	// exposed methods
	for _, method := range node.ExposedMethods {
		data[method.String()] = method.Yaml()
	}
	// queue handler methods
	for _, method := range node.QueueHandlerMethods {
		data[method.String()] = method.Yaml()
	}
	// internal methods
	for _, method := range node.InternalMethods {
		data[method.String()] = method.Yaml()
	}
	return data
}

func (node *Service) GetPackage() *types.Package {
	return node.File.Package
}
func (node *Service) GetPackageName() string {
	return node.File.Package.Name
}

func (node *Service) GetQueueHandlersForDatabase(database datastores.DatabaseInstance) []*types.ParsedMethod {
	if _, ok := node.Databases[database.GetName()]; !ok {
		return nil
	}

	var handlers []*types.ParsedMethod
	for _, handler := range node.QueueHandlerMethods {
		if slices.Contains(handler.DbInstances, database) {
			handlers = append(handlers, handler)
		}
	}
	return handlers
}

func (node *Service) GetExposedMethod(name string) *types.ParsedMethod {
	return node.ExposedMethods[name]
}

func (node *Service) GetInternalMethod(name string) *types.ParsedMethod {
	return node.InternalMethods[name]
}

func (node *Service) GetQueueHandlerMethod(name string) *types.ParsedMethod {
	return node.QueueHandlerMethods[name]
}

// MarshalJSON is used by app.Save()
func (node *Service) MarshalJSON() ([]byte, error) {
	var serviceKeys []string
	for k := range node.Services {
		serviceKeys = append(serviceKeys, k)
	}
	var databaseKeys []string
	for k := range node.Databases {
		databaseKeys = append(databaseKeys, k)
	}
	fieldTypes := make(map[string]string)
	for name, field := range node.Fields {
		fieldTypes[name] = field.GetTypeName()
	}
	return json.MarshalIndent(&struct {
		Fields    map[string]string `json:"fields,omitempty"`
		Services  []string          `json:"services,omitempty"`
		Databases []string          `json:"databases,omitempty"`
	}{
		Fields:    fieldTypes,
		Services:  serviceKeys,
		Databases: databaseKeys,
	}, "", " ")
}

func (node *Service) String() string {
	str, _ := node.MarshalJSON()
	return string(str)
}

func (node *Service) ServicePath() string {
	return node.File.Package.PackagePath + "." + node.Name
}

func (node *Service) ServiceShortPath() string {
	return node.File.Package.Name + "." + node.Name
}
