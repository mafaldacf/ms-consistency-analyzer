package variables

import (
	"encoding/json"
	"fmt"
	"slices"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type StructVariable struct {
	Variable
	Origin       *Variable
	VariableInfo *VariableInfo
	Fields       map[string]Variable
	FieldsLst    []Variable
}

func (v *StructVariable) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Origin       *Variable           `json:"-"`
		VariableInfo *VariableInfo       `json:"struct"`
		Fields       map[string]Variable `json:"struct_fields,omitempty"`
		FieldsLst    []Variable          `json:"-"`
	}{
		Origin:       v.Origin,
		VariableInfo: v.VariableInfo,
		Fields:       v.Fields,
		FieldsLst:    v.FieldsLst,
	})
}

func (v *StructVariable) String() string {
	return v.VariableInfo.String()
}

func (v *StructVariable) LongString() string {
	s := v.VariableInfo.LongString() + " \n\t\t\t\t\t\t = {"
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

func (v *StructVariable) GetElementAt(index int) Variable {
	if index > len(v.FieldsLst)-1 {
		logger.Logger.Fatalf("[VARS STRUCT] element at index (%d) does not exist in array variable with len (%d): %s", index, len(v.FieldsLst), v.String())
	}
	return v.FieldsLst[index]
}

func (v *StructVariable) GetFieldVariablesLst() []*FieldVariable {
	var fields []*FieldVariable
	for _, f := range v.Fields {
		fields = append(fields, f.(*FieldVariable))
	}
	return fields
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
	logger.Logger.Warnf("[VARS STRUCT] adding field named (%s) to struct variable (%s): (%s) %s", fieldVariable.GetFieldType().GetFieldName(), v.String(), VariableTypeName(fieldVariable.WrappedVariable), fieldVariable.WrappedVariable.String())
	if fieldVariable.GetFieldType().GetFieldName() != "" {
		v.Fields[fieldVariable.GetFieldType().GetFieldName()] = fieldVariable
	} else {
		logger.Logger.Warnf("[VARS STRUCT] FIXME! SOMETIMES WE CAN HAVE UNKEYED FIELDS ")
	}

	v.Fields[fieldVariable.GetFieldType().GetFieldName()] = fieldVariable
	v.FieldsLst = append(v.FieldsLst, fieldVariable)
	v.attachFieldVariable(fieldVariable)
	fieldVariable.GetVariableInfo().SetParent(fieldVariable, v)

	v.GetStructType().UpdateFieldAtIfExists(len(v.FieldsLst)-1, fieldVariable.GetFieldType())
}

func (v *StructVariable) AddFieldVariableAndType(fieldVariable *FieldVariable) {
	v.AddFieldVariable(fieldVariable)
	v.GetStructType().AddFieldType(fieldVariable.GetFieldType())
	fieldVariable.GetVariableInfo().SetParent(fieldVariable, v)
}

func (v *StructVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *StructVariable) GetType() gotypes.Type {
	if v.VariableInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for struct variable: %s", v.String())
	}
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

func (v *StructVariable) GetOrderedFields() []Variable {
	var orderedKeys []string
	for k := range v.Fields {
		orderedKeys = append(orderedKeys, k)
	}
	slices.Sort(orderedKeys)

	var orderedFields []Variable
	for _, k := range orderedKeys {
		orderedFields = append(orderedFields, v.Fields[k])
	}
	return orderedFields
}

func (v *StructVariable) GetDependencies() []Variable {
	return append(v.GetVariableInfo().GetDependencies(), v.GetOrderedFields()...)
}

func (v *StructVariable) GetNestedDependencies(nearestFields bool) []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	for _, elem := range v.GetOrderedFields() {
		deps = append(deps, elem.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *StructVariable) Copy(force bool) Variable {
	copy := &StructVariable{
		VariableInfo: v.VariableInfo.Copy(force),
		Fields:       make(map[string]Variable),
	}
	for n, p := range v.Fields {
		copy.Fields[n] = p.Copy(force)
		copy.Fields[n].GetVariableInfo().SetParent(copy.Fields[n], copy)
	}
	return copy
}

func (v *StructVariable) DeepCopy() Variable {
	logger.Logger.Debugf("[VARS STRUCT - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &StructVariable{
		VariableInfo: v.VariableInfo.DeepCopy(),
		Fields:       make(map[string]Variable),
	}
	for n, p := range v.Fields {
		copy.Fields[n] = p.DeepCopy()
		copy.Fields[n].GetVariableInfo().SetParent(copy.Fields[n], copy)
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
	v.FieldsLst = append(v.FieldsLst, field)
	field.GetVariableInfo().SetParent(field, v)
}

func (v *StructVariable) AddFieldKeyVariableIfNotExists(name string, field Variable) bool {
	if _, exists := v.Fields[name]; !exists {
		v.Fields[name] = field
		v.FieldsLst = append(v.FieldsLst, field)
		field.GetVariableInfo().SetParent(field, v)
		return true
	} else {
		logger.Logger.Warnf("[VARS STRUCT] field (%s) already exists in structure (%s)", name, v.String())
	}
	return false
}

func (v *StructVariable) attachReferenceToFields(target Variable, creator string) {
	if targetField, ok := target.(*FieldVariable); ok {
		logger.Logger.Warnf("------- FOUND FIELD THAT IS ALSO A STRUCT!!!!")
		target = targetField.WrappedVariable
	}

	if referenceStruct, ok := target.(*StructVariable); ok {
		logger.Logger.Infof("[VARS STRUCT - REF] current variable has %d fields & reference variable has (%d)", len(v.Fields), len(referenceStruct.Fields))
		for name, field := range referenceStruct.Fields {
			if _, ok := v.Fields[name]; ok {
				v.Fields[name].AddReferenceWithID(field, creator)
			} else {
				logger.Logger.Warnf("[VARS STRUCT - REF] skipping reference for unknown field (%s) in struct variable %s", name, v.String())
			}
		}
	} else {
		logger.Logger.Fatalf("[VARS STRUCT - REF] referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
}

func (v *StructVariable) AddReferenceWithID(target Variable, creator string) {
	logger.Logger.Infof("[VARS STRUCT - REF] trying to reference struct variable type (%s) for target type (%s) for variables: \n\t\t\t\t\t - current: %s \n\t\t\t\t\t - target: %s", utils.GetType(v), utils.GetType(target), v.String(), target.String())
	v.VariableInfo.AddReferenceWithID(v, target, creator)

	// target can also have its own references e.g.
	// (i) 1st reference: StorageService pushes to queue and Analytics service pops from queue using the workerThread() method
	// (ii) 2nd reference: AnalyticsService queue handler calls another function to process the message with the handleMessage() method
	// the current variable (v) is e.g. the "message" in the handleMessage() method
	// which references the message pop by AnalyticsService and passed in (ii)
	// which in turn references the message queued by StorageService in (i)
	v.attachReferenceToFields(target, creator)
	for _, ref := range target.GetVariableInfo().GetReferences() {
		v.AddReferenceWithID(ref.Variable, ref.Creator)
	}

	logger.Logger.Debugf("[VARS STRUCT - REF] added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
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
			logger.Logger.Fatalf("[VARS STRUCT] ignoring field variable (%s) for (%s)", f.String(), VariableTypeName(f))
		}
	}
	return nestedVariables, nestedIDs
}

func (v *StructVariable) GetNestedFieldVariablesWithReferences(prefix string) ([]Variable, []string) {
	nestedVariables, nestedIDs := v.GetNestedFieldVariables(prefix)
	for _, reference := range v.GetVariableInfo().GetReferences() {
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
