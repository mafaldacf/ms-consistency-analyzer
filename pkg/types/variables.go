package types

import (
	"analyzer/pkg/logger"
	"encoding/json"
	"fmt"
	"github.com/golang-collections/collections/stack"
)

type Ref struct {
	Creator  string
	Variable *Variable
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
	Name          string
	Type          Type
	Id            int64

	Deps          []*Variable
	Ref           *Ref

	IsBlockParam  bool
	BlockParamIdx int
}

func (v *Variable) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name    	string 			`json:"name"`
		Type      	string 			`json:"type,omitempty"`
		Id      	int64  			`json:"id"`
		Deps      	[]*Variable 	`json:"deps,omitempty"`
		Ref      	*Ref  			`json:"ref,omitempty"`
	}{
		Name:   v.Name,
		Type: 	v.Type.String(),
		Id: 	v.Id,
		Deps: 	v.Deps,
		Ref: 	v.Ref,
	})
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

func (v *Variable) IsReferencedObject(target *Variable) bool {
	var stack stack.Stack
	stack.Push(v)
	for stack.Len() != 0 {
		variable := stack.Pop().(*Variable)
		// cannot do variable == target since they can be different due to the Ref variable
		// but ids are still the same because they were previously matched in the abstract graph
		// e.g. in case variable == target.ref.variable
		if variable.Id == target.Id {
			return true
		}
		if variable.HasReference() {
			stack.Push(variable.Ref.Variable)
		}
		for _, dep := range variable.Deps {
			stack.Push(dep)
		}
	}
	return false
}
