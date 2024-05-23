package types

import (
	"analyzer/pkg/logger"
	"encoding/json"
	"fmt"

	"github.com/golang-collections/collections/stack"
)

type Reference struct {
	Variable
	Creator  string
}
func (ref *Reference) MarshalJSON() ([]byte, error) {
	deps := ""
	for i, d := range ref.Variable.GetDependencies() {
		deps += fmt.Sprintf("%s (%d)", d.GetVariableInfo().GetName(), d.GetVariableInfo().GetId())
		if i < len(ref.Variable.GetDependencies()) - 1 {
			deps += ", "
		}
	}

	return json.Marshal(&struct {
		Name    string `json:"name"`
		Creator string `json:"creator"`
		Id      int64  `json:"id"`
		Deps 	string 	`json:"deps,omitempty"`
	}{
		Name:    ref.Variable.GetVariableInfo().GetName(),
		Creator: ref.Creator,
		Id:      ref.Variable.GetVariableInfo().GetId(),
		Deps: 	 deps,
	})
}
func (ref *Reference) String() string{
	if ref.Variable != nil {
		return ref.Variable.String() + "(created by " + ref.Creator + ")"
	}
	return "nil-reference"
}
func (ref *Reference) GetVariableInfo() *VariableInfo{
	if ref.Variable != nil {
		return ref.Variable.GetVariableInfo()
	}
	return nil
}
func (ref *Reference) GetDependencies() []Variable{
	if ref.Variable != nil {
		return ref.Variable.GetDependencies()
	}
	return nil
}

const VARIABLE_INLINE_ID int64 = 0
const VARIABLE_UNASSIGNED_ID int64 = -1
type Variable interface {
	String() string
	GetVariableInfo() *VariableInfo
	GetDependencies() []Variable
}
type VariableInfo struct {
	Name string
	Type Type
	Id   int64

	Reference *Reference
	IsBlockParam  bool
	BlockParamIdx int
}

func (v *VariableInfo) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      		string     `json:"name,omitempty"`
		Type      		string     `json:"type,omitempty"`
		Id        		int64      `json:"id,omitempty"`
		Reference 		*Reference `json:"ref,omitempty"`
	}{
		Name:      v.Name,
		Type:      v.Type.String(),
		Id:        v.Id,
		Reference: v.Reference,
	})
}

type GenericVariable struct {
	Variable 							`json:"-"`
	VariableInfo *VariableInfo 			`json:"variable"`
	Params 		 []Variable 		    `json:"params,omitempty"`
}

type ParameterVariable struct {
	Variable 							`json:"-"`
	VariableInfo *VariableInfo 		 	`json:"variable"`
}

type StructVariable struct {
	Variable 							`json:"-"`
	VariableInfo *VariableInfo  		`json:"variable"`
	Fields       map[string]Variable 	`json:"fields,omitempty"`
}

type MapVariable struct {
	Variable 							`json:"-"`
	VariableInfo *VariableInfo  		`json:"variable"`
	KeyValues     map[Variable]Variable `json:"key_values,omitempty"`
}

type ArrayVariable struct {
	Variable 							`json:"-"`
	VariableInfo *VariableInfo  		`json:"variable"`
	Elements      []Variable 			`json:"elements"`
}

type PointerVariable struct {
	Variable 							`json:"-"`
	VariableInfo *VariableInfo 			`json:"variable"`
	PointerTo    Variable 				`json:"pointer_to"`
}

type AddressVariable struct {
	Variable 							`json:"-"`
	VariableInfo *VariableInfo 			`json:"variable"`
	AddressOf    Variable 				`json:"address_of"`
}

// ----------------
// GENERIC VARIABLE
// ----------------
func (v *GenericVariable) String() string                 { return v.VariableInfo.String() }
func (v *GenericVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *GenericVariable) GetDependencies() []Variable 	  { return v.Params }

// ---------------
// STRUCT VARIABLE
// ---------------
func (v *StructVariable) String() string                       { return v.VariableInfo.String() }
func (v *StructVariable) GetVariableInfo() *VariableInfo       { return v.VariableInfo }
func (v *StructVariable) AddField(name string, field Variable) { v.Fields[name] = field }

func (v *StructVariable) GetDependencies() []Variable { 
	var deps []Variable
	for _, field := range v.Fields {
		deps = append(deps, field)
	}
	return deps
}

// ------------
// MAP VARIABLE
// ------------
func (v *MapVariable) String() string                       			{ return v.VariableInfo.String() }
func (v *MapVariable) GetVariableInfo() *VariableInfo       			{ return v.VariableInfo }
func (v *MapVariable) AddKeyValuePair(key Variable, value Variable) 	{ v.KeyValues[key] = value }
func (v *MapVariable) GetDependencies() []Variable {
	var dependencies []Variable 
	for _, v := range v.KeyValues {
		dependencies = append(dependencies, v.GetDependencies()...)
	}
	return dependencies
}
func (v *MapVariable) MarshalJSON() ([]byte, error) {
	type kvstruct struct {
		Key Variable
		Value Variable
	}

	var kvs []kvstruct
	for key, value := range v.KeyValues {
		kvs = append(kvs, kvstruct{
			Key: key,
			Value: value,
		})
	}

	return json.MarshalIndent(&struct {
		VariableInfo *VariableInfo  `json:"variable"`
		KeyValues     []kvstruct 	`json:"key_values"`
	}{
		VariableInfo: v.VariableInfo,
		KeyValues: kvs,
	}, "", " ")
}

// --------------
// ARRAY VARIABLE
// --------------
func (v *ArrayVariable) String() string                       { return v.VariableInfo.String() }
func (v *ArrayVariable) GetVariableInfo() *VariableInfo       { return v.VariableInfo }
func (v *ArrayVariable) AddElement(element Variable) 		  { v.Elements = append(v.Elements, element) }
func (v *ArrayVariable) GetDependencies() []Variable 		  { return v.Elements}

// ----------------
// POINTER VARIABLE
// ----------------
func (v *PointerVariable) String() string                 { return v.VariableInfo.String() }
func (v *PointerVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *PointerVariable) GetDependencies() []Variable 	  { return v.PointerTo.GetDependencies() }
func (v *PointerVariable) GetPointerTo() Variable 	  	  { return v.PointerTo }


// ----------------
// ADDRESS VARIABLE
// ----------------
func (v *AddressVariable) String() string                 { return v.VariableInfo.String() }
func (v *AddressVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *AddressVariable) GetDependencies() []Variable 	  { return v.AddressOf.GetDependencies() }
func (v *AddressVariable) GetAddressOf() Variable 	  	  { return v.AddressOf }

// -------------
// VARIABLE INFO
// -------------
func (vinfo *VariableInfo) String() string {
	if vinfo.Type != nil {
		return fmt.Sprintf("%s %s", vinfo.Name, vinfo.Type)
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
	vinfo.Id = target.GetVariableInfo().GetId()
	vinfo.Reference = &Reference{
		Creator:  creator,
		Variable: target,
	}
	logger.Logger.Debugf("added reference (%s) -> (%s) with id = %d (creator: %s)", vinfo.Name, target.GetVariableInfo().GetName(), vinfo.Id, creator)
}

func (vinfo *VariableInfo) AddOriginalReferenceWithID(ref *Reference) {
	vinfo.Id = ref.Variable.GetVariableInfo().Id
	vinfo.Reference = ref
}

func IsReferencedObject(current Variable, target Variable) bool {
	var stack stack.Stack
	stack.Push(current)
	for stack.Len() != 0 {
		variable := stack.Pop().(Variable)
		// cannot do variable == target since they can be different due to the Reference variable
		// but ids are still the same because they were previously matched in the abstract graph
		// e.g. in case variable == target.ref.variable
		if variable.GetVariableInfo().GetId() == target.GetVariableInfo().GetId() {
			return true
		}
		if variable.GetVariableInfo().HasReference() {
			stack.Push(variable.GetVariableInfo().GetReference().Variable)
		}
		for _, dep := range variable.GetDependencies() {
			stack.Push(dep)
		}
	}
	return false
}

func (vinfo *VariableInfo) GetName() string             	{ return vinfo.Name }
func (vinfo *VariableInfo) GetId() int64                	{ return vinfo.Id }
func (vinfo *VariableInfo) GetType() Type               	{ return vinfo.Type }
func (vinfo *VariableInfo) GetReference() *Reference        { return vinfo.Reference }
