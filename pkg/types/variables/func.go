package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type FuncVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Name         string
}

func (v *FuncVariable) String() string {
	return v.VariableInfo.String()
}

func (v *FuncVariable) LongString() string {
	return v.VariableInfo.LongString()
}

func (v *FuncVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *FuncVariable) GetType() gotypes.Type {
	if v.VariableInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS FUNC] unexpected nil type for interface variable: %s", v.String())
	}
	return v.VariableInfo.GetType()
}

func (v *FuncVariable) GetFuncType() *gotypes.FuncTypeType {
	return v.VariableInfo.GetType().(*gotypes.FuncTypeType)
}

func (v *FuncVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *FuncVariable) GetDependencies() []Variable {
	return nil
}

func (v *FuncVariable) GetNestedDependencies(nearestFields bool) []Variable {
	return nil
}

func (v *FuncVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
}

func (v *FuncVariable) Copy(force bool) Variable {
	copy := &FuncVariable{
		VariableInfo: v.VariableInfo.Copy(force),
	}
	return copy
}

func (v *FuncVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS INTERFACE - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &FuncVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
	}
	return copy
}

func (v *FuncVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}

func (v *FuncVariable) UpgradeToAssertedType(newType gotypes.Type) {
	v.GetVariableInfo().Type = newType
}
