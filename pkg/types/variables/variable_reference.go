package variables

import (
	"encoding/json"
	"fmt"
)

type Reference struct {
	Variable
	Creator string
	Id      int64
}

func (ref *Reference) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name    string `json:"name"`
		Creator string `json:"creator"`
		//Id      int64  `json:"id"`
		//Variable Variable `json:"variable"`
		/* IndirectDeps string `json:"indirect_deps"` */
		/* Params 			[]Variable 		`json:"ref_params"` */
	}{
		Name:    ref.Variable.GetVariableInfo().GetName(),
		Creator: ref.Creator,
		//Id:      ref.Variable.GetId(),
		//Variable: ref.Variable,
		/* IndirectDeps: getDependenciesString(GetIndirectDependencies(ref)...), */
		/* Params:  		ref.Variable.GetDependencies(), */
	})
}

func (ref *Reference) Copy(force bool) Variable {
	return &Reference{
		Variable: ref.Variable.Copy(force),
		Creator:  ref.Creator,
	}
}

func (ref *Reference) DeepCopy() Variable {
	return &Reference{
		Variable: ref.Variable.DeepCopy(),
		Creator:  ref.Creator,
	}
}

func (ref *Reference) String() string {
	if ref.Variable != nil {
		return fmt.Sprintf("ref <%s> @ %s", ref.Variable.String(), ref.Creator)
	}
	return "nil-reference"
}

func (ref *Reference) GetVariableInfo() *VariableInfo {
	if ref.Variable != nil {
		return ref.Variable.GetVariableInfo()
	}
	return nil
}

func (ref *Reference) GetDependencies() []Variable {
	if ref.Variable != nil {
		return ref.Variable.GetDependencies()
	}
	return nil
}

func (ref *Reference) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{ref}
	if ref.Variable != nil {
		deps = append(deps, ref.Variable.GetNestedDependencies(nearestFields)...)
	}
	return deps
}
