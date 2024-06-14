package frameworks

import (
	"analyzer/pkg/types"
	"fmt"
)

func IsBlueprintPackage(name string) bool {
	return name == "github.com/blueprint-uservices/blueprint/runtime/core/backend"
}

func IsBlueprintBackend(name string) bool {
	switch name {
	case "Queue", "NoSQLDatabase", "Cache":
		return true
	}
	return false
}

func IsBlueprintBackendQueue(name string) bool {
	return name == "Queue"
}

type BlueprintBackend struct {
	types.Method
	Name   string
	Params []*types.FunctionParameter
	Write  bool
}

func (b *BlueprintBackend) String() string {
	repr := fmt.Sprintf("%s(", b.Name)
	for i, param := range b.Params {
		repr += param.String()
		if i < len(b.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	return repr
}

func (b *BlueprintBackend) GetParams() []*types.FunctionParameter {
	return b.Params
}

func (b *BlueprintBackend) IsWrite() bool {
	return b.Write
}

func (b *BlueprintBackend) IsQueueRead() bool {
	return !b.Write && b.Name == "Queue.Pop"
}

func (b *BlueprintBackend) IsQueueWrite() bool {
	return b.Write && b.Name == "Queue.Push"
}

func (b *BlueprintBackend) MatchQueueIdentifiers() map[int]int {
	var matches map[int]int
	if b.Name == "Queue.Push" {
		matches = make(map[int]int, 0)
		// we have Queue.Push(ctx, src) and Queue.Pop(ctx, dst)
		// so the (src @ index 1) matches (dst @ index 1)
		matches[1] = 1
	}
	return matches
}

func (b *BlueprintBackend) GetWrittenObjectIndex() int {
	switch b.Name {
	case "Cache.Put":
		return 2
	case "Queue.Push":
		return 1
	}
	return -1
}

func (b *BlueprintBackend) GetReadObjectIndex() int {
	switch b.Name {
	case "Cache.Get":
		return 2
	case "Queue.Pop":
		return 1
	}
	return -1
}

func (b *BlueprintBackend) GetWrittenKeyIndex() int {
	switch b.Name {
	case "Cache.Put":
		return 1
	case "Queue.Push":
		return 1
	}
	return -1
}

func (b *BlueprintBackend) GetReadKeyIndex() int {
	switch b.Name {
	case "Cache.Get":
		return 1
	case "Queue.Pop":
		return 1
	}
	return -1
}

func GetBackendMethod(name string) *BlueprintBackend {
	switch name {
	case "Cache.Put":
		return &BlueprintBackend{Name: name, Write: true, Params: []*types.FunctionParameter{&ctxParam, &keyParam, &valueParam}}
	case "Cache.Get":
		return &BlueprintBackend{Name: name, Write: false, Params: []*types.FunctionParameter{&ctxParam, &keyParam, &valueParam}}
	case "Queue.Push":
		return &BlueprintBackend{Name: name, Write: true, Params: []*types.FunctionParameter{&ctxParam, &itemParam}}
		case "Queue.Pop":
			return &BlueprintBackend{Name: name, Write: false, Params: []*types.FunctionParameter{&ctxParam, &itemParam}}
	case "NoSQLCollection.InsertOne": // InsertOne(ctx context.Context, document interface{}) error
		return &BlueprintBackend{Name: name, Write: false, Params: []*types.FunctionParameter{&ctxParam, &docParam}}
	case "NoSQLCollection.FindOne": // FindOne(ctx context.Context, filter bson.D, projection ...bson.D) (NoSQLCursor, error)
		return &BlueprintBackend{Name: name, Write: false, Params: []*types.FunctionParameter{&ctxParam, &filterParam, &projectionParam}}
	}
	return nil
}

var ctxParam = types.FunctionParameter{
	FieldInfo: types.FieldInfo{
		Name: "ctx",
		Type: &types.UserType{
			Name:    "Context",
			Package: "context",
			UserType: nil,
		},
	},
}
var keyParam = types.FunctionParameter{
	FieldInfo: types.FieldInfo{
		Name: "key",
		Type: &types.BasicType{
			Name: "string",
		},
	},
}
var valueParam = types.FunctionParameter{
	FieldInfo: types.FieldInfo{
		Name: "value",
		Type: &types.InterfaceType{},
	},
}
var itemParam = types.FunctionParameter{
	FieldInfo: types.FieldInfo{
		Name: "item",
		Type: &types.InterfaceType{},
	},
}
var docParam = types.FunctionParameter{
	FieldInfo: types.FieldInfo{
		Name: "document",
		Type: &types.InterfaceType{},
	},
}
var filterParam = types.FunctionParameter{
	FieldInfo: types.FieldInfo{
		Name: "filter",
		Type: &types.UserType{
			Name: "D",
			Package: "bson",
		},
	},
}
var projectionParam = types.FunctionParameter{
	FieldInfo: types.FieldInfo{
		Name: "projection",
		Type: &types.UserType{
			Name: "D",
			Package: "bson",
		},
	},
}
