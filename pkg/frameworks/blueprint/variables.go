package blueprint

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
)

type BlueprintBackendVariable struct {
	variables.Variable
	VariableInfo   *variables.VariableInfo
	TargetVariable variables.Variable // variables that read cursors with cursor.One() or cursor.All() - applies only if Type is NoSQLCursorType
}

func (v *BlueprintBackendVariable) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		VariableInfo   *variables.VariableInfo `json:"blueprint_backend"`
		TargetVariable variables.Variable      `json:"target_variable,omitempty"`
	}{
		VariableInfo:   v.VariableInfo,
		TargetVariable: v.TargetVariable,
	})
}

func (v *BlueprintBackendVariable) IsNoSQLCollection() bool {
	return v.GetBlueprintBackendType().IsNoSQLComponent() && v.GetBlueprintBackendType().IsNoSQLCollection()
}

func (v *BlueprintBackendVariable) DeepCopy() variables.Variable {
	return &BlueprintBackendVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
	}
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
	return v.VariableInfo.LongString()
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
	deps := v.GetVariableInfo().GetDependencies()
	if v.TargetVariable != nil {
		deps = append(deps, v.TargetVariable.GetDependencies()...)
	}
	return deps
}

func (v *BlueprintBackendVariable) GetNestedDependencies(nearestFields bool) []variables.Variable {
	var deps = []variables.Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	deps = append(deps, v.TargetVariable.GetNestedDependencies(nearestFields)...)
	return deps
}

func (v *BlueprintBackendVariable) AddReferenceWithID(target variables.Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
}

func (v *BlueprintBackendVariable) Copy(force bool) variables.Variable {
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

func (v *BlueprintBackendVariable) SetTargetVariable(target variables.Variable) {
	if v.TargetVariable != nil {
		logger.Logger.Fatalf("[BLUEPRINT BACKEND] target (%s) already exists for cursor (%s)", target.String(), v.String())
	}
	v.TargetVariable = target
}

func (v *BlueprintBackendVariable) GetTargetVariable() variables.Variable {
	return v.TargetVariable
}
