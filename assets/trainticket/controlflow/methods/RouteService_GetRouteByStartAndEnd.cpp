[] (-1) (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) start string // read(route_db), 

[] (-1) (BasicVariable BasicType) end string // read(route_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(route_db), 
[_] (0) (StructVariable StructType) struct{ "$and" string,  primitive.A} // read(route_db), 
[__] (0) (FieldVariable FieldType) primitive.A // read(route_db), 
[___] (0) (SliceVariable UserType) primitive.A // read(route_db), 
[____] (0) (SliceVariable UserType) primitive.D // read(route_db), 
[_____] (0) (StructVariable StructType) struct{ "startstation" string,  string} // read(route_db), 
[______] (0) (FieldVariable FieldType) string // read(route_db), 
[_______] (-1) (BasicVariable BasicType) start string // read(route_db), 
[____] (0) (SliceVariable UserType) primitive.D // read(route_db), 
[_____] (0) (StructVariable StructType) struct{ "endstation" string,  string} // read(route_db), 
[______] (0) (FieldVariable FieldType) string // read(route_db), 
[_______] (-1) (BasicVariable BasicType) end string // read(route_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} // read(route_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

