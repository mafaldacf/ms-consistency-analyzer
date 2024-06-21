package variables

import "analyzer/pkg/types/gotypes"

type ArrayVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Elements     []Variable    `json:"array_elems,omitempty"`
}

func (v *ArrayVariable) String() string {
	return v.VariableInfo.String()
}

func (v *ArrayVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *ArrayVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *ArrayVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *ArrayVariable) AddElement(element Variable) {
	v.Elements = append(v.Elements, element)
}

func (v *ArrayVariable) AddElements(element []Variable) {
	v.Elements = append(v.Elements, element...)
}

func (v *ArrayVariable) GetDependencies() []Variable {
	return v.Elements
}

func (v *ArrayVariable) DeepCopy() Variable {
	copy := &ArrayVariable{
		VariableInfo: v.VariableInfo,
	}
	for _, v := range v.Elements {
		copy.Elements = append(copy.Elements, v.DeepCopy())
	}
	return copy
}

func (v *ArrayVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, v := range v.Elements {
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
