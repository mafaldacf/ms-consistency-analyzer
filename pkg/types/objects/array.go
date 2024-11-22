package objects

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type ArrayObject struct {
	Object
	ObjectInfo *ObjectInfo
	Elements   []Object
}

func (v *ArrayObject) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		ObjectInfo *ObjectInfo `json:"array"`
		Elements   []Object    `json:"array_elems,omitempty"`
	}{
		ObjectInfo: v.ObjectInfo,
		Elements:   v.Elements,
	})
}

func (v *ArrayObject) String() string {
	return v.ObjectInfo.String()
}

func (v *ArrayObject) UpgradeToSlice() *SliceObject {
	v.ObjectInfo.Type = &gotypes.SliceType{
		UnderlyingType: v.GetArrayType().ElementsType,
	}
	sliceVariable := &SliceObject{
		ObjectInfo: v.ObjectInfo,
		Elements:   v.Elements,
	}
	for _, elem := range sliceVariable.Elements {
		elem.GetVariableInfo().SetParent(elem, sliceVariable)
	}
	return sliceVariable
}

func (v *ArrayObject) LongString() string {
	s := v.ObjectInfo.String() + " = ("
	for i, elem := range v.Elements {
		s += elem.String()
		if i < len(v.Elements)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *ArrayObject) AddReferenceWithID(target Object, creator string) {
	v.ObjectInfo.AddReferenceWithID(v, target, creator)
	for i := 0; i < len(v.Elements); i++ {
		v.AddReferenceWithID(target.GetElementAt(i), creator)
	}
}

func (v *ArrayObject) GetElements() []Object {
	return v.Elements
}

func (v *ArrayObject) AppendElements(varElements Object) {
	if varElementsSlice, ok := varElements.(*ArrayObject); ok {
		v.Elements = append(v.Elements, varElementsSlice.GetElements()...)
	} else {
		if v.GetArrayType().ElementsType.IsSameType(varElements.GetType()) {
			v.Elements = append(v.Elements, varElements)
		} else {
			logger.Logger.Fatalf("[VARS SLICE] slice variable underlying type (%s) does not match elements type (%s)", utils.GetType(v.GetArrayType().ElementsType), utils.GetType(varElements.GetType()))
		}
	}
}

func (v *ArrayObject) GetId() int64 {
	return v.ObjectInfo.GetId()
}

func (v *ArrayObject) GetType() gotypes.Type {
	if v.ObjectInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for array variable: %s", v.String())
	}
	return v.ObjectInfo.GetType()
}

func (v *ArrayObject) GetArrayType() *gotypes.ArrayType {
	if userType, ok := v.ObjectInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.ArrayType)
	}
	return v.ObjectInfo.GetType().(*gotypes.ArrayType)
}

func (v *ArrayObject) GetVariableInfo() *ObjectInfo {
	return v.ObjectInfo
}

func (v *ArrayObject) AddElement(element Object) {
	v.Elements = append(v.Elements, element)
}

func (v *ArrayObject) AddElements(element []Object) {
	v.Elements = append(v.Elements, element...)
}

func (v *ArrayObject) GetElementAt(index int) Object {
	if index > len(v.Elements)-1 {
		logger.Logger.Fatalf("[VARS ARRAY] element at index (%d) does not exist in array variable with len (%d): %s", index, len(v.Elements), v.String())
	}
	return v.Elements[index]
}

func (v *ArrayObject) GetElementAtIfExists(index int) Object {
	if index > len(v.Elements)-1 {
		logger.Logger.Warnf("[VARS ARRAY] element at index (%d) does not exist in array variable with len (%d): %s", index, len(v.Elements), v.String())
		return nil
	}
	return v.Elements[index]
}

func (v *ArrayObject) GetDependencies() []Object {
	return append(v.GetVariableInfo().GetDependencies(), v.Elements...)
}

func (v *ArrayObject) GetNestedDependencies(nearestFields bool) []Object {
	var deps = []Object{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	if v.GetVariableInfo().IsReferencedBy() {
		deps = append(deps, v.GetVariableInfo().GetNestedRefByDependencies(nil)...)
	}
	for _, elem := range v.Elements {
		deps = append(deps, elem.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *ArrayObject) Copy(force bool) Object {
	copy := &ArrayObject{
		ObjectInfo: v.ObjectInfo.Copy(force),
	}
	for _, elem := range v.Elements {
		newElem := elem.Copy(force)
		copy.Elements = append(copy.Elements, newElem)
		newElem.GetVariableInfo().SetParent(newElem, copy)
	}
	return copy
}

func (v *ArrayObject) DeepCopy() Object {
	logger.Logger.Debugf("[VARS ARRAY - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &ArrayObject{
		ObjectInfo: v.ObjectInfo.DeepCopy(),
	}
	for _, elem := range v.Elements {
		newElem := elem.DeepCopy()
		copy.Elements = append(copy.Elements, newElem)
		newElem.GetVariableInfo().SetParent(newElem, copy)
	}
	return copy
}

func (v *ArrayObject) GetUnassaignedVariables() []Object {
	var variables []Object
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, v := range v.Elements {
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
