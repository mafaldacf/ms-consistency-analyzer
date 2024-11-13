package types

import (
	"go/ast"
)

type File struct {
	Ast     *ast.File
	Package *Package
	Name    string
	Path    string
}

func (file *File) MarshalYAML() (interface{}, error) {
	return &struct {
		Name string `yaml:"name"`
		Path string `yaml:"path"`
	}{
		Name: file.Name,
		Path: file.Path,
	}, nil
}
