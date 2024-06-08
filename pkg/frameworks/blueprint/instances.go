package frameworks

import (
	"analyzer/pkg/datastores"
	"encoding/json"
)

type BlueprintDatabaseInstance struct {
	datastores.DatabaseInstance 	`json:"-"`
	Name      string 				`json:"name"`
	Datastore *datastores.Datastore `json:"datastore"`
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
	return q.Name + " " + q.GetTypeName()
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
		Name      string 			   	`json:"name"`
		Datastore *datastores.Datastore `json:"datastore"`
	}{
		Name:      q.GetName(),
		Datastore: q.GetDatastore(),
	})
}

type CacheInstance struct {
	BlueprintDatabaseInstance
}

func (c *CacheInstance) GetName() string {
	return c.Name
}

func (c *CacheInstance) String() string {
	return c.Name + " " + c.GetTypeName()
}

func (c *CacheInstance) IsQueue() bool {
	return false
}

func (c *CacheInstance) GetTypeName() string {
	return "Cache"
}

// MarshalJSON is used by app.Save()
func (c *CacheInstance) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Name      string `json:"name"`
		Datastore *datastores.Datastore `json:"datastore"`
	}{
		Name:      c.GetName(),
		Datastore: c.GetDatastore(),
	})
}
