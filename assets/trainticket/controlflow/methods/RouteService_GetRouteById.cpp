[] (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ RouteService 

[] (BasicVariable BasicType) id string // read(route_db), 
[_] (Reference BasicType) ref <string> @ RouteService // read(route_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} // read(route_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

