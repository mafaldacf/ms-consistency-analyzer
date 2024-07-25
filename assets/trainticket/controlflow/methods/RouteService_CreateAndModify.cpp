[] (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) info route.RouteInfo struct{ID string, StartStation string, EndStation string, StationList string, DistanceList string} 
[_] (FieldVariable FieldType) StationList string 
[__] (BasicVariable BasicType) StationList string // write(route_db), 
[_] (FieldVariable FieldType) ID string 
[__] (BasicVariable BasicType) ID string // read(route_db), 
[_] (FieldVariable FieldType) StartStation string 
[__] (BasicVariable BasicType) StartStation string // write(route_db), 
[_] (FieldVariable FieldType) EndStation string 
[__] (BasicVariable BasicType) EndStation string // write(route_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (InterfaceVariable UserType) err .error 

[] (ArrayVariable SliceType) distances []int64 // write(route_db), 

[] (SliceVariable SliceType) stations []string // write(route_db), 
[_] (BasicVariable BasicType) StationList string // write(route_db), 
[_] (BasicVariable BasicType) "," string // write(route_db), 

[] (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} // write(route_db), 
[_] (FieldVariable FieldType) Distances []int64 // write(route_db), 
[__] (ArrayVariable SliceType) distances []int64 // write(route_db), 
[_] (FieldVariable FieldType) StartStation string // write(route_db), 
[__] (BasicVariable BasicType) StartStation string // write(route_db), 
[_] (FieldVariable FieldType) EndStation string // write(route_db), 
[__] (BasicVariable BasicType) EndStation string // write(route_db), 
[_] (FieldVariable FieldType) ID string // write(route_db), 
[__] (BasicVariable BasicType) ID string // read(route_db), 
[_] (FieldVariable FieldType) Stations []string // write(route_db), 
[__] (SliceVariable SliceType) stations []string // write(route_db), 
[___] (BasicVariable BasicType) StationList string // write(route_db), 
[___] (BasicVariable BasicType) "," string // write(route_db), 

[] (BasicVariable BasicType) old_exists false bool 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} // read(route_db), 

[] (InterfaceVariable UserType) err .error 

