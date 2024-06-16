package datastores

import "analyzer/pkg/logger"

type Schema struct {
	Fields []Field `json:"fields"`
}

func (s *Schema) String() string {
	str := "{ "
	for i, f := range s.Fields {
		str += f.String()
		if i < len(s.Fields)-1 {
			str += " | "
		}
	}
	return str + " }"
}

func (s *Schema) AddKey(name string, t string) {
	s.Fields = append(s.Fields, &Key{
		Name: name,
		Type: t,
	})
}
func (s *Schema) AddForeignEntry(name string, t string, reference Field) {
	s.Fields = append(s.Fields, &ForeignEntry{
		Name:      name,
		Type:      t,
		Reference: reference,
	})
}
func (s *Schema) AddEntry(name string, t string) {
	s.Fields = append(s.Fields, &Entry{
		Name: name,
		Type: t,
	})
}
func (s *Schema) GetField(name string) Field {
	for _, f := range s.Fields {
		if f.GetName() == name {
			return f
		}
	}
	logger.Logger.Fatalf("no field for name %s in datastore schema %v", name, s)
	return nil
}

type Field interface {
	String() string
	GetName() string
	GetType() string
}
type Key struct {
	Field `json:"-"`
	Name  string `json:"name"`
	Type  string `json:"type"`
}
type Entry struct {
	Field `json:"-"`
	Name  string `json:"name"`
	Type  string `json:"type"`
}
type ForeignEntry struct {
	Field     `json:"-"`
	Name      string `json:"name"`
	Type      string `json:"type"`
	Reference Field  `json:"reference"`
}

// Key
func (f *Key) GetName() string {
	return f.Name
}
func (f *Key) GetType() string {
	return f.Type
}
func (f *Key) String() string {
	return f.Name + " " + f.Type
}

// Entry
func (f *Entry) GetName() string {
	return f.Name
}
func (f *Entry) GetType() string {
	return f.Type
}
func (f *Entry) String() string {
	return f.Name + " " + f.Type
}

// Foreign Key
func (f *ForeignEntry) GetName() string {
	return f.Name
}
func (f *ForeignEntry) GetType() string {
	return f.Type
}
func (f *ForeignEntry) String() string {
	return f.Name + " " + f.Type
}
