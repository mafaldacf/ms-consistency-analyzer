[] (PointerVariable PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ AssuranceService 

[] (BasicVariable BasicType) id string // read(assurance_db), 
[_] (Reference BasicType) ref <ID string> @ AssuranceService // read(assurance_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(assurance_db), 
[_] (StructVariable StructType) struct{ "id" string,  string} // read(assurance_db), 
[__] (FieldVariable FieldType) string // read(assurance_db), 
[___] (BasicVariable BasicType) id string // read(assurance_db), 
[____] (Reference BasicType) ref <ID string> @ AssuranceService // read(assurance_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = assurance, collection = assurance} // read(assurance_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) ass assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

