[] (PointerObject PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) config.ConfigServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(config_db.Config) {1}
[] (StructObject UserType) conf config.Config struct{Name string, Value string, Description string}
     --> w-tainted: write(config_db.Config.Name) {1}
[_] (FieldObject FieldType) Name string
      --> w-tainted: write(config_db.Config.Name) {1}           --> w-tainted: write(config_db.Config.Name) {1} --> r-tainted: read(config_db._.name) {1}
[__] (BasicObject BasicType) Name string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = config, collection = config}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "name" string,  string}

    --> r-tainted: read(config_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = config, collection = config}
     --> r-tainted: read(config_db.Config) {1}
[_] (StructObject UserType) saved_conf config.Config struct{Name string, Value string, Description string}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(config_db.Config) {1}
[] (StructObject UserType) saved_conf config.Config struct{Name string, Value string, Description string}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

