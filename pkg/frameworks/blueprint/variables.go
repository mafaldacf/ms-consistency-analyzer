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
