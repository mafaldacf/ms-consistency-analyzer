[] (-1) (PointerVariable PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (14) (InterfaceVariable UserType) ctx context.Context 

[] (15) (BasicVariable BasicType) typeindex int64 

[] (-1) (BasicVariable BasicType) orderid string // write(assurance_db), 

[] (-1) (StructVariable UserType) at assurance.AssuranceType struct{Index int64, Name string, Price float64} // write(assurance_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) id string // write(assurance_db), 

[] (-1) (StructVariable UserType) assurance assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} // write(assurance_db), 
[_] (-1) (FieldVariable FieldType) ID string // write(assurance_db), 
[__] (-1) (BasicVariable BasicType) id string // write(assurance_db), 
[_] (-1) (FieldVariable FieldType) OrderID string // write(assurance_db), 
[__] (-1) (BasicVariable BasicType) orderid string // write(assurance_db), 
[_] (-1) (FieldVariable FieldType) AT assurance.AssuranceType struct{Index int64, Name string, Price float64} // write(assurance_db), 
[__] (-1) (StructVariable UserType) at assurance.AssuranceType struct{Index int64, Name string, Price float64} // write(assurance_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance} 

[] (-1) (InterfaceVariable UserType) err .error 

