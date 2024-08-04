[] (PointerVariable PointerType) ts (*train.TrainServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) train.TrainServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) tt train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64} // write(train_db), 
[_] (FieldVariable FieldType) Name string // write(train_db), 
[__] (BasicVariable BasicType) Name string // write(train_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = train, collection = train} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "name" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) Name string // write(train_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = train, collection = train} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) saved_tt train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

[] (InterfaceVariable UserType) err .error 

