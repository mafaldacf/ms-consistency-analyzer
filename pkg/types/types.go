package types

import (
	"fmt"
	"strings"
)

type Type interface {
	String() string
	GetName() string
}

type Service struct {
	Type    `json:"-"`
	Package string
	Name    string
}
type User struct {
	Type    `json:"-"`
	Package string
	Name    string
}
type Basic struct {
	Type    `json:"-"`
	Name    string
}
type Interface struct {
	Type    `json:"-"`
}
type Pointer struct {
	Type      `json:"-"`
	PointerTo Type
}

func packageAlias(pkg string) string {
	splits := strings.Split(pkg, "/")
	return splits[len(splits)-1]
}

// ------------
// SERVICE TYPE
// ------------
func (t *Service) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *Service) GetName() string {
	return t.Name
}

// ------------
// POINTER TYPE
// ------------
func (t *Pointer) String() string {
	return fmt.Sprintf("*%s", t.PointerTo)
}
func (t *Pointer) GetName() string {
	return t.PointerTo.GetName()
}

// ---------
// USER TYPE
// ---------
func (t *User) String() string {
	return fmt.Sprintf("%s.%s", packageAlias(t.Package), t.Name)
}
func (t *User) GetName() string {
	return t.Name
}

// ----------
// BASIC TYPE
// ----------
func (t *Basic) String() string {
	return t.Name
}
func (t *Basic) GetName() string {
	return t.Name
}

// --------------
// INTERFACE TYPE
// --------------
func (t *Interface) String() string {
	return "interface{}"
}
func (t *Interface) GetName() string {
	return "interface{}"
}
