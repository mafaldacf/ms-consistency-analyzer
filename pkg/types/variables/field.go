package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type FieldVariable struct {
	Variable        `json:"-"`
	VariableInfo    *VariableInfo `json:"variable"`
	WrappedVariable Variable      `json:"wrapped_variable,omitempty"`
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

func (v *FieldVariable) GetFieldType() *gotypes.FieldType {
	return v.VariableInfo.GetType().(*gotypes.FieldType)
}

func (v *FieldVariable) FieldTypeIsDirectStructType() bool {
	// if it is directly a struct type (and not user type)
	_, ok := v.VariableInfo.GetType().(*gotypes.FieldType).GetWrappedType().(*gotypes.StructType)
	return ok
}

func (v *FieldVariable) AssignVariable(rvariable Variable) {
	// e.g. post.Text = post2.Text2
	if v.GetType().IsSameType(rvariable.GetType()) {
		logger.Logger.Infof("[VAR FIELD] (a) assigning variables with types (%s --> %s) for lvariable (%s) and rvariable (%s)", utils.GetType(v.WrappedVariable), utils.GetType(rvariable), v.WrappedVariable.String(), rvariable.String())
		v.WrappedVariable = rvariable.(*FieldVariable).WrappedVariable.DeepCopy(false)
		return
	}
	// e.g. post.Text = text
	if v.WrappedVariable.GetType().IsSameType(rvariable.GetType()) {
		logger.Logger.Infof("[VAR FIELD] (b) assigning variables with types (%s --> %s) for lvariable (%s) and rvariable (%s)", utils.GetType(v.WrappedVariable), utils.GetType(rvariable), v.WrappedVariable.String(), rvariable.String())
		v.WrappedVariable = rvariable.DeepCopy(false)
		return
	}

	// e.g. some_slice = some_array
	_, leftSliceOk := v.WrappedVariable.GetType().(*gotypes.SliceType)
	_, rightArrayOk := rvariable.GetType().(*gotypes.ArrayType)
	if leftSliceOk && rightArrayOk {
		// maintain left slice and add copy right array
		v.WrappedVariable = rvariable.DeepCopy(false)
		v.WrappedVariable.(*ArrayVariable).UpgradeToSlice()
		return
	}

	logger.Logger.Fatalf("[VAR FIELD] cannot assign variable with unmatched types (%s --> %s) for lvariable (%s) and rvariable (%s)", utils.GetType(v.WrappedVariable), utils.GetType(rvariable), v.WrappedVariable.String(), rvariable.String())
}

func (v *FieldVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *FieldVariable) GetDependencies() []Variable {
	var deps = []Variable{v.WrappedVariable}
	return append(deps, v.WrappedVariable.GetDependencies()...)
}

func (v *FieldVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.Id = target.GetId()
	v.VariableInfo.Reference = &Reference{
		Creator:  creator,
		Variable: target,
	}
	v.WrappedVariable.AddReferenceWithID(target, creator)
}

func (v *FieldVariable) DeepCopy(force bool) Variable {
	copy := &FieldVariable{
		VariableInfo:    v.VariableInfo.DeepCopy(force),
		WrappedVariable: v.WrappedVariable.DeepCopy(force),
	}
	return copy
}

func (v *FieldVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		variables = append(variables, v.WrappedVariable.GetUnassaignedVariables()...)
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
	if nestedField, ok := t.WrappedVariable.(*FieldVariable); ok {
		r1, r2 := nestedField.GetNestedFieldVariables(prefix)
		nestedVariables = append(nestedVariables, r1...)
		nestedNames = append(nestedNames, r2...)
	} else if nestedStruct, ok := t.WrappedVariable.(*StructVariable); ok {
		r1, r2 := nestedStruct.GetNestedFieldVariables(prefix)
		nestedVariables = append(nestedVariables, r1...)
		nestedNames = append(nestedNames, r2...)
	} else {
		nestedVariables = append(nestedVariables, t.WrappedVariable)
		nestedNames = append(nestedNames, prefix)
	}
	return nestedVariables, nestedNames
}

func (t *FieldVariable) GetNestedFieldVariablesWithReferences(prefix string) ([]Variable, []string) {
	nestedVariables, nestedIDs := t.GetNestedFieldVariables(prefix)
	if reference := t.GetVariableInfo().GetReference(); reference != nil {
		logger.Logger.Debugf("HEREEEEE FOR REFERENCE %s", reference.String())
		nestedVariablesRef, nestedIDsRef := reference.Variable.(*FieldVariable).GetNestedFieldVariablesWithReferences(prefix)
		nestedVariables = append(nestedVariables, nestedVariablesRef...)
		nestedIDs = append(nestedIDs, nestedIDsRef...)
	}
	return nestedVariables, nestedIDs
}
