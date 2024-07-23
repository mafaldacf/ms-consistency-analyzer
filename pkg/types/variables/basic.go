package variables

import "analyzer/pkg/types/gotypes"

type BasicVariable struct {
	Variable            `json:"-"`
	VariableInfo        *VariableInfo `json:"variable"`
	UnderlyingVariables []Variable `json:"-"` // variables that influence the value of basic variables - e.g. "some_variable" in len(some_variable)
}

func (v *BasicVariable) String() string {
	return v.VariableInfo.String()
}

func (v *BasicVariable) LongString() string {
	return v.VariableInfo.String()
}

func (v *BasicVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *BasicVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *BasicVariable) GetBasicType() *gotypes.BasicType {
	return v.VariableInfo.GetType().(*gotypes.BasicType)
}

func (v *BasicVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *BasicVariable) GetDependencies() []Variable {
	return v.UnderlyingVariables
}

func (v *BasicVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
	for _, v := range v.UnderlyingVariables {
		v.AddReferenceWithID(target, creator)
	}
}

func (v *BasicVariable) DeepCopy() Variable {
	var underlyingVariablesCopy []Variable
	for _, v := range v.UnderlyingVariables {
		underlyingVariablesCopy = append(underlyingVariablesCopy, v.DeepCopy())
	}
	copy := &BasicVariable{
		VariableInfo:        v.VariableInfo.DeepCopy(),
		UnderlyingVariables: underlyingVariablesCopy,
	}
	return copy
}

func (v *BasicVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	for _, v := range v.UnderlyingVariables {
		variables = append(variables, v.GetUnassaignedVariables()...)
	}
	return variables
}
