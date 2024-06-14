package frameworks

import (
	"analyzer/pkg/logger"
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
	Params []*types.FunctionField
	Returns []*types.FunctionField
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

func (b *BlueprintBackend) GetParams() []*types.FunctionField {
	return b.Params
}

func (b *BlueprintBackend) GetReturns() []*types.FunctionField {
	return b.Returns
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
	case "Cache.Put": // Put(ctx context.Context, key string, value interface{}) error
		return &BlueprintBackend{Name: name, Write: true, 
			Params: []*types.FunctionField{&ctxParam, &keyParam, &valueParam},
			Returns: []*types.FunctionField{&errorReturn},
		}
	case "Cache.Get": // Get(ctx context.Context, key string, val interface{}) (bool, error)
		return &BlueprintBackend{Name: name, Write: false, 
			Params: []*types.FunctionField{&ctxParam, &keyParam, &valueParam},
			Returns: []*types.FunctionField{&boolReturn, &errorReturn},
	}
	case "Queue.Push": // Push(ctx context.Context, item interface{}) (bool, error)
		return &BlueprintBackend{Name: name, Write: true, 
			Params: []*types.FunctionField{&ctxParam, &itemParam},
			Returns: []*types.FunctionField{&boolReturn, &errorReturn},
		}
	case "Queue.Pop": // Pop(ctx context.Context, dst interface{}) (bool, error)
		return &BlueprintBackend{Name: name, Write: false, 
			Params: []*types.FunctionField{&ctxParam, &itemParam},
			Returns: []*types.FunctionField{&boolReturn, &errorReturn},
		}
	case "NoSQLDatabase.GetCollection": // GetCollection(ctx context.Context, db_name string, collection_name string) (NoSQLCollection, error)
		return &BlueprintBackend{Name: name, Write: false, 
			Params: []*types.FunctionField{&ctxParam, &dbNameParam, &collectionNameParam},
			Returns: []*types.FunctionField{&NoSQLCollection, &errorReturn},
		}
	case "NoSQLCollection.InsertOne": // InsertOne(ctx context.Context, document interface{}) error
		return &BlueprintBackend{Name: name, Write: false, 
			Params: []*types.FunctionField{&ctxParam, &docParam},
			Returns: []*types.FunctionField{&errorReturn},
		}
	case "NoSQLCollection.FindOne": // FindOne(ctx context.Context, filter bson.D, projection ...bson.D) (NoSQLCursor, error)
		return &BlueprintBackend{Name: name, Write: false, 
			Params: []*types.FunctionField{&ctxParam, &filterParam, &projectionParam},
			Returns: []*types.FunctionField{&errorReturn},
		}
	default:
		logger.Logger.Fatalf("could not find blueprint backend method with name %s", name)
	}
	return nil
}

var ctxParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "ctx",
		Type: &types.UserType{
			Name:     "Context",
			Package:  "context",
			UserType: nil,
		},
	},
}
var keyParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "key",
		Type: &types.BasicType{
			Name: "string",
		},
	},
}
var valueParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "value",
		Type: &types.InterfaceType{},
	},
}
var itemParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "item",
		Type: &types.InterfaceType{},
	},
}
var docParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "document",
		Type: &types.InterfaceType{},
	},
}
var filterParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "filter",
		Type: &types.UserType{
			Name:    "D",
			Package: "bson",
		},
	},
}
var projectionParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "projection",
		Type: &types.UserType{
			Name:    "D",
			Package: "bson",
		},
	},
}
var dbNameParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "db_name",
		Type: &types.BasicType{
			Name:    "string",
		},
	},
}
var collectionNameParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "collection_name",
		Type: &types.BasicType{
			Name:    "string",
		},
	},
}
var boolReturn = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Type: &types.BasicType{
			Name:    "err",
		},
	},
}
var NoSQLCursor = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Type: &types.UserType{
			Name:    "NoSQLCursor",
			Package: "github.com/blueprint-uservices/blueprint/runtime/core/backend",
		},
	},
}
var NoSQLCollection = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Type: &types.UserType{
			Name:    "NoSQLCollection",
			Package: "github.com/blueprint-uservices/blueprint/runtime/core/backend",
		},
	},
}
var errorReturn = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Type: &types.BasicType{
			Name:    "error",
		},
	},
}
