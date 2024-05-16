package types

type Method interface {
	String() string
	GetParams() []*FunctionParameter
	GetReturns() []*FunctionParameter
	IsQueueWrite() bool
	IsQueueRead() bool
}

type DatabaseInstance interface {
	String() string
	IsQueue() bool
	GetTypeName() string
	GetName() string
	Equals() bool
}
