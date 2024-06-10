package datastores

type Schema struct {
	Fields []Field `json:"fields"`
}

func (s *Schema) String() string {
	str := "{ "
	for i, f := range s.Fields {
		str += f.String()
		if i < len(s.Fields) - 1 {
			str += ", "
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
func (s *Schema) AddForeignKey(name string, t string, reference Field) {
	s.Fields = append(s.Fields, &ForeignKey{
		Name:	 	name,
		Type: t,
		Reference: 	reference,
	})
}
func (s *Schema) AddValue(name string, t string) {
	s.Fields = append(s.Fields, &Value{
		Name: name,
		Type: t,
	})
}

type Field interface {
	String() string
	GetName() string
}
type Key struct {
	Field      		`json:"-"`
	Name string 	`json:"name"`
	Type string     `json:"type"`
}
type Value struct {
	Field      		`json:"-"`
	Name string 	`json:"name"`
	Type string     `json:"type"`
}
type ForeignKey struct {
	Field 				`json:"-"`
	Name 		string  `json:"name"`
	Type 		string   `json:"type"`
	Reference 	Field   `json:"reference"`
}

// Key
func (f *Key) GetName() string { 
	return f.Name 
}
func (f *Key) String() string { 
	return f.Name + " " + f.Type
}
// Value
func (f *Value) GetName() string { 
	return f.Name 
}
func (f *Value) String() string { 
	return f.Name +  " " + f.Type
}
// Foreign Key
func (f *ForeignKey) GetName() string { 
	return f.Name 
}
func (f *ForeignKey) String() string { 
	return f.Name +  " " + f.Type
}
