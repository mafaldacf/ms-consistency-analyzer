package services

import (
	"analyzer/pkg/app/datastores"
	"analyzer/pkg/types"
	"analyzer/pkg/types/objects"
)

type Service struct {
	objects.Object
	name            string
	constructorName string
	pkg             *types.Package // package where service is defined and initialized
	services        map[string]*Service
	datastores      map[string]*datastores.Datastore
	methods         map[string]*types.Method
	constructor     *types.Method
}

func NewService(name string, constructorName string, pkg *types.Package) *Service {
	return &Service{
		name:            name,
		pkg:             pkg,
		constructorName: constructorName,
		services:        make(map[string]*Service),
		datastores:      make(map[string]*datastores.Datastore),
		methods:         make(map[string]*types.Method),
	}
}

func (svc *Service) Name() string {
	return svc.name
}

func (svc *Service) ConstructorName() string {
	return svc.constructorName
}

func (svc *Service) Package() *types.Package {
	return svc.pkg
}

func (svc *Service) Services() map[string]*Service {
	return svc.services
}

func (svc *Service) Datastores() map[string]*datastores.Datastore {
	return svc.datastores
}

func (svc *Service) Methods() map[string]*types.Method {
	return svc.methods
}

func (svc *Service) Constructor() *types.Method {
	return svc.constructor
}

func (svc *Service) SetConstructor(constructor *types.Method) {
	svc.constructor = constructor
}

func (svc *Service) AddMethod(method *types.Method) {
	svc.methods[method.Name()] = method
}

func (svc *Service) AddService(name string, other *Service) {
	svc.services[name] = other
}

func (svc *Service) AddDatastore(name string, datastore *datastores.Datastore) {
	svc.datastores[name] = datastore
}

func (svc *Service) MarshalYAML() (interface{}, error) {
	var services []string
	for key := range svc.services {
		services = append(services, key)
	}
	var datastores []string
	for key := range svc.datastores {
		datastores = append(datastores, key)
	}

	return &struct {
		Object     objects.Object `yaml:"-"`
		Name       string         `yaml:"name"`
		Package    string         `yaml:"package"`
		Services   []string       `yaml:"services"`
		Datastores []string       `yaml:"datastores"`
	}{
		Object:     svc.Object,
		Name:       svc.name,
		Package:    svc.pkg.GetPath(),
		Services:   services,
		Datastores: datastores,
	}, nil
}
