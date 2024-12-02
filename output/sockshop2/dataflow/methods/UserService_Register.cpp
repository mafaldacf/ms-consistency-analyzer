[0] (PointerObject PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase})
[_1] (StructObject UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}
[__2] (FieldObject FieldType) db NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context

[0] (BasicObject BasicType) username string

[0] (BasicObject BasicType) password string

[0] (BasicObject BasicType) email string

[0] (BasicObject BasicType) first string

[0] (BasicObject BasicType) last string

[0] (StructObject UserType) u user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}
[_1] (FieldObject FieldType) Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[__2] (StructObject UserType) user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[_1] (FieldObject FieldType) Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}
[__2] (StructObject UserType) user.Card struct{LongNum string, Expires string, CCV string, ID string}
[_1] (FieldObject FieldType) Email string
[__2] (BasicObject BasicType) email string
[_1] (FieldObject FieldType) FirstName string
[__2] (BasicObject BasicType) first string
[_1] (FieldObject FieldType) LastName string
[__2] (BasicObject BasicType) last string
[_1] (FieldObject FieldType) Password string
[__2] (BasicObject BasicType) password string
[_1] (FieldObject FieldType) UserID string
[__2] (BasicObject BasicType) UserID string
[_1] (FieldObject FieldType) Username string
[__2] (BasicObject BasicType) username string

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[0] (InterfaceObject UserType) _ .error

