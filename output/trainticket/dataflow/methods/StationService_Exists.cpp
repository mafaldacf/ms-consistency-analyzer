[] (PointerObject PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase})
[_] (StructObject UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase}
[__] (FieldObject FieldType) stationDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(station_db.Station.Name) {1}
[] (BasicObject BasicType) name string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = station, collection = station}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "name" string,  string}

    --> r-tainted: read(station_db.Station) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = station, collection = station}
     --> r-tainted: read(station_db.Station) {1}
[_] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(station_db.Station) {1}
[] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

