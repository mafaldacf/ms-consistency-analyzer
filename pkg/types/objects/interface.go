package objects

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type InterfaceObject struct {
	Object
	ObjectInfo         *ObjectInfo
	UnderlyingVariable Object
}

func (v *InterfaceObject) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		ObjectInfo *ObjectInfo `json:"interface"`
	}{
		ObjectInfo: v.ObjectInfo,
	})
}

func (v *InterfaceObject) String() string {
	return v.ObjectInfo.String()
}

func (v *InterfaceObject) LongString() string {
	return v.ObjectInfo.LongString()
}

func (v *InterfaceObject) GetId() int64 {
	return v.ObjectInfo.GetId()
}

func (v *InterfaceObject) GetType() gotypes.Type {
	if v.ObjectInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for interface variable: %s", v.String())
	}
	return v.ObjectInfo.GetType()
}

func (v *InterfaceObject) GetInterfaceType() *gotypes.InterfaceType {
	if userType, ok := v.ObjectInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.InterfaceType)
	}
	return v.ObjectInfo.GetType().(*gotypes.InterfaceType)
}

func (v *InterfaceObject) GetVariableInfo() *ObjectInfo {
	return v.ObjectInfo
}

func (v *InterfaceObject) GetDependencies() []Object {
	if v.UnderlyingVariable != nil {
		return append(v.GetVariableInfo().GetDependencies(), v.UnderlyingVariable)
	}
	return v.GetVariableInfo().GetDependencies()
}

func (v *InterfaceObject) GetNestedDependencies(nearestFields bool) []Object {
	var deps = []Object{v}
	if v.UnderlyingVariable != nil {
		deps = append(deps, v.UnderlyingVariable.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *InterfaceObject) AddReferenceWithID(target Object, creator string) {
	v.ObjectInfo.AddReferenceWithID(v, target, creator)
	if v.UnderlyingVariable != nil {
		v.UnderlyingVariable.AddReferenceWithID(target, creator)
	}
}

func (v *InterfaceObject) Copy(force bool) Object {
	copy := &InterfaceObject{
		ObjectInfo: v.ObjectInfo.Copy(force),
	}
	if v.UnderlyingVariable != nil {
		copy.UnderlyingVariable = v.UnderlyingVariable.Copy(force)
	}
	return copy
}

func (v *InterfaceObject) DeepCopy() Object {
	logger.Logger.Debugf("[VARS INTERFACE - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &InterfaceObject{
		ObjectInfo: v.ObjectInfo.DeepCopy(),
	}
	if v.UnderlyingVariable != nil {
		copy.UnderlyingVariable = v.UnderlyingVariable.DeepCopy()
	}
	return copy
}

func (v *InterfaceObject) GetUnassaignedVariables() []Object {
	var variables []Object
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}

func (v *InterfaceObject) UpgradeToAssertedType(newType gotypes.Type) {
	v.GetVariableInfo().Type = newType
}
