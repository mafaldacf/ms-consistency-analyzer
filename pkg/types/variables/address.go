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
	return []Variable{v.AddressOf}
}

func (v *AddressVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	deps = append(deps, v.AddressOf.GetNestedDependencies(nearestFields)...)
	return deps
}

func (v *AddressVariable) GetAddressOf() Variable {
	return v.AddressOf
}

func (v *AddressVariable) AddReferenceWithID(target Variable, creator string) {
	if targetAddressOf, ok := target.(*AddressVariable); ok {
		v.AddressOf.AddReferenceWithID(targetAddressOf.AddressOf, creator)
	} else {
		logger.Logger.Fatalf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
}

func (v *AddressVariable) Copy(force bool) Variable {
	copy := &AddressVariable{
		VariableInfo: v.VariableInfo.Copy(force),
		AddressOf:    v.AddressOf, // underlying values of addresses are never deep copied
	}
	copy.AddressOf.GetVariableInfo().SetParent(copy.AddressOf, copy)
	return copy
}

func (v *AddressVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS ADDRESS - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &AddressVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
		AddressOf:    v.AddressOf.DeepCopy(), // underlying values of addresses are never deep copied
	}
	copy.AddressOf.GetVariableInfo().SetParent(copy.AddressOf, copy)
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
