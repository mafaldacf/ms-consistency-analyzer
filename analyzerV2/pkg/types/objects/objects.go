package objects

import (
	"fmt"
	"go/constant"
)

type Object interface {
	Name() string
	Type() Type
	Struct() *Struct
	Interface() *Interface
	String(depth int) string
	TypeName() string
}

type Service struct {
	Object
	t     *Struct
	iface *Interface
	name  string
}

func NewService(name string, t Type, iface Type) *Service {
	return &Service{
		t:     t.(*Struct),
		iface: iface.(*Interface),
		name:  name,
	}
}

func (obj *Service) Name() string {
	return obj.name
}

func (obj *Service) Struct() *Struct {
	return obj.t
}

func (obj *Service) Interface() *Interface {
	return obj.iface
}

func (obj *Service) TypeName() string {
	return fmt.Sprintf("[%s] %s %s", obj.name, obj.t.TypeName(), obj.iface.TypeName())
}

func (obj *Service) String(depth int) string {
	return fmt.Sprintf("[%s] %s %s", obj.name, obj.t.String(depth), obj.iface.String(depth))
}

type Datastore struct {
	Object
	iface *Interface
	name  string
}

func NewDatastore(name string, iface Type) *Datastore {
	return &Datastore{
		iface: iface.(*Interface),
		name:  name,
	}
}

func (obj *Datastore) Name() string {
	return obj.name
}

func (obj *Datastore) Interface() *Interface {
	return obj.iface
}

func (obj *Datastore) TypeName() string {
	return fmt.Sprintf("[%s] %s", obj.name, obj.iface.TypeName())
}

func (obj *Datastore) String(depth int) string {
	return fmt.Sprintf("[%s] %s", obj.name, obj.iface.String(depth))
}

type Variable struct {
	Object
	t    Type
	name string
}

func NewVariable(name string, t Type) *Variable {
	return &Variable{
		t:    t,
		name: name,
	}
}

func (obj *Variable) Name() string {
	return obj.name
}

func (obj *Variable) Type() Type {
	return obj.t
}

func (obj *Variable) TypeName() string {
	return fmt.Sprintf("%s %s", obj.name, obj.Type().TypeName())
}

func (obj *Variable) String(depth int) string {
	return fmt.Sprintf("%s %s", obj.name, obj.Type().String(depth))
}

type Constant struct {
	Object `yaml:"-"`
	t      Type           `yaml:"type"`
	name   string         `yaml:"name"`
	val    constant.Value `yaml:"-"`
}

func NewConstant(name string, t Type, val constant.Value) *Constant {
	return &Constant{
		t:    t,
		name: name,
		val:  val,
	}
}

func (obj *Constant) Name() string {
	return obj.name
}

func (obj *Constant) Type() Type {
	return obj.t
}

func (obj *Constant) Value() constant.Value {
	return obj.val
}

func (obj *Constant) TypeName() string {
	return fmt.Sprintf("const %s %s = %s", obj.name, obj.t.TypeName(), obj.val.String())
}

func (obj *Constant) String(depth int) string {
	return fmt.Sprintf("const %s %s = %s", obj.name, obj.t.String(depth), obj.val.String())
}

type Func struct {
	Object `yaml:"-"`
	t      *Signature `yaml:"type"`
	name   string     `yaml:"name"`
}

func NewFunc(name string, t Type) *Func {
	return &Func{
		t:    t.(*Signature),
		name: name,
	}
}

func (obj *Func) Name() string {
	return obj.name
}

func (obj *Func) Type() Type {
	return obj.t
}

func (obj *Func) TypeName() string {
	recv := obj.t.recv
	if recv != nil {
		return fmt.Sprintf("func (%s).%s %s", recv.TypeName(), obj.name, obj.t.TypeNameCompact())
	}
	return fmt.Sprintf("func %s %s", obj.name, obj.t.TypeNameCompact())
}

func (obj *Func) String(depth int) string {
	recv := obj.t.recv
	if recv != nil {
		return fmt.Sprintf("func (%s).%s %s", recv.String(depth), obj.name, obj.t.StringCompact(depth))
	}
	return fmt.Sprintf("func %s %s", obj.name, obj.t.StringCompact(depth))
}

type TypeName struct {
	Object `yaml:"-"`
	t      Type   `yaml:"type"`
	name   string `yaml:"name"`
}

func NewTypeName(name string, t Type) *TypeName {
	return &TypeName{
		name: name,
		t:    t,
	}
}

func (obj *TypeName) Name() string {
	return obj.name
}

func (obj *TypeName) Type() Type {
	return obj.t
}

func (obj *TypeName) TypeName() string {
	return fmt.Sprintf("type %s %s", obj.name, obj.t.TypeName())
}

func (obj *TypeName) String(depth int) string {
	return fmt.Sprintf("type %s %s", obj.name, obj.t.String(depth))
}

type PkgName struct {
	Object `yaml:"-"`
	t      Type   `yaml:"type"`
	name   string `yaml:"name"`
}

func NewPkgName(name string, t Type) *PkgName {
	return &PkgName{
		t:    t,
		name: name,
	}
}

func (obj *PkgName) Name() string {
	return obj.name
}

func (obj *PkgName) Type() Type {
	return obj.t
}

func (obj *PkgName) TypeName() string {
	return fmt.Sprintf("package %s %s", obj.name, obj.t.TypeName())
}

func (obj *PkgName) String(depth int) string {
	return fmt.Sprintf("package %s %s", obj.name, obj.t.String(depth))
}
