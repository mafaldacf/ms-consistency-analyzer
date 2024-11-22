[] (PointerObject PointerType) s (*stationfood.StationFoodServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) stationfood.StationFoodServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (ArrayObject ArrayType) stations []string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = stationfood, collection = stationfood}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) doc primitive.A

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "stationname" string,  primitive.D}

    --> r-tainted: read(stationfood_db.StationFoodStore) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = stationfood, collection = stationfood}
     --> r-tainted: read(stationfood_db.[]stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}}) {1}
[_] (ArrayObject ArrayType) stores []stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(stationfood_db.[]stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}}) {1}
[] (ArrayObject ArrayType) stores []stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}}

[] (InterfaceObject UserType) err .error

