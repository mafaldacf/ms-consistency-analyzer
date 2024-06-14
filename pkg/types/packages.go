package types

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
	"fmt"
	"go/ast"
	gotypes "go/types"
	"slices"
)

type Package struct {
	Name              string
	Module            string
	PackagePath       string
	Files             []*File

	TypesInfo 		 *gotypes.Info
	DeclaredVariables map[string]Variable
	DeclaredTypes     map[string]Type
	ServiceTypes 	  map[string]*ServiceType
	// contains blueprint backend types for datastores
	// key: type_name (e.g. Cache, Queue, etc)
	DatastoreTypes 	  map[string]*DatastoreType
	// contains all imported types, including blueprint backend types for datastores
	// key: package_path.type_name, where package_path is the real package name
	ImportedTypes 	  map[string]Type
}

func (p *Package) String() string {
	return p.Name
}

func (p *Package) GetTypeInfo(expr ast.Expr) gotypes.Type {
	return p.TypesInfo.TypeOf(expr)
}

func (p *Package) HasPath(path string) bool {
	return p.PackagePath == path
}

func (p *Package) GetFile(filepath string) *File {
	for _, f := range p.Files {
		if f.AbsPath == filepath {
			return f
		}
	}
	logger.Logger.Fatalf("could not find file with path %s for package %s", filepath, p.Name)
	return nil
}

func importedTypeKey(packagePath string, typeName string) string {
	return packagePath + "." + typeName
}

func (p *Package) AddDeclaredType(t Type) {
	if _, exists := p.DeclaredTypes[t.GetName()]; exists {
		logger.Logger.Fatalf("package %s already constains declared type %s", p.Name, t.String())
	}
	p.DeclaredTypes[t.GetName()] = t
}

func (p *Package) AddImportedType(t Type) {
	key := importedTypeKey(t.GetPackage(), t.GetName())
	if _, exists := p.ImportedTypes[key]; exists {
		logger.Logger.Fatalf("package %s already constains imported type %s", p.Name, t.String())
	}
	p.ImportedTypes[key] = t
}

func (p *Package) AddServiceType(t *ServiceType) {
	if _, exists := p.ServiceTypes[t.Name]; exists {
		logger.Logger.Fatalf("package %s already constains service type %s", p.Name, t.String())
	}
	p.ServiceTypes[t.Name] = t
}

func (p *Package) AddDatastoreType(t *DatastoreType) {
	if _, exists := p.DatastoreTypes[t.Name]; exists {
		logger.Logger.Fatalf("package %s already constains datastore type %s", p.Name, t.String())
	}
	p.DatastoreTypes[t.Name] = t
}

func (p *Package) LinkFile(file *File) {
	if slices.Contains(p.Files, file) {
		logger.Logger.Fatalf("package %s already constains file %s", p.Name, file.Name)
	}
	p.Files = append(p.Files, file)
	file.Package = p
}

func (p *Package) GetImportedTypeFromPath(fullPath string) (Type, bool) {
	if e, ok := p.ImportedTypes[fullPath]; ok {
		return e, true
	}
	logger.Logger.Fatalf("unknown imported package %s in package %s", fullPath, p.Name)
	return nil, false
}


func (p *Package) GetImportedType(packagePath string, typeName string) (Type, bool) {
	key := importedTypeKey(packagePath, typeName)
	if e, ok := p.ImportedTypes[key]; ok {
		return e, true
	}
	logger.Logger.Fatalf("unknown imported package %s in package %s", key, p.Name)
	return nil, false
}

func (p *Package) GetNamedType(name string) (Type, bool) {
	if e, ok := p.DeclaredTypes[name]; ok {
		return e, true
	}
	if e, ok := p.ServiceTypes[name]; ok {
		return e, true
	}
	if e, ok := p.DatastoreTypes[name]; ok {
		return e, true
	}
	logger.Logger.Fatalf("unknown named type %s in package %s", name, p.Name)
	return nil, false
}

func (p *Package) GenerateUnderlyingTypesFromGoType(goType gotypes.Type) Type {
	switch t := goType.(type) {
	case *gotypes.Named:
		name := t.Obj().Name()
		if namedType, ok := p.DeclaredTypes[name]; ok {
			return namedType
		}
		if serviceType, ok := p.ServiceTypes[name]; ok {
			return serviceType
		}
		if datastoreType, ok := p.DatastoreTypes[name]; ok {
			return datastoreType
		}
		logger.Logger.Fatalf("named type %s not declared in package %s", t.String(), p.String())
	case *gotypes.Struct:
		structType := &StructType{
			FieldTypes: make(map[string]Type),
		}
		for i := 0; i < t.NumFields(); i++ {
			var v *gotypes.Var = t.Field(i)
			structType.FieldTypes[v.Name()] = p.GenerateUnderlyingTypesFromGoType(v.Type())
		}
		return structType
	case *gotypes.Basic:
		return &BasicType{
			Name: t.Name(),
		}
	case *gotypes.Interface:
		return &InterfaceType{
			Content: goType.String(),
		}
	case *gotypes.Signature:
		signatureType := &SignatureType{}
		for i := 0; i < t.Results().Len(); i++ {
			var v* gotypes.Var = t.Results().At(i)
			signatureType.ReturnTypes = append(signatureType.ReturnTypes, p.GenerateUnderlyingTypesFromGoType(v.Type()))
		}
		return signatureType
	default:
		if goType != nil {
			logger.Logger.Fatalf("unknown gotype %s for %v", utils.GetType(goType), goType)
		}
	}
	return nil
}


func (p *Package) Yaml() map[string]interface{} {
	data := make(map[string]interface{})
	var key string
	// info
	info := make(map[string]interface{})
	info["_package name"] = p.Name
	info["_package path"] = p.PackagePath
	info["_module"] = p.Module
	files := []string{}
	for _, f := range p.Files {
		files = append(files, f.String())
		}
	key = fmt.Sprintf("files (%d)", len(files))
	info[key] = files
	data["_info"] = info
	// declared types
	declaredTypes := []string{}
	for _, f := range p.DeclaredTypes {
		declaredTypes = append(declaredTypes, f.FullString())
	}
	key = "declared types"
	if len(declaredTypes) > 0 {
		key += fmt.Sprintf(" (%d)", len(declaredTypes))
	}
	data[key] = declaredTypes
	// imported types
	importedTypes := []string{}
	for _, f := range p.ImportedTypes {
		importedTypes = append(importedTypes, f.FullString())
	}
	key = "imported types"
	if len(importedTypes) > 0 {
		key += fmt.Sprintf(" (%d)", len(importedTypes))
	}
	data[key] = importedTypes
	// service types
	serviceTypes := []string{}
	for _, f := range p.ServiceTypes {
		serviceTypes = append(serviceTypes, f.FullString())
	}
	key = "service types"
	if len(serviceTypes) > 0 {
		key += fmt.Sprintf(" (%d)", len(serviceTypes))
	}
	data[key] = serviceTypes
	// datastore types
	datastoreTypes := []string{}
	for _, f := range p.DatastoreTypes {
		datastoreTypes = append(datastoreTypes, f.FullString())
	}
	key = "datastore types"
	if len(datastoreTypes) > 0 {
		key += fmt.Sprintf(" (%d)", len(datastoreTypes))
	}
	data[key] = datastoreTypes
	// declared variables
	declaredVariables := []string{}
	for _, f := range p.DeclaredVariables {
		declaredVariables = append(declaredVariables, f.String())
	}
	key = "declared variables"
	if len(declaredVariables) > 0 {
		key += fmt.Sprintf(" (%d)", len(declaredVariables))
	}
	data[key] = declaredVariables
	return data
}
