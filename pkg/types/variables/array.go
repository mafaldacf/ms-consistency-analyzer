package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type ArrayVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Elements     []Variable    `json:"array_elems,omitempty"`
}

func (v *ArrayVariable) String() string {
	return v.VariableInfo.String()
}

func (v *ArrayVariable) UpgradeToSlice() *SliceVariable {
	v.VariableInfo.Type = &gotypes.SliceType{
		UnderlyingType: v.GetArrayType().ElementsType,
	}
	sliceVariable := &SliceVariable{
		VariableInfo: v.VariableInfo,
		Elements:     v.Elements,
	}
	for _, elem := range sliceVariable.Elements {
		elem.GetVariableInfo().SetParent(elem, sliceVariable)
	}
	return sliceVariable
}

func (v *ArrayVariable) LongString() string {
	s := v.VariableInfo.String() + " = ("
	for i, elem := range v.Elements {
		s += elem.String()
		if i < len(v.Elements)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *ArrayVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
	for i := 0; i < len(v.Elements); i++ {
		v.AddReferenceWithID(target.GetElementAt(i), creator)
	}
}

func (v *ArrayVariable) GetElements() []Variable {
	return v.Elements
}

func (v *ArrayVariable) AppendElements(varElements Variable) {
	if varElementsSlice, ok := varElements.(*ArrayVariable); ok {
		v.Elements = append(v.Elements, varElementsSlice.GetElements()...)
	} else {
		if v.GetArrayType().ElementsType.IsSameType(varElements.GetType()) {
			v.Elements = append(v.Elements, varElements)
		} else {
			logger.Logger.Fatalf("[VARS SLICE] slice variable underlying type (%s) does not match elements type (%s)", utils.GetType(v.GetArrayType().ElementsType), utils.GetType(varElements.GetType()))
		}
	}
}

func (v *ArrayVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *ArrayVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *ArrayVariable) GetArrayType() *gotypes.ArrayType {
	if userType, ok := v.VariableInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.ArrayType)
	}
	return v.VariableInfo.GetType().(*gotypes.ArrayType)
}

func (v *ArrayVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *ArrayVariable) AddElement(element Variable) {
	v.Elements = append(v.Elements, element)
}

func (v *ArrayVariable) AddElements(element []Variable) {
	v.Elements = append(v.Elements, element...)
}

func (v *ArrayVariable) GetElementAt(index int) Variable {
	if index > len(v.Elements)-1 {
		logger.Logger.Fatalf("[VARS ARRAY] element at index (%d) does not exist in array variable with len (%d): %s", index, len(v.Elements), v.String())
	}
	return v.Elements[index]
}

func (v *ArrayVariable) GetElementAtIfExists(index int) Variable {
	if index > len(v.Elements)-1 {
		logger.Logger.Warnf("[VARS ARRAY] element at index (%d) does not exist in array variable with len (%d): %s", index, len(v.Elements), v.String())
		return nil
	}
	return v.Elements[index]
}

func (v *ArrayVariable) GetDependencies() []Variable {
	return v.Elements
}

func (v *ArrayVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	for _, elem := range v.Elements {
		deps = append(deps, elem.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *ArrayVariable) DeepCopy(force bool) Variable {
	copy := &ArrayVariable{
		VariableInfo: v.VariableInfo.DeepCopy(force),
	}
	for _, elem := range v.Elements {
		newElem := elem.DeepCopy(force)
		copy.Elements = append(copy.Elements, newElem)
		newElem.GetVariableInfo().SetParent(newElem, copy)
	}
	return copy
}

func (v *ArrayVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, v := range v.Elements {
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
