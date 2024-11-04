package variables

import (
	"fmt"
	"slices"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

const VARIABLE_INLINE_ID int64 = 0
const VARIABLE_UNASSIGNED_ID int64 = -1

type Variable interface {
	String() string
	LongString() string
	GetVariableInfo() *VariableInfo
	GetDependencies() []Variable
	AddReferenceWithID(reference Variable, creator string)
	GetUnassaignedVariables() []Variable
	Copy(force bool) Variable
	DeepCopy() Variable
	GetId() int64
	GetType() gotypes.Type
	AssignVariable(variable Variable)
	UpgradeFromPreviousInterface(interfaceVariable *InterfaceVariable)
	GetNestedDependencies(nearestFields bool) []Variable
	GetElementAt(index int) Variable
}

func VariableTypeName(v Variable) string {
	return utils.GetType(v) + " " + utils.GetType(v.GetType())
}

func GetDependenciesStringLst(deps ...Variable) string {
	out := ""
	for _, d := range deps {
		out += fmt.Sprintf("\t\t\t\t\t - [%d] (%s) %s: %s\n", d.GetId(), VariableTypeName(d), d.GetVariableInfo().GetName(), d.GetVariableInfo().String())
	}
	return out
}

func UnwrapTupleIfSingleElement(variable Variable) Variable {
	if tupleVar, ok := variable.(*TupleVariable); ok && len(tupleVar.Variables) == 1 {
		return tupleVar.Variables[0]
	}
	return variable
}

func WrapToFieldVariable(variable Variable, structVariable *StructVariable, addTypeToStruct bool) {
	fieldVariable, ok := variable.(*FieldVariable)
	if !ok {
		fieldVariable = &FieldVariable{
			VariableInfo: &VariableInfo{
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

func UnwrapAddressVariable(variable Variable) Variable {
	if addressVar, ok := variable.(*AddressVariable); ok {
		return UnwrapAddressVariable(addressVar.GetAddressOf())
	}
	return variable
}

func UnwrapPointerVariable(variable Variable) Variable {
	if pointerVar, ok := variable.(*PointerVariable); ok {
		return UnwrapPointerVariable(pointerVar.GetPointerTo())
	}
	return variable
}

func UnwrapFieldVariable(variable Variable) Variable {
	if fieldVar, ok := variable.(*FieldVariable); ok {
		return UnwrapPointerVariable(fieldVar.WrappedVariable)
	}
	return variable
}

func AddVariableInfoDependencies(variable Variable, deps []Variable) {
	variable.GetVariableInfo().Dependencies = append(variable.GetVariableInfo().Dependencies, deps...)
}

func AddUnderlyingDependencies(variable Variable, deps []Variable) bool {
	variableType, _ := gotypes.UnwrapUserAndFieldTypes(variable.GetType())

	if _, ok := variableType.(*gotypes.GenericType); ok {
		genericVariable, _ := variable.(*GenericVariable)
		genericVariable.Params = append(genericVariable.Params, deps...)
		return true
	}
	if _, ok := variableType.(*gotypes.BasicType); ok {
		basicVariable, _ := variable.(*BasicVariable)
		basicVariable.UnderlyingVariables = append(basicVariable.UnderlyingVariables, deps...)
		return true
	}
	if _, ok := variableType.(*gotypes.InterfaceType); ok {
		interfaceVariable, _ := variable.(*InterfaceVariable)
		if interfaceVariable.UnderlyingVariable != nil || len(deps) > 1 {
			return false
		}
		interfaceVariable.UnderlyingVariable = deps[0]
		return true
	}
	if sliceType, ok := variableType.(*gotypes.SliceType); ok {
		sliceVariable, _ := variable.(*SliceVariable)
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

func GetReversedNestedFieldsAndNames(variable Variable, fieldName string, noSQL bool, queue bool) (nestedVariables []Variable, nestedNames []string) {
	logger.Logger.Debugf("[VARS] get reversed nested fields and names for variable (%s): %s", utils.GetType(variable), variable.String())

	// e.g. in queue.pop we need to explicitly specify the fieldname otherwise it will be wrong because we are reading from an inteface
	// also applies to nosql
	logger.Logger.Debugf("TOP FIELD NAME BEFORE = %s", fieldName)
	if fieldName == "" {
		fieldName = variable.GetType().GetName()
	}

	logger.Logger.Debugf("TOP FIELD NAME AFTER = %s", fieldName)

	if structVariable, ok := variable.(*StructVariable); ok {
		variables := []Variable{structVariable}
		names := []string{fieldName}
		nestedVariables, nestedNames = structVariable.GetNestedFieldVariablesWithReferences(fieldName, noSQL)

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)
		slices.Reverse(variables)
		slices.Reverse(names)
		return variables, names
	} else if mapVariable, ok := variable.(*MapVariable); ok {
		variables := []Variable{mapVariable}
		names := []string{fieldName}
		nestedVariables, nestedNames = mapVariable.GetNestedFieldVariablesWithReferences(fieldName, noSQL)

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)
		slices.Reverse(variables)
		slices.Reverse(names)
		return variables, names
	} else if addressVariable, ok := variable.(*AddressVariable); ok {
		return GetReversedNestedFieldsAndNames(addressVariable.AddressOf, fieldName, noSQL, queue)
	} else if pointerVariable, ok := variable.(*PointerVariable); ok {
		return GetReversedNestedFieldsAndNames(pointerVariable.PointerTo, fieldName, noSQL, queue)
	} else {
		logger.Logger.Fatalf("unexpected type (%s) for variable (%s)", utils.GetType(variable), variable.String())
	}
	return nil, nil
}
