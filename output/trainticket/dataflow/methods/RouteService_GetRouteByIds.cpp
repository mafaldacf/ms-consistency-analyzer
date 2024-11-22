[] (PointerObject PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) route.RouteServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (ArrayObject ArrayType) ids []string

[] (ArrayObject ArrayType) routes []route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}
[_] (StructObject UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}
      --> r-tainted: read(route_db.Route) {1}
[__] (Reference UserType) ref <route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}> @ GetRouteById

[] (StructObject UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}
     --> r-tainted: read(route_db.Route) {1}
[_] (Reference UserType) ref <route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}> @ GetRouteById

[] (InterfaceObject UserType) _ .error
[_] (Reference BasicType) ref <nil> @ GetRouteById

[] (ArrayObject ArrayType) routes []route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}
[_] (StructObject UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}

