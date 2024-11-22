[] (PointerObject PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase})
[_] (StructObject UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) username string

[] (BasicObject BasicType) password string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "username" string, Value string}
[__] (FieldObject FieldType) Key "username" string
[___] (BasicObject BasicType) "username" string
[__] (FieldObject FieldType) Value string
[___] (BasicObject BasicType) username string

[] (SliceObject UserType) projection primitive.D
[_] (StructObject StructType) struct{Key "password" string, Value true bool}
[__] (FieldObject FieldType) Key "password" string
[___] (BasicObject BasicType) "password" string
[__] (FieldObject FieldType) Value true bool
[___] (BasicObject BasicType) true bool

[] (StructObject UserType) user user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}

[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = users, collection = users}
[_] (StructObject UserType) user user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}

[] (InterfaceObject UserType) _ .error

