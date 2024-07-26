package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type GenericVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Params       []Variable    `json:"generic_params,omitempty"`
}

func (v *GenericVariable) String() string {
	return v.VariableInfo.String()
}

func (v *GenericVariable) LongString() string {
	return v.VariableInfo.LongString()
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

func (v *GenericVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	for _, elem := range v.Params {
		deps = append(deps, elem.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *GenericVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
	if targetGeneric, ok := target.(*GenericVariable); ok {
		for i, p := range v.Params {
			if i > len(targetGeneric.Params) {
				logger.Logger.Fatalf("[VARS GENERIC - REF] invalid argument index %d for length %d in params: %v", i, (targetGeneric.Params), targetGeneric.Params)
			} else {
				p.AddReferenceWithID(targetGeneric.Params[i], creator)
			}
		}
	} else {
		logger.Logger.Fatalf("[VARS GENERIC - REF] skipping referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), GetVariableTypeAndTypeString(v), GetVariableTypeAndTypeString(target))
	}
	logger.Logger.Tracef("[VARS GENERIC - REF] added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
}

func (v *GenericVariable) DeepCopy(force bool) Variable {
	copy := &GenericVariable{
		VariableInfo: v.VariableInfo.DeepCopy(force),
	}
	for _, p := range v.Params {
		copy.Params = append(copy.Params, p.DeepCopy(force))
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
