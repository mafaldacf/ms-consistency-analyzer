package blueprint

import (
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
)

type BlueprintBackendVariable struct {
	variables.Variable `json:"-"`
	VariableInfo       *variables.VariableInfo `json:"variable"`
}

func (v *BlueprintBackendVariable) IsNoSQLCollection() bool {
	return v.GetBlueprintBackendType().IsNoSQLComponent() && v.GetBlueprintBackendType().IsNoSQLCollection()
}

func (v *BlueprintBackendVariable) IsNoSQLCursor() bool {
	return v.GetBlueprintBackendType().IsNoSQLComponent() && v.GetBlueprintBackendType().IsNoSQLCursor()
}

func (v *BlueprintBackendVariable) IsNoSQLComponent() bool {
	return v.GetBlueprintBackendType().IsNoSQLComponent()
}

func (v *BlueprintBackendVariable) String() string {
	return v.VariableInfo.String()
}

func (v *BlueprintBackendVariable) LongString() string {
	return v.VariableInfo.String()
}

func (v *BlueprintBackendVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *BlueprintBackendVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *BlueprintBackendVariable) GetBlueprintBackendType() *BlueprintBackendType {
	return v.VariableInfo.GetType().(*BlueprintBackendType)
}

func (v *BlueprintBackendVariable) GetVariableInfo() *variables.VariableInfo {
	return v.VariableInfo
}

func (v *BlueprintBackendVariable) GetDependencies() []variables.Variable {
	return nil
}

func (v *BlueprintBackendVariable) AddReferenceWithID(target variables.Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}

func (v *BlueprintBackendVariable) DeepCopy() variables.Variable {
	copy := &BlueprintBackendVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

func (v *BlueprintBackendVariable) GetUnassaignedVariables() []variables.Variable {
	var variables []variables.Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}
