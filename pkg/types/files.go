package types

import (
	"fmt"
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

// ---------------------
// ------- Import ------
// ---------------------
type Import struct {
	Alias   		string
	ImportPath    	string
	PackageName 	string
	// real pack of the imported package
	// FIXME: if dev uses go.mod to replace paths then we have to translate to the real path
	PackagePath 	string
}

func (i *Import) IsBlueprintPackage() bool {
	return i.PackagePath == "github.com/blueprint-uservices/blueprint/runtime/core/backend"
}
func (i *Import) String() string {
	return fmt.Sprintf("%s \"%s\" (package: %s)", i.Alias, i.ImportPath, i.PackagePath)
}
