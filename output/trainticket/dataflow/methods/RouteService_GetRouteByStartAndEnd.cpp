[] (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) start string 

[] (BasicVariable BasicType) end string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "$and" string,  primitive.A} 
[__] (FieldVariable FieldType) primitive.A 
[___] (SliceVariable UserType) primitive.A 
[____] (SliceVariable UserType) primitive.D 
[_____] (StructVariable StructType) struct{ "startstation" string,  string} 
[______] (FieldVariable FieldType) string 
[_______] (BasicVariable BasicType) start string 
[____] (SliceVariable UserType) primitive.D 
[_____] (StructVariable StructType) struct{ "endstation" string,  string} 
[______] (FieldVariable FieldType) string 
[_______] (BasicVariable BasicType) end string 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

