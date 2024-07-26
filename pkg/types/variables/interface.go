package variables

import "analyzer/pkg/types/gotypes"

type InterfaceVariable struct {
	Variable           `json:"-"`
	VariableInfo       *VariableInfo `json:"variable"`
	UnderlyingVariable Variable      `json:"-"`
}

func (v *InterfaceVariable) String() string {
	return v.VariableInfo.String()
}

func (v *InterfaceVariable) LongString() string {
	return v.VariableInfo.LongString()
}

func (v *InterfaceVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *InterfaceVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *InterfaceVariable) GetInterfaceType() *gotypes.InterfaceType {
	if userType, ok := v.VariableInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.InterfaceType)
	}
	return v.VariableInfo.GetType().(*gotypes.InterfaceType)
}

func (v *InterfaceVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *InterfaceVariable) GetDependencies() []Variable {
	if v.UnderlyingVariable != nil {
		return []Variable{v.UnderlyingVariable}
	}
	return nil
}

func (v *InterfaceVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.UnderlyingVariable != nil {
		deps = append(deps, v.UnderlyingVariable.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *InterfaceVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
	if v.UnderlyingVariable != nil {
		v.UnderlyingVariable.AddReferenceWithID(target, creator)
	}
}

func (v *InterfaceVariable) DeepCopy(force bool) Variable {
	copy := &InterfaceVariable{
		VariableInfo: v.VariableInfo.DeepCopy(force),
	}
	if v.UnderlyingVariable != nil {
		copy.UnderlyingVariable = v.UnderlyingVariable.DeepCopy(force)
	}
	return copy
}

func (v *InterfaceVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}

func (v *InterfaceVariable) UpgradeToAssertedType(newType gotypes.Type) {
	v.GetVariableInfo().Type = newType
}
