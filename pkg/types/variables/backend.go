package variables

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type BackendVariable struct {
	Variable
	Origin       *Variable
	VariableInfo *VariableInfo
}

func (v *BackendVariable) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		VariableInfo *VariableInfo `json:"backend"`
	}{
		VariableInfo: v.VariableInfo,
	})
}

func (v *BackendVariable) String() string {
	return v.VariableInfo.String()
}

func (v *BackendVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *BackendVariable) GetType() gotypes.Type {
	if v.VariableInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for backend variable: %s", v.String())
	}
	return v.VariableInfo.GetType()
}

func (v *BackendVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *BackendVariable) GetDependencies() []Variable {
	return v.GetVariableInfo().GetDependencies()
}

func (v *BackendVariable) GetNestedDependencies(nearestFields bool) []Variable {
	return nil
}

func (v *BackendVariable) Copy(force bool) Variable {
	return &BackendVariable{
		VariableInfo: v.VariableInfo.Copy(force),
	}
}

func (v *BackendVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS BACKEND - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	return &BackendVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
	}
}

func (v *BackendVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
}

func (v *BackendVariable) GetUnassaignedVariables() []Variable {
	return nil
}

func (t *BackendVariable) GetNestedFieldVariables(prefix string, noSQL bool) ([]Variable, []string) {
	return nil, nil
}

func (t *BackendVariable) CopyFrom(target *BackendVariable) {
	// nothing to be done here
}
