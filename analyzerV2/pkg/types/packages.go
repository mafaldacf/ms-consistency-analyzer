package types

import (
	"go/ast"
	golangtypes "go/types"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/objects"
)

type PackageType int

const (
	APP PackageType = iota
	BLUEPRINT
	BUILTIN
	EXTERNAL
)

func (pkg *Package) TypeToString() string {
	var typeToString = map[PackageType]string{
		APP:       "App",
		BLUEPRINT: "Blueprint",
		BUILTIN:   "Built-in",
		EXTERNAL:  "External",
	}
	return typeToString[pkg.Type]
}

type Package struct {
	Name       string
	Type       PackageType
	Module     string
	Path       string
	Files      []*File
	TypesInfo  *golangtypes.Info
	NamedTypes map[*golangtypes.Named]*objects.Named
	Objects    map[string]objects.Object // only variables or constants
	Imports    map[string]*Package       // key is package path
	methods    map[string]*Method        // key is method name

	// are included in Objects above
	Services   map[string]objects.Object
	Datastores map[string]objects.Object
}

func NewPackage(name string, path string, modulePath string, typesInfo *golangtypes.Info) *Package {
	return &Package{
		Name:       name,    // e.g. models
		Path:       path, // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification/models
		Module:     modulePath,        // e.g. github.com/blueprint-uservices/blueprint/examples/postnotification/workflow
		TypesInfo:  typesInfo,
		Imports:    make(map[string]*Package),
		methods:    make(map[string]*Method),
		NamedTypes: make(map[*golangtypes.Named]*objects.Named),
		Objects:    make(map[string]objects.Object),
	}
}

func (pkg *Package) MarshalYAML() (interface{}, error) {
	var imports []string
	for key := range pkg.Imports {
		imports = append(imports, key)
	}
	var datastores []string
	for key := range pkg.Datastores {
		datastores = append(datastores, key)
	}
	var services []string
	for key := range pkg.Services {
		services = append(services, key)
	}
	var namedTypes []string
	for _, t := range pkg.NamedTypes {
		namedTypes = append(namedTypes, t.String(0))
	}
	var objects []string
	for _, obj := range pkg.Objects {
		objects = append(objects, obj.String(0))
	}

	return &struct {
		Name       string             `yaml:"name"`
		Type       string             `yaml:"type"`
		Module     string             `yaml:"module"`
		Path       string             `yaml:"path"`
		Files      []*File            `yaml:"files"`
		Imports    []string           `yaml:"imports"`
		methods    map[string]*Method `yaml:"methods"`
		NamedTypes []string           `yaml:"named_types"`
		Objects    []string           `yaml:"objects"`
		Services   []string           `yaml:"-"`
		Datastores []string           `yaml:"-"`
	}{
		Name:       pkg.Name,
		Module:     pkg.Module,
		Path:       pkg.Path,
		Type:       pkg.TypeToString(),
		Files:      pkg.Files,
		methods:    pkg.Methods(),
		NamedTypes: namedTypes,
		Objects:    objects,
		Imports:    imports,
		Services:   services,
		Datastores: datastores,
	}, nil
}

func (pkg *Package) String() string {
	return pkg.Name + "." + pkg.Path
}

func (pkg *Package) Equals(other *Package) bool {
	return pkg == other
}

func (pkg *Package) Methods() map[string]*Method {
	return pkg.methods
}

func (pkg *Package) GetNamedTypeIfExists(key *golangtypes.Named) (*objects.Named, bool) {
	named, exists := pkg.NamedTypes[key]
	return named, exists
}

func (pkg *Package) AddNamedType(key *golangtypes.Named, value *objects.Named) {
	pkg.NamedTypes[key] = value
}

func (pkg *Package) AddObject(obj objects.Object) {
	pkg.Objects[obj.Name()] = obj
}

func (pkg *Package) IsExternal() bool {
	return pkg.Type == EXTERNAL
}

func (pkg *Package) HasPath(other string) bool {
	return pkg.Path == other
}

func (pkg *Package) GetName() string {
	return pkg.Name
}

func (pkg *Package) GetPath() string {
	return pkg.Path
}

func (pkg *Package) GetFiles() []*File {
	return pkg.Files
}

func (pkg *Package) GetMethod(name string) *Method {
	return pkg.methods[name]
}

func (pkg *Package) AddMethod(method *Method) {
	pkg.methods[method.Name()] = method
}

func (pkg *Package) GetTypesInfo() *golangtypes.Info {
	return pkg.TypesInfo
}

func (pkg *Package) GetTypeInfo(ident *ast.Ident) golangtypes.Object {
	obj, exists := pkg.TypesInfo.Defs[ident]
	if !exists {
		logger.Logger.Fatalf("[PACKAGE] could not find golang object for ident (%s) in package (%s)", ident.Name, pkg.String())
	}
	return obj
}
