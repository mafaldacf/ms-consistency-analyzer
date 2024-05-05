package frameworks

import "analyzer/pkg/types"


type BlueprintDatabaseInstance struct {
	types.DatabaseInstance 	`json:"-"`
	Name string 			`json:"name"`
}
type QueueInstance struct {
	BlueprintDatabaseInstance
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
type CacheInstance struct {
	BlueprintDatabaseInstance
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
