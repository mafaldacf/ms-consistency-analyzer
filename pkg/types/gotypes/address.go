package gotypes

import "fmt"

type AddressType struct {
	Type      `json:"-"`
	AddressOf Type
}

// ------------
// Type Methods
// ------------

func (t *AddressType) IsSameType(other Type) bool {
	_, ok := other.(*AddressType)
	return ok
}
func (t *AddressType) String() string {
	return fmt.Sprintf("(&%s)", t.AddressOf.String())
}
func (t *AddressType) LongString() string {
	return fmt.Sprintf("(&%s)", t.AddressOf.LongString())
}
func (t *AddressType) GetName() string {
	return "(&" + t.AddressOf.GetName() + ")"
}
func (t *AddressType) GetLongName() string {
	return "(&" + t.AddressOf.GetLongName() + ")"
}
func (t *AddressType) GetBasicValue() string {
	return t.AddressOf.GetBasicValue()
}
func (t *AddressType) AddValue(value string) {
	t.AddressOf.AddValue(value)
}

// ---------------
// Address Methods
// ---------------
