package frameworks

import "analyzer/pkg/types"


type BlueprintDatabaseInstance struct {
	types.DatabaseInstance
}

type QueueInstance struct {
	BlueprintDatabaseInstance
	Name string
}

func (q *QueueInstance) String() string {
	return q.Name
}

func (q *QueueInstance) IsQueue() bool {
	return true
}

type CacheInstance struct {
	BlueprintDatabaseInstance
	Name string
}

func (c *CacheInstance) String() string {
	return c.Name
}

func (c *CacheInstance) IsQueue() bool {
	return false
}
