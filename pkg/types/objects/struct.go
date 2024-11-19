package objects

import (
	"encoding/json"
	"fmt"
	"slices"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type StructObject struct {
	Object
	Origin     *Object
	ObjectInfo *ObjectInfo
	Fields     map[string]Object
	FieldsLst  []Object
}

func (v *StructObject) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Origin     *Object           `json:"-"`
		ObjectInfo *ObjectInfo       `json:"struct"`
		Fields     map[string]Object `json:"struct_fields,omitempty"`
		FieldsLst  []Object          `json:"-"`
	}{
		Origin:     v.Origin,
		ObjectInfo: v.ObjectInfo,
		Fields:     v.Fields,
		FieldsLst:  v.FieldsLst,
	})
}

func (v *StructObject) String() string {
	return v.ObjectInfo.String()
}

func (v *StructObject) LongString() string {
	s := v.ObjectInfo.LongString() + " \n\t\t\t\t\t\t = {"
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

func (v *StructObject) GetElementAt(index int) Object {
	if index > len(v.FieldsLst)-1 {
		logger.Logger.Fatalf("[VARS STRUCT] element at index (%d) does not exist in array variable with len (%d): %s", index, len(v.FieldsLst), v.String())
	}
	return v.FieldsLst[index]
}

func (v *StructObject) GetFieldVariablesLst() []*FieldObject {
	var fields []*FieldObject
	for _, f := range v.Fields {
		fields = append(fields, f.(*FieldObject))
	}
	return fields
}

func (v *StructObject) GetFieldVariables() map[string]*FieldObject {
	fields := make(map[string]*FieldObject)
	for n, f := range v.Fields {
		fields[n] = f.(*FieldObject)
	}
	return fields
}

func (v *StructObject) attachFieldVariable(fieldVariable *FieldObject) {
	fieldType := fieldVariable.GetFieldType()
	fieldType.SetOrigin(v.GetType())
	fieldType.EnableStructField()
	if fieldVariable.FieldTypeIsDirectStructType() {
		fieldType.EnableEmbedded()
	}
}

func (v *StructObject) AddOrGetFieldVariable(fieldVariable *FieldObject) {
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

func (v *StructObject) AddOrGetFieldVariableAndType(fieldVariable *FieldObject) {
	v.AddOrGetFieldVariable(fieldVariable)
	v.GetStructType().AddOrGetFieldType(fieldVariable.GetFieldType())
	fieldVariable.GetVariableInfo().SetParent(fieldVariable, v)
}

func (v *StructObject) GetId() int64 {
	return v.ObjectInfo.GetId()
}

func (v *StructObject) GetType() gotypes.Type {
	if v.ObjectInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for struct variable: %s", v.String())
	}
	return v.ObjectInfo.GetType()
}

func (v *StructObject) GetStructType() *gotypes.StructType {
	if userType, ok := v.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.StructType)
	}
	return v.GetType().(*gotypes.StructType)
}

func (v *StructObject) GetVariableInfo() *ObjectInfo {
	return v.ObjectInfo
}

func (v *StructObject) GetOrderedFields() []Object {
	var orderedKeys []string
	for k := range v.Fields {
		orderedKeys = append(orderedKeys, k)
	}
	slices.Sort(orderedKeys)

	var orderedFields []Object
	for _, k := range orderedKeys {
		orderedFields = append(orderedFields, v.Fields[k])
	}
	return orderedFields
}

func (v *StructObject) GetDependencies() []Object {
	return append(v.GetVariableInfo().GetDependencies(), v.GetOrderedFields()...)
}

func (v *StructObject) GetNestedDependencies(nearestFields bool) []Object {
	var deps = []Object{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	for _, elem := range v.GetOrderedFields() {
		deps = append(deps, elem.GetNestedDependencies(nearestFields)...)
	}
	return deps
}

func (v *StructObject) Copy(force bool) Object {
	copy := &StructObject{
		ObjectInfo: v.ObjectInfo.Copy(force),
		Fields:     make(map[string]Object),
	}
	for n, p := range v.Fields {
		copy.Fields[n] = p.Copy(force)
		copy.Fields[n].GetVariableInfo().SetParent(copy.Fields[n], copy)
	}
	return copy
}

func (v *StructObject) DeepCopy() Object {
	logger.Logger.Debugf("[VARS STRUCT - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &StructObject{
		ObjectInfo: v.ObjectInfo.DeepCopy(),
		Fields:     make(map[string]Object),
	}
	for n, p := range v.Fields {
		copy.Fields[n] = p.DeepCopy()
		copy.Fields[n].GetVariableInfo().SetParent(copy.Fields[n], copy)
	}
	return copy
}

func (v *StructObject) GetFieldVariableIfExists(name string) Object {
	if f, ok := v.Fields[name]; ok {
		return f
	}
	//logger.Logger.Warnf("[VARS STRUCT] unknown field (%s) for struct variable (%s)", name, v.String())
	return nil
}

func (v *StructObject) AddOrGetFieldKeyVariable(name string, field Object) {
	v.Fields[name] = field
	v.FieldsLst = append(v.FieldsLst, field)
	field.GetVariableInfo().SetParent(field, v)
}

func (v *StructObject) AddOrGetFieldKeyVariableIfNotExists(name string, field Object) bool {
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

func (v *StructObject) attachReferenceToFields(target Object, creator string) {
	if targetField, ok := target.(*FieldObject); ok {
		logger.Logger.Warnf("------- FOUND FIELD THAT IS ALSO A STRUCT!!!!")
		target = targetField.WrappedVariable
	}

	if referenceStruct, ok := target.(*StructObject); ok {
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

func (v *StructObject) AddReferenceWithID(target Object, creator string) {
	logger.Logger.Infof("[VARS STRUCT - REF] trying to reference struct variable type (%s) for target type (%s) for variables: \n\t\t\t\t\t - current: %s \n\t\t\t\t\t - target: %s", utils.GetType(v), utils.GetType(target), v.String(), target.String())
	v.ObjectInfo.AddReferenceWithID(v, target, creator)

	// target can also have its own references e.g.
	// (i) 1st reference: StorageService pushes to queue and Analytics service pops from queue using the workerThread() method
	// (ii) 2nd reference: AnalyticsService queue handler calls another function to process the message with the handleMessage() method
	// the current variable (v) is e.g. the "message" in the handleMessage() method
	// which references the message pop by AnalyticsService and passed in (ii)
	// which in turn references the message queued by StorageService in (i)
	v.attachReferenceToFields(target, creator)
	for _, ref := range target.GetVariableInfo().GetReferences() {
		v.AddReferenceWithID(ref.Object, ref.Creator)
	}

	logger.Logger.Debugf("[VARS STRUCT - REF] added reference (%s) -> (%s) with id = %d (creator: %s)", v.ObjectInfo.Name, target.GetVariableInfo().GetName(), v.ObjectInfo.Id, creator)
}

func (v *StructObject) GetUnassaignedVariables() []Object {
	var variables []Object
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for _, p := range v.Fields {
			variables = append(variables, p.GetUnassaignedVariables()...)
		}
	}
	return variables
}

func (v *StructObject) GetNestedFieldVariables(prefix string, noSQL bool) ([]Object, []string) {
	var nestedVariables []Object
	var nestedIDs []string

	logger.Logger.Debugf("[VARS STRUCT] found (%d) field VARIABLES for (%s); current prefix = %s", len(v.Fields), v.String(), prefix)
	for _, f := range v.Fields {
		if fieldVariable, ok := f.(*FieldObject); ok {
			nestedFieldObjects, nestedFieldIDs := fieldVariable.GetNestedFieldVariables(prefix, noSQL)
			nestedVariables = append(nestedVariables, nestedFieldObjects...)
			nestedIDs = append(nestedIDs, nestedFieldIDs...)
		} else {
			logger.Logger.Fatalf("[VARS STRUCT] ignoring field variable (%s) for (%s)", f.String(), VariableTypeName(f))
		}
	}
	return nestedVariables, nestedIDs
}

func (v *StructObject) GetNestedFieldVariablesWithReferences(prefix string, noSQL bool) ([]Object, []string) {
	nestedVariables, nestedIDs := v.GetNestedFieldVariables(prefix, noSQL)
	for _, reference := range v.GetVariableInfo().GetReferences() {
		nestedVariablesRef, nestedIDsRef := reference.Object.(*StructObject).GetNestedFieldVariablesWithReferences(prefix, noSQL)
		nestedVariables = append(nestedVariables, nestedVariablesRef...)
		nestedIDs = append(nestedIDs, nestedIDsRef...)
	}
	return nestedVariables, nestedIDs
}

func (v *StructObject) CopyFrom(target *StructObject) {
	logger.Logger.Debugf("[VARS STRUCT COPY] copying from %s", target.LongString())
	for name, targetField := range target.Fields {
		if _, ok := v.Fields[name]; !ok {
			v.Fields[name] = targetField
		}
	}
}
