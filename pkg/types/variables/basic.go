package variables

import "analyzer/pkg/types/gotypes"

type BasicVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
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

func (v *BasicVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *BasicVariable) GetDependencies() []Variable {
	return nil
}

func (v *BasicVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}

func (v *BasicVariable) DeepCopy() Variable {
	copy := &BasicVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

func (v *BasicVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}
