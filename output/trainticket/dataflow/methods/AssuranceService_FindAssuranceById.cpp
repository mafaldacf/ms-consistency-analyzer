[] (PointerVariable PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ AssuranceService 

[] (BasicVariable BasicType) id string 
[_] (Reference BasicType) ref <ID string> @ AssuranceService 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) id string 
[____] (Reference BasicType) ref <ID string> @ AssuranceService 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = assurance, collection = assurance} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) ass assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

