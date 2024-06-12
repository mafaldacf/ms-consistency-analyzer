package datastores

import (
	"encoding/json"
)

type DatastoreType int
const (
	SQL DatastoreType = iota
    Cache
    NoSQL
	Queue
)

type DatastoreKind int
const (
	MySQL DatastoreKind = iota
    Redis
    MongoDB
	RabbitMQ
)

type Datastore struct {
	Name 	string
	Type 	DatastoreType
	Kind 	DatastoreKind
	Schema  *Schema
}

func (ds *Datastore) GetTypeString() string {
	var typeToString = map[DatastoreType]string{
		SQL: 	"SQL",
		Cache:	"Cache",
		NoSQL: 	"NoSQL",
		Queue: 	"Queue",
	}
	return typeToString[ds.Type]
}

func (ds *Datastore) GetKindString() string {
	var kindToString = map[DatastoreKind]string{
		MySQL: 		"MySQL",
		Redis:		"Redis",
		MongoDB: 	"MongoDB",
		RabbitMQ: 	"RabbitMQ",
	}
	return kindToString[ds.Kind]
}

func (ds *Datastore) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name	string  `json:"name"`
		Type 	string  `json:"type"`
		Kind 	string  `json:"kind"`
		Schema 	*Schema `json:"-"`
	}{
		Name:  	ds.Name,
		Type:  	ds.GetTypeString(),
		Kind:  	ds.GetKindString(),
		Schema: ds.Schema,
	})
}
