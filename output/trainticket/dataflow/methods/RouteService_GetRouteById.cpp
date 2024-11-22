[] (PointerObject PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) route.RouteServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ RouteService

    --> r-tainted: read(route_db._.id) {1}
[] (BasicObject BasicType) id string
     --> r-tainted: read(route_db._.id) {1}
[_] (Reference BasicType) ref <string> @ RouteService

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = route, collection = route}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(route_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = route, collection = route}
     --> r-tainted: read(route_db.Route) {1}
[_] (StructObject UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(route_db.Route) {1}
[] (StructObject UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

