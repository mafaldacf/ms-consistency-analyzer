[] (PointerVariable PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase}) 
[_] (StructVariable UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) stationDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) station station.Station struct{ID string, Name string, StayTime int64} 
[_] (FieldVariable FieldType) ID string 
[__] (BasicVariable BasicType) ID string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = station, collection = station} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) ID string 

