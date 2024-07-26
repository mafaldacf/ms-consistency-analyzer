package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type SliceVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Elements     []Variable    `json:"slice_variables,omitempty"`
}

func (v *SliceVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *SliceVariable) GetElements() []Variable {
	return v.Elements
}

func (v *SliceVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(v, target, creator)
	for i := 0; i < len(v.Elements); i++ {
		v.AddReferenceWithID(target.GetElementAt(i), creator)
	}
}

func (v *SliceVariable) AppendElements(varElements Variable) {
	if varElementsSlice, ok := varElements.(*SliceVariable); ok {
		v.Elements = append(v.Elements, varElementsSlice.GetElements()...)
	} else {
		if v.GetSliceType().UnderlyingType.IsSameType(varElements.GetType()) {
			v.Elements = append(v.Elements, varElements)
		} else {
			logger.Logger.Fatalf("[VARS SLICE] slice variable underlying type (%s) does not match elements type (%s)", utils.GetType(v.GetSliceType().UnderlyingType), utils.GetType(varElements.GetType()))
		}
	}
}

func (v *SliceVariable) AddElement(element Variable) {
	v.Elements = append(v.Elements, element)
	element.GetVariableInfo().SetParent(element, v)
}

func (v *SliceVariable) AddElements(elements []Variable) {
	v.Elements = append(v.Elements, elements...)
	for _, elem := range elements {
		elem.GetVariableInfo().SetParent(elem, v)
	}
}

func (v *SliceVariable) GetVariableAt(index int) Variable {
	if index < len(v.Elements) {
		return v.Elements[index]
	}
	logger.Logger.Fatalf("index (%d) out of bounds for tuple variable (%s) -- variables: %v", index, v.LongString(), v.Elements)
	return nil
}

func (v *SliceVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *SliceVariable) NumVariables() int {
	return len(v.Elements)
}

func (v *SliceVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *SliceVariable) GetSliceType() *gotypes.SliceType {
	if userType, ok := v.VariableInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.SliceType)
	}
	return v.VariableInfo.GetType().(*gotypes.SliceType)
}

func (v *SliceVariable) GetDependencies() []Variable {
	return v.Elements
}

func (v *SliceVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	for _, elem := range v.Elements {
		deps = append(deps, elem.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *SliceVariable) GetElementAt(index int) Variable {
	if index > len(v.Elements)-1 {
		logger.Logger.Fatalf("[VARS SLICE] element at index (%d) does not exist in array variable with len (%d): %s", index, len(v.Elements), v.String())
	}
	return v.Elements[index]
}

func (v *SliceVariable) GetElementAtIfExists(index int) Variable {
	if index > len(v.Elements)-1 {
		logger.Logger.Warnf("[VARS SLICE] element at index (%d) does not exist in array variable with len (%d): %s", index, len(v.Elements), v.String())
		return nil
	}
	return v.Elements[index]
}

func (v *SliceVariable) String() string {
	return v.VariableInfo.String()
}

func (v *SliceVariable) LongString() string {
	s := v.VariableInfo.LongString() + " = ("
	for i, elem := range v.Elements {
		s += elem.String()
		if i < len(v.Elements)-1 {
			s += ", "
		}
	}
	return s + ")"
}

func (v *SliceVariable) DeepCopy(force bool) Variable {
	copy := &SliceVariable{VariableInfo: v.VariableInfo.DeepCopy(force)}
	for _, v := range v.Elements {
		newElem := v.DeepCopy(force)
		copy.Elements = append(copy.Elements, newElem)
		newElem.GetVariableInfo().SetParent(newElem, copy)
	}
	return copy
}

func (v *SliceVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, v := range v.Elements {
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
