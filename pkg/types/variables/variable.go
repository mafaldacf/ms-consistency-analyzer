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
	DeepCopy(force bool) Variable
	GetId() int64
	GetType() gotypes.Type
	AssignVariable(variable Variable)
	UpgradeFromPreviousInterface(interfaceVariable *InterfaceVariable)
	GetNestedIndirectDependencies() []Variable
}

func GetVariableTypeAndTypeString(v Variable) string {
	return utils.GetType(v) + " " + utils.GetType(v.GetType())
}

func GetDependenciesStringLst(deps ...Variable) string {
	out := ""
	for _, d := range deps {
		out += fmt.Sprintf("\t\t\t\t\t - [%d] (%s) %s: %s\n", d.GetId(), GetVariableTypeAndTypeString(d), d.GetVariableInfo().GetName(), d.GetVariableInfo().String())
	}
	return out
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
				logger.Logger.Fatalf("[CFG CALLS] (%s) --- (%s) %s", utils.GetType(sliceType.UnderlyingType), GetVariableTypeAndTypeString(dep), dep.String())
				return false
			}
		}
		sliceVariable.Elements = append(sliceVariable.Elements, deps...)
		return true
	}
	return false
}

func GetReversedNestedFieldsAndNames(variable Variable, includeReferences bool, fieldName string) (nestedVariables []Variable, nestedNames []string) {
	logger.Logger.Debugf("[VARS] get reversed nested fields and names for variable (%s): %s", utils.GetType(variable), variable.String())

	// e.g. in queue.pop we need to explicitly specify the fieldname otherwise it will be wrong because we are reading from an inteface
	if fieldName == "" {
		fieldName = variable.GetType().GetName()
	}

	if structVariable, ok := variable.(*StructVariable); ok {
		variables := []Variable{structVariable}
		names := []string{fieldName}

		if includeReferences {
			nestedVariables, nestedNames = structVariable.GetNestedFieldVariablesWithReferences(fieldName)
		} else {
			nestedVariables, nestedNames = structVariable.GetNestedFieldVariables(fieldName)
		}

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)
		slices.Reverse(variables)
		slices.Reverse(names)
		return variables, names
	} else if mapVariable, ok := variable.(*MapVariable); ok {
		variables := []Variable{mapVariable}
		names := []string{fieldName}

		if includeReferences {
			nestedVariables, nestedNames = mapVariable.GetNestedFieldVariablesWithReferences(fieldName)
		} else {
			nestedVariables, nestedNames = mapVariable.GetNestedFieldVariables(fieldName)
		}

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)
		slices.Reverse(variables)
		slices.Reverse(names)
		return variables, names
	} else if addressVariable, ok := variable.(*AddressVariable); ok {
		return GetReversedNestedFieldsAndNames(addressVariable.AddressOf, includeReferences, fieldName)
	} else {
		logger.Logger.Fatalf("unexpected type (%s) for variable (%s)", utils.GetType(variable), variable.String())
	}
	return nil, nil
}
