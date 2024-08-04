[] (PointerVariable PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) typeindex int64 

[] (BasicVariable BasicType) orderid string // write(assurance_db), 

[] (StructVariable UserType) at assurance.AssuranceType struct{Index int64, Name string, Price float64} // write(assurance_db), 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) id string // write(assurance_db), 

[] (StructVariable UserType) assurance assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} // write(assurance_db), 
[_] (FieldVariable FieldType) AT assurance.AssuranceType struct{Index int64, Name string, Price float64} // write(assurance_db), 
[__] (StructVariable UserType) at assurance.AssuranceType struct{Index int64, Name string, Price float64} // write(assurance_db), 
[_] (FieldVariable FieldType) ID string // write(assurance_db), 
[__] (BasicVariable BasicType) id string // write(assurance_db), 
[_] (FieldVariable FieldType) OrderID string // write(assurance_db), 
[__] (BasicVariable BasicType) orderid string // write(assurance_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance} 

[] (InterfaceVariable UserType) err .error 

