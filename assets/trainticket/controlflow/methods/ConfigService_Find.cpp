[] (PointerVariable PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) config.ConfigServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) name string // read(config_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = config, collection = config} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(config_db), 
[_] (StructVariable StructType) struct{ "name" string,  string} // read(config_db), 
[__] (FieldVariable FieldType) string // read(config_db), 
[___] (BasicVariable BasicType) name string // read(config_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = config, collection = config} // read(config_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) conf config.Config struct{Name string, Value string, Description string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

