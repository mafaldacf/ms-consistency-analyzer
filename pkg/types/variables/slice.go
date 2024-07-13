package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type SliceVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Variables    []Variable    `json:"slice_variables,omitempty"`
}

func (v *SliceVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *SliceVariable) GetVariableAt(index int) Variable {
	if index < len(v.Variables) {
		return v.Variables[index]
	}
	logger.Logger.Fatalf("index (%d) out of bounds for tuple variable (%s) -- variables: %v", index, v.LongString(), v.Variables)
	return nil
}

func (v *SliceVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *SliceVariable) NumVariables() int {
	return len(v.Variables)
}

func (v *SliceVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *SliceVariable) GetDependencies() []Variable {
	return nil
}

func (v *SliceVariable) String() string {
	s := "("
	for i, elem := range v.Variables {
		s += elem.String()
		if i < len(v.Variables)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *SliceVariable) LongString() string {
	s := v.VariableInfo.String() + " = ("
	for i, elem := range v.Variables {
		s += elem.String()
		if i < len(v.Variables)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *SliceVariable) DeepCopy() Variable {
	copy := &SliceVariable{}
	for _, v := range v.Variables {
		copy.Variables = append(copy.Variables, v.DeepCopy())
	}
	return copy
}

func (v *SliceVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, v := range v.Variables {
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
