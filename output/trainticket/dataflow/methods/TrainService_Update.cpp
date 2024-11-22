[] (PointerObject PointerType) ts (*train.TrainServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) train.TrainServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) ttype train.TrainType struct{ID string, Name string, EconomyClass int64, ComfortClass int64, AvgSpeed int64}
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = train, collection = train}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

