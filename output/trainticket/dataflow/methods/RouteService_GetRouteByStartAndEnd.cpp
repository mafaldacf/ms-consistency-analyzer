[] (-1) (PointerVariable PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) route.RouteServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) start string 

[] (-1) (BasicVariable BasicType) end string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = route, collection = route} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "$and" string,  primitive.A} 
[__] (0) (FieldVariable FieldType) primitive.A 
[___] (0) (SliceVariable UserType) primitive.A 
[____] (0) (SliceVariable UserType) primitive.D 
[_____] (0) (StructVariable StructType) struct{ "startstation" string,  string} 
[______] (0) (FieldVariable FieldType) string 
[_______] (-1) (BasicVariable BasicType) start string 
[____] (0) (SliceVariable UserType) primitive.D 
[_____] (0) (StructVariable StructType) struct{ "endstation" string,  string} 
[______] (0) (FieldVariable FieldType) string 
[_______] (-1) (BasicVariable BasicType) end string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = route, collection = route} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

