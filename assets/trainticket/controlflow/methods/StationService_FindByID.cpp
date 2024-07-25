[] (PointerVariable PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase}) 
[_] (StructVariable UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) stationDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ StationService 

[] (BasicVariable BasicType) id string 
[_] (Reference BasicType) ref <string> @ StationService 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = station, collection = station} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) id string 
[____] (Reference BasicType) ref <string> @ StationService 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = station, collection = station} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) st station.Station struct{ID string, Name string, StayTime int64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

