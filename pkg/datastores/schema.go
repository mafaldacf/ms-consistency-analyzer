package datastores

import (
	"fmt"
	"slices"
	"strings"

	"analyzer/pkg/logger"
)

const UNKNOWN_FIELD_TYPE = "<unknown type>"

const ROOT_FIELD_NAME_NOSQL = "_"
const ROOT_FIELD_NAME_QUEUE = "_"

const ROOT_FIELD_NAME_CACHE_KEY = "key"
const ROOT_FIELD_NAME_CACHE_VALUE = "value"

type Schema struct {
	Fields         []Field         `json:"fields"`
	UnfoldedFields []Field         `json:"unfolded_fields"`
	ForeignKeys    []*ForeignEntry `json:"foreign_keys"`
}

func NewEntry(name string, t string, id int64, datastore *Datastore) *Entry {
	return &Entry{
		Name:      name,
		Type:      t,
		Id:        id,
		Datastore: datastore,
	}
}

func (s *Schema) GetAllFields() []Field {
	var fields []Field
	for _, field := range s.Fields {
		if !slices.Contains(fields, field) {
			fields = append(fields, field)
		}
	}
	for _, unfoldedField := range s.UnfoldedFields {
		if !slices.Contains(fields, unfoldedField) {
			fields = append(fields, unfoldedField)
		}
	}
	return fields
}

func (s *Schema) GetRootFieldName() string {
	//logger.Logger.Infof("SCHEMA: %v", s.Fields)
	// FIXME: better to have an additional bool for the fields that state if they are root or no, but for now we have:
	// index 0 is for "_" root field (that can be created in reads if no fields exists) and index 1 is when there was a previous write
	if len(s.Fields) >= 2 {
		return s.Fields[1].GetName()
	}
	if len(s.Fields) == 1 {
		return s.Fields[0].GetName()
	}
	// should never happen because prior to this is only called for query objects and prior to this
	// the cursor must have already created a new root field if it did not exist yet
	logger.Logger.Fatalf("[SCHEMA] no fields for schema: %s", s.String())
	return ""
}

func (s *Schema) GetOrCreateField(name string, t string, id int64, datastore *Datastore) Field {
	for _, field := range s.Fields {
		if field.GetName() == name && field.GetDatastoreName() == datastore.GetName() { // last condition of datastore is just for sanity check
			// upgrade type if type is unknown
			if field.HasUnknownType() && t != UNKNOWN_FIELD_TYPE {
				field.SetType(t)
			}
			return field
		}
	}

	e := NewEntry(name, t, id, datastore)
	s.Fields = append(s.Fields, e)
	return e
}

func (s *Schema) GetOrCreateUnfoldedField(name string, t string, id int64, datastore *Datastore) Field {
	for _, field := range s.UnfoldedFields {
		if field.IsNamed(name) && field.GetDatastoreName() == datastore.GetName() { // last condition of datastore is just for sanity check
			// upgrade type if type is unknown
			if field.HasUnknownType() && t != UNKNOWN_FIELD_TYPE {
				field.SetType(t)
			}
			return field
		}
	}

	e := NewEntry(name, t, id, datastore)
	s.UnfoldedFields = append(s.UnfoldedFields, e)
	return e
}

func (s *Schema) GetOrCreateRootField(name string, t string, id int64, datastore *Datastore) Field {
	// FIXME: better to have an additional bool for the fields that state if they are root or no, but for now we have:
	// index 0 is for "_" root field (that can be created in reads if no fields exists) and index 1 is when there was a previous write
	if len(s.Fields) >= 2 {
		return s.Fields[1]
	}
	if len(s.Fields) == 1 {
		return s.Fields[0]
	}
	e := NewEntry(name, t, id, datastore)
	s.Fields = append(s.Fields, e)
	return e
}

func (s *Schema) AddForeignReferenceToField(current Field, reference Field) {
	if !slices.Contains(current.(*Entry).References, reference) {
		current.(*Entry).References = append(current.(*Entry).References, reference)
	}
}

func (s *Schema) String() string {
	fieldsStr := "fields = {"
	for i, f := range s.Fields {
		fieldsStr += fmt.Sprintf("[field #%d] %s", i, f.String())
		if i < len(s.Fields) - 1 {
			fieldsStr += ", "
		}
	}
	fieldsStr += "}"

	unfoldedFieldsStr := "unfolded fields = {"
	for i, f := range s.UnfoldedFields {
		unfoldedFieldsStr += fmt.Sprintf("[unfolded field #%d] %s", i, f.String())
		if i < len(s.Fields) - 1 {
			unfoldedFieldsStr += ", "
		}
	}
	unfoldedFieldsStr += "}"

	return fieldsStr + ", " + unfoldedFieldsStr
}

func (s *Schema) GetRootUnfoldedField() Field {
	if len(s.UnfoldedFields) > 1 {
		return s.UnfoldedFields[0]
	}
	logger.Logger.Fatalf("[SCHEMA] no root unfolded field for schema: %s", s.String())
	return nil
}

func (s *Schema) GetField(name string) Field {
	for _, f := range s.Fields {
		if f.IsNamed(name) {
			return f
		}
	}
	for _, f := range s.UnfoldedFields {
		if f.IsNamed(name) {
			return f
		}
	}
	for _, f := range s.ForeignKeys {
		if f.IsNamed(name) {
			return f
		}
	}
	logger.Logger.Fatalf("[FIXME] no field for name %s in datastore schema %s", name, s.String())
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
	HasUnknownType() bool
	SetType(t string)
	AddReference(Field)
	GetDatastoreName() string
	GetDatastore() *Datastore
	IsNamed(other string) bool
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
func (f *Entry) IsNamed(other string) bool {
	return strings.EqualFold(f.GetName(), other) // FIXME NOSQL MONGODB
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
func (f *Entry) HasUnknownType() bool {
	return f.Type == UNKNOWN_FIELD_TYPE
}
func (f *Entry) SetType(t string) {
	f.Type = t
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
