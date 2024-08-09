package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type BasicVariable struct {
	Variable            `json:"-"`
	VariableInfo        *VariableInfo `json:"variable"`
	UnderlyingVariables []Variable    `json:"-"` // variables that influence the value of basic variables - e.g. "some_variable" in len(some_variable)
}

func (v *BasicVariable) String() string {
	return v.VariableInfo.String()
}

func (v *BasicVariable) LongString() string {
	return v.VariableInfo.String()
}

func (v *BasicVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *BasicVariable) GetType() gotypes.Type {
	if v.VariableInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for basic variable: %s", v.String())
	}
	return v.VariableInfo.GetType()
}

func (v *BasicVariable) GetBasicType() *gotypes.BasicType {
	if userType, ok := v.VariableInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.BasicType)
	}
	return v.VariableInfo.GetType().(*gotypes.BasicType)
}

func (v *BasicVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *BasicVariable) GetDependencies() []Variable {
	return append(v.GetVariableInfo().GetDependencies(), v.UnderlyingVariables...)
}

func (v *BasicVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	for _, elem := range v.UnderlyingVariables {
		logger.Logger.Tracef("GOT NESTED DEP FOR ELEM %s (%s)", elem.String(), VariableTypeName(elem))
		deps = append(deps, elem.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *BasicVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
	for _, v := range v.UnderlyingVariables {
		v.AddReferenceWithID(target, creator)
	}
}

func (v *BasicVariable) Copy(force bool) Variable {
	var underlyingVariablesCopy []Variable
	for _, v := range v.UnderlyingVariables {
		underlyingVariablesCopy = append(underlyingVariablesCopy, v.Copy(force))
	}
	copy := &BasicVariable{
		VariableInfo:        v.VariableInfo.Copy(force),
		UnderlyingVariables: underlyingVariablesCopy,
	}
	return copy
}

func (v *BasicVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS BASIC - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	var underlyingVariablesCopy []Variable
	for _, v := range v.UnderlyingVariables {
		underlyingVariablesCopy = append(underlyingVariablesCopy, v.DeepCopy())
	}
	copy := &BasicVariable{
		VariableInfo:        v.VariableInfo.DeepCopy(),
		UnderlyingVariables: underlyingVariablesCopy,
	}
	return copy
}

func (v *BasicVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	for _, v := range v.UnderlyingVariables {
		variables = append(variables, v.GetUnassaignedVariables()...)
	}
	return variables
}

func (v *BasicVariable) UpgradeFromPreviousInterface(interfaceVariable *InterfaceVariable) {
	/* v.GetVariableInfo().Reference = interfaceVariable.GetVariableInfo().Reference
	v.GetVariableInfo().Dataflows = interfaceVariable.GetVariableInfo().Dataflows
	v.GetVariableInfo().IndirectDataflows = interfaceVariable.GetVariableInfo().IndirectDataflows */
	v.UnderlyingVariables = append(v.UnderlyingVariables, interfaceVariable)
	interfaceVariable.GetVariableInfo().AddParent(interfaceVariable, v)
}
