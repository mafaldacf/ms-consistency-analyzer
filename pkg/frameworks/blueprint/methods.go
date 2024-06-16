package blueprint

import (
	"fmt"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
)

type BackendMethod struct {
	types.Method
	Name    string
	Backend string
	Params  []*types.MethodField
	Returns []*types.MethodField
	Write   bool
}

func (b *BackendMethod) String() string {
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

func (b *BackendMethod) GetParams() []*types.MethodField {
	return b.Params
}

func (b *BackendMethod) GetReturns() []*types.MethodField {
	return b.Returns
}

func (b *BackendMethod) FullName() string {
	return b.Backend + "." + b.Name
}

// FIXME: this is messing up with previous assignments!
func (b *BackendMethod) SetNoSQLDatabaseCollection(databaseName string, collectionName string, dbInstance datastores.DatabaseInstance) []*types.MethodField {
	if b.Name == "GetCollection" {
		collection := b.Returns[0]
		collection.GetType().(*BackendType).DbInstance = dbInstance
		collection.GetType().(*BackendType).NoSQLComponent = &NoSQLComponent{
			Database:   databaseName,
			Collection: collectionName,
		}
		logger.Logger.Warnf("[BLUEPRINT] setting NoSQL database collection for (%s, %s)", databaseName, collectionName)
	} else {
		logger.Logger.Fatalf("[BLUEPRINT] method %s is not NoSQLDatabase.GetCollection()", b.Name)
	}
	return b.Returns
}

func (b *BackendMethod) IsNoSQLGetCollectionCall() bool {
	return b.Name == "GetCollection"
}

func (b *BackendMethod) IsWrite() bool {
	return b.Write
}

func (b *BackendMethod) IsQueueRead() bool {
	return !b.Write && b.FullName() == "Queue.Pop"
}

func (b *BackendMethod) IsQueueWrite() bool {
	return b.Write && b.FullName() == "Queue.Push"
}

func (b *BackendMethod) MatchQueueIdentifiers() map[int]int {
	var matches map[int]int
	if b.FullName() == "Queue.Push" {
		matches = make(map[int]int, 0)
		// we have Queue.Push(ctx, src) and Queue.Pop(ctx, dst)
		// so the (src @ index 1) matches (dst @ index 1)
		matches[1] = 1
	}
	return matches
}

func (b *BackendMethod) GetWrittenObjectIndex() int {
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

func (b *BackendMethod) GetReadObjectIndex() int {
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

func (b *BackendMethod) GetWrittenKeyIndex() int {
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

func (b *BackendMethod) GetReadKeyIndex() int {
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

func BuildBackendComponentMethods(name string) []*BackendMethod {
	var methods []*BackendMethod
	switch name {
	// --------
	// Backends
	// --------
	case "Cache":
		// Put(ctx context.Context, key string, value interface{}) error
		methods = append(methods, &BackendMethod{Name: "Put", Backend: "Cache", Write: true,
			Params:  []*types.MethodField{&ctxParam, &keyParam, &valueParam},
			Returns: []*types.MethodField{&errorReturn},
		})
		// Get(ctx context.Context, key string, val interface{}) (bool, error)
		methods = append(methods, &BackendMethod{Name: "Get", Backend: "Cache", Write: false,
			Params:  []*types.MethodField{&ctxParam, &keyParam, &valueParam},
			Returns: []*types.MethodField{&boolReturn, &errorReturn},
		})
	case "Queue":
		// Push(ctx context.Context, item interface{}) (bool, error)
		methods = append(methods, &BackendMethod{Name: "Push", Backend: "Queue", Write: true,
			Params:  []*types.MethodField{&ctxParam, &itemParam},
			Returns: []*types.MethodField{&boolReturn, &errorReturn},
		})
		// // Pop(ctx context.Context, dst interface{}) (bool, error)
		methods = append(methods, &BackendMethod{Name: "Pop", Backend: "Queue", Write: false,
			Params:  []*types.MethodField{&ctxParam, &itemParam},
			Returns: []*types.MethodField{&boolReturn, &errorReturn},
		})
	case "NoSQLDatabase":
		// GetCollection(ctx context.Context, db_name string, collection_name string) (NoSQLCollection, error)
		methods = append(methods, &BackendMethod{Name: "GetCollection", Backend: "NoSQLDatabase", Write: false,
			Params:  []*types.MethodField{&ctxParam, &dbNameParam, &collectionNameParam},
			Returns: []*types.MethodField{&NoSQLCollection, &errorReturn},
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

func buildBackendNoSQLComponentMethods(name string) []*BackendMethod {
	var methods []*BackendMethod
	switch name {
	case "NoSQLCollection":
		// InsertOne(ctx context.Context, document interface{}) error
		methods = append(methods, &BackendMethod{Name: "InsertOne", Backend: "NoSQLDatabase.NoSQLCollection", Write: true,
			Params:  []*types.MethodField{&ctxParam, &docParam},
			Returns: []*types.MethodField{&errorReturn},
		})
		// FindOne(ctx context.Context, filter bson.D, projection ...bson.D) (NoSQLCursor, error)
		methods = append(methods, &BackendMethod{Name: "FindOne", Backend: "NoSQLDatabase.NoSQLCollection", Write: false,
			Params:  []*types.MethodField{&ctxParam, &filterParam, &projectionParam},
			Returns: []*types.MethodField{&errorReturn},
		})
	case "NoSQLCursor":
		// One(ctx context.Context, obj interface{}) (bool, error)
		methods = append(methods, &BackendMethod{Name: "One", Backend: "NoSQLDatabase.NoSQLCursor", Write: false,
			Params:  []*types.MethodField{&ctxParam, &objParam},
			Returns: []*types.MethodField{&boolReturn, &errorReturn},
		})
	default:
		logger.Logger.Fatalf("could not build methods for backend %s", name)
	}
	return methods
}

var ctxParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "ctx",
		Type: &types.UserType{
			Name:     "Context",
			Package:  "context",
			UserType: nil,
		},
	},
}
var keyParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "key",
		Type: &types.BasicType{
			Name: "string",
		},
	},
}
var valueParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "value",
		Type: &types.InterfaceType{},
	},
}
var itemParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "item",
		Type: &types.InterfaceType{},
	},
}
var docParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "document",
		Type: &types.InterfaceType{},
	},
}
var objParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "obj",
		Type: &types.InterfaceType{},
	},
}
var filterParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "filter",
		Type: &types.UserType{
			Name:    "D",
			Package: "bson",
		},
	},
}
var projectionParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "projection",
		Type: &types.UserType{
			Name:    "D",
			Package: "bson",
		},
	},
}
var dbNameParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "db_name",
		Type: &types.BasicType{
			Name: "string",
		},
	},
}
var collectionNameParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "collection_name",
		Type: &types.BasicType{
			Name: "string",
		},
	},
}
var boolReturn = types.MethodField{
	FieldInfo: types.FieldInfo{
		Type: &types.BasicType{
			Name: "err",
		},
	},
}
var NoSQLCursor = types.MethodField{
	FieldInfo: types.FieldInfo{
		Type: &BackendType{
			Name:    "NoSQLCursor",
			Package: "github.com/blueprint-uservices/blueprint/runtime/core/backend",
			Methods: buildBackendNoSQLComponentMethods("NoSQLCursor"),
		},
	},
}
var NoSQLCollection = types.MethodField{
	FieldInfo: types.FieldInfo{
		Type: &BackendType{
			Name:    "NoSQLCollection",
			Package: "github.com/blueprint-uservices/blueprint/runtime/core/backend",
			Methods: buildBackendNoSQLComponentMethods("NoSQLCollection"),
		},
	},
}
var errorReturn = types.MethodField{
	FieldInfo: types.FieldInfo{
		// error is actually an interface
		Type: &types.InterfaceType{},
	},
}
