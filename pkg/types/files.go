package types

import (
	"go/ast"
)

type File struct {
	Ast     *ast.File
	Package *Package
	Name    string
	AbsPath string
	Imports map[string]*Import // key is the alias of the import
}

func (f *File) GetImport(alias string) (*Import, bool) {
	impt, ok := f.Imports[alias]
	return impt, ok
}

func (f *File) String() string {
	return f.AbsPath
}
