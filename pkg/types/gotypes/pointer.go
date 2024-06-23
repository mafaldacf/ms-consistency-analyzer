package gotypes

import "fmt"

type PointerType struct {
	Type      `json:"-"`
	PointerTo Type
}

// ------------
// Type Methods
// ------------

func (t *PointerType) IsSameType(other Type) bool {
	_, ok := other.(*PointerType)
	return ok
}
func (t *PointerType) String() string {
	return fmt.Sprintf("*%s", t.PointerTo.String())
}
func (t *PointerType) LongString() string {
	return fmt.Sprintf("*%s", t.PointerTo.LongString())
}
func (t *PointerType) GetName() string {
	return "*" + t.PointerTo.GetName()
}
func (t *PointerType) GetLongName() string {
	return "(*" + t.PointerTo.GetLongName() + ")"
}
func (t *PointerType) GetBasicValue() string {
	return t.PointerTo.GetBasicValue()
}
func (t *PointerType) AddValue(value string) {
	t.PointerTo.AddValue(value)
}

// ---------------
// Pointer Methods
// ---------------
