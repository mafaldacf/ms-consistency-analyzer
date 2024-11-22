[] (PointerObject PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) assurance assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}
[_] (FieldObject FieldType) ID string
      --> r-tainted: read(assurance_db._.id) {1}
[__] (BasicObject BasicType) ID string

[] (StructObject UserType) _ assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}
     --> r-tainted: read(assurance_db.Assurance) {1}
[_] (Reference UserType) ref <ass assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}> @ FindAssuranceById

[] (InterfaceObject UserType) err .error
[_] (Reference BasicType) ref <nil> @ FindAssuranceById

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

[] (BasicObject BasicType) ok bool

[] (InterfaceObject UserType) err .error

