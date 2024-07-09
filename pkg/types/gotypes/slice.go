package gotypes

import "analyzer/pkg/logger"

type SliceType struct {
	Type  `json:"-"`
	UnderlyingType Type
}

// ------------
// Type Methods
// ------------

func (t *SliceType) IsSameType(other Type) bool {
	_, ok := other.(*SliceType)
	return ok
}
func (t *SliceType) String() string {
	return "(" + t.UnderlyingType.String() + ")"
}
func (t *SliceType) LongString() string {
	return t.String()
}
func (t *SliceType) GetName() string {
	return ""
}
func (t *SliceType) GetUnderlyingType() Type {
	return t.UnderlyingType
}
func (t *SliceType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for tuple type %s", t.String())
	return ""
}
func (t *SliceType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for tuple type %s", t.String())
}

// -------------
// Tuple Methods
// -------------
