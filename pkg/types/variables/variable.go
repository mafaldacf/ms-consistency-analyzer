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
	AddReferenceWithID(target Variable, creator string)
	GetUnassaignedVariables() []Variable
	DeepCopy() Variable
	GetId() int64
	GetType() gotypes.Type
}

func GetVariableTypeAndTypeString(v Variable) string {
	return utils.GetType(v) + " " + utils.GetType(v.GetType())
}

func GetIndirectDependencies(v Variable) []Variable {
	indirectDeps := []Variable{v}
	// indirect dependencies from reference
	if v.GetVariableInfo().HasReference() {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(v.GetVariableInfo().GetReference())...)
	}
	// direct dependencies
	for _, dep := range v.GetDependencies() {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(dep)...)
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
	currentDeps := GetIndirectDependencies(current)
	logger.Logger.Debugf("[VAR] %s: got current dependencies: %v", getDependenciesString(current), getDependenciesString(currentDeps...))
	targetDeps := GetIndirectDependencies(target)
	logger.Logger.Debugf("[VAR] %s: got target dependencies: %v", getDependenciesString(target), getDependenciesString(targetDeps...))

	for _, d := range currentDeps {
		if slices.Contains(targetDeps, d) {
			return true
		}
	}
	return false
}
