[] (-1) (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) info route.RouteInfo struct{ID string, StartStation string, EndStation string, StationList string, DistanceList string} 
[_] (-1) (FieldVariable FieldType) StationList string 
[__] (-1) (BasicVariable BasicType) StationList string // write(route_db), 
[_] (-1) (FieldVariable FieldType) ID string 
[__] (-1) (BasicVariable BasicType) ID string 
[_] (-1) (FieldVariable FieldType) StartStation string 
[__] (-1) (BasicVariable BasicType) StartStation string // write(route_db), 
[_] (-1) (FieldVariable FieldType) EndStation string 
[__] (-1) (BasicVariable BasicType) EndStation string // write(route_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (ArrayVariable SliceType) distances []int64 // write(route_db), 

[] (-1) (SliceVariable SliceType) stations []string // write(route_db), 
[_] (-1) (BasicVariable BasicType) StationList string // write(route_db), 
[_] (0) (BasicVariable BasicType) "," string // write(route_db), 

[] (-1) (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} // write(route_db), 
[_] (-1) (FieldVariable FieldType) EndStation string // write(route_db), 
[__] (-1) (BasicVariable BasicType) EndStation string // write(route_db), 
[_] (-1) (FieldVariable FieldType) ID string // write(route_db), 
[__] (-1) (BasicVariable BasicType) ID string 
[_] (-1) (FieldVariable FieldType) Stations []string // write(route_db), 
[__] (-1) (SliceVariable SliceType) stations []string // write(route_db), 
[___] (-1) (BasicVariable BasicType) StationList string // write(route_db), 
[___] (0) (BasicVariable BasicType) "," string // write(route_db), 
[_] (-1) (FieldVariable FieldType) Distances []int64 // write(route_db), 
[__] (-1) (ArrayVariable SliceType) distances []int64 // write(route_db), 
[_] (-1) (FieldVariable FieldType) StartStation string // write(route_db), 
[__] (-1) (BasicVariable BasicType) StartStation string // write(route_db), 

[] (-1) (BasicVariable BasicType) old_exists false bool 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} 

[] (-1) (InterfaceVariable UserType) err .error 

