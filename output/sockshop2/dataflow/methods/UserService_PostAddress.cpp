[] (PointerObject PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase})
[_] (StructObject UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) userid string

[] (StructObject UserType) address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{Key "userid" string, Value string}
[__] (FieldObject FieldType) Key "userid" string
[___] (BasicObject BasicType) "userid" string
[__] (FieldObject FieldType) Value string
[___] (BasicObject BasicType) userid string

[] (SliceObject UserType) update primitive.D
[_] (StructObject StructType) struct{Key "address" string, Value user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}}
[__] (FieldObject FieldType) Key "address" string
[___] (BasicObject BasicType) "address" string
[__] (FieldObject FieldType) Value user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[___] (StructObject UserType) address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}

