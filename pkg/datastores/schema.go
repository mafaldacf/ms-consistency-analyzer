package datastores

type Schema struct {
	Fields []Field `json:"fields"`
}

func (s *Schema) AddKey(name string) {
	s.Fields = append(s.Fields, &Key{
		Name: name,
	})
}

func (s *Schema) AddForeignKey(name string, reference Field) {
	s.Fields = append(s.Fields, &ForeignKey{
		Name:	 	name,
		Reference: 	reference,
	})
}

type Field interface {
	GetName() string
}
type Key struct {
	Field      		`json:"-"`
	Name string 	`json:"name"`
}
type ForeignKey struct {
	Field 				`json:"-"`
	Name 		string  `json:"name"`
	Reference 	Field   `json:"reference"`
}

// Primary Key
func (f *Key) GetName() string { 
	return f.Name 
}
// Foreign Key
func (f *ForeignKey) GetName() string { 
	return f.Name 
}
