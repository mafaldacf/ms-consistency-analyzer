package gotypes

import "analyzer/pkg/logger"

type ArrayType struct {
	Type         `json:"-"`
	ElementsType Type
}

// ------------
// Type Methods
// ------------

func (t *ArrayType) String() string {
	return "[]" + t.ElementsType.String()
}
func (t *ArrayType) LongString() string {
	return "[]" + t.ElementsType.LongString()
}
func (t *ArrayType) GetName() string {
	return t.String()
}
func (t *ArrayType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for array type %s", t.String())
	return ""
}
func (t *ArrayType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for array type %s", t.String())
}

// -------------
// Array Methods
// -------------
