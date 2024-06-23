package gotypes

import "analyzer/pkg/logger"

type TupleType struct {
	Type  `json:"-"`
	Types []Type
}

// ------------
// Type Methods
// ------------

func (t *TupleType) IsSameType(other Type) bool {
	_, ok := other.(*TupleType)
	return ok
}
func (t *TupleType) String() string {
	s := "("
	for i, elem := range t.Types {
		s += elem.String()
		if i < len(t.Types)-1 {
			s += ", "
		}
	}
	return s + ")"
}
func (t *TupleType) LongString() string {
	return t.String()
}
func (t *TupleType) GetName() string {
	return ""
}
func (t *TupleType) GetTypes() []Type {
	return t.Types
}
func (t *TupleType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for tuple type %s", t.String())
	return ""
}
func (t *TupleType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for tuple type %s", t.String())
}

// -------------
// Tuple Methods
// -------------
