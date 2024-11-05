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

func CreateEntry(name string, t string, id int64, datastore *Datastore) *Entry {
	return &Entry{
		Name:      name,
		Type:      t,
		Id:        id,
		Datastore: datastore,
	}
}

func (s *Schema) GetRootField() Field {
	return s.Fields[1] //FIXME!
}

func (s *Schema) GetRootFieldName() string {
	return s.Fields[1].GetName() //FIXME!
}

func (s *Schema) AddOrGetField(name string, t string, id int64, datastore *Datastore) Field {
	for _, field := range s.Fields {
		if field.GetName() == name && field.GetDatastoreName() == datastore.GetName() { // last condition of datastore is just for sanity check
			return field
		}
	}

	e := CreateEntry(name, t, id, datastore)
	s.Fields = append(s.Fields, e)
	return e
}

func (s *Schema) AddOrGetUnfoldedField(name string, t string, id int64, datastore *Datastore) Field {
	for _, field := range s.UnfoldedFields {
		if field.GetName() == name && field.GetDatastoreName() == datastore.GetName() { // last condition of datastore is just for sanity check
			return field
		}
	}

	e := CreateEntry(name, t, id, datastore)
	s.UnfoldedFields = append(s.UnfoldedFields, e)
	return e
}

func (s *Schema) AddForeignReferenceToField(current Field, reference Field) {
	if !slices.Contains(current.(*Entry).References, reference) {
		current.(*Entry).References = append(current.(*Entry).References, reference)
	}
}

func (s *Schema) String() string {
	str := "FIELDS = {\n"
	for _, f := range s.Fields {
		str += f.String() + ", "
	}
	str = "\n} \nUNFOLDED FIELDS = {\n"
	for _, f := range s.UnfoldedFields {
		str += f.String() + ", "
	}
	return str + "\n}"
}

func (s *Schema) GetRootUnfoldedField() Field {
	return s.UnfoldedFields[0]
}

func (s *Schema) GetField(name string) Field {
	for _, f := range s.Fields {
		if f.GetName() == name || strings.EqualFold(f.GetName(), name) { // FIXME NOSQL MONGODB
			return f
		}
	}
	for _, f := range s.UnfoldedFields {
		if f.GetName() == name || strings.EqualFold(f.GetName(), name) { // FIXME NOSQL MONGODB
			return f
		}
	}
	for _, f := range s.ForeignKeys {
		if f.GetName() == name || strings.EqualFold(f.GetName(), name) { // FIXME NOSQL MONGODB
			return f
		}
	}
	logger.Logger.Fatalf("[FIXME] no field for name %s in datastore schema %v", name, s.String())
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
	GetDatastoreName() string
	GetDatastore() *Datastore
}
type Key struct {
	Field
	Name      string
	Type      string
	Datastore *Datastore
	Id        int64
}
type Entry struct {
	Field
	Name       string
	Type       string
	Datastore  *Datastore
	References []Field
	Id         int64
}
type ForeignEntry struct {
	Field
	Name      string
	Type      string
	Reference Field
	Datastore *Datastore
	Id        int64
}

// Key
func (f *Key) GetName() string {
	return f.Name
}
func (f *Key) GetDatastoreName() string {
	return f.Datastore.GetName()
}
func (f *Key) GetDatastore() *Datastore {
	return f.Datastore
}
func (f *Key) GetFullName() string {
	return strings.ToUpper(f.Datastore.GetName()) + "." + f.Name
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
func (f *Entry) GetDatastoreName() string {
	return f.Datastore.GetName()
}
func (f *Entry) GetDatastore() *Datastore {
	return f.Datastore
}
func (f *Entry) GetFullName() string {
	return strings.ToUpper(f.Datastore.GetName()) + "." + f.Name
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
func (f *ForeignEntry) GetDatastoreName() string {
	return f.Datastore.GetName()
}
func (f *ForeignEntry) GetDatastore() *Datastore {
	return f.Datastore
}
func (f *ForeignEntry) GetFullName() string {
	return strings.ToUpper(f.Datastore.GetName()) + "." + f.Name
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
	return f.Datastore.GetName() + "." + f.GetName()
}
