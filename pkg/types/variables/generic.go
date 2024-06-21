package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type GenericVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Params       []Variable    `json:"generic_params,omitempty"`
}

func (v *GenericVariable) String() string {
	return v.VariableInfo.String()
}

func (v *GenericVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *GenericVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *GenericVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *GenericVariable) GetDependencies() []Variable {
	return v.Params
}

func (v *GenericVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
	if targetGeneric, ok := target.(*GenericVariable); ok {
		for i, p := range v.Params {
			if i > len(targetGeneric.Params) {
				logger.Logger.Warnf("invalid argument index %d for length %d in params: %v", i, (targetGeneric.Params), targetGeneric.Params)
			} else {
				p.AddReferenceWithID(targetGeneric.Params[i], creator)
			}
		}
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
	logger.Logger.Debugf("added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
}

func (v *GenericVariable) DeepCopy() Variable {
	copy := &GenericVariable{
		VariableInfo: v.VariableInfo,
	}
	for _, p := range v.Params {
		copy.Params = append(copy.Params, p.DeepCopy())
	}
	return copy
}

func (v *GenericVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, p := range v.Params {
			variables = append(variables, p.GetUnassaignedVariables()...)
		}
	}
	return variables
}
