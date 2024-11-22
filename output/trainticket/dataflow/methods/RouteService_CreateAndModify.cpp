[] (PointerObject PointerType) r (*route.RouteServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) route.RouteServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) info route.RouteInfo struct{ID string, StartStation string, EndStation string, StationList string, DistanceList string}
[_] (FieldObject FieldType) EndStation string
      --> w-tainted: write(route_db.Route.EndStation) {1}
[__] (BasicObject BasicType) EndStation string
[_] (FieldObject FieldType) ID string
      --> r-tainted: read(route_db.Route.ID) {1}
[__] (BasicObject BasicType) ID string
[_] (FieldObject FieldType) StartStation string
      --> w-tainted: write(route_db.Route.StartStation) {1}
[__] (BasicObject BasicType) StartStation string
[_] (FieldObject FieldType) StationList string
      --> w-tainted: write(route_db.Route.Stations) {1}
[__] (BasicObject BasicType) StationList string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = route, collection = route}

[] (InterfaceObject UserType) err .error

    --> w-tainted: write(route_db.Route.Distances) {1}
[] (ArrayObject SliceType) distances []int64

    --> w-tainted: write(route_db.Route.Stations) {1}
[] (SliceObject SliceType) stations []string
     --> w-tainted: write(route_db.Route.Stations) {1}
[_] (BasicObject BasicType) StationList string
     --> w-tainted: write(route_db.Route.Stations) {1}
[_] (BasicObject BasicType) "," string

    --> w-tainted: write(route_db.Route) {1}
[] (StructObject UserType) route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}
     --> w-tainted: write(route_db.Route.Distances) {1}
[_] (FieldObject FieldType) Distances []int64
      --> w-tainted: write(route_db.Route.Distances) {1}
[__] (ArrayObject SliceType) distances []int64
     --> w-tainted: write(route_db.Route.EndStation) {1}
[_] (FieldObject FieldType) EndStation string
      --> w-tainted: write(route_db.Route.EndStation) {1}
[__] (BasicObject BasicType) EndStation string
     --> w-tainted: write(route_db.Route.ID) {1}
[_] (FieldObject FieldType) ID string
      --> r-tainted: read(route_db.Route.ID) {1}
[__] (BasicObject BasicType) ID string
     --> w-tainted: write(route_db.Route.StartStation) {1}
[_] (FieldObject FieldType) StartStation string
      --> w-tainted: write(route_db.Route.StartStation) {1}
[__] (BasicObject BasicType) StartStation string
     --> w-tainted: write(route_db.Route.Stations) {1}
[_] (FieldObject FieldType) Stations []string
      --> w-tainted: write(route_db.Route.Stations) {1}
[__] (SliceObject SliceType) stations []string
       --> w-tainted: write(route_db.Route.Stations) {1}
[___] (BasicObject BasicType) StationList string
       --> w-tainted: write(route_db.Route.Stations) {1}
[___] (BasicObject BasicType) "," string

[] (BasicObject BasicType) MAXIDLEN 32 int

[] (BasicObject BasicType) old_exists false bool

    --> r-tainted: read(route_db.Route) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = route, collection = route}
     --> r-tainted: read(route_db.Route, route_db.ID, route_db.string) {3}
[_] (StructObject UserType) old_route route.Route struct{ID string, Stations []string, Distances []int64, StartStation string, EndStation string}
      --> r-tainted: read(route_db.ID) {1}
[__] (FieldObject FieldType) ID string
       --> r-tainted: read(route_db.string) {1}
[___] (BasicObject BasicType) ID string

[] (InterfaceObject UserType) err .error

