package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type AddressVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	AddressOf    Variable      `json:"addr_of,omitempty"`
}

func (v *AddressVariable) String() string {
	return v.VariableInfo.String()
}

func (v *AddressVariable) LongString() string {
	return v.VariableInfo.String() + " = " + "*" + v.AddressOf.LongString()
}

func (v *AddressVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *AddressVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *AddressVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *AddressVariable) GetDependencies() []Variable {
	return v.AddressOf.GetDependencies()
}

func (v *AddressVariable) GetAddressOf() Variable {
	return v.AddressOf
}

func (v *AddressVariable) AddReferenceWithID(target Variable, creator string) {
	if targetAddressOf, ok := target.(*AddressVariable); ok {
		v.AddressOf.AddReferenceWithID(targetAddressOf.AddressOf, creator)
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
}

func (v *AddressVariable) DeepCopy() Variable {
	copy := &AddressVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
		AddressOf:    v.AddressOf.DeepCopy(),
	}
	return copy
}

func (v *AddressVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		variables = append(variables, v.AddressOf.GetUnassaignedVariables()...)
	}
	return variables
}
