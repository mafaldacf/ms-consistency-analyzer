[] (PointerObject PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase})
[_] (StructObject UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase}
[__] (FieldObject FieldType) stationDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(station_db.Station) {1}
[] (StructObject UserType) station station.Station struct{ID string, Name string, StayTime int64}
     --> w-tainted: write(station_db.Station.ID) {1}
[_] (FieldObject FieldType) ID string
      --> w-tainted: write(station_db.Station.ID) {1}           --> w-tainted: write(station_db.Station.ID) {1} --> r-tainted: read(station_db._.id) {1}
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = station, collection = station}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

    --> r-tainted: read(station_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = station, collection = station}
     --> r-tainted: read(station_db.Station) {1}
[_] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(station_db.Station) {1}
[] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

