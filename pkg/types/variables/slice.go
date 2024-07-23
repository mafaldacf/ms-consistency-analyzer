package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type SliceVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Elements     []Variable    `json:"slice_variables,omitempty"`
}

func (v *SliceVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *SliceVariable) GetElements() []Variable {
	return v.Elements
}

func (v *SliceVariable) AppendElements(varElements Variable) {
	if varElementsSlice, ok := varElements.(*SliceVariable); ok {
		v.Elements = append(v.Elements, varElementsSlice.GetElements()...)
	} else {
		if v.GetSliceType().UnderlyingType.IsSameType(varElements.GetType()) {
			v.Elements = append(v.Elements, varElements)
		} else {
			logger.Logger.Fatalf("[VARS SLICE] slice variable underlying type (%s) does not match elements type (%s)", utils.GetType(v.GetSliceType().UnderlyingType), utils.GetType(varElements.GetType()))
		}
	}
}

func (v *SliceVariable) GetVariableAt(index int) Variable {
	if index < len(v.Elements) {
		return v.Elements[index]
	}
	logger.Logger.Fatalf("index (%d) out of bounds for tuple variable (%s) -- variables: %v", index, v.LongString(), v.Elements)
	return nil
}

func (v *SliceVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *SliceVariable) NumVariables() int {
	return len(v.Elements)
}

func (v *SliceVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *SliceVariable) GetSliceType() *gotypes.SliceType {
	if userType, ok := v.VariableInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.SliceType)
	}
	return v.VariableInfo.GetType().(*gotypes.SliceType)
}

func (v *SliceVariable) GetDependencies() []Variable {
	return nil
}

func (v *SliceVariable) String() string {
	s := "("
	for i, elem := range v.Elements {
		s += elem.String()
		if i < len(v.Elements)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *SliceVariable) LongString() string {
	s := v.VariableInfo.String() + " = ("
	for i, elem := range v.Elements {
		s += elem.String()
		if i < len(v.Elements)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *SliceVariable) DeepCopy() Variable {
	copy := &SliceVariable{VariableInfo: v.VariableInfo.DeepCopy()}
	for _, v := range v.Elements {
		copy.Elements = append(copy.Elements, v.DeepCopy())
	}
	return copy
}

func (v *SliceVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, v := range v.Elements {
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
