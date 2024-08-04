[] (PointerVariable PointerType) ts (*train.TrainServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) train.TrainServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) ttype train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64} 
[_] (FieldVariable FieldType) ID string 
[__] (BasicVariable BasicType) ID string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = train, collection = train} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) ID string 

