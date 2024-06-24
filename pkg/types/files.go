package types

import (
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

func (f *File) GetImport(alias string) *Import {
	if impt, ok := f.Imports[alias]; ok {
		return impt
	}
	logger.Logger.Fatalf("unknown import alias (%s) in file (%s)", alias, f.String())
	return nil
}

func (f *File) String() string {
	return f.AbsPath
}
