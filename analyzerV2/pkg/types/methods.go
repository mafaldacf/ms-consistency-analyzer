package types

import (
	"go/ast"

	"analyzer/pkg/types/objects"
)

type Method struct {
	ast  *ast.FuncDecl `yaml:"-"`
	name string        `yaml:"name"`
	fn   *objects.Func `yaml:"function"`
	pkg  *Package      `yaml:"-"`
	cf   *ControlFlow  `yaml:"-"`

	// used to fetch the params when generating the basic cfg
	// to store in the variables array of the function
	//Params   []*MethodField
	//Returns  []*MethodField
	//Receiver *MethodField `yaml:"-"`
}

func NewMethod(funcDecl *ast.FuncDecl, fn objects.Object, pkg *Package) *Method {
	return &Method{
		ast:  funcDecl,
		fn:   fn.(*objects.Func),
		name: funcDecl.Name.Name,
		pkg:  pkg,
		cf:   NewControlFlow(funcDecl.Body),
	}
}

func (m *Method) Ast() *ast.FuncDecl {
	return m.ast
}

func (m *Method) Name() string {
	return m.name
}

func (m *Method) String() string {
	return m.fn.String(0)
}

func (m *Method) Func() *objects.Func {
	return m.fn
}

func (m *Method) Package() *Package {
	return m.pkg
}

func (m *Method) ControlFlow() *ControlFlow {
	return m.cf
}
