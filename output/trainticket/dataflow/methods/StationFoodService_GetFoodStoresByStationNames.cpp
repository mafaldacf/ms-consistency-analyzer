[] (PointerVariable PointerType) s (*stationfood.StationFoodServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) stationfood.StationFoodServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ArrayVariable ArrayType) stations []string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = stationfood, collection = stationfood} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) doc primitive.A 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "stationname" string,  primitive.D} 
[__] (FieldVariable FieldType) primitive.D 
[___] (SliceVariable UserType) primitive.D 
[____] (StructVariable StructType) struct{ "$in" string,  primitive.A} 
[_____] (FieldVariable FieldType) primitive.A 
[______] (SliceVariable UserType) doc primitive.A 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = stationfood, collection = stationfood} 

[] (InterfaceVariable UserType) err .error 

[] (ArrayVariable ArrayType) stores []stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}} 

[] (InterfaceVariable UserType) err .error 

