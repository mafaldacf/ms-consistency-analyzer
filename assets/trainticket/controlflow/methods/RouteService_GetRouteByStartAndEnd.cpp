[] (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) start string // read(route_db), 

[] (BasicVariable BasicType) end string // read(route_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(route_db), 
[_] (StructVariable StructType) struct{ "$and" string,  primitive.A} // read(route_db), 
[__] (FieldVariable FieldType) primitive.A // read(route_db), 
[___] (SliceVariable UserType) primitive.A // read(route_db), 
[____] (SliceVariable UserType) primitive.D // read(route_db), 
[_____] (StructVariable StructType) struct{ "startstation" string,  string} // read(route_db), 
[______] (FieldVariable FieldType) string // read(route_db), 
[_______] (BasicVariable BasicType) start string // read(route_db), 
[____] (SliceVariable UserType) primitive.D // read(route_db), 
[_____] (StructVariable StructType) struct{ "endstation" string,  string} // read(route_db), 
[______] (FieldVariable FieldType) string // read(route_db), 
[_______] (BasicVariable BasicType) end string // read(route_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} // read(route_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

