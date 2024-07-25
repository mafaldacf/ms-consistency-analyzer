[] (PointerVariable PointerType) t (*trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) tripid string // read(trainfood_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = trainfood, collection = trainfood} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = trainfood, collection = trainfood} // read(trainfood_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

