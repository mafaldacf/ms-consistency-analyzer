package blueprint

import (
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
)

type NoSQLCollectionVariable struct {
	variables.Variable `json:"-"`
	VariableInfo       *variables.VariableInfo `json:"variable"`
}

func (v *NoSQLCollectionVariable) String() string {
	return v.VariableInfo.String()
}

func (v *NoSQLCollectionVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *NoSQLCollectionVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *NoSQLCollectionVariable) GetVariableInfo() *variables.VariableInfo {
	return v.VariableInfo
}

func (v *NoSQLCollectionVariable) GetDependencies() []variables.Variable {
	return nil
}

func (v *NoSQLCollectionVariable) AddReferenceWithID(target variables.Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}

func (v *NoSQLCollectionVariable) DeepCopy() variables.Variable {
	copy := &NoSQLCollectionVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

func (v *NoSQLCollectionVariable) GetUnassaignedVariables() []variables.Variable {
	var variables []variables.Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}

type NoSQLCursorVariable struct {
	variables.Variable `json:"-"`
	VariableInfo       *variables.VariableInfo `json:"variable"`
}

func (v *NoSQLCursorVariable) String() string {
	return v.VariableInfo.String()
}

func (v *NoSQLCursorVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *NoSQLCursorVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *NoSQLCursorVariable) GetVariableInfo() *variables.VariableInfo {
	return v.VariableInfo
}

func (v *NoSQLCursorVariable) GetDependencies() []variables.Variable {
	return nil
}

func (v *NoSQLCursorVariable) AddReferenceWithID(target variables.Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}

func (v *NoSQLCursorVariable) DeepCopy() variables.Variable {
	copy := &NoSQLCursorVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

func (v *NoSQLCursorVariable) GetUnassaignedVariables() []variables.Variable {
	var variables []variables.Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}
