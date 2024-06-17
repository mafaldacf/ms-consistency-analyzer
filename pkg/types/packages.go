package types

import (
	"go/ast"
	golangtypes "go/types"
	"slices"
	"sort"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
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

	TypesInfo         *golangtypes.Info
	DeclaredVariables map[string]Variable
	DeclaredTypes     map[string]gotypes.Type
	ServiceTypes      map[string]*gotypes.ServiceType

	// contains blueprint backend types for datastores
	// key: type_name (e.g. Cache, Queue, etc)
	DatastoreTypes map[string]gotypes.Type

	// contains all imported types, including blueprint backend types for datastores
	// key: package_path.type_name, where package_path is the real package name
	ImportedTypes map[string]gotypes.Type

	ParsedMethods []*ParsedMethod
}

func (p *Package) IsAppPackage() bool {
	return p.Type == APP
}

func (p *Package) GetParsedMethodIfExists(methodName string, recvTypeName string) *ParsedMethod {
	for _, m := range p.ParsedMethods {
		if m.Name == methodName && m.Recv.Type != nil && m.Recv.Type.GetName() == recvTypeName {
			return m
		}
	}
	return nil
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

func (p *Package) GetDeclaredType(name string) gotypes.Type {
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

func (p *Package) GetTypeInfo(expr ast.Expr) golangtypes.Type {
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

func (p *Package) AddDeclaredType(t gotypes.Type) {
	if _, exists := p.DeclaredTypes[t.GetName()]; exists {
		logger.Logger.Fatalf("package %s already constains declared type %s", p.Name, t.String())
	}
	p.DeclaredTypes[t.GetName()] = t
}

func (p *Package) AddImportedType(t gotypes.Type) {
	key := importedTypeKey(t.GetPackage(), t.GetName())
	if _, exists := p.ImportedTypes[key]; exists {
		logger.Logger.Fatalf("package %s already constains imported type %s", p.Name, t.String())
	}
	p.ImportedTypes[key] = t
}

func (p *Package) AddServiceType(t *gotypes.ServiceType) {
	if _, exists := p.ServiceTypes[t.Name]; exists {
		logger.Logger.Fatalf("package %s already constains service type %s", p.Name, t.String())
	}
	p.ServiceTypes[t.Name] = t
}

func (p *Package) AddDatastoreType(t gotypes.Type) {
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

func (p *Package) GetImportedTypeFromPath(fullPath string) (gotypes.Type, bool) {
	if e, ok := p.ImportedTypes[fullPath]; ok {
		return e, true
	}
	logger.Logger.Fatalf("unknown imported package %s in package %s", fullPath, p.Name)
	return nil, false
}

func (p *Package) GetImportedType(packagePath string, typeName string) (gotypes.Type, bool) {
	key := importedTypeKey(packagePath, typeName)
	if e, ok := p.ImportedTypes[key]; ok {
		return e, true
	}
	logger.Logger.Fatalf("unknown imported package %s in package %s", key, p.Name)
	return nil, false
}

func (p *Package) GetNamedType(name string) (gotypes.Type, bool) {
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

func (p *Package) GenerateUnderlyingTypesFromGoType(goType golangtypes.Type) gotypes.Type {
	switch t := goType.(type) {
	case *golangtypes.Named:
		name := t.Obj().Name()
		path := ""
		if t.Obj().Pkg() != nil { // error never has an object
			path = t.Obj().Pkg().Path()
		}
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
	case *golangtypes.Struct:
		structType := &gotypes.StructType{
			FieldTypes: make(map[string]gotypes.Type),
			FieldTags:  make(map[string]string),
		}
		for i := 0; i < t.NumFields(); i++ {
			var v *golangtypes.Var = t.Field(i)
			structType.FieldTypes[v.Name()] = p.GenerateUnderlyingTypesFromGoType(v.Type())
			if tag := t.Tag(i); tag != "" {
				structType.FieldTags[v.Name()] = tag
			}
			structType.FieldNames = append(structType.FieldNames, v.Name())
		}
		return structType
	case *golangtypes.Basic:
		return &gotypes.BasicType{
			Name: t.Name(),
		}
	case *golangtypes.Interface:
		return &gotypes.InterfaceType{
			Content: goType.String(),
		}
	case *golangtypes.Signature:
		signatureType := &gotypes.SignatureType{}
		for i := 0; i < t.Results().Len(); i++ {
			var v *golangtypes.Var = t.Results().At(i)
			signatureType.ReturnTypes = append(signatureType.ReturnTypes, p.GenerateUnderlyingTypesFromGoType(v.Type()))
		}
		return signatureType
	case *golangtypes.Tuple:
		tupleType := &gotypes.TupleType{}
		for i := 0; i < t.Len(); i++ {
			var v *golangtypes.Var = t.At(i)
			tupleType.Types = append(tupleType.Types, p.GenerateUnderlyingTypesFromGoType(v.Type()))
		}
		return tupleType
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
