[] (PointerObject PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase})
[_] (StructObject UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) u user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}
[_] (FieldObject FieldType) UserID string
[__] (BasicObject BasicType) UserID string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[] (InterfaceObject UserType) _ .error

