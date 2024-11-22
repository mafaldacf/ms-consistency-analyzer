[] (PointerObject PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(assurance_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = assurance, collection = assurance}
     --> r-tainted: read(assurance_db.[]assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}) {1}
[_] (ArrayObject ArrayType) assurances []assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(assurance_db.[]assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}) {1}
[] (ArrayObject ArrayType) assurances []assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}

[] (InterfaceObject UserType) err .error

