[0] (PointerObject PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase})
[_1] (StructObject UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase}
[__2] (FieldObject FieldType) stationDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ StationService

    --> r-tainted: read(station_db._.id, station_db.Station.ID) {2}
[0] (BasicObject BasicType) id string
     --> r-tainted: read(station_db._.id, station_db.Station.ID) {2}
[_1] (Reference BasicType) ref <string> @ StationService

[0] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = station, collection = station}

[0] (InterfaceObject UserType) err .error

[0] (SliceObject UserType) query primitive.D
[_1] (StructObject StructType) struct{ string,  "id" string,  string}

    --> r-tainted: read(station_db._, station_db.Station) {2}
[0] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = station, collection = station}
     --> r-tainted: read(station_db.Station) {1}
[_1] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(station_db.Station) {1}
[0] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

