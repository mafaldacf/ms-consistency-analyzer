package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type PointerVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	PointerTo    Variable      `json:"ptr_to,omitempty"`
}

func (v *PointerVariable) String() string {
	return v.VariableInfo.String()
}

func (v *PointerVariable) LongString() string {
	return v.VariableInfo.LongString() + " = " + "*" + v.PointerTo.LongString()
}

func (v *PointerVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *PointerVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *PointerVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *PointerVariable) GetDependencies() []Variable {
	return []Variable{v.PointerTo}
}

func (v *PointerVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	deps = append(deps, v.PointerTo.GetNestedDependencies(nearestFields)...)
	return deps
}

func (v *PointerVariable) GetPointerTo() Variable {
	if v.PointerTo == nil {
		logger.Logger.Fatalf("[VARS POINTER] unexpected nil pointer to variable in pointer variable (%s)", v.String())
	}
	return v.PointerTo
}

func (v *PointerVariable) AddReferenceWithID(target Variable, creator string) {
	if targetPointerTo, ok := target.(*PointerVariable); ok {
		v.PointerTo.AddReferenceWithID(targetPointerTo.PointerTo, creator)
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
}

func (v *PointerVariable) Copy(force bool) Variable {
	copy := &PointerVariable{
		VariableInfo: v.VariableInfo.Copy(force),
		PointerTo:    v.PointerTo, // underlying values of pointers are never deep copied
	}
	copy.PointerTo.GetVariableInfo().SetParent(copy.PointerTo, copy)
	return copy
}

func (v *PointerVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS POINTER - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &PointerVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
		PointerTo:    v.PointerTo.DeepCopy(), // underlying values of pointers are never deep copied
	}
	copy.PointerTo.GetVariableInfo().SetParent(copy.PointerTo, copy)
	return copy
}

func (v *PointerVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		variables = append(variables, v.PointerTo.GetUnassaignedVariables()...)
	}
	return variables
}
