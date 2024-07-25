package gotypes

import (
	"fmt"

	"analyzer/pkg/logger"
)

type MapType struct {
	Type      `json:"-"`
	KeyType   Type
	ValueType Type
}

// ------------
// Type Methods
// ------------

func (t *MapType) IsSameType(other Type) bool {
	_, ok := other.(*MapType)
	return ok
}
func (t *MapType) String() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.String(), t.ValueType.String())
}
func (t *MapType) LongString() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.LongString(), t.ValueType.LongString())
}
func (t *MapType) GetName() string {
	return t.String()
}
func (t *MapType) GetLongName() string {
	return t.String()
}
func (t *MapType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for map type %s", t.String())
	return ""
}
func (t *MapType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for map type %s", t.String())
}

// -----------
// Map Methods
// -----------

func (t *MapType) GetKeyType() Type {
	return t.KeyType
}

func (t *MapType) GetValueType() Type {
	return t.ValueType
}
