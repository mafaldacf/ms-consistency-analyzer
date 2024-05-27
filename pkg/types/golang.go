package types

import (
	"fmt"
	"go/ast"
)

// -------
// Package
// -------
type Package struct {
	Name   				string
	DeclaredTypes     	map[string]Type
	DeclaredVariables 	map[string]Variable
}

func (p *Package) String() string {
	return p.Name
}

// ----
// File
// ----
type File struct {
	Ast 				*ast.File
	Path 				string
	Package 			*Package
	Imports   			map[string]*Import
}

func (f *File) GetImport(alias string) (*Import, bool) {
	impt, ok := f.Imports[alias]
	return impt, ok
}
func (f *File) String() string {
	return fmt.Sprintf("%s (package: %s)", f.Path, f.Package.String())
}

// ------
// Import
// -----
type Import struct {
	Alias              string
	Path               string
	Package            string
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
