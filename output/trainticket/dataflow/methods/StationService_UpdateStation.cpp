[] (-1) (PointerVariable PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) stationDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) station station.Station struct{ID string, Name string, StayTime int64} 
[_] (-1) (FieldVariable FieldType) ID string 
[__] (-1) (BasicVariable BasicType) ID string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = station, collection = station} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) ID string 

