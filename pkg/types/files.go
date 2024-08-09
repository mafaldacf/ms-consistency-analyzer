package types

import (
	"fmt"
	"go/ast"

	"analyzer/pkg/logger"
)

type File struct {
	Ast     *ast.File
	Package *Package
	Name    string
	AbsPath string
	Imports map[string]*Import // key is the alias of the import
}

func (f *File) ImportsListStr() string {
	str := ""
	for _, impt := range f.Imports {
		str += "\t\t\t\t\t - " + impt.Alias + ": " + impt.PackagePath + "\n"
	}
	return str
}

func (f *File) GetImport(alias string) *Import {
	if impt, ok := f.Imports[alias]; ok {
		return impt
	}
	lst := ""
	for k, impt := range f.Imports {
		lst += fmt.Sprintf("\t\t\t\t - %s: %s\n", k, impt.ImportPath)
	}
	logger.Logger.Fatalf("[FILES] unknown import alias (%s) in file (%s) with import list:\n%s", alias, f.String(), lst)
	return nil
}

func (f *File) GetImportIfExists(alias string) *Import {
	if impt, ok := f.Imports[alias]; ok {
		return impt
	}
	return nil
}

func (f *File) String() string {
	return f.AbsPath
}
