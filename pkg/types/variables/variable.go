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

func getDependenciesString(deps ...Variable) string {
	out := ""
	for i, d := range deps {
		out += fmt.Sprintf("%s (%d)", d.GetVariableInfo().GetName(), d.GetId())
		if i < len(deps)-1 {
			out += ", "
		}
	}
	return out
}

func ContainsMatchingDependencies(current Variable, target Variable) bool {
	currentDeps := GetIndirectDependenciesWithCurrent(current)
	logger.Logger.Debugf("[VAR] %s: got current dependencies: %v", getDependenciesString(current), getDependenciesString(currentDeps...))
	targetDeps := GetIndirectDependenciesWithCurrent(target)
	logger.Logger.Debugf("[VAR] %s: got target dependencies: %v", getDependenciesString(target), getDependenciesString(targetDeps...))

	for _, d := range currentDeps {
		if slices.Contains(targetDeps, d) {
			return true
		}
	}
	return false
}
