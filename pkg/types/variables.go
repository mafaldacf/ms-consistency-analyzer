package types

import (
	"analyzer/pkg/logger"
	"encoding/json"
	"fmt"
)

type Ref struct {
	Creator  string    `json:"creator,omitempty"`
	Variable *Variable `json:"-"`
}

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

	Deps          []*Variable     `json:"deps,omitempty"`
	Ref           *Ref            `json:"ref,omitempty"`

	IsBlockParam  bool            `json:"-"`
	BlockParamIdx int             `json:"-"`

	Type          Type 			  `json:"-"`
}

func (v *Variable) String() string {
	if v.Type != nil {
		return fmt.Sprintf("%s %s", v.Name, v.Type)
	}
	return fmt.Sprintf("%s (unknown)", v.Name)
}

func (v *Variable) IsBlockParameter() bool {
	return v.IsBlockParam
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
