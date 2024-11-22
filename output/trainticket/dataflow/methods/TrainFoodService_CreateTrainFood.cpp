[] (PointerObject PointerType) t (*trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(trainfood_db.TrainFood) {1}
[] (StructObject UserType) tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}
     --> w-tainted: write(trainfood_db.TrainFood.TripID) {1}
[_] (FieldObject FieldType) TripID string
      --> w-tainted: write(trainfood_db.TrainFood.TripID) {1}           --> w-tainted: write(trainfood_db.TrainFood.TripID) {1} --> r-tainted: read(trainfood_db._.tripid) {1}
[__] (BasicObject BasicType) TripID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = trainfood, collection = trainfood}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "tripid" string,  string}

    --> r-tainted: read(trainfood_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = trainfood, collection = trainfood}
     --> r-tainted: read(trainfood_db.TrainFood) {1}
[_] (StructObject UserType) stored_tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(trainfood_db.TrainFood) {1}
[] (StructObject UserType) stored_tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) ok bool

[] (InterfaceObject UserType) err .error

