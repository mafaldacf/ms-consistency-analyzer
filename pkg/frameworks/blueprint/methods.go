package blueprint

import (
	"fmt"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
)

type BackendMethod struct {
	types.Method
	Name      string
	Backend   string
	Component string
	Params    []*types.MethodField
	Returns   []*types.MethodField
	Write     bool
}

func (b *BackendMethod) DeepCopy() *BackendMethod {
	return &BackendMethod{
		Name:      b.Name,
		Backend:   b.Backend,
		Component: b.Component,
		Params:    b.Params,
		Returns:   b.Returns,
		Write:     b.Write,
	}
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

func (b *BackendMethod) LongString() string {
	repr := fmt.Sprintf("%s.%s(", b.Backend, b.Name)
	for i, param := range b.Params {
		repr += param.String()
		if i < len(b.Params)-1 {
			repr += ", "
		}
	}
	repr += ")"
	if len(b.Returns) == 1 {
		repr += " " + b.Returns[0].String()
	}
	if len(b.Returns) > 1 {
		repr += " ("
		for i, ret := range b.Returns {
			repr += ret.String()
			if i < len(b.Returns)-1 {
				repr += ", "
			}
		}
		repr += ")"
	}
	return repr
}

func (b *BackendMethod) GetParams() []*types.MethodField {
	return b.Params
}

func (b *BackendMethod) GetReturns() []*types.MethodField {
	return b.Returns
}

func (b *BackendMethod) FullName() string {
	if b.Component != "" {
		return b.Backend + "." + b.Component + "." + b.Name
	}
	return b.Backend + "." + b.Name
}

// FIXME: this is messing up with previous assignments!
func (b *BackendMethod) SetNoSQLDatabaseCollection(databaseName string, collectionName string, dbInstance datastores.DatabaseInstance) {
	if len(b.Returns) > 0 {
		collection := b.Returns[0]
		collection.GetType().(*BlueprintBackendType).DbInstance = dbInstance
		collection.GetType().(*BlueprintBackendType).NoSQLComponent = &NoSQLComponent{
			Database:   databaseName,
			Collection: collectionName,
			Type:       NoSQLCollectionType,
		}
		logger.Logger.Warnf("[BLUEPRINT] setting NoSQL collection for (%s, %s)", databaseName, collectionName)
	}
}

// FIXME: this is messing up with previous assignments!
func (b *BackendMethod) SetNoSQLDatabaseCursor(databaseName string, collectionName string, dbInstance datastores.DatabaseInstance) {
	if len(b.Returns) > 0 {
		collection := b.Returns[0]
		if backendType, ok := collection.GetType().(*BlueprintBackendType); ok {
			backendType.DbInstance = dbInstance
			backendType.NoSQLComponent = &NoSQLComponent{
				Database:   databaseName,
				Collection: collectionName,
				// upgrade type
				Type: NoSQLCursorType,
			}
			logger.Logger.Warnf("[BLUEPRINT] setting NoSQL cursor for (%s, %s) ", databaseName, collectionName)
		} else {
			logger.Logger.Fatalf("[BLUEPRINT] cannot set NoSQL cursor for (%s, %s)", databaseName, collectionName)
		}
	}
}

func (b *BackendMethod) IsNoSQLBackendCall() bool {
	return b.Backend == "NoSQLDatabase" && b.Component == ""
}

func (b *BackendMethod) IsNoSQLComponentCall() bool {
	return b.Backend == "NoSQLDatabase" && (b.Component == "NoSQLCollection" || b.Component == "NoSQLCursor")
}

func (b *BackendMethod) IsNoSQLCollectionCall() bool {
	return b.Backend == "NoSQLDatabase" && b.Component == "NoSQLCollection"
}

func (b *BackendMethod) IsNoSQLCursorCall() bool {
	return b.Backend == "NoSQLDatabase" && b.Component == "NoSQLCursor"
}

func (b *BackendMethod) ReturnsNoSQLCollection() (bool, int) {
	return b.Backend == "NoSQLDatabase" && b.Name == "GetCollection", 0 // index of collection
}

func (b *BackendMethod) ReturnsNoSQLCursor() (bool, int) {
	return b.Backend == "NoSQLDatabase" && b.Component == "NoSQLCollection" && (b.Name == "FindOne" || b.Name == "FindMany"), 0 // index of cursor
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
		return -2
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
		return 1
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
			Returns: []*types.MethodField{&NoSQLCollectionReturn, &errorReturn},
		})
	// ----------------
	// NoSQL Components
	// ----------------
	case "NoSQLCollection":
		methods = buildBackendNoSQLCollectionMethods()
	case "NoSQLCursor":
		methods = buildBackendNoSQLCursorMethods()
	default:
		logger.Logger.Fatalf("could not build methods for backend %s", name)
	}
	return methods
}

func buildBackendNoSQLCollectionMethods() []*BackendMethod {
	var methods []*BackendMethod
	// InsertOne(ctx context.Context, document interface{}) error
	methods = append(methods, &BackendMethod{Name: "InsertOne", Backend: "NoSQLDatabase", Component: "NoSQLCollection", Write: true,
		Params:  []*types.MethodField{&ctxParam, &docParam},
		Returns: []*types.MethodField{&errorReturn},
	})
	// FindOne(ctx context.Context, filter bson.D, projection ...bson.D) (NoSQLCursor, error)
	methods = append(methods, &BackendMethod{Name: "FindOne", Backend: "NoSQLDatabase", Component: "NoSQLCollection", Write: false,
		Params:  []*types.MethodField{&ctxParam, &filterParam, &projectionParam},
		Returns: []*types.MethodField{&NoSQLCursorReturn, &errorReturn},
	})
	return methods
}

func buildBackendNoSQLCursorMethods() []*BackendMethod {
	var methods []*BackendMethod
	methods = append(methods, &BackendMethod{Name: "One", Backend: "NoSQLDatabase", Component: "NoSQLCursor", Write: false,
		Params:  []*types.MethodField{&ctxParam, &objParam},
		Returns: []*types.MethodField{&boolReturn, &errorReturn},
	})
	return methods
}

var ctxParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "ctx",
		Type: &gotypes.UserType{
			Name:     "Context",
			Package:  "context",
			UserType: nil,
		},
	},
}
var keyParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "key",
		Type: &gotypes.BasicType{
			Name: "string",
		},
	},
}
var valueParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "value",
		Type: &gotypes.InterfaceType{Methods: make(map[string]string)},
	},
}
var itemParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "item",
		Type: &gotypes.InterfaceType{Methods: make(map[string]string)},
	},
}
var docParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "document",
		Type: &gotypes.InterfaceType{Methods: make(map[string]string)},
	},
}
var objParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "obj",
		Type: &gotypes.InterfaceType{Methods: make(map[string]string)},
	},
}
var filterParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "filter",
		Type: &gotypes.UserType{
			Name:    "D",
			Package: "bson",
		},
	},
}
var projectionParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "projection",
		Type: &gotypes.UserType{
			Name:    "D",
			Package: "bson",
		},
	},
}
var dbNameParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "db_name",
		Type: &gotypes.BasicType{
			Name: "string",
		},
	},
}
var collectionNameParam = types.MethodField{
	FieldInfo: types.FieldInfo{
		Name: "collection_name",
		Type: &gotypes.BasicType{
			Name: "string",
		},
	},
}
var boolReturn = types.MethodField{
	FieldInfo: types.FieldInfo{
		Type: &gotypes.BasicType{
			Name: "err",
		},
	},
}
var NoSQLCursorReturn = types.MethodField{
	FieldInfo: types.FieldInfo{
		Type: &BlueprintBackendType{
			Name:    "NoSQLCursor",
			Package: "github.com/blueprint-uservices/blueprint/runtime/core/backend",
			Methods: buildBackendNoSQLCursorMethods(),
		},
	},
}
var NoSQLCollectionReturn = types.MethodField{
	FieldInfo: types.FieldInfo{
		Type: &BlueprintBackendType{
			Name:    "NoSQLCollection",
			Package: "github.com/blueprint-uservices/blueprint/runtime/core/backend",
			Methods: buildBackendNoSQLCollectionMethods(),
		},
	},
}
var errorReturn = types.MethodField{
	FieldInfo: types.FieldInfo{
		// error is actually an interface
		Type: &gotypes.InterfaceType{Methods: make(map[string]string)},
	},
}
