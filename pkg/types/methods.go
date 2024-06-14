package types

type Method interface {
	String() string
	GetParams() []*FunctionField
	GetReturns() []*FunctionField
	IsQueueWrite() bool
	IsQueueRead() bool
	IsWrite() bool
}
