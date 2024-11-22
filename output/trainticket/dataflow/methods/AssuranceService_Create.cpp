[] (PointerObject PointerType) a (*assurance.AssuranceServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) assurance.AssuranceServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) typeindex int64

    --> w-tainted: write(assurance_db.Assurance.OrderID) {1}
[] (BasicObject BasicType) orderid string

    --> w-tainted: write(assurance_db.Assurance.AT) {1}
[] (StructObject UserType) at assurance.AssuranceType struct{Index int64, Name string, Price float64}
     --> w-tainted: write(assurance_db.Assurance.AT) {1}
[_] (Reference UserType) ref <assurance.AssuranceType struct{Index int64, Name string, Price float64}> @ getAssuranceType

[] (InterfaceObject UserType) err .error
[_] (Reference BasicType) ref <nil> @ getAssuranceType

    --> w-tainted: write(assurance_db.Assurance.ID) {1}
[] (BasicObject BasicType) id string

    --> w-tainted: write(assurance_db.Assurance) {1}
[] (StructObject UserType) assurance assurance.Assurance struct{ID string, OrderID string, AT assurance.AssuranceType struct{Index int64, Name string, Price float64}}
     --> w-tainted: write(assurance_db.Assurance.AT) {1}
[_] (FieldObject FieldType) AT assurance.AssuranceType struct{Index int64, Name string, Price float64}
      --> w-tainted: write(assurance_db.Assurance.AT) {1}
[__] (StructObject UserType) at assurance.AssuranceType struct{Index int64, Name string, Price float64}
       --> w-tainted: write(assurance_db.Assurance.AT) {1}
[___] (Reference UserType) ref <assurance.AssuranceType struct{Index int64, Name string, Price float64}> @ getAssuranceType
     --> w-tainted: write(assurance_db.Assurance.ID) {1}
[_] (FieldObject FieldType) ID string
      --> w-tainted: write(assurance_db.Assurance.ID) {1}
[__] (BasicObject BasicType) id string
     --> w-tainted: write(assurance_db.Assurance.OrderID) {1}
[_] (FieldObject FieldType) OrderID string
      --> w-tainted: write(assurance_db.Assurance.OrderID) {1}
[__] (BasicObject BasicType) orderid string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = assurance, collection = assurance}

[] (InterfaceObject UserType) err .error

