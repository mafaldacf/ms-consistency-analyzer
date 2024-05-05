package types

import (
	"fmt"
	"go/ast"
	"go/token"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

type Field interface {
	GetTypeName() string
}

type FunctionField struct {
	Field
	gocode.Variable
	Lineno token.Pos
	Ast    *ast.Field
}

type ServiceField struct {
	Field
	gocode.Variable
	Lineno token.Pos
	Ast    *ast.Field
}
type DatabaseField struct {
	Field
	gocode.Variable 
	Lineno 		token.Pos
	Ast    		*ast.Field
	IsQueue		bool
	Instance    DatabaseInstance
}

func (svc *ServiceField) GetTypeName() string {
	return svc.GetType()
}

func (db *DatabaseField) GetTypeName() string {
	return db.GetType()
}

func (fn *FunctionField) GetTypeName() string {
	return fn.GetType()
}

type Method interface {
	String() string
	GetParams() []*FunctionField
	GetReturns() []*FunctionField
}

type Ref struct {
	Name     string    `json:"name,omitempty"`
	Creator  string    `json:"creator,omitempty"`
	Id       int64     `json:"id"`
	Variable *Variable `json:"-"`
}

type Variable struct {
	Name          string          `json:"name"`
	Id            int64           `json:"id"`
	Lineno        token.Pos       `json:"-"` // 0 represents inline variable
	Deps          []*Variable     `json:"deps,omitempty"`
	IsBlockParam  bool            `json:"-"`
	BlockParamIdx int             `json:"-"`
	Ref           *Ref            `json:"ref,omitempty"`
	Type          gocode.TypeName `json:"-"`
}

func (v *Variable) String() string {
	if v.Type != nil {
		return fmt.Sprintf("%s %s", v.Name, v.Type)
	}
	return fmt.Sprintf("%s (unknown)", v.Name)
}
