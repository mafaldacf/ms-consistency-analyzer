[] (PointerObject PointerType) t (*trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(trainfood_db._.tripid) {1}
[] (BasicObject BasicType) tripid string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = trainfood, collection = trainfood}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(trainfood_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = trainfood, collection = trainfood}
     --> r-tainted: read(trainfood_db.TrainFood, trainfood_db.Foods, trainfood_db.[]food.Food struct{Name string, Price float64}) {3}
[_] (StructObject UserType) tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}
      --> r-tainted: read(trainfood_db.Foods) {1}
[__] (FieldObject FieldType) Foods []food.Food struct{Name string, Price float64}
       --> r-tainted: read(trainfood_db.[]food.Food struct{Name string, Price float64}) {1}
[___] (SliceObject SliceType) Foods []food.Food struct{Name string, Price float64}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(trainfood_db.TrainFood, trainfood_db.Foods, trainfood_db.[]food.Food struct{Name string, Price float64}) {3}
[] (StructObject UserType) tf trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}
     --> r-tainted: read(trainfood_db.Foods) {1}
[_] (FieldObject FieldType) Foods []food.Food struct{Name string, Price float64}
      --> r-tainted: read(trainfood_db.[]food.Food struct{Name string, Price float64}) {1}
[__] (SliceObject SliceType) Foods []food.Food struct{Name string, Price float64}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

