package variables

import "analyzer/pkg/types/gotypes"

type InterfaceVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}

func (v *InterfaceVariable) String() string {
	return v.VariableInfo.String()
}

func (v *InterfaceVariable) LongString() string {
	return v.VariableInfo.LongString()
}

func (v *InterfaceVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *InterfaceVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *InterfaceVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *InterfaceVariable) GetDependencies() []Variable {
	return nil
}

func (v *InterfaceVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}

func (v *InterfaceVariable) DeepCopy() Variable {
	copy := &InterfaceVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
	}
	return copy
}

func (v *InterfaceVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}
