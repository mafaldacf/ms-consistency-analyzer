package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type ChanVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}

func (v *ChanVariable) String() string {
	return v.VariableInfo.String()
}

func (v *ChanVariable) LongString() string {
	return v.VariableInfo.LongString()
}

func (v *ChanVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *ChanVariable) GetType() gotypes.Type {
	if v.VariableInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for chan variable: %s", v.String())
	}
	return v.VariableInfo.GetType()
}

func (v *ChanVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *ChanVariable) GetDependencies() []Variable {
	return nil
}

func (v *ChanVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	return deps
}

func (v *ChanVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
}

func (v *ChanVariable) Copy(force bool) Variable {
	copy := &ChanVariable{
		VariableInfo: v.VariableInfo.Copy(force),
	}
	return copy
}

func (v *ChanVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS CHAN - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &ChanVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
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
