package frameworks

import (
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
)

type BlueprintBackend struct {
	types.Method
	Name    	string
	Backend    	string
	Params  	[]*types.FunctionField
	Returns 	[]*types.FunctionField
	Write   	bool
}

func (b *BlueprintBackend) String() string {
	repr := fmt.Sprintf("%s.%s(", b.Backend, b.Name)
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

func (b *BlueprintBackend) FullName() string {
	return b.Backend + "." + b.Name
}

//FIXME: this is messing up with previous assignments!
func (b *BlueprintBackend) SetNoSQLDatabaseCollection(databaseName string, collectionName string, dbInstance datastores.DatabaseInstance) []*types.FunctionField {
	if b.Name == "GetCollection" {
		collection := b.Returns[0]
		collection.GetType().(*BlueprintBackendType).DbInstance = dbInstance
		collection.GetType().(*BlueprintBackendType).NoSQLComponent = &BlueprintNoSQLComponent{
			Database: databaseName,
			Collection: collectionName,
		}
		logger.Logger.Warnf("[BLUEPRINT] setting NoSQL database collection for (%s, %s)", databaseName, collectionName)
	} else {
		logger.Logger.Fatalf("[BLUEPRINT] method %s is not NoSQLDatabase.GetCollection()", b.Name)
	}
	return b.Returns
}

func (b *BlueprintBackend) IsNoSQLGetCollectionCall() bool {
	return b.Name == "GetCollection"
}

func (b *BlueprintBackend) IsWrite() bool {
	return b.Write
}

func (b *BlueprintBackend) IsQueueRead() bool {
	return !b.Write && b.FullName() == "Queue.Pop"
}

func (b *BlueprintBackend) IsQueueWrite() bool {
	return b.Write && b.FullName() == "Queue.Push"
}

func (b *BlueprintBackend) MatchQueueIdentifiers() map[int]int {
	var matches map[int]int
	if b.FullName() == "Queue.Push" {
		matches = make(map[int]int, 0)
		// we have Queue.Push(ctx, src) and Queue.Pop(ctx, dst)
		// so the (src @ index 1) matches (dst @ index 1)
		matches[1] = 1
	}
	return matches
}

func (b *BlueprintBackend) GetWrittenObjectIndex() int {
	switch b.FullName() {
	case "Cache.Put":
		return 2
	case "NoSQLDatabase.NoSQLCollection.InsertOne":
		return 1
	case "Queue.Push":
		return 1
	default:
		logger.Logger.Fatalf("unknown backend %s", b.FullName())
	}
	return -1
}

func (b *BlueprintBackend) GetReadObjectIndex() int {
	switch b.FullName() {
	case "Cache.Get":
		return 2
	case "NoSQLDatabase.NoSQLCollection.FindOne":
		return -1
	case "Queue.Pop":
		return 1
	default:
		logger.Logger.Fatalf("unknown backend %s", b.FullName())
	}
	
	return -1
}

func (b *BlueprintBackend) GetWrittenKeyIndex() int {
	switch b.FullName() {
	case "Cache.Put":
		return 1
	case "NoSQLDatabase.NoSQLCollection.InsertOne":
		return 1
	case "Queue.Push":
		return 1
	default:
		logger.Logger.Fatalf("unknown backend %s", b.FullName())
	}
	return -1
}

func (b *BlueprintBackend) GetReadKeyIndex() int {
	switch b.FullName() {
	case "Cache.Get":
		return 1
	case "NoSQLDatabase.NoSQLCollection.FindOne":
		return -1
	case "Queue.Pop":
		return 1
	default:
		logger.Logger.Fatalf("unknown backend %s", b.FullName())
	}
	return -1
}

func BuildBackendComponentMethods(name string) []*BlueprintBackend {
	var methods []*BlueprintBackend
	switch name {
	// --------
	// Backends
	// --------
	case "Cache":
		// Put(ctx context.Context, key string, value interface{}) error
		methods = append(methods, &BlueprintBackend{Name: "Put", Backend: "Cache", Write: true,
			Params:  []*types.FunctionField{&ctxParam, &keyParam, &valueParam},
			Returns: []*types.FunctionField{&errorReturn},
		})
		// Get(ctx context.Context, key string, val interface{}) (bool, error)
		methods = append(methods, &BlueprintBackend{Name: "Get", Backend: "Cache", Write: false,
			Params:  []*types.FunctionField{&ctxParam, &keyParam, &valueParam},
			Returns: []*types.FunctionField{&boolReturn, &errorReturn},
		})
	case "Queue":
		// Push(ctx context.Context, item interface{}) (bool, error)
		methods = append(methods, &BlueprintBackend{Name: "Push", Backend: "Queue", Write: true,
			Params:  []*types.FunctionField{&ctxParam, &itemParam},
			Returns: []*types.FunctionField{&boolReturn, &errorReturn},
		})
		// // Pop(ctx context.Context, dst interface{}) (bool, error)
		methods = append(methods, &BlueprintBackend{Name: "Pop", Backend: "Queue", Write: false,
			Params:  []*types.FunctionField{&ctxParam, &itemParam},
			Returns: []*types.FunctionField{&boolReturn, &errorReturn},
		})
	case "NoSQLDatabase":
		// GetCollection(ctx context.Context, db_name string, collection_name string) (NoSQLCollection, error)
		methods = append(methods, &BlueprintBackend{Name: "GetCollection", Backend: "NoSQLDatabase", Write: false,
			Params:  []*types.FunctionField{&ctxParam, &dbNameParam, &collectionNameParam},
			Returns: []*types.FunctionField{&NoSQLCollection, &errorReturn},
		})
	// ----------------
	// NoSQL Components
	// ----------------
	case "NoSQLCollection":
		buildBackendNoSQLComponentMethods(name)
	case "NoSQLCursor":
		buildBackendNoSQLComponentMethods(name)
	default:
		logger.Logger.Fatalf("could not build methods for backend %s", name)
	}
	return methods
}

func buildBackendNoSQLComponentMethods(name string) []*BlueprintBackend {
	var methods []*BlueprintBackend
	switch name {
	case "NoSQLCollection":
		// InsertOne(ctx context.Context, document interface{}) error
		methods = append(methods, &BlueprintBackend{Name: "InsertOne", Backend: "NoSQLDatabase.NoSQLCollection", Write: true,
			Params:  []*types.FunctionField{&ctxParam, &docParam},
			Returns: []*types.FunctionField{&errorReturn},
		})
		// FindOne(ctx context.Context, filter bson.D, projection ...bson.D) (NoSQLCursor, error)
		methods = append(methods, &BlueprintBackend{Name: "FindOne", Backend: "NoSQLDatabase.NoSQLCollection", Write: false,
			Params:  []*types.FunctionField{&ctxParam, &filterParam, &projectionParam},
			Returns: []*types.FunctionField{&errorReturn},
		})
	case "NoSQLCursor":
		// One(ctx context.Context, obj interface{}) (bool, error)
		methods = append(methods, &BlueprintBackend{Name: "One", Backend: "NoSQLDatabase.NoSQLCursor", Write: false,
			Params:  []*types.FunctionField{&ctxParam, &objParam},
			Returns: []*types.FunctionField{&boolReturn, &errorReturn},
		})
	default:
		logger.Logger.Fatalf("could not build methods for backend %s", name)
	}
	return methods
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
var objParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "obj",
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
			Name: "string",
		},
	},
}
var collectionNameParam = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Name: "collection_name",
		Type: &types.BasicType{
			Name: "string",
		},
	},
}
var boolReturn = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Type: &types.BasicType{
			Name: "err",
		},
	},
}
var NoSQLCursor = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Type: &BlueprintBackendType{
			Name:    "NoSQLCursor",
			Package: "github.com/blueprint-uservices/blueprint/runtime/core/backend",
			Methods: buildBackendNoSQLComponentMethods("NoSQLCursor"),
		},
	},
}
var NoSQLCollection = types.FunctionField{
	FieldInfo: types.FieldInfo{
		Type: &BlueprintBackendType{
			Name:    "NoSQLCollection",
			Package: "github.com/blueprint-uservices/blueprint/runtime/core/backend",
			Methods: buildBackendNoSQLComponentMethods("NoSQLCollection"),
		},
	},
}
var errorReturn = types.FunctionField{
	FieldInfo: types.FieldInfo{
		// error is actually an interface
		Type: &types.InterfaceType{},
	},
}
