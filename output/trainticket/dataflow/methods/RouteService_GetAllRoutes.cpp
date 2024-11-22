[] (PointerObject PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) route.RouteServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(route_db.[]route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}) {1}
[] (ArrayObject ArrayType) routes []route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}

[] (BasicObject BasicType) err error

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = route, collection = route}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(route_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = route, collection = route}
     --> r-tainted: read(route_db.[]route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}) {1}
[_] (ArrayObject ArrayType) routes []route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}

[] (InterfaceObject UserType) err .error

[] (InterfaceObject UserType) err .error

