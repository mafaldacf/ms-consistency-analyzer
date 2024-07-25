[] (PointerVariable PointerType) s (*stationfood.StationFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) stationfood.StationFoodServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ArrayVariable ArrayType) stations []string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = stationfood, collection = stationfood} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) doc primitive.A // read(stationfood_db), 

[] (SliceVariable UserType) query primitive.D // read(stationfood_db), 
[_] (StructVariable StructType) struct{ "stationname" string,  primitive.D} // read(stationfood_db), 
[__] (FieldVariable FieldType) primitive.D // read(stationfood_db), 
[___] (SliceVariable UserType) primitive.D // read(stationfood_db), 
[____] (StructVariable StructType) struct{ "$in" string,  primitive.A} // read(stationfood_db), 
[_____] (FieldVariable FieldType) primitive.A // read(stationfood_db), 
[______] (SliceVariable UserType) doc primitive.A // read(stationfood_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = stationfood, collection = stationfood} // read(stationfood_db), 

[] (InterfaceVariable UserType) err .error 

[] (ArrayVariable ArrayType) stores []stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}} 

[] (InterfaceVariable UserType) err .error 

