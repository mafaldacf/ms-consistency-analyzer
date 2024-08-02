[] (-1) (PointerVariable PointerType) s (*station.StationServiceImpl struct{stationDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) station.StationServiceImpl struct{stationDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) stationDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (12) (Reference UserType) ref <ctx context.Context> @ StationService 

[] (0) (BasicVariable BasicType) id string 
[_] (13) (Reference BasicType) ref <string> @ StationService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = station, collection = station} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (0) (BasicVariable BasicType) id string 
[____] (13) (Reference BasicType) ref <string> @ StationService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = station, collection = station} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) st station.Station struct{ID string, Name string, StayTime int64} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

