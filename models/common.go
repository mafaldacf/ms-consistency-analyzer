package models

import (
	"go/token"
)

type Variable struct {
	Lineno token.Pos 	`json:"lineno"`
	Id 	   int 			`json:"id"`
	Name   string 		`json:"name"`
	Deps   []*Variable 	`json:"deps"`
}
