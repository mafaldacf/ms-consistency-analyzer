package blueprint

import (
	"analyzer/pkg/types"
)

type NoSQLCollectionVariable struct {
	types.Variable `json:"-"`
	VariableInfo   *types.VariableInfo `json:"variable"`
}

func (v *NoSQLCollectionVariable) String() string {
	return v.VariableInfo.String()
}
func (v *NoSQLCollectionVariable) GetVariableInfo() *types.VariableInfo {
	return v.VariableInfo
}
func (v *NoSQLCollectionVariable) GetDependencies() []types.Variable {
	return nil
}
func (v *NoSQLCollectionVariable) AddReferenceWithID(target types.Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}
func (v *NoSQLCollectionVariable) DeepCopy() types.Variable {
	copy := &NoSQLCollectionVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

type NoSQLCursorVariable struct {
	types.Variable `json:"-"`
	VariableInfo   *types.VariableInfo `json:"variable"`
}

func (v *NoSQLCursorVariable) String() string {
	return v.VariableInfo.String()
}
func (v *NoSQLCursorVariable) GetVariableInfo() *types.VariableInfo {
	return v.VariableInfo
}
func (v *NoSQLCursorVariable) GetDependencies() []types.Variable {
	return nil
}
func (v *NoSQLCursorVariable) AddReferenceWithID(target types.Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}
func (v *NoSQLCursorVariable) DeepCopy() types.Variable {
	copy := &NoSQLCursorVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}
