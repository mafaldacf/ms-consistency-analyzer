[] (PointerObject PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(assurance_db._.orderid) {1}
[] (BasicObject BasicType) order_id string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "orderid" string,  string}

    --> r-tainted: read(assurance_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = assurance, collection = assurance}
     --> r-tainted: read(assurance_db.Assurance) {1}
[_] (StructObject UserType) ass assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(assurance_db.Assurance) {1}
[] (StructObject UserType) ass assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

