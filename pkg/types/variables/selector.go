package variables

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type SelectorVariable struct {
	Variable `json:"wrapped_variable"`
	Parent   Variable `json:"-"`
	Field    string   `json:"selector"`
}

func (v *SelectorVariable) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Variable Variable `json:"wrapped_variable"`
		Parent   string   `json:"parent"`
		Field    string   `json:"selector"`
	}{
		Variable: v.Variable,
		Parent:   v.Parent.GetVariableInfo().Name,
		Field:    v.Field,
	})
}

func (v *SelectorVariable) String() string {
	return v.Variable.String()
}

func (v *SelectorVariable) GetId() int64 {
	return v.Variable.GetId()
}

func (v *SelectorVariable) GetType() gotypes.Type {
	return v.Variable.GetType()
}

func (v *SelectorVariable) GetVariableInfo() *VariableInfo {
	return v.Variable.GetVariableInfo()
}

func (v *SelectorVariable) GetDependencies() []Variable {
	return v.Variable.GetDependencies()
}

func (v *SelectorVariable) AddReferenceWithID(target Variable, creator string) {
	logger.Logger.Warnf("IGNORING REFERENCES FOR SELECTOR VARIABLE!!")
}

func (v *SelectorVariable) DeepCopy(force bool) Variable {
	copy := &SelectorVariable{
		Parent: v.Parent.DeepCopy(force),
		Field:  v.Field,
	}
	return copy
}

func (v *SelectorVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		variables = append(variables, v.Parent.GetUnassaignedVariables()...)
	}
	return variables
}
