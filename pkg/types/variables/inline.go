package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type InlineVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}

func (v *InlineVariable) String() string {
	return v.VariableInfo.String()
}

func (v *InlineVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *InlineVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *InlineVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *InlineVariable) GetDependencies() []Variable {
	return nil
}

func (v *InlineVariable) AddReferenceWithID(target Variable, creator string) {
	logger.Logger.Warnf("IGNORING REFERENCES FOR INLINE VARIABLE!!")
}

func (v *InlineVariable) DeepCopy(force bool) Variable {
	copy := &InlineVariable{
		VariableInfo: v.VariableInfo.DeepCopy(force),
	}
	return copy
}

func (v *InlineVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}
