package analyzer

import (
	"fmt"
	"go/token"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

type Ref struct {
	Name          string      `json:"name"`
	Id            int64       `json:"id"`
	Origin 		  string 	  `json:"origin"`
	Variable 	  *Variable   `json:"-"`
}

type Variable struct {
	Name          string      		`json:"name"`
	Id            int64       		`json:"id"`
	Lineno        token.Pos   		`json:"-"` // 0 represents inline variable
	Deps          []*Variable 		`json:"deps,omitempty"`
	IsBlockParam  bool        		`json:"node_param,omitempty"`
	BlockParamIdx int         		`json:"node_param_idx,omitempty"`
	Ref 		  *Ref        		`json:"ref,omitempty"`
	Type 		  gocode.TypeName 	`json:"-"`
}

func (v *Variable) String() string {
	if v.Type != nil && v.Type.String() != "" {
		return fmt.Sprintf("%s (%s)", v.Name, v.Type)
	}
	return fmt.Sprintf("%s (unknown)", v.Name)
}
