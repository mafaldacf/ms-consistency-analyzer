package objects

import (
	"fmt"
	"slices"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

const VARIABLE_INLINE_ID int64 = 0
const VARIABLE_UNASSIGNED_ID int64 = -1

type Object interface {
	String() string
	LongString() string
	GetVariableInfo() *ObjectInfo
	GetDependencies() []Object
	AddReferenceWithID(reference Object, creator string)
	GetUnassaignedVariables() []Object
	Copy(force bool) Object
	DeepCopy() Object
	GetId() int64
	GetType() gotypes.Type
	AssignVariable(variable Object)
	UpgradeFromPreviousInterface(interfaceVariable *InterfaceObject)
	GetNestedDependencies(nearestFields bool) []Object
	GetElementAt(index int) Object
}

func VariableTypeName(v Object) string {
	return utils.GetType(v) + " " + utils.GetType(v.GetType())
}

func GetDependenciesStringLst(deps ...Object) string {
	out := ""
	for _, d := range deps {
		out += fmt.Sprintf("\t\t\t\t\t - [%d] (%s) %s: %s\n", d.GetId(), VariableTypeName(d), d.GetVariableInfo().GetName(), d.GetVariableInfo().String())
	}
	return out
}

func UnwrapTupleIfSingleElement(variable Object) Object {
	if tupleVar, ok := variable.(*TupleObject); ok && len(tupleVar.Objects) == 1 {
		return tupleVar.Objects[0]
	}
	return variable
}

func WrapToFieldVariable(variable Object, structVariable *StructObject, addTypeToStruct bool) {
	fieldVariable, ok := variable.(*FieldObject)
	if !ok {
		fieldVariable = &FieldObject{
			ObjectInfo: &ObjectInfo{
				Type: &gotypes.FieldType{
					WrappedType: variable.GetType(),
				},
				Id: VARIABLE_INLINE_ID,
			},
			WrappedVariable: variable,
		}
	}
	if addTypeToStruct {
		structVariable.AddOrGetFieldVariableAndType(fieldVariable)
	} else {
		structVariable.AddOrGetFieldVariable(fieldVariable)
	}
}

func UnwrapAddressVariable(variable Object) Object {
	if addressVar, ok := variable.(*AddressObject); ok {
		return UnwrapAddressVariable(addressVar.GetAddressOf())
	}
	return variable
}

func UnwrapPointerVariable(variable Object) Object {
	if pointerVar, ok := variable.(*PointerObject); ok {
		return UnwrapPointerVariable(pointerVar.GetPointerTo())
	}
	return variable
}

func UnwrapFieldVariable(variable Object) Object {
	if fieldVar, ok := variable.(*FieldObject); ok {
		return UnwrapPointerVariable(fieldVar.WrappedVariable)
	}
	return variable
}

func AddVariableInfoDependencies(variable Object, deps []Object) {
	variable.GetVariableInfo().Dependencies = append(variable.GetVariableInfo().Dependencies, deps...)
}

func AddUnderlyingDependencies(variable Object, deps []Object) bool {
	variableType, _ := gotypes.UnwrapUserAndFieldTypes(variable.GetType())

	if _, ok := variableType.(*gotypes.GenericType); ok {
		genericVariable, _ := variable.(*GenericObject)
		genericVariable.Params = append(genericVariable.Params, deps...)
		return true
	}
	if _, ok := variableType.(*gotypes.BasicType); ok {
		basicVariable, _ := variable.(*BasicObject)
		basicVariable.UnderlyingObjects = append(basicVariable.UnderlyingObjects, deps...)
		return true
	}
	if _, ok := variableType.(*gotypes.InterfaceType); ok {
		interfaceVariable, _ := variable.(*InterfaceObject)
		if interfaceVariable.UnderlyingVariable != nil || len(deps) > 1 {
			return false
		}
		interfaceVariable.UnderlyingVariable = deps[0]
		return true
	}
	if sliceType, ok := variableType.(*gotypes.SliceType); ok {
		sliceVariable, _ := variable.(*SliceObject)
		for _, dep := range deps {
			depType, _ := gotypes.UnwrapUserAndFieldTypes(dep.GetType())
			if !sliceType.UnderlyingType.IsSameType(depType) {
				logger.Logger.Fatalf("[CFG CALLS] (%s) --- (%s) %s", utils.GetType(sliceType.UnderlyingType), VariableTypeName(dep), dep.String())
				return false
			}
		}
		sliceVariable.Elements = append(sliceVariable.Elements, deps...)
		return true
	}
	return false
}

func GetReversedNestedFieldsAndNames(variable Object, fieldName string, noSQL bool, queue bool) (nestedObjects []Object, nestedNames []string) {
	logger.Logger.Debugf("[VARS] get reversed nested fields and names for variable (%s): %s", utils.GetType(variable), variable.String())

	// e.g. in queue.pop we need to explicitly specify the fieldname otherwise it will be wrong because we are reading from an inteface
	// also applies to nosql
	logger.Logger.Debugf("TOP FIELD NAME BEFORE = %s", fieldName)
	if fieldName == "" {
		fieldName = variable.GetType().GetName()
	}

	logger.Logger.Debugf("TOP FIELD NAME AFTER = %s", fieldName)

	if structVariable, ok := variable.(*StructObject); ok {
		variables := []Object{structVariable}
		names := []string{fieldName}
		nestedObjects, nestedNames = structVariable.GetNestedFieldVariablesWithReferences(fieldName, noSQL)

		variables = append(variables, nestedObjects...)
		names = append(names, nestedNames...)
		slices.Reverse(variables)
		slices.Reverse(names)
		return variables, names
	} else if mapVariable, ok := variable.(*MapObject); ok {
		variables := []Object{mapVariable}
		names := []string{fieldName}
		nestedObjects, nestedNames = mapVariable.GetNestedFieldVariablesWithReferences(fieldName, noSQL)

		variables = append(variables, nestedObjects...)
		names = append(names, nestedNames...)
		slices.Reverse(variables)
		slices.Reverse(names)
		return variables, names
	} else if addressVariable, ok := variable.(*AddressObject); ok {
		return GetReversedNestedFieldsAndNames(addressVariable.AddressOf, fieldName, noSQL, queue)
	} else if pointerVariable, ok := variable.(*PointerObject); ok {
		return GetReversedNestedFieldsAndNames(pointerVariable.PointerTo, fieldName, noSQL, queue)
	} else {
		logger.Logger.Fatalf("unexpected type (%s) for variable (%s)", utils.GetType(variable), variable.String())
	}
	return nil, nil
}
