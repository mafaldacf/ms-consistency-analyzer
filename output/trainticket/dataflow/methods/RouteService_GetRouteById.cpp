[] (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ RouteService 

[] (BasicVariable BasicType) id string 
[_] (Reference BasicType) ref <string> @ RouteService 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

