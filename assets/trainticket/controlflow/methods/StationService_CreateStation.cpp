[] (PointerVariable PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase}) 
[_] (StructVariable UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) stationDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) station station.Station struct{ID string, Name string, StayTime int64} // write(station_db), 
[_] (FieldVariable FieldType) ID string // write(station_db), 
[__] (BasicVariable BasicType) ID string // write(station_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = station, collection = station} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string, ID string} 
[__] (FieldVariable FieldType) "id" string 
[___] (BasicVariable BasicType) "id" string 
[__] (FieldVariable FieldType) ID string // write(station_db), 
[___] (BasicVariable BasicType) ID string // write(station_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = station, collection = station} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) st station.Station struct{ID string, Name string, StayTime int64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

