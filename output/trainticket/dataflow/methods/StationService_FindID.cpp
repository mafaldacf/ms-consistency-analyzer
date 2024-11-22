[] (PointerObject PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase})
[_] (StructObject UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase}
[__] (FieldObject FieldType) stationDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ StationService

    --> r-tainted: read(station_db.Station.Name) {1}
[] (BasicObject BasicType) name string
     --> r-tainted: read(station_db.Station.Name) {1}
[_] (Reference BasicType) ref <string> @ StationService

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = station, collection = station}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "name" string,  string}

    --> r-tainted: read(station_db.Station) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = station, collection = station}
     --> r-tainted: read(station_db.Station, station_db.ID, station_db.string) {3}
[_] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}
      --> r-tainted: read(station_db.ID) {1}
[__] (FieldObject FieldType) ID string
       --> r-tainted: read(station_db.string) {1}
[___] (BasicObject BasicType) ID string

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(station_db.Station, station_db.ID, station_db.string) {3}
[] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}
     --> r-tainted: read(station_db.ID) {1}
[_] (FieldObject FieldType) ID string
      --> r-tainted: read(station_db.string) {1}
[__] (BasicObject BasicType) ID string

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

