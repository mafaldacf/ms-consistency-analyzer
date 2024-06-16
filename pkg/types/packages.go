package types

import (
	"go/ast"
	gotypes "go/types"
	"slices"
	"sort"

	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

type PackageType int

const (
	APP       PackageType = iota
	BLUEPRINT             // blueprint backend package
	EXTERNAL
)

type Package struct {
	Name        string
	Module      string
	PackagePath string
	Files       []*File

	// app packages are fully parsed
	// blueprint packages only contain declared types and package metadata (above)
	// external packages are not parsed
	Type PackageType

	// maps the package path to another parsed package
	// REMINDER: IDK if key is the same of the package path (CHECK IF THIS CONCERNS THE REPLACEMENT IN GO.MODULE)
	ImportedPackages map[string]*Package

	TypesInfo         *gotypes.Info
	DeclaredVariables map[string]Variable
	DeclaredTypes     map[string]Type
	ServiceTypes      map[string]*ServiceType

	// contains blueprint backend types for datastores
	// key: type_name (e.g. Cache, Queue, etc)
	DatastoreTypes map[string]Type

	// contains all imported types, including blueprint backend types for datastores
	// key: package_path.type_name, where package_path is the real package name
	ImportedTypes map[string]Type
}

func (p *Package) IsAppPackage() bool {
	return p.Type == APP
}

func (p *Package) IsBlueprintBackendPackage() bool {
	return p.Type == BLUEPRINT
}

func (p *Package) IsExternalPackage() bool {
	return p.Type == EXTERNAL
}

func (p *Package) String() string {
	return p.Name
}

func (p *Package) GetDeclaredType(name string) Type {
	decl, ok := p.DeclaredTypes[name]
	if !ok {
		logger.Logger.Fatalf("type %s not found in declared types of package %s", name, p.Name)
	}
	return decl
}

func (p *Package) GetImportedPackage(name string) *Package {
	imptPkg, ok := p.ImportedPackages[name]
	if !ok {
		logger.Logger.Fatalf("package %s not found in imports of package %s", name, p.Name)
	}
	return imptPkg
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

func (p *Package) AddDatastoreType(t Type) {
	if _, exists := p.DatastoreTypes[t.GetName()]; exists {
		logger.Logger.Fatalf("package %s already constains datastore type %s", p.Name, t.String())
	}
	p.DatastoreTypes[t.GetName()] = t
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
		path := t.Obj().Pkg().Path()
		if namedType, ok := p.DeclaredTypes[name]; ok {
			return namedType
		}
		if serviceType, ok := p.ServiceTypes[name]; ok {
			return serviceType
		}
		if datastoreType, ok := p.DatastoreTypes[name]; ok {
			return datastoreType
		}
		if importedType, ok := p.ImportedTypes[importedTypeKey(path, name)]; ok {
			return importedType
		}
		logger.Logger.Fatalf("named type %s not declared in package %s", t.String(), p.String())
	case *gotypes.Struct:
		structType := &StructType{
			FieldTypes: make(map[string]Type),
		}
		for i := 0; i < t.NumFields(); i++ {
			var v *gotypes.Var = t.Field(i)
			structType.FieldTypes[v.Name()] = p.GenerateUnderlyingTypesFromGoType(v.Type())
			structType.FieldNames = append(structType.FieldNames, v.Name())
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
			var v *gotypes.Var = t.Results().At(i)
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

// for blueprint packages
func (p *Package) DumpShortYaml() utils.OrderedProperties {
	propsData := utils.NewOrderedPropertyList()

	// metadata
	propsMetadata := utils.NewOrderedPropertyList()
	propsMetadata.AddOrderedProperty("package", p.Name)
	propsMetadata.AddOrderedProperty("package path", p.PackagePath)
	propsMetadata.AddOrderedProperty("module", p.Module)
	// save metadata
	propsData.AddOrderedProperty("metadata", propsMetadata.Result())

	// declared types
	declaredTypes := []string{}
	for _, t := range p.DeclaredTypes {
		declaredTypes = append(declaredTypes, t.FullString())
	}
	sort.Strings(declaredTypes)
	propsData.AddOrderedProperty("declared types", declaredTypes)

	// save final data
	return propsData.Result()
}

func (p *Package) DumpYaml() utils.OrderedProperties {
	propsData := utils.NewOrderedPropertyList()

	// metadata
	propsMetadata := utils.NewOrderedPropertyList()
	propsMetadata.AddOrderedProperty("package", p.Name)
	propsMetadata.AddOrderedProperty("package path", p.PackagePath)
	propsMetadata.AddOrderedProperty("module", p.Module)
	// metadata > files
	files := []string{}
	for _, f := range p.Files {
		files = append(files, f.String())
	}
	sort.Strings(files)
	propsMetadata.AddOrderedProperty("files", files)
	// metadata > imports
	imports := []string{}
	for key := range p.ImportedPackages {
		imports = append(imports, key)
	}
	sort.Strings(imports)
	propsMetadata.AddOrderedProperty("imports", imports)
	// save metadata
	propsData.AddOrderedProperty("metadata", propsMetadata.Result())

	// imported types
	importedTypes := []string{}
	for _, t := range p.ImportedTypes {
		importedTypes = append(importedTypes, t.FullString())
	}
	sort.Strings(importedTypes)
	propsData.AddOrderedProperty("imported types", importedTypes)

	// declared types
	declaredTypes := []string{}
	for _, t := range p.DeclaredTypes {
		declaredTypes = append(declaredTypes, t.FullString())
	}
	sort.Strings(declaredTypes)
	propsData.AddOrderedProperty("declared types", declaredTypes)

	// declared variables
	declaredVariables := []string{}
	for _, v := range p.DeclaredVariables {
		declaredVariables = append(declaredVariables, v.String())
	}
	sort.Strings(declaredVariables)
	propsData.AddOrderedProperty("declared variables", declaredVariables)

	// save final data
	return propsData.Result()
}
