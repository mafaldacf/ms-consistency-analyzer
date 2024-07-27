package abstractgraph

import (
	"encoding/json"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

type AbstractGraph struct {
	AppName  string
	Nodes    []AbstractNode
	Services map[string]*service.Service
	GIndex   int64
}

type AbstractNode interface {
	GetParams() []variables.Variable
	GetParam(int) variables.Variable
	GetReturns() []variables.Variable
	GetMethodStr() string
	String() string
	LongString() string
	GetName() string
	GetChildren() []AbstractNode
	AddChild(AbstractNode)
	SetVisited(bool)
	IsVisited() bool
	GetCallerStr() string
	GetCallee() string
	GetParsedCall() types.ParsedCall
	GetNodeType() string
	GetDepth() int
	GetNextDepth() int
	SetDepth(int)
}

type AbstractServiceCall struct {
	AbstractNode `json:"-"`
	Visited      bool
	Caller       string
	Callee       string
	// nodes representing database calls cannot contain children as well
	Children   []AbstractNode
	ParsedCall *types.ParsedServiceCall
	Depth      int
}

func (call *AbstractServiceCall) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Method   string               `json:"method"`
		Depth    int                  `json:"depth"`
		Caller   string               `json:"caller"`
		Children []AbstractNode       `json:"edges"`
		Params   []variables.Variable `json:"params"`
		Returns  []variables.Variable `json:"returns,omitempty"`
	}{
		Caller:   call.Caller,
		Depth:    call.Depth,
		Method:   call.ParsedCall.Method.String(),
		Children: call.Children,
		Params:   call.ParsedCall.Params,
		Returns:  call.ParsedCall.Returns,
	})
}

func (call *AbstractServiceCall) GetDepth() int {
	return call.Depth
}

func (call *AbstractServiceCall) GetNextDepth() int {
	return call.Depth + 1
}

func (call *AbstractServiceCall) GetParams() []variables.Variable {
	return call.ParsedCall.Params
}

func (call *AbstractServiceCall) GetReturns() []variables.Variable {
	return call.ParsedCall.Returns
}

func (call *AbstractServiceCall) GetParam(index int) variables.Variable {
	return call.ParsedCall.Params[index]
}

func (call *AbstractServiceCall) GetName() string {
	return call.ParsedCall.Name
}

func (call *AbstractServiceCall) GetCallee() string {
	return call.Callee
}

func (call *AbstractServiceCall) GetMethodStr() string {
	return call.ParsedCall.Method.String()
}

func (call *AbstractServiceCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractServiceCall) LongString() string {
	return call.ParsedCall.String()
}

func (call *AbstractServiceCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractServiceCall) AddChild(child AbstractNode) {
	logger.Logger.Tracef("[ABSTRACT CALL] adding child %s (%s) > %s (%s)", call.GetName(), utils.GetType(call), child.GetName(), utils.GetType(child))
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

func (call *AbstractServiceCall) GetParsedCall() types.ParsedCall {
	return call.ParsedCall.ParsedCall
}

func (call *AbstractServiceCall) GetNodeType() string {
	return "service"
}

type AbstractTempInternalCall struct {
	AbstractNode
	Visited    bool
	Service    string
	ParsedCall *types.ParsedInternalCall
	Children   []AbstractNode
	Depth      int
}

func (call *AbstractTempInternalCall) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Method   string               `json:"method"`
		Depth    int                  `json:"depth"`
		Service  string               `json:"service"`
		Params   []variables.Variable `json:"params"`
		Returns  []variables.Variable `json:"returns,omitempty"`
		Children []AbstractNode       `json:"edges"`
	}{
		Method:   call.ParsedCall.Method.String(),
		Depth:    call.Depth,
		Service:  call.Service,
		Params:   call.ParsedCall.Params,
		Returns:  call.ParsedCall.Returns,
		Children: call.Children,
	})
}

func (call *AbstractTempInternalCall) GetDepth() int {
	return call.Depth
}

func (call *AbstractTempInternalCall) GetNextDepth() int {
	return call.Depth + 1
}

func (call *AbstractTempInternalCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractTempInternalCall) GetMethodStr() string {
	return call.ParsedCall.Method.String()
}

func (call *AbstractTempInternalCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractTempInternalCall) LongString() string {
	return call.ParsedCall.String()
}

func (call *AbstractTempInternalCall) GetParams() []variables.Variable {
	return call.ParsedCall.Params
}

func (call *AbstractTempInternalCall) GetReturns() []variables.Variable {
	return call.ParsedCall.Returns
}

func (call *AbstractTempInternalCall) GetParam(index int) variables.Variable {
	return call.ParsedCall.Params[index]
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

func (call *AbstractTempInternalCall) GetParsedCall() types.ParsedCall {
	return call.ParsedCall.ParsedCall
}

func (call *AbstractTempInternalCall) GetNodeType() string {
	return "service"
}

func (call *AbstractTempInternalCall) GetCallee() string {
	return call.GetName()
}

type AbstractQueueHandler struct {
	AbstractServiceCall `json:"handler"`
	DbInstance          datastores.DatabaseInstance `json:"datastore"`
	Publisher           *AbstractDatabaseCall       `json:"-"`
	Enabled             bool                        `json:"-"`
}

func (call *AbstractQueueHandler) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		AbstractServiceCall `json:"handler"`
		DbInstance          string `json:"datastore"`
	}{
		AbstractServiceCall: call.AbstractServiceCall,
		DbInstance:          call.DbInstance.GetName(),
	})
}

func (call *AbstractQueueHandler) IsEnabled() bool {
	return call.Enabled
}

func (call *AbstractQueueHandler) Enable() {
	call.Enabled = true
}

type AbstractDatabaseCall struct {
	AbstractNode
	Visited    bool
	Service    string
	ParsedCall *types.ParsedDatabaseCall
	Children   []AbstractNode
	DbInstance datastores.DatabaseInstance
	Subscriber bool
	Depth      int
}

func (call *AbstractDatabaseCall) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Method     string               `json:"method"`
		Depth      int                  `json:"depth"`
		Service    string               `json:"caller"`
		Params     []variables.Variable `json:"params"`
		Returns    []variables.Variable `json:"returns,omitempty"`
		Children   []AbstractNode       `json:"queue_handlers,omitempty"`
		DbInstance string               `json:"datastore"`
		Subscriber bool                 `json:"subscriber,omitempty"`
	}{
		Method:     call.ParsedCall.Method.String(),
		Depth:      call.Depth,
		Service:    call.Service,
		Params:     call.ParsedCall.Params,
		Returns:    call.ParsedCall.Returns,
		Children:   call.Children,
		DbInstance: call.DbInstance.GetName(),
		Subscriber: call.Subscriber,
	})
}

func (call *AbstractDatabaseCall) GetDepth() int {
	return call.Depth
}

func (call *AbstractDatabaseCall) GetNextDepth() int {
	return call.Depth + 1
}

func (call *AbstractDatabaseCall) GetParams() []variables.Variable {
	return call.ParsedCall.Params
}

func (call *AbstractDatabaseCall) GetParam(index int) variables.Variable {
	if index > 0 && index < len(call.ParsedCall.Params) {
		logger.Logger.Tracef("got param with index %d for call %s", index, call.LongString())
		return call.ParsedCall.Params[index]
	}
	logger.Logger.Fatalf("cannot get param with index %d for call %s", index, call.LongString())
	return nil
}

func (call *AbstractDatabaseCall) GetReturns() []variables.Variable {
	return call.ParsedCall.Returns
}

func (call *AbstractDatabaseCall) GetReturn(index int) variables.Variable {
	if index >= 0 && index < len(call.ParsedCall.Returns) {
		logger.Logger.Tracef("got return with index %d for call %s", index, call.LongString())
		return call.ParsedCall.Returns[index]
	}
	logger.Logger.Fatalf("cannot get return with index %d for call %s", index, call.LongString())
	return nil
}

func (call *AbstractDatabaseCall) GetName() string {
	return call.ParsedCall.Name
}

func (call *AbstractDatabaseCall) GetMethodStr() string {
	return call.ParsedCall.Method.String()
}

func (call *AbstractDatabaseCall) String() string {
	return call.ParsedCall.SimpleString()
}

func (call *AbstractDatabaseCall) LongString() string {
	return call.ParsedCall.String()
}

func (call *AbstractDatabaseCall) GetChildren() []AbstractNode {
	return call.Children
}

func (call *AbstractDatabaseCall) AddChild(child AbstractNode) {
	logger.Logger.Tracef("[ABSTRACT CALL] adding child %s (%s) > %s (%s)", call.GetName(), utils.GetType(call), child.GetName(), utils.GetType(child))
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

func (call *AbstractDatabaseCall) GetParsedCall() types.ParsedCall {
	return call.ParsedCall.ParsedCall
}

func (call *AbstractDatabaseCall) GetCallee() string {
	return call.ParsedCall.DbInstance.String()
}

func (call *AbstractDatabaseCall) GetNodeType() string {
	return "datastore"
}
