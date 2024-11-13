package datastores

import "fmt"

type Type int

const (
	SQL Type = iota
	Cache
	NoSQL
	Queue
)

type Kind int

const (
	MySQL Kind = iota
	Redis
	Memcached
	MongoDB
	RabbitMQ
)

type Datastore struct {
	Name string
	Type Type
	Kind Kind
}

func (ds *Datastore) MarshalYAML() (interface{}, error) {
	return &struct {
		Name string `yaml:"name"`
		Type string `yaml:"type"`
		Kind string `yaml:"kind"`
	}{
		Name: ds.Name,
		Type: ds.TypeToString(),
		Kind: ds.KindToString(),
	}, nil
}

func (ds *Datastore) String() string {
	return fmt.Sprintf("%s %s (%s)", ds.Name, ds.KindToString(), ds.TypeToString())
}

func (ds *Datastore) TypeToString() string {
	var typeToString = map[Type]string{
		SQL:   "SQL",
		Cache: "Cache",
		NoSQL: "NoSQL",
		Queue: "Queue",
	}
	return typeToString[ds.Type]
}

func (ds *Datastore) KindToString() string {
	var kindToString = map[Kind]string{
		MySQL:    "MySQL",
		Redis:    "Redis",
		MongoDB:  "MongoDB",
		RabbitMQ: "RabbitMQ",
	}
	return kindToString[ds.Kind]
}

func (ds *Datastore) GetName() string {
	return ds.Name
}

func (ds *Datastore) IsTypeSQL() bool {
	return ds.Type == SQL
}
func (ds *Datastore) IsTypeCache() bool {
	return ds.Type == Cache
}
func (ds *Datastore) IsTypeNoSQL() bool {
	return ds.Type == NoSQL
}
func (ds *Datastore) IsTypeQueue() bool {
	return ds.Type == Queue
}

func (ds *Datastore) IsKindMySQL() bool {
	return ds.Kind == MySQL
}
func (ds *Datastore) IsKindRedis() bool {
	return ds.Kind == Redis
}
func (ds *Datastore) IsKindMemcached() bool {
	return ds.Kind == Memcached
}
func (ds *Datastore) IsKindMongoDB() bool {
	return ds.Kind == MongoDB
}
func (ds *Datastore) IsKindRabbitMQ() bool {
	return ds.Kind == RabbitMQ
}
