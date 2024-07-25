[] (PointerVariable PointerType) s (*stationfood.StationFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) stationfood.StationFoodServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) station string // read(stationfood_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = stationfood, collection = stationfood} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(stationfood_db), 
[_] (StructVariable StructType) struct{ "stationname" string,  string} // read(stationfood_db), 
[__] (FieldVariable FieldType) string // read(stationfood_db), 
[___] (BasicVariable BasicType) station string // read(stationfood_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = stationfood, collection = stationfood} // read(stationfood_db), 

[] (InterfaceVariable UserType) err .error 

[] (ArrayVariable ArrayType) stores []stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}} 

[] (InterfaceVariable UserType) err .error 

