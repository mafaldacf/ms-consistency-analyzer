package abstractgraph

import (
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
)

type AbstractGraph struct {
	AppName  string
	Nodes    []AbstractNode
	Services map[string]*service.ServiceNode
	GIndex   int64
}

func (graph *AbstractGraph) getAndIncGIndex() int64 {
	prev := graph.GIndex
	graph.GIndex++
	return prev
}

type AbstractNode interface {
	GetParams() []types.Variable
	GetParam(int) types.Variable
	String() string
	GetName() string
	GetChildren() []AbstractNode
	AddChild(AbstractNode)
	SetVisited(bool)
	IsVisited() bool
	GetCallerStr() string
	GetCallee() string
}

type AbstractServiceCall struct {
	AbstractNode `json:"-"` // omit from json
	Visited      bool       `json:"-"` // omit from json
	Method       string     `json:"method"`

	Caller string `json:"caller"`
	Callee string `json:"-"`

	Params     []types.Variable               `json:"-"`
	ParsedCall *service.ServiceParsedCallExpr `json:"-"` // omit from json

	// nodes representing database calls cannot contain children as well
	Children []AbstractNode `json:"edges"`
}

func (call *AbstractServiceCall) GetParams() []types.Variable {
	return call.Params
}

func (call *AbstractServiceCall) GetParam(index int) types.Variable {
	return call.Params[index]
}

func (call *AbstractServiceCall) GetName() string {
	return call.ParsedCall.Name
}

func (call *AbstractServiceCall) GetCallee() string {
	return call.Callee
}

func (call *AbstractServiceCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractServiceCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractServiceCall) AddChild(child AbstractNode) {
	logger.Logger.Debugf("adding child %s (%s) > %s (%s)", call.GetName(), utils.GetType(call), child.GetName(), utils.GetType(child))
	call.Children = append(call.Children, child)
}

func (call *AbstractServiceCall) SetVisited(v bool) {
	call.Visited = v
}

func (call *AbstractServiceCall) IsVisited() bool {
	return call.Visited
}

func (call *AbstractServiceCall) GetCallerStr() string {
	return call.Caller
}

type AbstractTempInternalCall struct {
	AbstractNode `json:"-"`
	Visited      bool                                `json:"-"`
	Method       string                              `json:"method"`
	Service      string                              `json:"service"`
	Params       []types.Variable                    `json:"params"`
	ParsedCall   *service.InternalTempParsedCallExpr `json:"-"`
	Children     []AbstractNode                      `json:"edges"`
}

func (call *AbstractTempInternalCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractTempInternalCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractTempInternalCall) GetParams() []types.Variable {
	return call.Params
}

func (call *AbstractTempInternalCall) GetParam(index int) types.Variable {
	return call.Params[index]
}

func (call *AbstractTempInternalCall) GetName() string {
	return call.ParsedCall.Name
}

func (call *AbstractTempInternalCall) IsVisited() bool {
	return call.Visited
}

func (call *AbstractTempInternalCall) SetVisited(v bool) {
	call.Visited = v
}

func (call *AbstractTempInternalCall) GetCallerStr() string {
	return call.Service
}

type AbstractDatabaseCall struct {
	AbstractNode `json:"-"`                      // omit from json
	Visited      bool                            `json:"-"` // omit from json
	Method       string                          `json:"method"`
	Service      string                          `json:"caller"`
	Params       []types.Variable                `json:"params"`
	ParsedCall   *service.DatabaseParsedCallExpr `json:"-"` // omit from json
	Children     []AbstractNode                  `json:"queue_handlers,omitempty"`
	DbInstance   datastores.DatabaseInstance     `json:"ds_instance"`
	Subscriber   bool                            `json:"subscriber,omitempty"`
}

type AbstractQueueHandler struct {
	AbstractServiceCall `json:"handler"`
	DbInstance          datastores.DatabaseInstance `json:"ds_instance"`
	Publisher           *AbstractDatabaseCall       `json:"-"`
	Receiver            bool                        `json:"-"`
}

func (call *AbstractQueueHandler) HasQueueReceiver() bool {
	return call.Receiver
}

func (call *AbstractQueueHandler) EnableQueueReceiver() {
	call.Receiver = true
}

func (call *AbstractDatabaseCall) GetParams() []types.Variable {
	return call.Params
}

func (call *AbstractDatabaseCall) GetParam(index int) types.Variable {
	if index > 0 && index < len(call.Params) {
		return call.Params[index]
	}
	return nil
}

func (call *AbstractDatabaseCall) GetName() string {
	return call.ParsedCall.Name
}

func (call *AbstractDatabaseCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractDatabaseCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractDatabaseCall) AddChild(child AbstractNode) {
	logger.Logger.Debugf("adding child %s (%s) > %s (%s)", call.GetName(), utils.GetType(call), child.GetName(), utils.GetType(child))
	call.Children = append(call.Children, child)
}

func (call *AbstractDatabaseCall) SetVisited(v bool) {
	call.Visited = v
}

func (call *AbstractDatabaseCall) IsVisited() bool {
	return call.Visited
}

func (call *AbstractDatabaseCall) GetCallerStr() string {
	return call.Service
}
