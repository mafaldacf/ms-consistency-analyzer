[] (-1) (PointerVariable PointerType) t (*trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}} // write(trainfood_db), 
[_] (-1) (FieldVariable FieldType) TripID string // write(trainfood_db), 
[__] (-1) (BasicVariable BasicType) TripID string // write(trainfood_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = trainfood, collection = trainfood} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "tripid" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) TripID string // write(trainfood_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = trainfood, collection = trainfood} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) stored_tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) ok bool 

[] (-1) (InterfaceVariable UserType) err .error 

