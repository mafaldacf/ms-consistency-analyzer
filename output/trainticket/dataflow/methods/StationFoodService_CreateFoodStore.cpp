[] (PointerObject PointerType) s (*stationfood.StationFoodServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) stationfood.StationFoodServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(stationfood_db.StationFoodStore) {1}
[] (StructObject UserType) store stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}}
     --> w-tainted: write(stationfood_db.StationFoodStore.ID) {1}
[_] (FieldObject FieldType) ID string
      --> w-tainted: write(stationfood_db.StationFoodStore.ID) {1}           --> w-tainted: write(stationfood_db.StationFoodStore.ID) {1} --> r-tainted: read(stationfood_db._.id) {1}
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = stationfood, collection = stationfood}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

    --> r-tainted: read(stationfood_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = stationfood, collection = stationfood}
     --> r-tainted: read(stationfood_db.StationFoodStore) {1}
[_] (StructObject UserType) st stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(stationfood_db.StationFoodStore) {1}
[] (StructObject UserType) st stationfood.StationFoodStore struct{ID string, StationName string, StoreName string, Telephone string, BusinessTime string, DeliveryFee float64, Foods []food.Food struct{Name string, Price float64}}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

