[] (PointerObject PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase})
[_] (StructObject UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) userid string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[] (InterfaceObject UserType) _ .error

[] (ArrayObject ArrayType) users []user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{Key "userid" string, Value string}
[__] (FieldObject FieldType) Key "userid" string
[___] (BasicObject BasicType) "userid" string
[__] (FieldObject FieldType) Value string
[___] (BasicObject BasicType) userid string

[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = users, collection = users}
[_] (ArrayObject ArrayType) users []user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}

[] (InterfaceObject UserType) _ .error

