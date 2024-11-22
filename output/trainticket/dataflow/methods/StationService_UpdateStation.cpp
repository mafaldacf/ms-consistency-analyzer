[] (PointerObject PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase})
[_] (StructObject UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase}
[__] (FieldObject FieldType) stationDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) station station.Station struct{ID string, Name string, StayTime int64}
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = station, collection = station}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

