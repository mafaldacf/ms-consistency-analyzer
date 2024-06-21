package variables

import "analyzer/pkg/types/gotypes"

type ChanVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}

func (v *ChanVariable) String() string {
	return v.VariableInfo.String()
}

func (v *ChanVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *ChanVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *ChanVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *ChanVariable) GetDependencies() []Variable {
	return nil
}

func (v *ChanVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}
func (v *ChanVariable) DeepCopy() Variable {
	copy := &ChanVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}
func (v *ChanVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}
