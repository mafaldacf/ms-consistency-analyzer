[] (-1) (PointerVariable PointerType) s (*stationfood.StationFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) stationfood.StationFoodServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ArrayVariable ArrayType) stations []string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = stationfood, collection = stationfood} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) doc primitive.A // read(stationfood_db), 

[] (-1) (SliceVariable UserType) query primitive.D // read(stationfood_db), 
[_] (0) (StructVariable StructType) struct{ "stationname" string,  primitive.D} // read(stationfood_db), 
[__] (0) (FieldVariable FieldType) primitive.D // read(stationfood_db), 
[___] (0) (SliceVariable UserType) primitive.D // read(stationfood_db), 
[____] (0) (StructVariable StructType) struct{ "$in" string,  primitive.A} // read(stationfood_db), 
[_____] (0) (FieldVariable FieldType) primitive.A // read(stationfood_db), 
[______] (-1) (SliceVariable UserType) doc primitive.A // read(stationfood_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = stationfood, collection = stationfood} // read(stationfood_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (ArrayVariable ArrayType) stores []stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}} 

[] (-1) (InterfaceVariable UserType) err .error 

