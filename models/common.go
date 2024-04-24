package models

import (
	"go/token"
)

type Ref struct {
	Name          string      `json:"name"`
	Id            int64       `json:"id"`
	Parent 		  string 	  `json:"origin"`
	Variable 	  *Variable   `json:"-"`
}

type Variable struct {
	Name          string      `json:"name"`
	Id            int64       `json:"id"`
	Lineno        token.Pos   `json:"-"` // 0 represents inline variable
	Deps          []*Variable `json:"deps,omitempty"`
	IsBlockParam  bool        `json:"node_param,omitempty"`
	BlockParamIdx int         `json:"node_param_idx,omitempty"`
	Ref 		  *Ref        `json:"ref,omitempty"`
}
