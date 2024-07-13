package blueprint

import (
	"encoding/json"

	"analyzer/pkg/datastores"
)

type BlueprintDatabaseInstance struct {
	datastores.DatabaseInstance `json:"-"`
	Name                        string                `json:"name"`
	Datastore                   *datastores.Datastore `json:"datastore"`
}

func (i *BlueprintDatabaseInstance) GetDatastore() *datastores.Datastore {
	return i.Datastore
}

type QueueInstance struct {
	BlueprintDatabaseInstance
}

func (q *QueueInstance) GetName() string {
	return q.Name
}

func (q *QueueInstance) String() string {
	return q.Name + " " + q.Datastore.GetKindString()
}

func (q *QueueInstance) IsQueue() bool {
	return true
}

func (q *QueueInstance) GetTypeName() string {
	return "Queue"
}

// MarshalJSON is used by app.Save()
func (q *QueueInstance) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string                `json:"name"`
		Datastore *datastores.Datastore `json:"datastore"`
	}{
		Name:      q.GetName(),
		Datastore: q.GetDatastore(),
	})
}

type CacheInstance struct {
	BlueprintDatabaseInstance
}

func (nosql *CacheInstance) GetName() string {
	return nosql.Name
}

func (nosql *CacheInstance) String() string {
	return nosql.Name + " " + nosql.Datastore.GetKindString()
}

func (nosql *CacheInstance) IsQueue() bool {
	return false
}

func (nosql *CacheInstance) GetTypeName() string {
	return "Cache"
}

// MarshalJSON is used by app.Save()
func (nosql *CacheInstance) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string                `json:"name"`
		Datastore *datastores.Datastore `json:"datastore"`
	}{
		Name:      nosql.GetName(),
		Datastore: nosql.GetDatastore(),
	})
}

type NoSQLInstance struct {
	BlueprintDatabaseInstance
}

func (nosql *NoSQLInstance) GetName() string {
	return nosql.Name
}

func (nosql *NoSQLInstance) String() string {
	return nosql.Name + " " + nosql.Datastore.GetKindString()
}

func (nosql *NoSQLInstance) IsQueue() bool {
	return false
}

func (nosql *NoSQLInstance) GetTypeName() string {
	return "NoSQLDatabase"
}

// MarshalJSON is used by app.Save()
func (nosql *NoSQLInstance) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string                `json:"name"`
		Datastore *datastores.Datastore `json:"datastore"`
	}{
		Name:      nosql.GetName(),
		Datastore: nosql.GetDatastore(),
	})
}
