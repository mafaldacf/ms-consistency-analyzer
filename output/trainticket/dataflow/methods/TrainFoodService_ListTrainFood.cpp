[] (PointerObject PointerType) t (*trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) trainfood.TrainFoodServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = trainfood, collection = trainfood}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(trainfood_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = trainfood, collection = trainfood}
     --> r-tainted: read(trainfood_db.[]trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}) {1}
[_] (ArrayObject ArrayType) all_foods []trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(trainfood_db.[]trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}) {1}
[] (ArrayObject ArrayType) all_foods []trainfood.TrainFood struct{ID string, TripID string, Foods []food.Food struct{Name string, Price float64}}

[] (InterfaceObject UserType) err .error

