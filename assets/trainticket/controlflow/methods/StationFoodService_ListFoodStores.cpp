[] (PointerVariable PointerType) s (*stationfood.StationFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) stationfood.StationFoodServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = stationfood, collection = stationfood} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = stationfood, collection = stationfood} // read(stationfood_db), 

[] (InterfaceVariable UserType) err .error 

[] (ArrayVariable ArrayType) stores []stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}} 

[] (InterfaceVariable UserType) err .error 

