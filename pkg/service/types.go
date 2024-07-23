package service

import (
	"encoding/json"
	"fmt"
	"slices"
	"strings"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type Service struct {
	Name            string
	ImplName        string
	ConstructorName string
	File            *types.File

	//TODO maybe use variable instead of Type + Fields
	//Impl   variables.Variable
	Type   *gotypes.ServiceType
	Fields map[string]types.Field

	// the map key is the service type (e.g. StorageService in 'storageService StorageService')
	Services  map[string]*Service
	Databases map[string]datastores.DatabaseInstance
	// safe because methods are unique since Golang does not allow overloading
	// also this captures all exposed methods because they must be defined within the service struct file
	ExposedMethods      map[string]*types.ParsedMethod
	QueueHandlerMethods map[string]*types.ParsedMethod
	InternalMethods     map[string]*types.ParsedMethod
	PackageMethods      map[string]*types.ParsedMethod
	Constructor         *types.ParsedMethod

	ImplementsQueue bool
}

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

func (node *Service) GetName() string {
	return node.Name
}

// Remove "Service" at the end and start with lower case
// e.g. StorageService → storage
func (node *Service) GetShortName() string {
	if strings.HasSuffix(node.Name, "Service") {
		shortName := strings.TrimSuffix(node.Name, "Service")
		return strings.ToLower(shortName[:1]) + shortName[1:]
	}
	return strings.ToLower(node.Name)
}

// Add space before "Service"
// e.g. StorageService → Storage Service
func (node *Service) GetSpacedName() string {
	return utils.GetSpacedName(node.Name)
}

func (node *Service) GetPackage() *types.Package {
	return node.File.Package
}
func (node *Service) GetFile() *types.File {
	return node.File
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

func (node *Service) GetExportedMethod(name string) *types.ParsedMethod {
	if m, ok := node.ExposedMethods[name]; ok {
		return m
	}
	logger.Logger.Fatalf("[SERVICE] unknown exposed method (%s) for service (%s)", name, node.GetName())
	return nil
}

func (node *Service) GetInternalMethod(name string) *types.ParsedMethod {
	if m, ok := node.InternalMethods[name]; ok {
		return m
	}
	logger.Logger.Fatalf("[SERVICE] unknown internal method (%s) for service (%s)", name, node.GetName())
	return nil
}

func (node *Service) GetPackageMethod(name string) *types.ParsedMethod {
	if m, ok := node.PackageMethods[name]; ok {
		return m
	}
	logger.Logger.Fatalf("[SERVICE] unknown package method (%s) for service (%s)", name, node.GetName())
	return nil
}

func (node *Service) GetInternalOrPackageMethod(name string) *types.ParsedMethod {
	if internalMethod, ok := node.InternalMethods[name]; ok {
		return internalMethod
	}
	if packageMethod, ok := node.PackageMethods[name]; ok {
		return packageMethod
	}
	// exposed methods can also call themselves
	if exposedMethod, ok := node.ExposedMethods[name]; ok {
		return exposedMethod
	}
	internalMethodsStr := "\t\t\t\t\t\t\t Internal Methods:\n"
	for _, m := range node.InternalMethods {
		internalMethodsStr += fmt.Sprintf("\t\t\t\t\t\t\t - %s\n", m.String())
	}
	packageMethodStr := "\t\t\t\t\t\t\t Package Methods:\n"
	for _, m := range node.PackageMethods {
		packageMethodStr += fmt.Sprintf("\t\t\t\t\t\t\t - %s\n", m.String())
	}
	exposedMethodsStr := "\t\t\t\t\t\t\t Exposed Methods:\n"
	for _, m := range node.ExposedMethods {
		exposedMethodsStr += fmt.Sprintf("\t\t\t\t\t\t\t - %s\n", m.String())
	}
	logger.Logger.Fatalf("[SERVICE] unknown internal/package/exposed method (%s) for service (%s):\n%s%s%s", name, node.GetName(), internalMethodsStr, packageMethodStr, exposedMethodsStr)
	return nil
}

func (node *Service) GetQueueHandlerMethod(name string) *types.ParsedMethod {
	return node.QueueHandlerMethods[name]
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
