package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type TupleVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Variables    []Variable    `json:"tuple_variables,omitempty"`
}

func (v *TupleVariable) GetVariableInfo() *VariableInfo {
	return nil
}

func (v *TupleVariable) GetVariableAt(index int) Variable {
	if index < len(v.Variables) {
		return v.Variables[index]
	}
	logger.Logger.Fatalf("index (%d) out of bounds for tuple variable (%s) -- variables: %v", index, v.LongString(), v.Variables)
	return nil
}

func (v *TupleVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *TupleVariable) NumVariables() int {
	return len(v.Variables)
}

func (v *TupleVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *TupleVariable) GetDependencies() []Variable {
	return nil
}

func (v *TupleVariable) String() string {
	s := "("
	for i, elem := range v.Variables {
		s += elem.String()
		if i < len(v.Variables)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *TupleVariable) LongString() string {
	s := v.VariableInfo.String() + " = ("
	for i, elem := range v.Variables {
		s += elem.String()
		if i < len(v.Variables)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *TupleVariable) DeepCopy() Variable {
	copy := &TupleVariable{}
	for _, v := range v.Variables {
		copy.Variables = append(copy.Variables, v.DeepCopy())
	}
	return copy
}

func (v *TupleVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, v := range v.Variables {
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
