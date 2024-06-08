package datastores

type DatabaseInstance interface {
	String() string
	IsQueue() bool
	GetTypeName() string
	GetName() string
	Equals() bool
	GetDatastore() *Datastore
}
