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
			if key.GetType().(*gotypes.BasicType).Value  == t.Value {
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
	for _, v := range v.KeyValues {
		dependencies = append(dependencies, v.GetDependencies()...)
	}
	return dependencies
}

func (v *MapVariable) DeepCopy() Variable {
	copy := &MapVariable{
		KeyValues: make(map[Variable]Variable, 0),
		VariableInfo: v.VariableInfo.DeepCopy(),
	}
	for k, v := range v.KeyValues {
		copy.KeyValues[k] = v.DeepCopy()
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
				logger.Logger.Warnf("invalid target key %s in map: %v", key, targetMap)
			} else {
				targetValue.AddReferenceWithID(value, creator)
			}
		}
	} else {
		logger.Logger.Warnf("[VARS MAP] referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}

	logger.Logger.Debugf("[VARS MAP] added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
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
