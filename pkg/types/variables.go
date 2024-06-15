package types

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
	"encoding/json"
	"fmt"
	"slices"
)

type Reference struct {
	Variable
	Creator string
}

func (ref *Reference) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name    string `json:"name"`
		Creator string `json:"creator"`
		Id      int64  `json:"id"`
		/* IndirectDeps string `json:"indirect_deps"` */
		/* Params 			[]Variable 		`json:"ref_params"` */
	}{
		Name:    ref.Variable.GetVariableInfo().GetName(),
		Creator: ref.Creator,
		Id:      ref.Variable.GetVariableInfo().GetId(),
		/* IndirectDeps: getDependenciesString(getIndirectDependencies(ref)...), */
		/* Params:  		ref.Variable.GetDependencies(), */
	})
}
func (ref *Reference) String() string {
	if ref.Variable != nil {
		return ref.Variable.String() + "(created by " + ref.Creator + ")"
	}
	return "nil-reference"
}
func (ref *Reference) GetVariableInfo() *VariableInfo {
	if ref.Variable != nil {
		return ref.Variable.GetVariableInfo()
	}
	return nil
}
func (ref *Reference) GetDependencies() []Variable {
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
	AddReferenceWithID(target Variable, creator string)
	DeepCopy() Variable
}

type Dataflow struct {
	DirectWrite bool
	Datastore   string
	Service     string

	// if it is not a direct write
	// then we set the variable that is the source of the write
	Source Variable
}
type VariableInfo struct {
	Name string
	Type Type
	Id   int64

	Reference     *Reference
	IsBlockParam  bool
	BlockParamIdx int

	Dataflow *Dataflow
}

func (v *VariableInfo) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name string `json:"name,omitempty"`
		Type string `json:"type,omitempty"`
		Id   int64  `json:"id,omitempty"`
		//Reference bool   `json:"ref,omitempty"`
		Reference *Reference `json:"ref,omitempty"`
	}{
		Name: v.Name,
		Type: v.Type.String(),
		Id:   v.Id,
		//Reference: v.Reference != nil,
		Reference: v.Reference,
	})
}

func (v *VariableInfo) SetDirectWrite(datastore string, service string) {
	if v.Dataflow != nil && v.Dataflow.Datastore != datastore && v.Dataflow.Service != service {
		logger.Logger.Fatalf("data flow already exists for variable %s", v.String())
	}
	if v.Dataflow != nil && !v.Dataflow.DirectWrite {
		logger.Logger.Warnf("upgrading data flow for variable %s", v.String())
	}
	v.Dataflow = &Dataflow{
		DirectWrite: true,
		Datastore:   datastore,
		Service:     service,
	}
}

func (v *VariableInfo) SetIndirectWrite(variable Variable) {
	v.Dataflow = &Dataflow{
		Source:    variable,
		Datastore: variable.GetVariableInfo().Dataflow.Datastore,
		Service:   variable.GetVariableInfo().Dataflow.Service,
	}
}

type TupleVariable struct {
	Variable     `json:"-"`
	Variables     []Variable    `json:"tuple_variables,omitempty"`
}

type CompositeVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Params       []Variable    `json:"composition,omitempty"`
}

type GenericVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Params       []Variable    `json:"generic_params,omitempty"`
}

type ParameterVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}

type StructVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo       `json:"variable"`
	Fields       map[string]Variable `json:"struct_fields,omitempty"`
}

type MapVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo         `json:"variable"`
	KeyValues    map[Variable]Variable `json:"map_kvs,omitempty"`
}

type ArrayVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	Elements     []Variable    `json:"array_elems,omitempty"`
}

type PointerVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	PointerTo    Variable      `json:"ptr_to,omitempty"`
}

type AddressVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
	AddressOf    Variable      `json:"addr_of,omitempty"`
}
type InterfaceVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}
type ChanVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}
type BasicVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}

type InlineVariable struct {
	Variable     `json:"-"`
	VariableInfo *VariableInfo `json:"variable"`
}
type SelectorVariable struct {
	Variable `json:"wrapped_variable"`
	Parent   Variable `json:"-"`
	Field    string   `json:"selector"`
}

func (v *SelectorVariable) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Variable Variable `json:"wrapped_variable"`
		Parent   string   `json:"parent"`
		Field    string   `json:"selector"`
	}{
		Variable: v.Variable,
		Parent:   v.Parent.GetVariableInfo().Name,
		Field:    v.Field,
	})
}

// ------------------
// COMPOSITE VARIABLE
// ------------------
func (v *CompositeVariable) String() string                 { return v.VariableInfo.String() }
func (v *CompositeVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *CompositeVariable) GetDependencies() []Variable    { return v.Params }
func (v *CompositeVariable) DeepCopy() Variable { 
	copy := &CompositeVariable{
		VariableInfo: v.VariableInfo,
	}
	for _, p := range v.Params {
		copy.Params = append(copy.Params, p.DeepCopy())
	}
	return copy
}

func (v *CompositeVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
	if targetComposite, ok := target.(*CompositeVariable); ok {
		for i, p := range v.Params {
			if i > len(targetComposite.Params) {
				logger.Logger.Warnf("invalid argument index %d for length %d in params: %v", i, (targetComposite.Params), targetComposite.Params)
			} else {
				p.AddReferenceWithID(targetComposite.Params[i], creator)
			}
		}
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
	logger.Logger.Debugf("added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
}

// ----------------
// GENERIC VARIABLE
// ----------------
func (v *GenericVariable) String() string                 { return v.VariableInfo.String() }
func (v *GenericVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *GenericVariable) GetDependencies() []Variable    { return v.Params }
func (v *GenericVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
	if targetGeneric, ok := target.(*GenericVariable); ok {
		for i, p := range v.Params {
			if i > len(targetGeneric.Params) {
				logger.Logger.Warnf("invalid argument index %d for length %d in params: %v", i, (targetGeneric.Params), targetGeneric.Params)
			} else {
				p.AddReferenceWithID(targetGeneric.Params[i], creator)
			}
		}
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
	logger.Logger.Debugf("added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
}
func (v *GenericVariable) DeepCopy() Variable { 
	copy := &GenericVariable{
		VariableInfo: v.VariableInfo,
	}
	for _, p := range v.Params {
		copy.Params = append(copy.Params, p.DeepCopy())
	}
	return copy
}

// ---------------
// STRUCT VARIABLE
// ---------------
func (v *StructVariable) String() string                 { return v.VariableInfo.String() }
func (v *StructVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
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
		Fields: make(map[string]Variable),
	}
	for n, p := range v.Fields {
		copy.Fields[n] = p.DeepCopy()
	}
	return copy
}

func (v *StructVariable) AddFieldIfNotExists(name string, field Variable) {
	if _, exists := v.Fields[name]; !exists {
		v.Fields[name] = field
	} else {
		logger.Logger.Warnf("field %s already exists in structure %s", name, v.String())
	}
}

func (v *StructVariable) GetStructType() *StructType {
	structType, ok := v.VariableInfo.Type.(*StructType)
	if !ok {
		structType = v.VariableInfo.Type.(*UserType).UserType.(*StructType)
	}
	return structType
}

func (v *StructVariable) AddReferenceWithID(target Variable, creator string) {
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

// ------------
// MAP VARIABLE
// ------------
func (v *MapVariable) String() string                               { return v.VariableInfo.String() }
func (v *MapVariable) GetVariableInfo() *VariableInfo               { return v.VariableInfo }
func (v *MapVariable) AddKeyValuePair(key Variable, value Variable) { v.KeyValues[key] = value }
func (v *MapVariable) GetDependencies() []Variable {
	var dependencies []Variable
	for _, v := range v.KeyValues {
		dependencies = append(dependencies, v.GetDependencies()...)
	}
	return dependencies
}

func (v *MapVariable) DeepCopy() Variable { 
	copy := &MapVariable{
		VariableInfo: v.VariableInfo,
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
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}

	logger.Logger.Debugf("added reference (%s) -> (%s) with id = %d (creator: %s)", v.VariableInfo.Name, target.GetVariableInfo().GetName(), v.VariableInfo.Id, creator)
}

// --------------
// ARRAY VARIABLE
// --------------
func (v *ArrayVariable) String() string                 { return v.VariableInfo.String() }
func (v *ArrayVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *ArrayVariable) AddElement(element Variable)    { v.Elements = append(v.Elements, element) }
func (v *ArrayVariable) AddElements(element []Variable)    { v.Elements = append(v.Elements, element...) }
func (v *ArrayVariable) GetDependencies() []Variable    { return v.Elements }
func (v *ArrayVariable) DeepCopy() Variable { 
	copy := &ArrayVariable{
		VariableInfo: v.VariableInfo,
	}
	for _, v := range v.Elements {
		copy.Elements = append(copy.Elements, v.DeepCopy())
	}
	return copy
}

// --------------
// TUPLE VARIABLE
// --------------
func (v *TupleVariable) String() string { return "tuple variable"}
func (v *TupleVariable) GetVariableInfo() *VariableInfo { return nil }
func (v *TupleVariable) GetDependencies() []Variable    { return nil }
func (v *TupleVariable) DeepCopy() Variable { 
	copy := &TupleVariable{}
	for _, v := range v.Variables {
		copy.Variables = append(copy.Variables, v.DeepCopy())
	}
	return copy
}

// ----------------
// POINTER VARIABLE
// ----------------
func (v *PointerVariable) String() string                 { return v.VariableInfo.String() }
func (v *PointerVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *PointerVariable) GetDependencies() []Variable    { return v.PointerTo.GetDependencies() }
func (v *PointerVariable) GetPointerTo() Variable         { return v.PointerTo }
func (v *PointerVariable) AddReferenceWithID(target Variable, creator string) {
	if targetPointerTo, ok := target.(*PointerVariable); ok {
		v.PointerTo.AddReferenceWithID(targetPointerTo.PointerTo, creator)
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
}
func (v *PointerVariable) DeepCopy() Variable { 
	copy := &PointerVariable{
		VariableInfo: v.VariableInfo,
		PointerTo: v.PointerTo.DeepCopy(),
	}
	return copy
}

// ----------------
// ADDRESS VARIABLE
// ----------------
func (v *AddressVariable) String() string                 { return v.VariableInfo.String() }
func (v *AddressVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *AddressVariable) GetDependencies() []Variable    { return v.AddressOf.GetDependencies() }
func (v *AddressVariable) GetAddressOf() Variable         { return v.AddressOf }
func (v *AddressVariable) AddReferenceWithID(target Variable, creator string) {
	if targetAddressOf, ok := target.(*AddressVariable); ok {
		v.AddressOf.AddReferenceWithID(targetAddressOf.AddressOf, creator)
	} else {
		logger.Logger.Warnf("referenced variables with different types (%s vs %s) (%s vs %s)", v.String(), target.String(), utils.GetType(v), utils.GetType(target))
	}
}
func (v *AddressVariable) DeepCopy() Variable { 
	copy := &AddressVariable{
		VariableInfo: v.VariableInfo,
		AddressOf: v.AddressOf.DeepCopy(),
	}
	return copy
}

// ---------------
// INLINE VARIABLE
// ---------------
func (v *InlineVariable) String() string                 { return v.VariableInfo.String() }
func (v *InlineVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *InlineVariable) GetDependencies() []Variable    { return nil }
func (v *InlineVariable) AddReferenceWithID(target Variable, creator string) {
	logger.Logger.Warnf("IGNORING REFERENCES FOR INLINE VARIABLE!!")
}
func (v *InlineVariable) DeepCopy() Variable { 
	copy := &InlineVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

// --------------
// BASIC VARIABLE
// --------------
func (v *BasicVariable) String() string                 { return v.VariableInfo.String() }
func (v *BasicVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *BasicVariable) GetDependencies() []Variable    { return nil }
func (v *BasicVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}
func (v *BasicVariable) DeepCopy() Variable { 
	copy := &BasicVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

// -----------------
// INTEFACE VARIABLE
// -----------------
func (v *InterfaceVariable) String() string                 { return v.VariableInfo.String() }
func (v *InterfaceVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *InterfaceVariable) GetDependencies() []Variable    { return nil }
func (v *InterfaceVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}
func (v *InterfaceVariable) DeepCopy() Variable { 
	copy := &InterfaceVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

// -------------
// CHAN VARIABLE
// -------------
func (v *ChanVariable) String() string                 { return v.VariableInfo.String() }
func (v *ChanVariable) GetVariableInfo() *VariableInfo { return v.VariableInfo }
func (v *ChanVariable) GetDependencies() []Variable    { return nil }
func (v *ChanVariable) AddReferenceWithID(target Variable, creator string) {
	v.VariableInfo.AddReferenceWithID(target, creator)
}
func (v *ChanVariable) DeepCopy() Variable { 
	copy := &ChanVariable{
		VariableInfo: v.VariableInfo,
	}
	return copy
}

// -----------------
// SELECTOR VARIABLE
// -----------------
func (v *SelectorVariable) String() string                 { return v.Variable.String() }
func (v *SelectorVariable) GetVariableInfo() *VariableInfo { return v.Variable.GetVariableInfo() }
func (v *SelectorVariable) GetDependencies() []Variable    { return v.Variable.GetDependencies() }
func (v *SelectorVariable) AddReferenceWithID(target Variable, creator string) {
	logger.Logger.Warnf("IGNORING REFERENCES FOR SELECTOR VARIABLE!!")
}
func (v *SelectorVariable) DeepCopy() Variable { 
	copy := &SelectorVariable{
		Parent: v.Parent.DeepCopy(),
		Field: v.Field,
	}
	return copy
}

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
	logger.Logger.Infof("\t added reference (%s) -> (%s) with id = %d (creator: %s)", vinfo.Name, target.GetVariableInfo().GetName(), vinfo.Id, creator)
}

func (vinfo *VariableInfo) AddOriginalReferenceWithID(ref *Reference) {
	vinfo.Id = ref.Variable.GetVariableInfo().Id
	vinfo.Reference = ref
}

func GetIndirectDependencies(v Variable) []Variable {
	indirectDeps := []Variable{v}
	// indirect dependencies from reference
	if v.GetVariableInfo().HasReference() {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(v.GetVariableInfo().GetReference())...)
	}
	// direct dependencies
	for _, dep := range v.GetDependencies() {
		indirectDeps = append(indirectDeps, GetIndirectDependencies(dep)...)
	}

	return indirectDeps
}

func getDependenciesString(deps ...Variable) string {
	out := ""
	for i, d := range deps {
		out += fmt.Sprintf("%s (%d)", d.GetVariableInfo().GetName(), d.GetVariableInfo().GetId())
		if i < len(deps)-1 {
			out += ", "
		}
	}
	return out
}

func ContainsMatchingDependencies(current Variable, target Variable) bool {
	currentDeps := GetIndirectDependencies(current)
	logger.Logger.Debugf("%s: got current dependencies: %v", getDependenciesString(current), getDependenciesString(currentDeps...))
	targetDeps := GetIndirectDependencies(target)
	logger.Logger.Debugf("%s: got target dependencies: %v", getDependenciesString(target), getDependenciesString(targetDeps...))

	for _, d := range currentDeps {
		if slices.Contains(targetDeps, d) {
			return true
		}
	}
	return false
}

func (vinfo *VariableInfo) GetName() string          { return vinfo.Name }
func (vinfo *VariableInfo) GetId() int64             { return vinfo.Id }
func (vinfo *VariableInfo) GetType() Type            { return vinfo.Type }
func (vinfo *VariableInfo) GetReference() *Reference { return vinfo.Reference }
