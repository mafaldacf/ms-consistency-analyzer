package types

import (
	"fmt"
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
	DeclaredConstants map[string]variables.Variable
	DeclaredTypes     map[string]gotypes.Type
	ServiceTypes      map[string]*gotypes.ServiceType
	ParsedMethods     []*ParsedMethod

	// contains blueprint backend types for datastores
	// key: type_name (e.g. Cache, Queue, etc)
	DatastoreTypes map[string]gotypes.Type

	// contains all imported types, including blueprint backend types for datastores
	// key: package_path.type_name, where package_path is the real package name
	ImportedTypes     map[string]gotypes.Type
	ImportedConstants map[string]variables.Variable
	ImportedVariables map[string]variables.Variable
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

func (p *Package) GetDeclaredVariableOrConst(typeNameIdent *ast.Ident) variables.Variable {
	if v, ok := p.DeclaredVariables[typeNameIdent.Name]; ok {
		return v
	}
	if v, ok := p.DeclaredConstants[typeNameIdent.Name]; ok {
		return v
	}
	logger.Logger.Fatalf("unknown declared variable or const (%s) in package (%s) -- declared variables: %v", typeNameIdent.Name, p.Name, p.DeclaredVariables)
	return nil
}

func (p *Package) GetDeclaredConstant(typeNameIdent *ast.Ident) variables.Variable {
	if v, ok := p.DeclaredConstants[typeNameIdent.Name]; ok {
		return v
	}
	logger.Logger.Fatalf("unknown declared constant (%s) in package (%s) -- constant variables: %v", typeNameIdent.Name, p.Name, p.DeclaredConstants)
	return nil
}

func (p *Package) GetDeclaredVariableOrConstIfExists(name string) variables.Variable {
	if v, ok := p.DeclaredVariables[name]; ok {
		return v
	}
	if v, ok := p.DeclaredConstants[name]; ok {
		return v
	}
	return nil
}

func (p *Package) RegisterMethodToParse(method *ParsedMethod) {
	p.ParsedMethods = append(p.ParsedMethods, method)
}

func (p *Package) GetAllParsedMethods() []*ParsedMethod {
	return p.ParsedMethods
}

func (p *Package) GetParsedMethod(methodName string, recvTypeName string) *ParsedMethod {
	for _, m := range p.ParsedMethods {
		if m.Name == methodName && (m.Receiver == nil || m.Receiver.GetType() == nil || m.Receiver.GetType().GetName() == recvTypeName) {
			if m.ParsedCfg == nil {
				logger.Logger.Warnf("[TYPES PACKAGES] encountered nil cfg - method (%s) is not yet parsed", methodName)
			}
			return m
		}
	}
	logger.Logger.Fatalf("unknown method (%s) with receiver type name (%s) for package (%s)", methodName, recvTypeName, p.Name)
	return nil
}

func (p *Package) GetParsedMethodIfExists(methodName string, recvTypeName string) *ParsedMethod {
	// only internal methods are parsed
	// if method is not found the it must be from an external package
	for _, m := range p.ParsedMethods {
		if m.Name == methodName && (m.Receiver == nil || m.Receiver.GetType() == nil || m.Receiver.GetType().GetName() == recvTypeName) {
			lst := ""
			for _, m := range p.ParsedMethods {
				lst += fmt.Sprintf("\t\t\t\t\t\t - %s\n", m)
			}

			logger.Logger.Debugf("[TYPES PACKAGE] found parsed method for name (%s) - parsed methods list in package:\n%s", methodName, lst)
			return m
		}
	}
	logger.Logger.Warnf("unknown method (%s) with receiver type name (%s) in package (%s)", methodName, recvTypeName, p.Name)
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

func (p *Package) AddConstant(v variables.Variable) {
	if _, exists := p.DeclaredConstants[v.GetVariableInfo().GetName()]; exists {
		logger.Logger.Fatalf("package %s already constains declared type %s", v.GetVariableInfo().GetName(), v.String())
	}
	p.DeclaredConstants[v.GetVariableInfo().GetName()] = v
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

func (p *Package) AddImportedConstant(v variables.Variable, packagePath string) {
	key := ImportedTypeKey(packagePath, v.GetVariableInfo().GetName())
	if _, exists := p.ImportedConstants[key]; exists {
		logger.Logger.Fatalf("package %s already constains imported constant %s", v.GetVariableInfo().GetName(), v.String())
	}
	p.ImportedConstants[key] = v
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

func (p *Package) getImportedTypesLstStr() string {
	importedTypesStr := ""
	for k, t := range p.ImportedTypes {
		importedTypesStr += "- " + k + ": " + t.String() + "\n"
	}
	return importedTypesStr
}

func (p *Package) getImportedPackagesLstStr() string {
	importedPackagesStr := ""
	for k, t := range p.ImportedPackages {
		importedPackagesStr += "- " + k + ": " + t.String() + "\n"
	}
	return importedPackagesStr
}

func (p *Package) GetImportedTypeIfExists(importPath string) gotypes.Type {
	if e, ok := p.ImportedTypes[importPath]; ok {
		return e
	}
	logger.Logger.Warnf("[PACKAGE] unknown imported type (%s) in package (%s) with import types list and packages:\n%v\n\n%v", importPath, p.Name, p.getImportedTypesLstStr(), p.getImportedPackagesLstStr())
	return nil
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
