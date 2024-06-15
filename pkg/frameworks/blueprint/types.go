package frameworks

import (
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"go/types"
)

func IsBlueprintBackendComponent(name string) bool {
	return IsBlueprintBackend(name) || IsBlueprintNoSQLComponent(name)
}

func IsBlueprintBackend(name string) bool {
	switch name {
	case "Queue", "Cache", "NoSQLDatabase":
		return true
	}
	return false
}

func IsBlueprintNoSQLComponent(name string) bool {
	switch name {
	case "NoSQLCollection", "NoSQLCursor":
		return true
	}
	return false
}

type BlueprintNoSQLComponent struct {
	Database 	string
	Collection 	string
}

type BlueprintBackendType struct {
	types.Type     `json:"-"`
	Name           string
	Package        string
	Methods        []*BlueprintBackend

	DbInstance datastores.DatabaseInstance
	NoSQLComponent *BlueprintNoSQLComponent
}

func (t *BlueprintBackendType) String() string {
	return t.Name
}
func (t *BlueprintBackendType) FullString() string {
	s := t.Name + " interface { "
	for i, m := range t.Methods {
		s += m.String()
		if i < len(t.Methods)-1 {
			s += ", "
		}
	}
	return s + " }"
}

func (t *BlueprintBackendType) GetName() string {
	return t.Name
}

func (t *BlueprintBackendType) GetPackage() string {
	return t.Package
}

func (t *BlueprintBackendType) GetBasicValue() string {
	logger.Logger.Fatalf("unable to get value for blueprint backend type type %s", t.String())
	return ""
}

func (t *BlueprintBackendType) IsNoSQLComponent() bool {
	return t.NoSQLComponent != nil
}

func (t *BlueprintBackendType) IsQueue() bool {
	return t.Name == "Queue"
}

func (t *BlueprintBackendType) IsNoSQLDatabase() bool {
	return t.Name == "NoSQLDatabase"
}

func (t *BlueprintBackendType) GetMethods() []*BlueprintBackend {
	return t.Methods
}

func (t *BlueprintBackendType) GetMethod(name string) *BlueprintBackend {
	for _, m := range t.Methods {
		if m.Name == name {
			return m
		}
	}
	logger.Logger.Fatalf("could not find method %s for backend type %s", name, t.String())
	return nil
}
