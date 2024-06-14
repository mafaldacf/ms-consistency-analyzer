package types

import (
	"go/ast"
)

// ---------------------
// -------- File -------
// ---------------------
type File struct {
	Ast     *ast.File
	Package *Package
	// name of the file (e.g. UploadService.go)
	Name  	string
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
