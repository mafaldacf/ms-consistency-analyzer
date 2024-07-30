[] (-1) (PointerVariable PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (16) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) assurance assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} 
[_] (-1) (FieldVariable FieldType) ID string 
[__] (17) (BasicVariable BasicType) ID string 

[] (-1) (StructVariable UserType) _ assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (17) (BasicVariable BasicType) ID string 

[] (-1) (BasicVariable BasicType) ok bool 

[] (-1) (InterfaceVariable UserType) err .error 

