package types

import (
	"go/ast"
	golangtypes "go/types"
	"slices"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
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
	DeclaredVariables map[string]variables.Variable
	DeclaredTypes     map[string]gotypes.Type
	ServiceTypes      map[string]*gotypes.ServiceType
	ParsedMethods     []*ParsedMethod

	// contains blueprint backend types for datastores
	// key: type_name (e.g. Cache, Queue, etc)
	DatastoreTypes map[string]gotypes.Type

	// contains all imported types, including blueprint backend types for datastores
	// key: package_path.type_name, where package_path is the real package name
	ImportedTypes map[string]gotypes.Type
}

func (p *Package) IsAppPackage() bool {
	return p.Type == APP
}

func (p *Package) IsExternalPackage() bool {
	return p.Type == EXTERNAL
}

func (p *Package) IsBlueprintBackendPackage() bool {
	return p.Type == BLUEPRINT
}

func (p *Package) GetName() string {
	return p.Name
}

func (p *Package) GetPackagePath() string {
	return p.PackagePath
}

func (p *Package) GetDeclaredVariable(typeNameIdent *ast.Ident) variables.Variable {
	if v, ok := p.DeclaredVariables[typeNameIdent.Name]; ok {
		return v
	}
	logger.Logger.Fatalf("unknown declared variable (%s) in package (%s) -- declared variables: %v", typeNameIdent.Name, p.Name, p.DeclaredVariables)
	return nil
}

func (p *Package) GetDeclaredVariableIfExists(name string) variables.Variable {
	if v, ok := p.DeclaredVariables[name]; ok {
		return v
	}
	return nil
}

func (p *Package) AddParsedMethod(method *ParsedMethod) {
	p.ParsedMethods = append(p.ParsedMethods, method)
}

func (p *Package) GetParsedMethod(methodName string, recvTypeName string) *ParsedMethod {
	for _, m := range p.ParsedMethods {
		if m.Name == methodName {
			if m.Receiver.GetType() == nil || m.Receiver.GetType().GetName() == recvTypeName {
				return m
			}
		}
	}
	logger.Logger.Fatalf("unknown method (%s) with receiver type name (%s) for package (%s)", methodName, recvTypeName, p.Name)
	return nil
}

func (p *Package) GetParsedMethodIfExists(methodName string, recvTypeName string) *ParsedMethod {
	for _, m := range p.ParsedMethods {
		if m.Name == methodName {
			if m.Receiver == nil && recvTypeName == "" || m.Receiver.GetType().GetName() == recvTypeName {
				return m
			}
		}
	}
	//logger.Logger.Warnf("unknown method (%s) with receiver type name (%s) in package (%s)", methodName, recvTypeName, p.Name)
	return nil
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

func (p *Package) GetImportedPackage(pkgPath string) *Package {
	if pkgPath == p.PackagePath {
		return p
	}
	imptPkg, ok := p.ImportedPackages[pkgPath]
	if !ok {
		logger.Logger.Fatalf("package (%s) not found in imports of package (%s)", pkgPath, p.PackagePath)
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

func ImportedTypeKey(packagePath string, typeName string) string {
	return packagePath + "." + typeName
}

func (p *Package) AddDeclaredType(e gotypes.Type) {
	if _, exists := p.DeclaredTypes[e.GetName()]; exists {
		logger.Logger.Fatalf("package %s already constains declared type %s", p.Name, e.String())
	}
	p.DeclaredTypes[e.GetName()] = e
}

func (p *Package) AddImportedType(e gotypes.Type) {
	key := ImportedTypeKey(e.GetPackage(), e.GetName())
	if _, exists := p.ImportedTypes[key]; exists {
		logger.Logger.Fatalf("package %s already constains imported type %s", p.Name, e.String())
	}
	p.ImportedTypes[key] = e
}

func (p *Package) AddServiceType(e *gotypes.ServiceType) {
	if _, exists := p.ServiceTypes[e.Name]; exists {
		logger.Logger.Fatalf("package %s already constains service type %s", p.Name, e.String())
	}
	p.ServiceTypes[e.Name] = e
}

func (p *Package) AddDatastoreType(e gotypes.Type) {
	if _, exists := p.DatastoreTypes[e.GetName()]; exists {
		logger.Logger.Fatalf("package %s already constains datastore type %s", p.Name, e.String())
	}
	p.DatastoreTypes[e.GetName()] = e
}

func (p *Package) LinkFile(file *File) {
	if slices.Contains(p.Files, file) {
		logger.Logger.Fatalf("package (%s) already constains file (%s)", p.Name, file.Name)
	}
	p.Files = append(p.Files, file)
	file.Package = p
}

func (p *Package) GetImportedTypeFromPath(fullPath string) (gotypes.Type, bool) {
	if e, ok := p.ImportedTypes[fullPath]; ok {
		return e, true
	}
	importedTypesStr := ""
	for k, t := range p.ImportedTypes {
		importedTypesStr += "- " + k + ": " + t.String() + "\n"
	}
	importedPackagesStr := ""
	for k, t := range p.ImportedPackages {
		importedPackagesStr += "- " + k + ": " + t.String() + "\n"
	}
	logger.Logger.Fatalf("unknown imported type (%s) in package (%s) with import types list and packages:\n%v\n\n%v", fullPath, p.Name, importedTypesStr, importedPackagesStr)
	return nil, false
}

func (p *Package) GetImportedType(packagePath string, typeName string) (gotypes.Type, bool) {
	key := ImportedTypeKey(packagePath, typeName)
	if e, ok := p.ImportedTypes[key]; ok {
		return e, true
	}
	logger.Logger.Fatalf("[PACKAGE] unknown imported package (%s) in package (%s)", key, p.Name)
	return nil, false
}

func (p *Package) GetDeclaredTypeIfExists(typeNameIdent *ast.Ident) gotypes.Type {
	if p.Type == APP {
		if e, ok := p.DeclaredTypes[typeNameIdent.Name]; ok {
			return e
		}
	}
	logger.Logger.Warnf("[PACKAGE] unknown declared type (%s) in package (%s)", typeNameIdent.Name, p.Name)
	return nil
}

func (p *Package) GetNamedType(name string) (gotypes.Type, bool) {
	if e, ok := p.ServiceTypes[name]; ok {
		logger.Logger.Tracef("[PACKAGE] found service type for (%s)", name)
		return e, true
	}
	if e, ok := p.DatastoreTypes[name]; ok {
		logger.Logger.Tracef("[PACKAGE] found datastore type for (%s)", name)
		return e, true
	}
	if e, ok := p.DeclaredTypes[name]; ok {
		logger.Logger.Tracef("[PACKAGE] found declared type for (%s)", name)
		return e, true
	}
	logger.Logger.Fatalf("unknown named type (%s) in package (%s)", name, p.Name)
	return nil, false
}
