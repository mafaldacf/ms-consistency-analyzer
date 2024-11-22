[] (PointerObject PointerType) ts (*train.TrainServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) train.TrainServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(train_db.[]train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64}) {1}
[] (ArrayObject ArrayType) trains []train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64}

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = train, collection = train}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(train_db.TrainType) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = train, collection = train}
     --> r-tainted: read(train_db.[]train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64}) {1}
[_] (ArrayObject ArrayType) trains []train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64}

[] (InterfaceObject UserType) err .error

[] (InterfaceObject UserType) err .error

