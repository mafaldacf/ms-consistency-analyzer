[] (PointerObject PointerType) ts (*train.TrainServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) train.TrainServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(train_db.TrainType.Name) {1}
[] (BasicObject BasicType) name string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = train, collection = train}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "name" string,  string}

    --> r-tainted: read(train_db.TrainType) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = train, collection = train}
     --> r-tainted: read(train_db.TrainType) {1}
[_] (StructObject UserType) tt train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(train_db.TrainType) {1}
[] (StructObject UserType) tt train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

