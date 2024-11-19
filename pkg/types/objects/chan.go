package objects

import (
	"encoding/json"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type ChanObject struct {
	Object
	ObjectInfo *ObjectInfo
}

func (v *ChanObject) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		ObjectInfo *ObjectInfo `json:"chan"`
	}{
		ObjectInfo: v.ObjectInfo,
	})
}

func (v *ChanObject) String() string {
	return v.ObjectInfo.String()
}

func (v *ChanObject) LongString() string {
	return v.ObjectInfo.LongString()
}

func (v *ChanObject) GetId() int64 {
	return v.ObjectInfo.GetId()
}

func (v *ChanObject) GetType() gotypes.Type {
	if v.ObjectInfo.GetType() == nil {
		logger.Logger.Fatalf("[VARS ADDRESS] unexpected nil type for chan variable: %s", v.String())
	}
	return v.ObjectInfo.GetType()
}

func (v *ChanObject) GetVariableInfo() *ObjectInfo {
	return v.ObjectInfo
}

func (v *ChanObject) GetDependencies() []Object {
	return v.GetVariableInfo().GetDependencies()
}

func (v *ChanObject) GetNestedDependencies(nearestFields bool) []Object {
	var deps = []Object{v}
	if v.GetVariableInfo().HasReferences() {
		deps = append(deps, v.GetVariableInfo().GetReferencesNestedDependencies(nearestFields, v)...)
	}
	return deps
}

func (v *ChanObject) AddReferenceWithID(target Object, creator string) {
	v.ObjectInfo.AddReferenceWithID(v, target, creator)
}

func (v *ChanObject) Copy(force bool) Object {
	copy := &ChanObject{
		ObjectInfo: v.ObjectInfo.Copy(force),
	}
	return copy
}

func (v *ChanObject) DeepCopy() Object {
	logger.Logger.Debugf("[VARS CHAN - DEEP COPY] (%s) %s", VariableTypeName(v), v.String())
	copy := &ChanObject{
		ObjectInfo: v.ObjectInfo.DeepCopy(),
	}
	return copy
}

func (v *ChanObject) GetUnassaignedVariables() []Object {
	var variables []Object
	if v.GetVariableInfo().IsUnassigned() {
		variables = append(variables, v)
	}
	return variables
}
