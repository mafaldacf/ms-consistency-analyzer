[] (PointerVariable PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) config.ConfigServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) conf config.Config struct{Name string, Value string, Description string} // write(config_db), 
[_] (FieldVariable FieldType) Name string // write(config_db), 
[__] (BasicVariable BasicType) Name string // write(config_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = config, collection = config} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "name" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) Name string // write(config_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = config, collection = config} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) saved_conf config.Config struct{Name string, Value string, Description string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

