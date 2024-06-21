package gotypes

import "fmt"

type PointerType struct {
	Type      `json:"-"`
	PointerTo Type
}

// ------------
// Type Methods
// ------------

func (t *PointerType) String() string {
	return fmt.Sprintf("*%s", t.PointerTo.String())
}
func (t *PointerType) LongString() string {
	return fmt.Sprintf("*%s", t.PointerTo.LongString())
}
func (t *PointerType) GetName() string {
	return t.String()
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
