package variables

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type StructVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo       `json:"variable"`
	Fields       map[string]Variable `json:"struct_fields,omitempty"`
}

func (v *StructVariable) String() string {
	return v.VariableInfo.String()
}

func (v *StructVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *StructVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *StructVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *StructVariable) GetDependencies() []Variable {
	var deps []Variable
	for _, field := range v.Fields {
		deps = append(deps, field)
	}
	return deps
}

func (v *StructVariable) DeepCopy() Variable {
	copy := &StructVariable{
		VariableInfo: v.VariableInfo,
		Fields:       make(map[string]Variable),
	}
	for n, p := range v.Fields {
		copy.Fields[n] = p.DeepCopy()
	}
	return copy
}

func (v *StructVariable) AddFieldVariableIfNotExists(name string, field Variable) bool {
	if _, exists := v.Fields[name]; !exists {
		v.Fields[name] = field
		return true
	} else {
		logger.Logger.Warnf("field %s already exists in structure %s", name, v.String())
	}
	return false
}

func (v *StructVariable) GetStructType() *gotypes.StructType {
	structType, ok := v.VariableInfo.Type.(*gotypes.StructType)
	if !ok {
		structType = v.VariableInfo.Type.(*gotypes.UserType).UserType.(*gotypes.StructType)
	}
	return structType
}

func (v *StructVariable) AddReferenceWithID(target Variable, creator string) {
	logger.Logger.Warnf("referencing in struct variable %s for target %s", v.String(), target.String())
	v.VariableInfo.AddReferenceWithID(target, creator)
	if targetStruct, ok := target.(*StructVariable); ok {
		for name, field := range v.Fields {
			targetField, ok := targetStruct.Fields[name]
			if !ok {
				logger.Logger.Warnf("invalid target field %s in struct fields: %v", name, targetStruct.Fields)
			} else {
				field.AddReferenceWithID(targetField, creator)
			}
		}
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}

	logger.Logger.Debugf("added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
}

func (v *StructVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, p := range v.Fields {
			variables = append(variables, p.GetUnassaignedVariables()...)
		}
	}
	return variables
}

func (t *StructVariable) GetNestedFieldVariables(prefix string) ([]Variable, []string) {
	var nestedVariables []Variable
	var nestedIDs []string

	logger.Logger.Warnf("FOUND %d FIELDS FOR %s", len(t.Fields), t.String())
	for _, f := range t.Fields {
		if fieldVariable, ok := f.(*FieldVariable); ok {
			nestedFieldVariables, nestedFieldIDs := fieldVariable.GetNestedFieldVariables(prefix)
			nestedVariables = append(nestedVariables, nestedFieldVariables...)
			nestedIDs = append(nestedIDs, nestedFieldIDs...)
		} else {
			logger.Logger.Fatalf("[FIXME] ignoring field variable %s (%s)", f.String(), GetVariableTypeAndTypeString(f))
		}
	}
	return nestedVariables, nestedIDs
}

func (t *StructVariable) CopyFrom(target *StructVariable) {
	for name, targetField := range target.Fields {
		if _, ok := t.Fields[name]; !ok {
			t.Fields[name] = targetField
		}
	}
}
