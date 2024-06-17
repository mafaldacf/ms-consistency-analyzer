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

func (t *MapType) String() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.String(), t.ValueType.String())
}
func (t *MapType) FullString() string {
	return fmt.Sprintf("map[%s]%s", t.KeyType.FullString(), t.ValueType.FullString())
}
func (t *MapType) GetName() string {
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
