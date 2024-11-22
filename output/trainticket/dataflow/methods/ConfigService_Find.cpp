[] (PointerObject PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) config.ConfigServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(config_db.Config.Name) {1}
[] (BasicObject BasicType) name string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = config, collection = config}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "name" string,  string}

    --> r-tainted: read(config_db.Config) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = config, collection = config}
     --> r-tainted: read(config_db.Config) {1}
[_] (StructObject UserType) conf config.Config struct{Name string, Value string, Description string}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(config_db.Config) {1}
[] (StructObject UserType) conf config.Config struct{Name string, Value string, Description string}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

