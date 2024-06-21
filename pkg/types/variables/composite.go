package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type CompositeVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Params       []Variable    `json:"func_composition,omitempty"`
}

func (v *CompositeVariable) String() string {
	return v.VariableInfo.String()
}

func (v *CompositeVariable) LongString() string {
	s := v.VariableInfo.String() + " = {"
	for i, elem := range v.Params {
		s += elem.LongString()
		if i < len(v.Params)-1 {
			s += ", "
		}
	}
	return s + "}"
}

func (v *CompositeVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *CompositeVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *CompositeVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *CompositeVariable) GetDependencies() []Variable {
	return v.Params
}

func (v *CompositeVariable) DeepCopy() Variable {
	copy := &CompositeVariable{
		VariableInfo: v.VariableInfo,
	}
	for _, p := range v.Params {
		copy.Params = append(copy.Params, p.DeepCopy())
	}
	return copy
}

func (v *CompositeVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
	if targetComposite, ok := target.(*CompositeVariable); ok {
		for i, p := range v.Params {
			if i > len(targetComposite.Params) {
				logger.Logger.Warnf("invalid argument index %d for length %d in params: %v", i, (targetComposite.Params), targetComposite.Params)
			} else {
				p.AddReferenceWithID(targetComposite.Params[i], creator)
			}
		}
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
	logger.Logger.Debugf("added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
}
func (v *CompositeVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable

	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, p := range v.Params {
			variables = append(variables, p.GetUnassaignedVariables()...)
		}
	}
	return variables
}
