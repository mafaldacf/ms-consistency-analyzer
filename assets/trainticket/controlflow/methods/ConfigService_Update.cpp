[] (PointerVariable PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) config.ConfigServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) conf config.Config struct{Name string, Value string, Description string} 
[_] (FieldVariable FieldType) Name string 
[__] (BasicVariable BasicType) Name string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = config, collection = config} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "name" string, Name string} 
[__] (FieldVariable FieldType) "name" string 
[___] (BasicVariable BasicType) "name" string 
[__] (FieldVariable FieldType) Name string 
[___] (BasicVariable BasicType) Name string 

