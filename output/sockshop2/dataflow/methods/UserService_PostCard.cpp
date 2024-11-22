[] (PointerObject PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase})
[_] (StructObject UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) userid string

[] (StructObject UserType) card user.Card struct{LongNum string, Expires string, CCV string, ID string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{Key "userid" string, Value string}
[__] (FieldObject FieldType) Key "userid" string
[___] (BasicObject BasicType) "userid" string
[__] (FieldObject FieldType) Value string
[___] (BasicObject BasicType) userid string

[] (SliceObject UserType) update primitive.D
[_] (StructObject StructType) struct{Key "card" string, Value user.Card struct{LongNum string, Expires string, CCV string, ID string}}
[__] (FieldObject FieldType) Key "card" string
[___] (BasicObject BasicType) "card" string
[__] (FieldObject FieldType) Value user.Card struct{LongNum string, Expires string, CCV string, ID string}
[___] (StructObject UserType) card user.Card struct{LongNum string, Expires string, CCV string, ID string}

