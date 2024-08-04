[] (PointerVariable PointerType) t (*trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}} // write(trainfood_db), 
[_] (FieldVariable FieldType) TripID string // write(trainfood_db), 
[__] (BasicVariable BasicType) TripID string // write(trainfood_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = trainfood, collection = trainfood} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "tripid" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) TripID string // write(trainfood_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = trainfood, collection = trainfood} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) stored_tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) ok bool 

[] (InterfaceVariable UserType) err .error 

