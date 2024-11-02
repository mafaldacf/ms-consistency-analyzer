package gotypes

import "analyzer/pkg/logger"

type ArrayType struct {
	Type         `json:"-"`
	ElementsType Type
}

// ------------
// Type Methods
// ------------

func (t *ArrayType) IsSameType(other Type) bool {
	_, ok := other.(*ArrayType)
	return ok
}
func (t *ArrayType) String() string {
	if t.ElementsType == nil {
		logger.Logger.Fatal("[TYPES ARRAY] unexpected nil underlying type for Array Type")
	}
	return "[]" + t.ElementsType.String()
}
func (t *ArrayType) LongString() string {
	if t.ElementsType == nil {
		logger.Logger.Fatal("[TYPES ARRAY] unexpected nil underlying type for Array Type")
	}
	return "[]" + t.ElementsType.LongString()
}
func (t *ArrayType) GetName() string {
	return t.String()
}
func (t *ArrayType) GetLongName() string {
	return t.String()
}
func (t *ArrayType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for array type %s", t.String())
	return ""
}
func (t *ArrayType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for array type %s", t.String())
}
func (t *ArrayType) GetNestedFieldTypes(prefix string, noSQL bool) ([]Type, []string) {
	logger.Logger.Warnf("[TYPES ARRAY] attempted to get nested fields and variables: %s", t.String())
	return nil, nil
}


// -------------
// Array Methods
// -------------
