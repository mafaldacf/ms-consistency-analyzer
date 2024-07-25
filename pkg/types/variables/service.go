package variables

import (
	"analyzer/pkg/types/gotypes"
)

type ServiceVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}

func (v *ServiceVariable) String() string {
	return v.VariableInfo.String()
}

func (v *ServiceVariable) LongString() string {
	return v.VariableInfo.String()
}

func (v *ServiceVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *ServiceVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *ServiceVariable) GetServiceName() string {
	return v.VariableInfo.GetType().GetName()
}

func (v *ServiceVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *ServiceVariable) GetDependencies() []Variable {
	return nil
}

func (v *ServiceVariable) GetNestedIndirectDependencies() []Variable {
	return nil
}

func (v *ServiceVariable) DeepCopy(force bool) Variable {
	return &ServiceVariable{
		VariableInfo: v.VariableInfo.DeepCopy(force),
	}
}

func (v *ServiceVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}

func (v *ServiceVariable) GetUnassaignedVariables() []Variable {
	return nil
}

func (t *ServiceVariable) GetNestedFieldVariables(prefix string) ([]Variable, []string) {
	return nil, nil
}

func (t *ServiceVariable) CopyFrom(target *ServiceVariable) {
	// nothing to be done here
}
