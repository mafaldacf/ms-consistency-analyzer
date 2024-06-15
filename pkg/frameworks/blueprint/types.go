package frameworks

import (
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

type BlueprintBackendType struct {
	types.Type     `json:"-"`
	Name           string
	Package        string
	Methods        []*BlueprintBackend
	NoSQLComponent bool
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

func (t *BlueprintBackendType) IsQueue() bool {
	return t.Name == "Queue"
}
