package types

import "analyzer/pkg/types/objects"

type Call struct {
	origin *Method           `yaml:"origin"`
	target *Method           `yaml:"target"`
	args   []*objects.Object `yaml:"args"`
	rpc    bool              `yaml:"rpc"`
}

func NewCall(origin *Method, target *Method, rpc bool) *Call {
	return &Call{
		origin: origin,
		target: target,
		rpc:    rpc,
	}
}

func (call *Call) Origin() *Method {
	return call.origin
}

func (call *Call) Target() *Method {
	return call.target
}

func (call *Call) Args() []*objects.Object {
	return call.args
}

func (call *Call) IsRPC() bool {
	return call.rpc
}
