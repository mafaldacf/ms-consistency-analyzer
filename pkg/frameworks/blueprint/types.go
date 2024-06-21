package blueprint

import (
	"fmt"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
)

func IsBackendComponent(name string) bool {
	return IsBackend(name) || IsNoSQLComponent(name)
}

func IsBackend(name string) bool {
	switch name {
	case "Queue", "Cache", "NoSQLDatabase":
		return true
	}
	return false
}

func IsNoSQLComponent(name string) bool {
	switch name {
	case "NoSQLCollection", "NoSQLCursor":
		return true
	}
	return false
}

type NoSQLComponentType int

const (
	NoSQLCollection NoSQLComponentType = iota
	NoSQLCursor
)

type NoSQLComponent struct {
	Type       NoSQLComponentType
	Database   string
	Collection string
}

func (t *NoSQLComponent) String() string {
	prefix := ""
	if t.Type == NoSQLCollection {
		prefix = "NoSQLCollection"
	} else if t.Type == NoSQLCursor {
		prefix = "NoSQLCursor"
	}
	return fmt.Sprintf("%s {database: %s, collection: %s}", prefix, t.Database, t.Collection)
}

type BackendType struct {
	gotypes.Type   `json:"-"`
	Name           string
	Package        string
	Methods        []*BackendMethod
	DbInstance     datastores.DatabaseInstance
	NoSQLComponent *NoSQLComponent
}

func (t *BackendType) String() string {
	if t.NoSQLComponent != nil {
		return t.NoSQLComponent.String()
	}
	return t.Name
}
func (t *BackendType) LongString() string {
	if len(t.Methods) == 0 {
		return t.Name + " interface{}"
	}
	s := t.Name + " interface{ "
	for i, m := range t.Methods {
		s += m.String()
		if i < len(t.Methods)-1 {
			s += ", "
		}
	}
	return s + "}"
}

func (t *BackendType) GetName() string {
	return t.Name
}

func (t *BackendType) GetPackage() string {
	return t.Package
}

func (t *BackendType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for blueprint backend type type %s", t.String())
	return ""
}

func (t *BackendType) AddValue(value string) {
	logger.Logger.Fatalf("unable to add value for blueprint backend type type %s", t.String())
}

func (t *BackendType) IsNoSQLComponent() bool {
	return t.NoSQLComponent != nil
}

func (t *BackendType) IsNoSQLCollection() bool {
	return t.NoSQLComponent.Type == NoSQLCollection
}

func (t *BackendType) IsNoSQLCursor() bool {
	return t.NoSQLComponent.Type == NoSQLCursor
}

func (t *BackendType) IsQueue() bool {
	return t.Name == "Queue"
}

func (t *BackendType) IsNoSQLDatabase() bool {
	return t.Name == "NoSQLDatabase"
}

func (t *BackendType) GetMethods() []*BackendMethod {
	return t.Methods
}

func (t *BackendType) GetNestedFieldTypes(prefix string) ([]gotypes.Type, []string) {
	logger.Logger.Fatalf("unable to get nested types blueprint backend type type %s", t.String())
	return nil, nil
}

func (t *BackendType) GetMethod(name string) *BackendMethod {
	for _, m := range t.Methods {
		if m.Name == name {
			return m
		}
	}
	logger.Logger.Fatalf("could not find method %s for backend type %s", name, t.String())
	return nil
}
