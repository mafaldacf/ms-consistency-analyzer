[] (-1) (PointerVariable PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) stationDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) station station.Station struct{ID string, Name string, StayTime int64} // write(station_db), 
[_] (-1) (FieldVariable FieldType) ID string // write(station_db), 
[__] (-1) (BasicVariable BasicType) ID string // write(station_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = station, collection = station} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) ID string // write(station_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = station, collection = station} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) st station.Station struct{ID string, Name string, StayTime int64} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

