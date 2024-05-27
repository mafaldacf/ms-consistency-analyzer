package types

type Method interface {
	String() string
	GetParams() []*FunctionParameter
	GetReturns() []*FunctionParameter
	IsQueueWrite() bool
	IsQueueRead() bool
}
