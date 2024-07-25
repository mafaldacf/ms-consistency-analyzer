[] (PointerVariable PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) assurance assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} 
[_] (FieldVariable FieldType) ID string // read(assurance_db), 
[__] (BasicVariable BasicType) ID string // read(assurance_db), 

[] (StructVariable UserType) _ assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string, ID string} 
[__] (FieldVariable FieldType) "id" string 
[___] (BasicVariable BasicType) "id" string 
[__] (FieldVariable FieldType) ID string // read(assurance_db), 
[___] (BasicVariable BasicType) ID string // read(assurance_db), 

[] (BasicVariable BasicType) ok bool 

[] (InterfaceVariable UserType) err .error 

