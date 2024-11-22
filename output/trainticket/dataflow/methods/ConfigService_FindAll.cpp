[] (PointerObject PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) config.ConfigServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = config, collection = config}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(config_db.[]config.Config struct{Name string, Value string, Description string}) {1}
[] (ArrayObject ArrayType) configs []config.Config struct{Name string, Value string, Description string}

    --> r-tainted: read(config_db.Config) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = config, collection = config}
     --> r-tainted: read(config_db.[]config.Config struct{Name string, Value string, Description string}) {1}
[_] (ArrayObject ArrayType) configs []config.Config struct{Name string, Value string, Description string}

[] (InterfaceObject UserType) err .error

[] (InterfaceObject UserType) err .error

