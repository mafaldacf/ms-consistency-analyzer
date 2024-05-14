package types

import (
	"analyzer/pkg/logger"
	"encoding/json"
	"fmt"
	"go/ast"
	"go/token"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

type Field interface {
	GetTypeName() string
	GetIndex() int
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
	Idx    int
}
type DatabaseField struct {
	Field
	gocode.Variable
	Lineno     token.Pos
	Ast        *ast.Field
	IsQueue    bool
	DbInstance DatabaseInstance
	Idx        int
}

func (svc *ServiceField) GetTypeName() string {
	return svc.GetType()
}

func (svc *ServiceField) GetIndex() int {
	return svc.Idx
}

func (db *DatabaseField) GetTypeName() string {
	return db.GetType()
}

func (db *DatabaseField) GetIndex() int {
	return db.Idx
}

func (fn *FunctionField) GetTypeName() string {
	return fn.GetType()
}

type Method interface {
	String() string
	GetParams() []*FunctionField
	GetReturns() []*FunctionField
	IsQueueWrite() bool
	IsQueueRead() bool
}

type Ref struct {
	Creator  string    `json:"creator,omitempty"`
	Variable *Variable `json:"-"`
}

// MarshalJSON is used by app.Save()
func (ref *Ref) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name    string `json:"name"`
		Creator string `json:"creator"`
		Id      int64  `json:"id"`
	}{
		Name:    ref.Variable.Name,
		Creator: ref.Creator,
		Id:      ref.Variable.Id,
	})
}

const VARIABLE_INLINE_ID int64 = -1
const VARIABLE_UNASSIGNED_ID int64 = -2

type Variable struct {
	Name          string          `json:"name"`
	Id            int64           `json:"id"`
	Lineno        token.Pos       `json:"-"` // 0 (default) represents inline variable
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

func (v *Variable) EqualBlockParamIndex(idx int) bool {
	return v.BlockParamIdx == idx
}

func (v *Variable) IsUnassigned() bool {
	return v.Id < 0
}

func (v *Variable) HasReference() bool {
	return v.Ref != nil
}

func (v *Variable) AssignID(id int64) {
	v.Id = id
}

func (v *Variable) AddDependencies(deps []*Variable) {
	v.Deps = append(v.Deps, deps...)
}

func (v *Variable) AddReferenceWithID(callerParam *Variable, callerStr string) {
	v.Id = callerParam.Id
	v.Ref = &Ref{
		Creator:  callerStr,
		Variable: callerParam,
	}
	logger.Logger.Debugf("added reference (%s) -> (%s) with id = %d (creator: %s)", v.Name, callerParam.Name, v.Id, callerStr)
}

func (v *Variable) AddOriginalReferenceWithID(ref *Ref) {
	v.Id = ref.Variable.Id
	v.Ref = ref
}
