[] (PointerVariable PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase}) 
[_] (StructVariable UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) stationDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) name string // read(station_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = station, collection = station} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(station_db), 
[_] (StructVariable StructType) struct{ "name" string,  string} // read(station_db), 
[__] (FieldVariable FieldType) string // read(station_db), 
[___] (BasicVariable BasicType) name string // read(station_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = station, collection = station} // read(station_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) st station.Station struct{ID string, Name string, StayTime int64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

