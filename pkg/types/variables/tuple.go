package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type TupleVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Variables    []Variable    `json:"tuple_variables,omitempty"`
}

func (v *TupleVariable) GetVariableInfo() *VariableInfo {
	return nil
}

func (v *TupleVariable) AddVariable(variable Variable) {
	logger.Logger.Warnf("[VARS TUPLE] adding variable (%s) to tuple variable (%s)", variable.String(), v.String())
	v.Variables = append(v.Variables, variable)
	v.GetTupleType().AddType(variable.GetType())
}

func (v *TupleVariable) GetVariables() []Variable {
	return v.Variables
}

func (v *TupleVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
	for i := 0; i < len(v.Variables); i++ {
		v.AddReferenceWithID(target.GetElementAt(i), creator)
	}
}

func (v *TupleVariable) MergeTupleVariable(tupleVariable *TupleVariable) {
	logger.Logger.Warnf("[VARS TUPLE] merging tuple variable (%s) to (%s)", tupleVariable.String(), v.String())
	v.Variables = append(v.Variables, tupleVariable.GetVariables()...)
}

func (v *TupleVariable) GetVariableAt(index int) Variable {
	if index < len(v.Variables) {
		return v.Variables[index]
	}
	logger.Logger.Fatalf("index (%d) out of bounds for tuple variable (%s) -- variables: %v", index, v.LongString(), v.Variables)
	return nil
}

func (v *TupleVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *TupleVariable) NumVariables() int {
	return len(v.Variables)
}

func (v *TupleVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *TupleVariable) GetTupleType() *gotypes.TupleType {
	return v.VariableInfo.GetType().(*gotypes.TupleType)
}

func (v *TupleVariable) GetDependencies() []Variable {
	return v.Variables
}

func (v *TupleVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	for _, elem := range v.Variables {
		deps = append(deps, elem.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *TupleVariable) String() string {
	s := "("
	for i, elem := range v.Variables {
		s += elem.String()
		if i < len(v.Variables)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *TupleVariable) LongString() string {
	s := v.VariableInfo.String() + " = ("
	for i, elem := range v.Variables {
		s += elem.String()
		if i < len(v.Variables)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *TupleVariable) Copy(force bool) Variable {
	copy := &TupleVariable{VariableInfo: v.VariableInfo.Copy(force)}
	for _, v := range v.Variables {
		newElem := v.Copy(force)
		copy.Variables = append(copy.Variables, newElem)
		newElem.GetVariableInfo().SetParent(newElem, copy)
	}
	return copy
}

func (v *TupleVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS TUPLE - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &TupleVariable{VariableInfo: v.VariableInfo.DeepCopy()}
	for _, v := range v.Variables {
		newElem := v.DeepCopy()
		copy.Variables = append(copy.Variables, newElem)
		newElem.GetVariableInfo().SetParent(newElem, copy)
	}
	return copy
}

func (v *TupleVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, v := range v.Variables {
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
