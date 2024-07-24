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
}

func GetVariableTypeAndTypeString(v Variable) string {
	return utils.GetType(v) + " " + utils.GetType(v.GetType())
}

func GetReversedNestedFieldsAndNames(variable Variable, includeReferences bool) (nestedVariables []Variable, nestedNames []string) {
	if structVariable, ok := variable.(*StructVariable); ok {
		variables := []Variable{structVariable}
		names := []string{structVariable.GetType().GetName()}

		if includeReferences {
			nestedVariables, nestedNames = structVariable.GetNestedFieldVariablesWithReferences(variable.GetType().GetName())
		} else {
			nestedVariables, nestedNames = structVariable.GetNestedFieldVariables(variable.GetType().GetName())
		}

		variables = append(variables, nestedVariables...)
		names = append(names, nestedNames...)
		slices.Reverse(variables)
		slices.Reverse(names)
		return variables, names
	} else {
		logger.Logger.Fatalf("unexpected type (%s) for variable (%s)", utils.GetType(variable), variable.String())
	}
	return nil, nil
}

func GetIndirectDependenciesWithCurrent(v Variable) []Variable {
	indirectDeps := []Variable{v}
	return append(indirectDeps, GetIndirectDependencies(v)...)
}

func GetIndirectDependencies(v Variable) []Variable {
	var indirectDeps []Variable
	// indirect dependencies from reference
	if v.GetVariableInfo().HasReference() {
		indirectDeps = append(indirectDeps, GetIndirectDependenciesWithCurrent(v.GetVariableInfo().GetReference())...)
	}
	// direct dependencies
	for _, dep := range v.GetDependencies() {
		indirectDeps = append(indirectDeps, GetIndirectDependenciesWithCurrent(dep)...)
	}

	return indirectDeps
}

func GetDependenciesStringLst(deps ...Variable) string {
	out := ""
	for _, d := range deps {
		out += fmt.Sprintf("\t\t\t\t\t - %s: %s\n", d.GetVariableInfo().GetName(), d.GetVariableInfo().String())
	}
	return out
}

func ContainsMatchingDependencies2(readKeyDeps []Variable, writeValueDeps []Variable) bool {
	for _, d := range readKeyDeps {
		if slices.Contains(writeValueDeps, d) {
			return true
		}
	}
	return false
}

func ContainsMatchingDependencies(readKey Variable, writeValue Variable) bool {
	readKeyDeps := GetIndirectDependenciesWithCurrent(readKey)
	logger.Logger.Debugf("[READ KEY] dependencies for %s: \n%v", readKey.String(), GetDependenciesStringLst(readKeyDeps...))
	writeValueDeps := GetIndirectDependenciesWithCurrent(writeValue)
	logger.Logger.Debugf("[WRITE VALUE] dependencies for %s: \n%v", writeValue.String(), GetDependenciesStringLst(writeValueDeps...))

	for _, d := range readKeyDeps {
		if slices.Contains(writeValueDeps, d) {
			return true
		}
	}
	return false
}
