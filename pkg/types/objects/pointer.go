package objects

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type PointerObject struct {
	Object
	ObjectInfo *ObjectInfo
	PointerTo  Object
}

func (v *PointerObject) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		ObjectInfo *ObjectInfo `json:"pointer"`
		PointerTo  Object      `json:"ptr_to,omitempty"`
	}{
		ObjectInfo: v.ObjectInfo,
		PointerTo:  v.PointerTo,
	})
}

func (v *PointerObject) String() string {
	return v.ObjectInfo.String()
}

func (v *PointerObject) LongString() string {
	return v.ObjectInfo.LongString() + " \n\t\t\t\t\t\t = " + "*" + v.GetPointerTo().LongString()
}

func (v *PointerObject) GetId() int64 {
	return v.ObjectInfo.GetId()
}

func (v *PointerObject) GetType() gotypes.Type {
	if v.ObjectInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for pointer variable: %s", v.String())
	}
	return v.ObjectInfo.GetType()
}

func (v *PointerObject) GetPointerType() *gotypes.PointerType {
	if userType, ok := v.ObjectInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.PointerType)
	}
	return v.ObjectInfo.GetType().(*gotypes.PointerType)
}

func (v *PointerObject) GetVariableInfo() *ObjectInfo {
	return v.ObjectInfo
}

func (v *PointerObject) GetDependencies() []Object {
	return append(v.GetVariableInfo().GetDependencies(), v.PointerTo)
}

func (v *PointerObject) GetNestedDependencies(includeRefBy bool) []Object {
	var deps = []Object{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(includeRefBy, v)...)
	}
	if includeRefBy && v.GetVariableInfo().IsReferencedBy() {
		deps = append(deps, v.GetVariableInfo().GetNestedRefByDependencies(nil)...)
	}
	for _, elem := range v.GetDependencies() { // to include underlying dependencies from variable info
		logger.Logger.Debugf("[POINTER OBJECT] GOT NESTED DEP (INC/ VINFO) FOR ELEM %s (%s)", elem.String(), VariableTypeName(elem))
		deps = append(deps, elem.GetNestedDependencies(includeRefBy)...)
	}
	return deps
}

func (v *PointerObject) GetPointerTo() Object {
	logger.Logger.Debugf("[VARS POINTER] getting pointerTo variable for pointer: %s", v.String())
	if v.PointerTo == nil {
		logger.Logger.Fatalf("[VARS POINTER] unexpected nil pointer to variable in pointer variable (%s)", v.String())
	}
	return v.PointerTo
}

func (v *PointerObject) AddReferenceWithID(target Object, creator string) {
	if targetPointerTo, ok := target.(*PointerObject); ok {
		v.PointerTo.AddReferenceWithID(targetPointerTo.PointerTo, creator)
	} else {
		logger.Logger.Fatalf("ignoring referencing of variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), VariableTypeName(v), VariableTypeName(target))
	}
}

func (v *PointerObject) Copy(force bool) Object {
	copy := &PointerObject{
		ObjectInfo: v.ObjectInfo.Copy(force),
		PointerTo:  v.PointerTo, // underlying values of pointers are never deep copied
	}
	copy.PointerTo.GetVariableInfo().SetParent(copy.PointerTo, copy)
	return copy
}

func (v *PointerObject) DeepCopy() Object {
	logger.Logger.Debugf("[VARS POINTER - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &PointerObject{
		ObjectInfo: v.ObjectInfo.DeepCopy(),
		PointerTo:  v.PointerTo.DeepCopy(), // underlying values of pointers are never deep copied
	}
	copy.PointerTo.GetVariableInfo().SetParent(copy.PointerTo, copy)
	return copy
}

func (v *PointerObject) GetUnassaignedVariables() []Object {
	var variables []Object
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		variables = append(variables, v.PointerTo.GetUnassaignedVariables()...)
	}
	return variables
}
