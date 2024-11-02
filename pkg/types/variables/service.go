package variables

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type ServiceVariable struct {
	Variable
	VariableInfo       *VariableInfo
	UnderlyingVariable Variable
}

func (v *ServiceVariable) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		VariableInfo       *VariableInfo `json:"service"`
		UnderlyingVariable Variable      `json:"underlying_variable"`
	}{
		VariableInfo:       v.VariableInfo,
		UnderlyingVariable: v.UnderlyingVariable,
	})
}

func (v *ServiceVariable) String() string {
	return v.VariableInfo.String()
}

func (v *ServiceVariable) LongString() string {
	return v.VariableInfo.String()
}

func (v *ServiceVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *ServiceVariable) GetType() gotypes.Type {
	if v.VariableInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for service variable: %s", v.String())
	}
	return v.VariableInfo.GetType()
}

func (v *ServiceVariable) GetServiceName() string {
	return v.VariableInfo.GetType().GetName()
}

func (v *ServiceVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *ServiceVariable) GetDependencies() []Variable {
	return v.GetVariableInfo().GetDependencies()
}

func (v *ServiceVariable) GetNestedDependencies(nearestFields bool) []Variable {
	return nil
}

func (v *ServiceVariable) Copy(force bool) Variable {
	return &ServiceVariable{
		VariableInfo: v.VariableInfo.Copy(force),
	}
}

func (v *ServiceVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS SERVICE - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	return &ServiceVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
	}
}

func (v *ServiceVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
}

func (v *ServiceVariable) GetUnassaignedVariables() []Variable {
	return nil
}

func (t *ServiceVariable) GetNestedFieldVariables(prefix string, noSQL bool) ([]Variable, []string) {
	return nil, nil
}

func (t *ServiceVariable) CopyFrom(target *ServiceVariable) {
	// nothing to be done here
}
