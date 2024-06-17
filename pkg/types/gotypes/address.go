package gotypes

import "fmt"

type AddressType struct {
	Type      `json:"-"`
	AddressOf Type
}

// ------------
// Type Methods
// ------------

func (t *AddressType) String() string {
	return fmt.Sprintf("&%s", t.AddressOf.String())
}
func (t *AddressType) FullString() string {
	return fmt.Sprintf("&%s", t.AddressOf.FullString())
}
func (t *AddressType) GetName() string {
	return t.String()
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
