[] (-1) (PointerVariable PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) config.ConfigServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) name string // read(config_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = config, collection = config} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(config_db), 
[_] (0) (StructVariable StructType) struct{ "name" string,  string} // read(config_db), 
[__] (0) (FieldVariable FieldType) string // read(config_db), 
[___] (-1) (BasicVariable BasicType) name string // read(config_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = config, collection = config} // read(config_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) conf config.Config struct{Name string, Value string, Description string} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

