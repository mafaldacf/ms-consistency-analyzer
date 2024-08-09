package variables

import (
	"encoding/json"
	"fmt"
	"runtime"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type VariableInfo struct {
	Name string
	Type gotypes.Type
	Id   int64

	// dependencies are added to variables computed from returns
	// from function calls that cannot be statically analyzed
	// in practice, all returned variables will have all the parameters passed to the function call has dependencies
	Dependencies []Variable

	ReferencedBy []Variable
	References   []*Reference
	Parents      []Variable

	IsBlockParam  bool
	BlockParamIdx int

	Dataflows         []*Dataflow
	IndirectDataflows []*Dataflow
}

func (vinfo *VariableInfo) GetDependencies() []Variable {
	return vinfo.Dependencies
}

func (vinfo *VariableInfo) SetType(t gotypes.Type) {
	vinfo.Type = t
}

func (vinfo *VariableInfo) GetDataflows() []*Dataflow {
	return vinfo.Dataflows
}

func (vinfo *VariableInfo) GetIndirectDataflows() []*Dataflow {
	return vinfo.IndirectDataflows
}

func (vinfo *VariableInfo) GetAllDataflows() []*Dataflow {
	return append(vinfo.Dataflows, vinfo.IndirectDataflows...)
}

func (vinfo *VariableInfo) GetAllDataflowsForDatastore(datastore string) []*Dataflow {
	var dataflows []*Dataflow
	for _, df := range vinfo.Dataflows {
		if df.IsOpInDatastore(datastore) {
			dataflows = append(dataflows, df)
		}
	}
	for _, df := range vinfo.IndirectDataflows {
		if df.IsOpInDatastore(datastore) {
			dataflows = append(dataflows, df)
		}
	}
	return dataflows
}

func (vinfo *VariableInfo) GetAllReadDataflowsForDatastore(datastore string) []*Dataflow {
	var dataflows []*Dataflow
	for _, df := range vinfo.Dataflows {
		if df.IsOpInDatastore(datastore) && !df.IsWriteOp() {
			dataflows = append(dataflows, df)
		}
	}
	for _, df := range vinfo.IndirectDataflows {
		if df.IsOpInDatastore(datastore) && !df.IsWriteOp() {
			dataflows = append(dataflows, df)
		}
	}
	return dataflows
}

func (vinfo *VariableInfo) GetAllWriteDataflowsForDatastore(datastore string) []*Dataflow {
	var dataflows []*Dataflow
	for _, df := range vinfo.Dataflows {
		if df.IsOpInDatastore(datastore) && df.IsWriteOp() {
			dataflows = append(dataflows, df)
		}
	}
	for _, df := range vinfo.IndirectDataflows {
		if df.IsOpInDatastore(datastore) && df.IsWriteOp() {
			dataflows = append(dataflows, df)
		}
	}
	return dataflows
}

func (vinfo *VariableInfo) GetAllWriteDataflows() []*Dataflow {
	var dataflows []*Dataflow
	for _, df := range vinfo.Dataflows {
		if df.IsWriteOp() {
			dataflows = append(dataflows, df)
		}
	}
	for _, df := range vinfo.IndirectDataflows {
		if df.IsWriteOp() {
			dataflows = append(dataflows, df)
		}
	}
	return dataflows
}

func (vinfo *VariableInfo) GetAllReadDataflows() []*Dataflow {
	var dataflows []*Dataflow
	for _, df := range vinfo.Dataflows {
		if !df.IsWriteOp() {
			dataflows = append(dataflows, df)
		}
	}
	for _, df := range vinfo.IndirectDataflows {
		if !df.IsWriteOp() {
			dataflows = append(dataflows, df)
		}
	}
	return dataflows
}

func (vinfo *VariableInfo) Copy(force bool) *VariableInfo {
	// skip deep copy, especially since we can have references and dataflows
	if !force {
		return vinfo
	}

	var dataflows []*Dataflow
	for _, df := range vinfo.Dataflows {
		dataflows = append(dataflows, df.Copy(force))
	}
	var indirectDataflows []*Dataflow
	for _, df := range vinfo.IndirectDataflows {
		indirectDataflows = append(indirectDataflows, df.Copy(force))
	}
	var refsCopy []*Reference
	for _, r := range vinfo.References {
		refsCopy = append(refsCopy, r.Copy(force).(*Reference))
	}
	return &VariableInfo{
		Name:              vinfo.Name,
		Type:              vinfo.Type,
		Id:                vinfo.Id,
		References:        refsCopy,
		IsBlockParam:      vinfo.IsBlockParam,
		BlockParamIdx:     vinfo.BlockParamIdx,
		Dataflows:         dataflows,
		IndirectDataflows: indirectDataflows,
	}
}

func (vinfo *VariableInfo) DeepCopy() *VariableInfo {
	var dataflows []*Dataflow
	for _, df := range vinfo.Dataflows {
		dataflows = append(dataflows, df.DeepCopy())
	}
	var indirectDataflows []*Dataflow
	for _, df := range vinfo.IndirectDataflows {
		indirectDataflows = append(indirectDataflows, df.DeepCopy())
	}
	var refsCopy []*Reference
	for _, r := range vinfo.References {
		logger.Logger.Infof("[VARS INFO - DEEP COPY] deep copy reference (%s) for creator = %s", vinfo.String(), r.Creator)
		refsCopy = append(refsCopy, r.DeepCopy().(*Reference))
	}
	return &VariableInfo{
		Name:              vinfo.Name,
		Type:              vinfo.Type,
		Id:                vinfo.Id,
		References:        refsCopy,
		IsBlockParam:      vinfo.IsBlockParam,
		BlockParamIdx:     vinfo.BlockParamIdx,
		Dataflows:         dataflows,
		IndirectDataflows: indirectDataflows,
	}
}

func (vinfo *VariableInfo) MarshalJSON() ([]byte, error) {
	/* refStr := "<nil>"
	if v.Reference != nil {
		refStr = v.Reference.Variable.GetVariableInfo().GetName() + fmt.Sprintf(" (%d) @ ", v.Reference.Variable.GetId()) + v.Reference.Creator
	} */
	return json.Marshal(&struct {
		Name string `json:"name,omitempty"`
		Type string `json:"type,omitempty"`
		//Id   int64  `json:"id,omitempty"`
		//Reference bool   `json:"ref,omitempty"`
		References []*Reference `json:"refs,omitempty"`
	}{
		Name: vinfo.Name,
		Type: vinfo.Type.String(),
		//Id:   vinfo.Id,
		//Reference: v.Reference != nil,
		References: vinfo.References,
	})
}

func (vinfo *VariableInfo) String() string {
	if vinfo.Type != nil {
		if vinfo.Name != "" {
			return fmt.Sprintf("%s %s", vinfo.Name, vinfo.Type.String())
		}
		return vinfo.Type.String()
	}
	return fmt.Sprintf("%s (unknown)", vinfo.Name)
}

func (vinfo *VariableInfo) LongString() string {
	if vinfo.Type != nil {
		if vinfo.Name != "" {
			return fmt.Sprintf("%s %s", vinfo.Name, vinfo.Type.LongString())
		}
		return vinfo.Type.LongString()
	}
	return fmt.Sprintf("%s (unknown)", vinfo.Name)
}

func (vinfo *VariableInfo) IsBlockParameter() bool {
	return vinfo.IsBlockParam
}

func (vinfo *VariableInfo) EqualBlockParamIndex(idx int) bool {
	return vinfo.BlockParamIdx == idx
}

func (vinfo *VariableInfo) SetName(name string) {
	vinfo.Name = name
}

func (vinfo *VariableInfo) SetUnassigned() {
	vinfo.Id = VARIABLE_UNASSIGNED_ID
}

func (vinfo *VariableInfo) IsUnassigned() bool {
	return vinfo.Id == VARIABLE_UNASSIGNED_ID || vinfo.Id == VARIABLE_INLINE_ID
}

func (vinfo *VariableInfo) HasReferences() bool {
	return vinfo.References != nil
}

func (vinfo *VariableInfo) AssignID(id int64) {
	vinfo.Id = id
}

func (vinfo *VariableInfo) AddReferenceWithID(source Variable, target Variable, creator string) {
	logger.Logger.Debugf("[VARS INFO] adding new reference (%s) @ (%s) for variable (%s) with references list (len=%d): %v", target.String(), creator, vinfo.String(), len(vinfo.GetReferences()), vinfo.GetReferences())
	vinfo.ReferencedBy = append(vinfo.ReferencedBy, source)
	vinfo.Id = target.GetId()
	vinfo.References = append(vinfo.References, &Reference{
		Creator:  creator,
		Variable: target,
		Id:       target.GetId(),
	})
}

func (vinfo *VariableInfo) GetName() string {
	return vinfo.Name
}

func (vinfo *VariableInfo) GetId() int64 {
	return vinfo.Id
}

func (vinfo *VariableInfo) GetType() gotypes.Type {
	return vinfo.Type
}

func (vinfo *VariableInfo) GetReferences() []*Reference {
	return vinfo.References
}

func (vinfo *VariableInfo) SetParent(current Variable, parent Variable) {
	vinfo.AddParent(current, parent)
}

func (vinfo *VariableInfo) AddParent(current Variable, parent Variable) {
	if current == parent || vinfo == parent.GetVariableInfo() {
		pc, file, line, ok := runtime.Caller(1)
		if !ok {
			logger.Logger.Fatalf("RECURSION!! (%s) %s", VariableTypeName(parent), parent.String())
		}
		callerFunc := runtime.FuncForPC(pc).Name()
		logger.Logger.Fatalf("RECURSION!! (%s) %s \n\t\t\t\t\t(caller: %s) \n\t\t\t\t\t %s:%d", VariableTypeName(parent), parent.String(), callerFunc, file, line)
	}
	vinfo.Parents = append(vinfo.Parents, parent)
}
func (vinfo *VariableInfo) GetReferencesNestedDependencies(nearestFields bool, v Variable) []Variable {
	var deps []Variable
	for _, ref := range vinfo.References {
		deps = append(deps, ref.GetNestedDependencies(false)...)
	}

	return deps
}
