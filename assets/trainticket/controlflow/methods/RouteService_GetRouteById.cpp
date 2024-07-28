[] (-1) (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (19) (Reference UserType) ref <ctx context.Context> @ RouteService 

[] (0) (BasicVariable BasicType) id string // read(route_db), 
[_] (20) (Reference BasicType) ref <string> @ RouteService // read(route_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} // read(route_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

