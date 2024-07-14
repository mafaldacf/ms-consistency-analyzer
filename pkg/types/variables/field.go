package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type FieldVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Underlying   Variable      `json:"underlying_field,omitempty"`
}

func (v *FieldVariable) String() string {
	return v.VariableInfo.String()
}

func (v *FieldVariable) LongString() string {
	return v.VariableInfo.LongString()
}

func (v *FieldVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *FieldVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *FieldVariable) AssignVariable(rvariable Variable) {
	if !v.Underlying.GetType().IsSameType(rvariable.GetType()) {
		logger.Logger.Fatalf("[VAR FIELD] lvariable (%s) with type (%s) does not match rvariable (%s) with type (%s)", v.Underlying.String(), utils.GetType(v.Underlying), rvariable.String(), utils.GetType(rvariable))
	}
	logger.Logger.Infof("[VAR FIELD] assigning lvariable (%s) with type (%s) with rvariable (%s) with type (%s)", v.Underlying.String(), utils.GetType(v.Underlying), rvariable.String(), utils.GetType(rvariable))
	v.Underlying = rvariable
}

func (v *FieldVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *FieldVariable) GetDependencies() []Variable {
	return v.Underlying.GetDependencies()
}

func (v *FieldVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.Id = target.GetId()
	v.VariableInfo.Reference = &Reference{
		Creator:  creator,
		Variable: target,
	}
	v.Underlying.AddReferenceWithID(target, creator)
}

func (v *FieldVariable) DeepCopy() Variable {
	copy := &FieldVariable{
		VariableInfo: v.VariableInfo,
		Underlying:   v.Underlying.DeepCopy(),
	}
	return copy
}

func (v *FieldVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		variables = append(variables, v.Underlying.GetUnassaignedVariables()...)
	}
	return variables
}

func (t *FieldVariable) GetNestedFieldVariables(prefix string) ([]Variable, []string) {
	variableType := t.VariableInfo.Type
	if userType, ok := t.GetType().(*gotypes.UserType); ok {
		variableType = userType.UserType
	}
	prefix = prefix + "." + variableType.(*gotypes.FieldType).FieldName

	nestedVariables := []Variable{t}
	nestedNames := []string{prefix}
	if nestedField, ok := t.Underlying.(*FieldVariable); ok {
		r1, r2 := nestedField.GetNestedFieldVariables(prefix)
		nestedVariables = append(nestedVariables, r1...)
		nestedNames = append(nestedNames, r2...)
	} else if nestedStruct, ok := t.Underlying.(*StructVariable); ok {
		r1, r2 := nestedStruct.GetNestedFieldVariables(prefix)
		nestedVariables = append(nestedVariables, r1...)
		nestedNames = append(nestedNames, r2...)
	} else {
		nestedVariables = append(nestedVariables, t.Underlying)
		nestedNames = append(nestedNames, prefix)
	}
	return nestedVariables, nestedNames
}
