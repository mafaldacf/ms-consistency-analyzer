package variables

import (
	"encoding/json"
	"fmt"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

type VariableInfo struct {
	Name string
	Type gotypes.Type
	Id   int64

	Reference     *Reference
	IsBlockParam  bool
	BlockParamIdx int

	Dataflows         []*Dataflow
	IndirectDataflows []*Dataflow
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

func (vinfo *VariableInfo) DeepCopy() *VariableInfo {
	var dataflows []*Dataflow
	for _, df := range vinfo.Dataflows {
		dataflows = append(dataflows, df.DeepCopy())
	}
	var indirectDataflows []*Dataflow
	for _, df := range vinfo.IndirectDataflows {
		indirectDataflows = append(indirectDataflows, df.DeepCopy())
	}
	return &VariableInfo{
		Name:              vinfo.Name,
		Type:              vinfo.Type,
		Id:                vinfo.Id,
		Reference:         vinfo.Reference.DeepCopy().(*Reference),
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
		Id   int64  `json:"id,omitempty"`
		//Reference bool   `json:"ref,omitempty"`
		Reference *Reference `json:"ref,omitempty"`
	}{
		Name: vinfo.Name,
		Type: vinfo.Type.String(),
		Id:   vinfo.Id,
		//Reference: v.Reference != nil,
		Reference: vinfo.Reference,
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
			return fmt.Sprintf("%s %s", vinfo.Name, vinfo.Type.String())
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

func (vinfo *VariableInfo) HasReference() bool {
	return vinfo.Reference != nil
}

func (vinfo *VariableInfo) AssignID(id int64) {
	vinfo.Id = id
}

func (vinfo *VariableInfo) AddReferenceWithID(target Variable, creator string) {
	vinfo.Id = target.GetId()
	vinfo.Reference = &Reference{
		Creator:  creator,
		Variable: target,
	}
	logger.Logger.Infof("\t\t\t[VARIABLE] added reference (%s) -> (%s) with id = %d (creator: %s)", vinfo.Name, target.GetVariableInfo().GetName(), vinfo.Id, creator)
}

func (vinfo *VariableInfo) AddOriginalReferenceWithID(ref *Reference) {
	vinfo.Id = ref.Variable.GetId()
	vinfo.Reference = ref
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

func (vinfo *VariableInfo) GetReference() *Reference {
	return vinfo.Reference
}
