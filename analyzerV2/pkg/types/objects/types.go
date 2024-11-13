package objects

import (
	"fmt"
	golangtypes "go/types"
)

type Type interface {
	Name() string
	Underlying() Type
	Elem() Type
	String(depth int) string
	TypeName() string
}

type Named struct {
	Type       `yaml:"-"`
	name       string `yaml:"name"`
	underlying Type   `yaml:"underlying"`
	pkgName    string `yaml:"package_name"`
	pkgPath    string `yaml:"package_path"` // includes name
	external   bool   // true if package is external
}

func NewNamed(name string, pkgName string, pkgPath string, underlying Type, external bool) *Named {
	return &Named{
		name:       name,
		pkgName:    pkgName,
		pkgPath:    pkgPath,
		underlying: underlying,
		external:   external,
	}
}

func (t *Named) Name() string {
	return t.name
}

func (t *Named) Underlying() Type {
	return t.underlying
}

func (t *Named) PackageName() string {
	return t.pkgName
}

func (t *Named) PackagePath() string {
	return t.pkgPath
}

func (t *Named) IsExternal() bool {
	return t.external
}

func (t *Named) TypeName() string {
	return fmt.Sprintf("%s.%s %s", t.pkgName, t.name, t.underlying.TypeName())
}

func (t *Named) String(depth int) string {
	if depth < 1 {
		return fmt.Sprintf("%s.%s %s", t.pkgName, t.name, t.underlying.String(depth+1))
	}
	return t.TypeName()
}

type Basic struct {
	Type `yaml:"-"`
	name string                `yaml:"name"`
	kind golangtypes.BasicKind `yaml:"-"`
	info golangtypes.BasicInfo `yaml:"-"`
}

func NewBasic(name string, kind golangtypes.BasicKind, info golangtypes.BasicInfo) *Basic {
	return &Basic{
		name: name,
		kind: kind,
		info: info,
	}
}

func (t *Basic) Name() string {
	return t.name
}

func (t *Basic) Kind() golangtypes.BasicKind {
	return t.kind
}

func (t *Basic) Info() golangtypes.BasicInfo {
	return t.info
}

func (t *Basic) TypeName() string {
	return t.name
}

func (t *Basic) String(depth int) string {
	return t.name
}

type Pointer struct {
	Type `yaml:"-"`
	elem Type `yaml:"elem"`
}

func NewPointer(elem Type) *Pointer {
	return &Pointer{
		elem: elem,
	}
}

func (t *Pointer) Elem() Type {
	return t.elem
}

func (t *Pointer) TypeName() string {
	return fmt.Sprintf("*%s", t.elem.TypeName())
}

func (t *Pointer) String(depth int) string {
	return fmt.Sprintf("*%s", t.elem.String(depth+1))
}

type Chan struct {
	Type `yaml:"-"`
	elem Type                `yaml:"elem"`
	dir  golangtypes.ChanDir `yaml:"dir"`
}

func NewChan(elem Type, dir golangtypes.ChanDir) *Chan {
	return &Chan{
		elem: elem,
		dir:  dir,
	}
}

func (t *Chan) Elem() Type {
	return t.elem
}

func (t *Chan) Dir() golangtypes.ChanDir {
	return t.dir
}

func (t *Chan) TypeName() string {
	var chandir string
	switch t.Dir() {
	case golangtypes.SendRecv:
		chandir = "chan"
	case golangtypes.SendOnly:
		chandir = "chan<-"
	case golangtypes.RecvOnly:
		chandir = "<-chan"
	}
	return fmt.Sprintf("%s %s", chandir, t.elem.TypeName())
}

func (t *Chan) String(depth int) string {
	var chandir string
	switch t.Dir() {
	case golangtypes.SendRecv:
		chandir = "chan"
	case golangtypes.SendOnly:
		chandir = "chan<-"
	case golangtypes.RecvOnly:
		chandir = "<-chan"
	}
	return fmt.Sprintf("%s %s", chandir, t.elem.String(depth+1))
}

type Map struct {
	Type  `yaml:"-"`
	key   Type `yaml:"key"`
	value Type `yaml:"value"`
}

func NewMap(key Type, value Type) *Map {
	return &Map{
		key:   key,
		value: value,
	}
}

func (t *Map) Key() Type {
	return t.key
}

func (t *Map) Elem() Type {
	return t.value
}

func (t *Map) TypeName() string {
	return fmt.Sprintf("map[%s]%s", t.key.TypeName(), t.value.TypeName())
}

func (t *Map) String(depth int) string {
	return fmt.Sprintf("map[%s]%s", t.key.String(depth+1), t.value.String(depth+1))
}

type Array struct {
	Type `yaml:"-"`
	elem Type  `yaml:"elem"`
	len  int64 `yaml:"elem"`
}

func NewArray(elem Type, len int64) *Array {
	return &Array{
		elem: elem,
		len:  len,
	}
}

func (t *Array) Elem() Type {
	return t.elem
}

func (t *Array) Len() int64 {
	return t.len
}

func (t *Array) TypeName() string {
	return fmt.Sprintf("[%d]%s", t.len, t.elem.TypeName())
}

func (t *Array) String(depth int) string {
	return fmt.Sprintf("[%d]%s", t.len, t.elem.String(depth+1))
}

type Slice struct {
	Type `yaml:"-"`
	elem Type `yaml:"elem"`
}

func NewSlice(elem Type) *Slice {
	return &Slice{
		elem: elem,
	}
}

func (t *Slice) Elem() Type {
	return t.elem
}

func (t *Slice) TypeName() string {
	return fmt.Sprintf("[]%s", t.elem.TypeName())
}

func (t *Slice) String(depth int) string {
	return fmt.Sprintf("[]%s", t.elem.String(depth+1))
}

type Struct struct {
	Type   `yaml:"-"`
	fields []*Variable `yaml:"fields"`
	tags   []string    `yaml:"string"`
}

func NewStruct(fields []*Variable, tags []string) *Struct {
	return &Struct{
		fields: fields,
		tags:   tags,
	}
}

func (t *Struct) NumFields() int {
	return len(t.fields)
}

func (t *Struct) Field(i int) *Variable {
	return t.fields[i]
}

func (t *Struct) Tag(i int) string {
	return t.tags[i]
}

func (t *Struct) TypeName() string {
	return "struct{}"
}

func (t *Struct) String(depth int) string {
	str := "struct{"
	for i, field := range t.fields {
		str += field.String(depth+1)
		if i < t.NumFields()-1 {
			str += "; "
		}
	}
	str += "}"
	return str
}

type Tuple struct {
	Type `yaml:"-"`
	vars []*Variable `yaml:"variables"`
}

func NewTuple(vars []*Variable) *Tuple {
	return &Tuple{
		vars: vars,
	}
}

func (t *Tuple) Len() int {
	return len(t.vars)
}

func (t *Tuple) At(i int) *Variable {
	return t.vars[i]
}

// StringCompact does not include the () when len == 1
func (t *Tuple) StringCompact(depth int) string {
	if t.Len() == 1 {
		return t.vars[0].String(depth)
	}
	return t.String(depth)
}

// TypeNameCompact does not include the () when len == 1
func (t *Tuple) TypeNameCompact() string {
	if t.Len() == 1 {
		return t.vars[0].TypeName()
	}
	return t.TypeName()
}

func (t *Tuple) TypeName() string {
	return "tuple()"
}

func (t *Tuple) String(depth int) string {
	str := "("
	for i, v := range t.vars {
		str += v.String(depth+1)
		if i < t.Len()-1 {
			str += ", "
		}
	}
	str += ")"
	return str
}

type Interface struct {
	Type      `yaml:"-"`
	methods   []*Func `yaml:"methods"`
	embeddeds []Type  `yaml:"embeddeds"`
}

func NewInterface(methods []*Func, embeddeds []Type) *Interface {
	return &Interface{
		methods:   methods,
		embeddeds: embeddeds,
	}
}

func (t *Interface) NumMethods() int {
	return len(t.methods)
}

func (t *Interface) Method(i int) *Func {
	return t.methods[i]
}

func (t *Interface) NumEmbeddeds() int {
	return len(t.embeddeds)
}

func (t *Interface) Embedded(i int) Type {
	return t.embeddeds[i]
}

func (t *Interface) TypeName() string {
	return "interface{}"
}

func (t *Interface) String(depth int) string {
	str := "interface {"
	for i, embedded := range t.embeddeds {
		str += embedded.String(depth+1)
		if i < t.NumEmbeddeds()-1 || t.NumMethods() > 0 {
			str += "; "
		}
	}
	for i, method := range t.methods {
		str += method.String(depth+1)
		if i < t.NumMethods()-1 {
			str += "; "
		}
	}
	str += "}"
	return str
}

type Signature struct {
	Type    `yaml:"-"`
	recv    *Variable `yaml:"variable"`
	params  *Tuple    `yaml:"tuple"`
	results *Tuple    `yaml:"results"`
}

func NewSignature(recv *Variable, params *Tuple, results *Tuple) *Signature {
	return &Signature{
		recv:    recv,
		params:  params,
		results: results,
	}
}

func (t *Signature) Recv() *Variable {
	return t.recv
}

func (t *Signature) Params() *Tuple {
	return t.params
}

func (t *Signature) Results() *Tuple {
	return t.results
}

// StringCompact does not return the 'func' prefix
func (t *Signature) StringCompact(depth int) string {
	return fmt.Sprintf("%s %s", t.params.String(depth), t.results.StringCompact(depth))
}

// TypeNameCompact does not return the 'func' prefix
func (t *Signature) TypeNameCompact() string {
	return fmt.Sprintf("%s %s", t.params.TypeName(), t.results.TypeNameCompact())
}

func (t *Signature) TypeName() string {
	return "func"
}

func (t *Signature) String(depth int) string {
	return fmt.Sprintf("func%s %s", t.params.String(depth+1), t.results.String(depth+1))
}
