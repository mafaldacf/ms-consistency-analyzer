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

func (ds *Datastore) MarshalJSON() ([]byte, error) {
	var typeToString = map[DatastoreType]string{
		SQL: 	"SQL",
		Cache:	"Cache",
		NoSQL: 	"NoSQL",
		Queue: 	"Queue",
	}
	var kindToString = map[DatastoreKind]string{
		MySQL: 		"MySQL",
		Redis:		"Redis",
		MongoDB: 	"MongoDB",
		RabbitMQ: 	"RabbitMQ",
	}
	return json.Marshal(&struct {
		Name	string  `json:"name"`
		Type 	string  `json:"type"`
		Kind 	string  `json:"kind"`
		Schema 	*Schema `json:"schema"`
	}{
		Name:  	ds.Name,
		Type:  	typeToString[ds.Type],
		Kind:  	kindToString[ds.Kind],
		Schema: ds.Schema,
	})
}
