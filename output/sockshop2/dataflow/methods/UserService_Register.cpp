[] (PointerObject PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase})
[_] (StructObject UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) username string

[] (BasicObject BasicType) password string

[] (BasicObject BasicType) email string

[] (BasicObject BasicType) first string

[] (BasicObject BasicType) last string

[] (StructObject UserType) u user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}
[_] (FieldObject FieldType) Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[__] (StructObject UserType) user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[_] (FieldObject FieldType) Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}
[__] (StructObject UserType) user.Card struct{LongNum string, Expires string, CCV string, ID string}
[_] (FieldObject FieldType) Email string
[__] (BasicObject BasicType) email string
[_] (FieldObject FieldType) FirstName string
[__] (BasicObject BasicType) first string
[_] (FieldObject FieldType) LastName string
[__] (BasicObject BasicType) last string
[_] (FieldObject FieldType) Password string
[__] (BasicObject BasicType) password string
[_] (FieldObject FieldType) UserID string
[__] (BasicObject BasicType) UserID string
[_] (FieldObject FieldType) Username string
[__] (BasicObject BasicType) username string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[] (InterfaceObject UserType) _ .error

