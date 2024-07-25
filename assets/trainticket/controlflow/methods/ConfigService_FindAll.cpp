[] (PointerVariable PointerType) c (*config.ConfigServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) config.ConfigServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = config, collection = config} 

[] (InterfaceVariable UserType) err .error 

[] (ArrayVariable ArrayType) configs []config.Config struct{Name string, Value string, Description string} 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = config, collection = config} 

[] (InterfaceVariable UserType) err .error 

[] (InterfaceVariable UserType) err .error 

