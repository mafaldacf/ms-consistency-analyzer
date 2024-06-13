package types

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
	"fmt"
	"go/ast"
	gotypes "go/types"
)

// ---------------------
// ------ Package ------
// ---------------------
type Package struct {
	Name              string
	Module            string
	PackagePath       string
	DeclaredTypes     map[string]*UserType
	ImportedTypes 	  map[string]*UserType

	ServiceTypes 	  map[string]*ServiceType
	DatastoreTypes 	  map[string]*DatastoreType

	DeclaredVariables map[string]Variable
	Files             []*File
}

func (p *Package) String() string {
	return p.Name
}

func (p *Package) FullString() string {
	s := p.Name + ":\n"
	s += "- Package Name: \t" + p.Name + "\n"
	s += "- Package Path: \t" + p.PackagePath + "\n"
	s += "- Module: \t\t" + p.Module + "\n"
	s += "- Files:\n"
	for _, f := range p.Files {
		s += fmt.Sprintf("\t - %s\n", f.String())
	}
	s += "- Declared Types:\n"
	for _, t := range p.DeclaredTypes {
		s += fmt.Sprintf("\t - %s\n", t.FullString())
	}
	s += "- Imported Types:\n"
	for _, t := range p.ImportedTypes {
		s += fmt.Sprintf("\t - %s\n", t.FullString())
	}
	s += "- Service Types:\n"
	for _, t := range p.ServiceTypes {
		s += fmt.Sprintf("\t - %s\n", t.FullString())
	}
	s += "- Datastore Types:\n"
	for _, t := range p.DatastoreTypes {
		s += fmt.Sprintf("\t - %s\n", t.FullString())
	}
	s += "- Declared Variables:\n"
	for _, t := range p.DeclaredVariables {
		s += fmt.Sprintf("\t - %s\n", t.String())
	}
	return s
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

func GenerateUnderlyingTypesFromGoType(pkg *Package, goType gotypes.Type) Type {
	switch t := goType.(type) {
	case *gotypes.Named:
		name := t.Obj().Name()
		if namedType, ok := pkg.DeclaredTypes[name]; ok {
			return namedType
		}
		if serviceType, ok := pkg.ServiceTypes[name]; ok {
			return serviceType
		}
		if datastoreType, ok := pkg.DatastoreTypes[name]; ok {
			return datastoreType
		}
		logger.Logger.Fatalf("named type %s not declared in package %s", t.String(), pkg.String())
	case *gotypes.Struct:
		structType := &StructType{
			FieldTypes: make(map[string]Type),
		}
		for i := 0; i < t.NumFields(); i++ {
			var v *gotypes.Var = t.Field(i)
			structType.FieldTypes[v.Name()] = GenerateUnderlyingTypesFromGoType(pkg, v.Type())
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
	default:
		logger.Logger.Fatalf("unknown gotype %s for %v", utils.GetType(goType), goType)
	}
	return nil
}

// ---------------------
// -------- File -------
// ---------------------
type File struct {
	Ast     *ast.File
	Package *Package
	// absolute filepath
	AbsPath string
	// key is the alias of the import
	Imports map[string]*Import
}

func (f *File) GetImport(alias string) (*Import, bool) {
	impt, ok := f.Imports[alias]
	return impt, ok
}
func (f *File) String() string {
	return f.AbsPath
}

// ---------------------
// ------- Import ------
// ---------------------
type Import struct {
	Alias   string
	Path    string
	Package string
}

func (i *Import) IsBlueprintPackage() bool {
	return i.Package == "github.com/blueprint-uservices/blueprint/runtime/core/backend"
}
func (i *Import) BuildPackageName() {
	i.Package = i.Path
}
func (i *Import) String() string {
	return fmt.Sprintf("%s \"%s\" (package: %s)", i.Alias, i.Path, i.Package)
}
