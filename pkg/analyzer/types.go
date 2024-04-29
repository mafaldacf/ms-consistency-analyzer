package analyzer

import (
	"go/token"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

type Method interface {
	// TODO: GetName(), GetPackage(), and return package.name in String()
	String() string
	GetNumParams() int
}

type Ref struct {
	Name     string    `json:"name"`
	Creator  string    `json:"creator"`
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
	return v.Name
	/* if v.Type != nil && v.Type.String() != "" {
		return fmt.Sprintf("%s %s", v.Name, v.Type)
	}
	return fmt.Sprintf("%s (unknown)", v.Name) */
}
