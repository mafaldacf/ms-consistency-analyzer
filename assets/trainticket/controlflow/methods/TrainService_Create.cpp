[] (-1) (PointerVariable PointerType) ts (*train.TrainServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) train.TrainServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) tt train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64} // write(train_db), 
[_] (-1) (FieldVariable FieldType) Name string // write(train_db), 
[__] (-1) (BasicVariable BasicType) Name string // write(train_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = train, collection = train} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "name" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) Name string // write(train_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = train, collection = train} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) saved_tt train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (InterfaceVariable UserType) err .error 

