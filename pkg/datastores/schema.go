package datastores

import (
	"slices"
	"strings"

	"analyzer/pkg/logger"
)

type Schema struct {
	Fields         []Field         `json:"fields"`
	UnfoldedFields []Field         `json:"unfolded_fields"`
	ForeignKeys    []*ForeignEntry `json:"foreign_keys"`
}

func (s *Schema) AddField(name string, t string, id int64, datastore string) Field {
	e := &Entry{
		Name:      name,
		Type:      t,
		Id:        id,
		Datastore: datastore,
	}
	s.Fields = append(s.Fields, e)
	return e
}
func (s *Schema) AddUnfoldedFieldWithId(name string, t string, id int64, datastore string) Field {
	e := &Entry{
		Name:      name,
		Type:      t,
		Id:        id,
		Datastore: datastore,
	}
	s.UnfoldedFields = append(s.UnfoldedFields, e)
	return e
}
func (s *Schema) AddUnfoldedField(name string, t string, datastore string) {
	s.UnfoldedFields = append(s.UnfoldedFields, &Entry{
		Datastore: datastore,
		Name:      name,
		Type:      t,
	})
}
func (s *Schema) AddForeignReferenceToField(current Field, reference Field) {
	if !slices.Contains(current.(*Entry).References, reference) {
		current.(*Entry).References = append(current.(*Entry).References, reference)
	}
}

func (s *Schema) String() string {
	str := "{ "
	for i, f := range s.Fields {
		str += f.String()
		if i < len(s.Fields)-1 {
			str += " | "
		}
	}
	for i, f := range s.UnfoldedFields {
		str += f.String()
		if i < len(s.Fields)-1 {
			str += " | "
		}
	}
	return str + " }"
}

func (s *Schema) AddKey(name string, t string, id int64) Field {
	k := &Key{
		Name: name,
		Type: t,
		Id:   id,
	}
	s.Fields = append(s.Fields, k)
	return k
}
func (s *Schema) AddFKReference(name string, t string, reference Field, datastore string) {
	for _, fk := range s.ForeignKeys {
		if fk.Name == name && fk.Datastore == datastore && fk.Reference.GetName() == reference.GetName() {
			logger.Logger.Debugf("found existing foreign key for name %s, type %s and datastore %s with reference %s", name, t, datastore, reference.String())
			return
		}
	}

	entry := &ForeignEntry{
		Name:      name,
		Type:      t,
		Reference: reference,
		Datastore: datastore,
	}
	s.ForeignKeys = append(s.ForeignKeys, entry)
	logger.Logger.Infof("added foreign reference (%s, %s)", name, entry.GetReferenceName())
}
func (s *Schema) AddEntry(name string, t string, id int64, datastore string) Field {
	e := &Entry{
		Name:      name,
		Type:      t,
		Id:        id,
		Datastore: datastore,
	}
	s.Fields = append(s.Fields, e)
	return e
}
func (s *Schema) GetField(name string) Field {
	for _, f := range s.Fields {
		if f.GetName() == name {
			return f
		}
	}
	for _, f := range s.UnfoldedFields {
		if f.GetName() == name {
			return f
		}
	}
	for _, f := range s.ForeignKeys {
		if f.GetName() == name {
			return f
		}
	}
	logger.Logger.Debugf("[FIXME] no field for name %s in datastore schema %v", name, s.String())
	return nil
}

func (s *Schema) GetFieldById(id int64) Field {
	for _, f := range s.Fields {
		if f.HasId(id) {
			return f
		}
	}
	for _, f := range s.UnfoldedFields {
		if f.HasId(id) {
			return f
		}
	}
	for _, f := range s.ForeignKeys {
		if f.HasId(id) {
			return f
		}
	}
	logger.Logger.Warnf("[FIXME] no field for id %d in datastore schema %v", id, s.String())
	return nil
}

type Field interface {
	String() string
	GetName() string
	GetFullName() string
	HasId(id int64) bool
	GetType() string
	AddReference(Field)
}
type Key struct {
	Field     `json:"-"`
	Name      string `json:"name"`
	Type      string `json:"type"`
	Datastore string `json:"datastore"`
	Id        int64
}
type Entry struct {
	Field      `json:"-"`
	Name       string  `json:"name"`
	Type       string  `json:"type"`
	Datastore  string  `json:"datastore"`
	References []Field `json:"references"`
	Id         int64
}
type ForeignEntry struct {
	Field     `json:"-"`
	Name      string `json:"name"`
	Type      string `json:"type"`
	Reference Field  `json:"reference"`
	Datastore string `json:"datastore"`
	Id        int64
}

// Key
func (f *Key) GetName() string {
	return f.Name
}
func (f *Key) GetFullName() string {
	return strings.ToUpper(f.Datastore) + "." + f.Name
}
func (f *Key) GetType() string {
	return f.Type
}
func (f *Key) String() string {
	return f.Name + " " + f.Type
}
func (f *Key) HasId(id int64) bool {
	return f.Id == id
}

// Entry
func (f *Entry) GetName() string {
	return f.Name
}
func (f *Entry) GetFullName() string {
	return strings.ToUpper(f.Datastore) + "." + f.Name
}
func (f *Entry) GetType() string {
	return f.Type
}
func (f *Entry) String() string {
	return f.Name + " " + f.Type
}
func (f *Entry) HasId(id int64) bool {
	return f.Id == id
}

// Foreign Key
func (f *ForeignEntry) GetName() string {
	return f.Name
}
func (f *ForeignEntry) GetFullName() string {
	return strings.ToUpper(f.Datastore) + "." + f.Name
}
func (f *ForeignEntry) GetType() string {
	return f.Type
}
func (f *ForeignEntry) String() string {
	return f.Name + " " + f.Type
}
func (f *ForeignEntry) HasId(id int64) bool {
	return f.Id == id
}
func (f *ForeignEntry) GetReferenceName() string {
	return f.Datastore + "." + f.GetName()
}
