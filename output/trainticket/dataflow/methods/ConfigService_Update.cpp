[] (PointerObject PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) config.ConfigServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) conf config.Config struct{Name string, Value string, Description string}
[_] (FieldObject FieldType) Name string
[__] (BasicObject BasicType) Name string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = config, collection = config}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "name" string,  string}

