[] (PointerObject PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase})
[_] (StructObject UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase}
[__] (FieldObject FieldType) stationDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (ArrayObject ArrayType) ids []string

[] (ArrayObject ArrayType) stations []station.Station struct{ID string, Name string, StayTime int64}
[_] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}
      --> r-tainted: read(station_db.Station) {1}
[__] (Reference UserType) ref <st station.Station struct{ID string, Name string, StayTime int64}> @ FindByID

[] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}
     --> r-tainted: read(station_db.Station) {1}
[_] (Reference UserType) ref <st station.Station struct{ID string, Name string, StayTime int64}> @ FindByID

[] (InterfaceObject UserType) _ .error
[_] (Reference BasicType) ref <nil> @ FindByID

[] (ArrayObject ArrayType) stations []station.Station struct{ID string, Name string, StayTime int64}
[_] (StructObject UserType) st station.Station struct{ID string, Name string, StayTime int64}

