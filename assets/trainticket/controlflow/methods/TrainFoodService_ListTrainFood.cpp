[] (-1) (PointerVariable PointerType) t (*trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = trainfood, collection = trainfood} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = trainfood, collection = trainfood} // read(trainfood_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (ArrayVariable ArrayType) all_foods []trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}} 

[] (-1) (InterfaceVariable UserType) err .error 

