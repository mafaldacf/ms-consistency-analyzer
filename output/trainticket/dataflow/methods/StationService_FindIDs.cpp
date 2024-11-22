[] (PointerObject PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase})
[_] (StructObject UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase}
[__] (FieldObject FieldType) stationDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (ArrayObject ArrayType) names []string

[] (ArrayObject ArrayType) ids []string
[_] (BasicObject BasicType) id string
      --> r-tainted: read(station_db.string) {1}
[__] (Reference BasicType) ref <ID string> @ FindID

[] (BasicObject BasicType) id string
     --> r-tainted: read(station_db.string) {1}
[_] (Reference BasicType) ref <ID string> @ FindID

[] (InterfaceObject UserType) _ .error
[_] (Reference BasicType) ref <nil> @ FindID

[] (ArrayObject ArrayType) ids []string
[_] (BasicObject BasicType) id string

