package types

import (
	"fmt"
	"go/ast"

	"analyzer/pkg/datastores"
)

type Method interface {
	String() string
	GetParams() []*MethodField
	GetReturns() []*MethodField
	IsQueueWrite() bool
	IsQueueRead() bool
	IsWrite() bool
}

type ParsedMethod struct {
	Method
	Ast         *ast.FuncDecl                 `json:"-"`
	Name        string                        `json:"name"`
	FullName    string                        `json:"-"`
	Calls       []Call                        `json:"-"`
	Service     string                        `json:"-"`
	Package     *Package                      `json:"-"`
	ParsedCfg   *CFG                          `json:"-"`
	DbInstances []datastores.DatabaseInstance `json:"-"`
	Exported    bool                          `json:"-"`

	// used to fetch the params when generating the basic cfg
	// to store in the variables array of the function
	Params   []*MethodField
	Returns  []*MethodField
	Receiver *MethodField `json:"-"`
}

func (f *ParsedMethod) Yaml() interface{} {
	return f.ParsedCfg.Yaml()
}

func (f *ParsedMethod) GetAst() *ast.FuncDecl {
	return f.Ast
}
func (f *ParsedMethod) GetBody() *ast.BlockStmt {
	return f.Ast.Body
}
func (f *ParsedMethod) SetParsedCFG(parsedCfg *CFG) {
	f.ParsedCfg = parsedCfg
}
func (*ParsedMethod) IsQueueWrite() bool {
	return false
}
func (*ParsedMethod) IsQueueRead() bool {
	return false
}

func (p *ParsedMethod) String() string {
	repr := fmt.Sprintf("%s.%s(", p.Service, p.Name)
	for i, arg := range p.Params {
		repr += arg.String()
		if i < len(p.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	return repr
}

func (p *ParsedMethod) LongString() string {
	prefix := p.Package.Name
	if p.Receiver != nil {
		prefix = p.Receiver.GetTypeLongName()
	}
	repr := fmt.Sprintf("%s.%s(", prefix, p.Name)
	for i, arg := range p.Params {
		repr += arg.String()
		if i < len(p.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	return repr
}

// TODO: missing returns!!
func (p *ParsedMethod) Signature() string {
	repr := fmt.Sprintf("%s(", p.Name)
	for i, arg := range p.Params {
		repr += arg.String()
		if i < len(p.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	if len(p.Returns) == 0 {
		return repr
	}
	if len(p.Returns) == 1 {
		return repr + " " + p.Returns[0].String()
	}

	repr += " ("
	for i, arg := range p.Returns {
		repr += arg.String()
		if i < len(p.Returns)-1 {
			repr += ", "
		}
	}
	return repr + ")"
}

func (p *ParsedMethod) GetParams() []*MethodField {
	return p.Params
}
func (p *ParsedMethod) GetReturns() []*MethodField {
	return p.Returns
}
