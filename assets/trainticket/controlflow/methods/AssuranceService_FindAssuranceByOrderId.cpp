[] (-1) (PointerVariable PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) order_id string // read(assurance_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(assurance_db), 
[_] (0) (StructVariable StructType) struct{ "orderid" string,  string} // read(assurance_db), 
[__] (0) (FieldVariable FieldType) string // read(assurance_db), 
[___] (-1) (BasicVariable BasicType) order_id string // read(assurance_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = assurance, collection = assurance} // read(assurance_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) ass assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

