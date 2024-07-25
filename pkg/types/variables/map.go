package variables

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

type MapVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo         `json:"variable"`
	KeyValues    map[Variable]Variable `json:"map_kvs,omitempty"`
}

func (v *MapVariable) String() string {
	return v.VariableInfo.String()
}

func (v *MapVariable) LongString() string {
	return v.VariableInfo.LongString()
}

func (v *MapVariable) GetKeyValueIfExists(targetKey Variable) Variable {
	if !v.GetMapType().GetKeyType().IsSameType(targetKey.GetType()) {
		logger.Logger.Fatalf("[VARS MAP] provided key (%s) with type (%s) does not match expected type (%s)", targetKey.String(), utils.GetType(targetKey.GetType()), utils.GetType(v.GetMapType().GetKeyType()))
	}
	switch t := targetKey.GetType().(type) {
	case *gotypes.BasicType:
		for key, value := range v.KeyValues {
			if key.GetType().(*gotypes.BasicType).Value == t.Value {
				return value
			}
		}
	default:
		logger.Logger.Fatalf("unknown gotype (%s) for target key (%s)", utils.GetType(targetKey.GetType()), targetKey.String())
	}
	logger.Logger.Warnf("??????? could not get or create key value pairs for target key (%s) in map (%v)", targetKey.String(), v.String())
	return v.KeyValues[targetKey]
}

func (v *MapVariable) AddKeyValue(key Variable, value Variable) {
	v.KeyValues[key] = value
}

func (v *MapVariable) GetId() int64 {
	return v.VariableInfo.GetId()
}

func (v *MapVariable) GetType() gotypes.Type {
	return v.VariableInfo.GetType()
}

func (v *MapVariable) GetMapType() *gotypes.MapType {
	if userType, ok := v.VariableInfo.GetType().(*gotypes.UserType); ok {
		return userType.UserType.(*gotypes.MapType)
	}
	return v.VariableInfo.GetType().(*gotypes.MapType)
}

func (v *MapVariable) GetVariableInfo() *VariableInfo {
	return v.VariableInfo
}

func (v *MapVariable) AddKeyValuePair(key Variable, value Variable) {
	v.KeyValues[key] = value
}

func (v *MapVariable) GetDependencies() []Variable {
	var dependencies []Variable
	for _, value := range v.KeyValues {
		dependencies = append(dependencies, value)
	}
	return dependencies
}

func (v *MapVariable) GetNestedIndirectDependencies() []Variable {
	var deps = []Variable{v}
	if v.GetVariableInfo().HasReference() {
		deps = append(deps, v.GetVariableInfo().GetReference().GetNestedIndirectDependencies()...)
	}
	for _, elem := range v.KeyValues {
		deps = append(deps, elem.GetNestedIndirectDependencies()...)
	}
	return deps
}

func (v *MapVariable) DeepCopy(force bool) Variable {
	copy := &MapVariable{
		KeyValues:    make(map[Variable]Variable, 0),
		VariableInfo: v.VariableInfo.DeepCopy(force),
	}
	for k, v := range v.KeyValues {
		copy.KeyValues[k] = v.DeepCopy(force)
	}
	return copy
}

func (v *MapVariable) MarshalJSON() ([]byte, error) {
	type kvstruct struct {
		Key   Variable
		Value Variable
	}

	var kvs []kvstruct
	for key, value := range v.KeyValues {
		kvs = append(kvs, kvstruct{
			Key:   key,
			Value: value,
		})
	}

	return json.MarshalIndent(&struct {
		VariableInfo *VariableInfo `json:"variable"`
		KeyValues    []kvstruct    `json:"key_values"`
	}{
		VariableInfo: v.VariableInfo,
		KeyValues:    kvs,
	}, "", " ")
}

func (v *MapVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
	if targetMap, ok := target.(*MapVariable); ok {
		for key, value := range v.KeyValues {
			targetValue, ok := targetMap.KeyValues[key]
			if !ok {
				logger.Logger.Warnf("[VARS MAP - REF] invalid target key %s in map: %v", key, targetMap)
			} else {
				targetValue.AddReferenceWithID(value, creator)
			}
		}
		logger.Logger.Debugf("[VARS MAP - REF] added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
		return
	}
	// exception: map[string]interface{} --> struct
	if _, keyIsMapType := v.GetMapType().KeyType.(*gotypes.BasicType); keyIsMapType {
		if _, valueIsInterfaceType := v.GetMapType().ValueType.(*gotypes.InterfaceType); valueIsInterfaceType {
			if targetStructVariable, ok := target.(*StructVariable); ok {
				for key, value := range v.KeyValues {
					targetValue, ok := targetStructVariable.Fields[key.GetType().GetBasicValue()]
					if !ok {
						logger.Logger.Warnf("[VARS MAP - REF] skipping target key (%s) (%s) in struct (%s) with fields:", utils.GetType(key), key.GetType().GetBasicValue(), targetStructVariable)
						for k, f := range targetStructVariable.Fields {
							logger.Logger.Warnf("\t\t [VARS MAP - REF] - %s: (%s) %s", k, GetVariableTypeAndTypeString(f), f.String())
						}
					} else {
						logger.Logger.Debugf("[VARS MAP - REF] target (%s) got referenced to value (%s)", targetValue.String(), value.String())
						targetValue.AddReferenceWithID(value, creator)
					}
				}
				logger.Logger.Debugf("[VARS MAP - REF] added reference (%s) (%s) -> (%s) (%s) with id = %d (creator: %s)", v.VariableInfo.Name, utils.GetType(v), target.GetVariableInfo().GetName(), utils.GetType(target), v.VariableInfo.Id, creator)
				return
			}
		}
	}
	logger.Logger.Fatalf("[VARS MAP - REF] attempted to reference variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))

}

func (v *MapVariable) GetNestedFieldVariables(prefix string) ([]Variable, []string) {
	var nestedVariables []Variable
	var nestedIDs []string

	logger.Logger.Debugf("[VARS MAP] found (%d) field VARIABLES for (%s): %v", len(v.KeyValues), v.String(), v.KeyValues)
	for _, value := range v.KeyValues {
		if fieldVariable, ok := value.(*FieldVariable); ok {
			nestedFieldVariables, nestedFieldIDs := fieldVariable.GetNestedFieldVariables(prefix)
			nestedVariables = append(nestedVariables, nestedFieldVariables...)
			nestedIDs = append(nestedIDs, nestedFieldIDs...)
		} else {
			logger.Logger.Warnf("[VARS MAP] ignoring field key typed (%s) for value variable (%s) in map variable (%s): (%s)", utils.GetType(value), value.String(), GetVariableTypeAndTypeString(v), v.String())
		}
	}
	return nestedVariables, nestedIDs
}

func (v *MapVariable) GetNestedFieldVariablesWithReferences(prefix string) ([]Variable, []string) {
	logger.Logger.Debugf("[VARS MAP] HAS REFERENCE????? %v", v.GetVariableInfo().GetReference())
	nestedVariables, nestedIDs := v.GetNestedFieldVariables(prefix)
	if reference := v.GetVariableInfo().GetReference(); reference != nil {
		logger.Logger.Debugf("[VARS MAP] HEREEEEE FOR REFERENCE %s", reference.String())
		if referenceMapVar, ok := reference.Variable.(*MapVariable); ok {
			nestedVariablesRef, nestedIDsRef := referenceMapVar.GetNestedFieldVariablesWithReferences(prefix)
			nestedVariables = append(nestedVariables, nestedVariablesRef...)
			nestedIDs = append(nestedIDs, nestedIDsRef...)
		} else if referenceStructVar, ok := reference.Variable.(*StructVariable); ok {
			nestedVariablesRef, nestedIDsRef := referenceStructVar.GetNestedFieldVariablesWithReferences(prefix)
			nestedVariables = append(nestedVariables, nestedVariablesRef...)
			nestedIDs = append(nestedIDs, nestedIDsRef...)
		} else {
			logger.Logger.Warnf("[VARS MAP] ignoring reference typed (%s) for reference variable (%s) in map variable (%s): (%s)", utils.GetType(reference.Variable), reference.Variable.String(), GetVariableTypeAndTypeString(v), v.String())
		}
	}
	return nestedVariables, nestedIDs
}

func (v *MapVariable) GetUnassaignedVariables() []Variable {
	var variables []Variable
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
		for k, v := range v.KeyValues {
			variables = append(variables, k.GetUnassaignedVariables()...)
			variables = append(variables, v.GetUnassaignedVariables()...)
		}
	}
	return variables
}
