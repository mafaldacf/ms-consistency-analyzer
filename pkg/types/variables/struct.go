package variables

import (
	"fmt"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type StructVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo       `json:"variable"`
	Fields       map[string]Variable `json:"struct_fields,omitempty"`
	FieldsLst    []Variable          `json:"omitempty"`
}

func (v *StructVariable) String() string {
	return v.VariableInfo.String()
}

func (v *StructVariable) LongString() string {
	s := v.VariableInfo.LongString() + " = {"
	i := len(v.Fields)
	for name, f := range v.Fields {
		s += fmt.Sprintf("%s: %s", name, f.LongString())
		if i < len(v.Fields)-1 {
			s += ", "
		}
		i++
	}
	return s + "}"
}

func (v *StructVariable) GetFieldVariables() map[string]*FieldVariable {
	fields := make(map[string]*FieldVariable)
	for n, f := range v.Fields {
		fields[n] = f.(*FieldVariable)
	}
	return fields
}

func (v *StructVariable) attachFieldVariable(fieldVariable *FieldVariable) {
	fieldType := fieldVariable.GetFieldType()
	fieldType.SetOrigin(v.GetType())
	fieldType.EnableStructField()
	if fieldVariable.FieldTypeIsDirectStructType() {
		fieldType.EnableEmbedded()
	}
}

func (v *StructVariable) AddFieldVariable(fieldVariable *FieldVariable) {
	logger.Logger.Warnf("[VARS STRUCT] adding field named (%s) for variable (%s) to struct variable (%s)", fieldVariable.GetFieldType().GetFieldName(), fieldVariable.String(), v.String())
	if fieldVariable.GetFieldType().GetFieldName() != "" {
		v.Fields[fieldVariable.GetFieldType().GetFieldName()] = fieldVariable
	} else {
		logger.Logger.Warnf("[VARS STRUCT] FIXME! SOMETIMES WE CAN HAVE UNKEYED FIELDS ")
	}
	v.Fields[fieldVariable.GetFieldType().GetFieldName()] = fieldVariable
	v.FieldsLst = append(v.FieldsLst, fieldVariable)
	v.attachFieldVariable(fieldVariable)
}

func (v *StructVariable) AddFieldVariableAndType(fieldVariable *FieldVariable) {
	v.AddFieldVariable(fieldVariable)
	v.GetStructType().AddFieldType(fieldVariable.GetFieldType())
}

func (v *StructVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *StructVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *StructVariable) GetStructType() *gotypes.StructType {
	if userType, ok := v.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.StructType)
	}
	return v.GetType().(*gotypes.StructType)
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

func (v *StructVariable) DeepCopy(force bool) Variable {
	copy := &StructVariable{
		VariableInfo: v.VariableInfo.DeepCopy(force),
		Fields:       make(map[string]Variable),
	}
	for n, p := range v.Fields {
		copy.Fields[n] = p.DeepCopy(force)
	}
	return copy
}

func (v *StructVariable) GetFieldVariableIfExists(name string) Variable {
	if f, ok := v.Fields[name]; ok {
		return f
	}
	//logger.Logger.Warnf("[VARS STRUCT] unknown field (%s) for struct variable (%s)", name, v.String())
	return nil
}

func (v *StructVariable) AddFieldKeyVariable(name string, field Variable) {
	v.Fields[name] = field
}

func (v *StructVariable) AddFieldKeyVariableIfNotExists(name string, field Variable) bool {
	if _, exists := v.Fields[name]; !exists {
		v.Fields[name] = field
		return true
	} else {
		logger.Logger.Warnf("[VARS STRUCT] field (%s) already exists in structure (%s)", name, v.String())
	}
	return false
}

func (v *StructVariable) AddReferenceWithID(reference Variable, creator string) {
	logger.Logger.Infof("[VARS STRUCT] trying to reference struct variable type (%s) for target type (%s) for variables: \n\t\t\t\t\t - current: %s \n\t\t\t\t\t - target: %s", utils.GetType(v), utils.GetType(reference), v.String(), reference.String())
	v.VariableInfo.AddReferenceWithID(reference, creator)

	for _, dep := range GetIndirectDependencies(reference) {
		logger.Logger.Debugf("\t\t[VARS STRUCT] indirect dep: %s", dep.String())
	}

	if referenceStruct, ok := reference.(*StructVariable); ok {
		logger.Logger.Infof("[VARS STRUCT] current variable has %d fields & reference variable has (%d)", len(v.Fields), len(referenceStruct.Fields))
		for name, field := range referenceStruct.Fields {
			if _, ok := v.Fields[name]; ok {
				v.Fields[name].AddReferenceWithID(field, creator)
			} else {
				logger.Logger.Warnf("[VARS STRUCT] skipping reference for unknown field (%s) in struct variable %s", name, v.String())
			}
		}
	} else {
		logger.Logger.Fatalf("[VARS STRUCT] referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), reference.String(), utils.GetType(v), utils.GetType(reference))
	}

	logger.Logger.Debugf("[VARS STRUCT] added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, v.VariableInfo.GetReference().GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
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

func (v *StructVariable) GetNestedFieldVariables(prefix string) ([]Variable, []string) {
	var nestedVariables []Variable
	var nestedIDs []string

	logger.Logger.Debugf("[VARS STRUCT] found (%d) field VARIABLES for (%s)", len(v.Fields), v.String())
	for _, f := range v.Fields {
		if fieldVariable, ok := f.(*FieldVariable); ok {
			nestedFieldVariables, nestedFieldIDs := fieldVariable.GetNestedFieldVariables(prefix)
			nestedVariables = append(nestedVariables, nestedFieldVariables...)
			nestedIDs = append(nestedIDs, nestedFieldIDs...)
		} else {
			logger.Logger.Fatalf("[VARS STRUCT] ignoring field variable (%s) for (%s)", f.String(), GetVariableTypeAndTypeString(f))
		}
	}
	return nestedVariables, nestedIDs
}

func (v *StructVariable) GetNestedFieldVariablesWithReferences(prefix string) ([]Variable, []string) {
	logger.Logger.Debugf("[VARS STRUCT] HAS REFERENCE????? %v", v.GetVariableInfo().GetReference())
	nestedVariables, nestedIDs := v.GetNestedFieldVariables(prefix)
	if reference := v.GetVariableInfo().GetReference(); reference != nil {
		logger.Logger.Debugf("[VARS STRUCT] HEREEEEE FOR REFERENCE %s", reference.String())
		nestedVariablesRef, nestedIDsRef := reference.Variable.(*StructVariable).GetNestedFieldVariablesWithReferences(prefix)
		nestedVariables = append(nestedVariables, nestedVariablesRef...)
		nestedIDs = append(nestedIDs, nestedIDsRef...)
	}
	return nestedVariables, nestedIDs
}

func (v *StructVariable) CopyFrom(target *StructVariable) {
	logger.Logger.Debugf("[VARS STRUCT COPY] copying from %s", target.LongString())
	for name, targetField := range target.Fields {
		if _, ok := v.Fields[name]; !ok {
			v.Fields[name] = targetField
		}
	}
}
