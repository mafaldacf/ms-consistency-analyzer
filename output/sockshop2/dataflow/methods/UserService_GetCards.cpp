[0] (PointerObject PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase})
[_1] (StructObject UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}
[__2] (FieldObject FieldType) db NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context

[0] (BasicObject BasicType) cardid string

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[0] (InterfaceObject UserType) _ .error

[0] (ArrayObject ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string}

[0] (SliceObject UserType) filter primitive.D
[_1] (StructObject StructType) struct{Key "addressid" string, Key "addressid" string, Value string, Value string}
[__2] (FieldObject FieldType) Key "addressid" string
[___3] (BasicObject BasicType) "addressid" string
[__2] (FieldObject FieldType) Value string
[___3] (BasicObject BasicType) cardid string

[0] (SliceObject UserType) projection primitive.D
[_1] (StructObject StructType) struct{Key "addressid" string, Key "addressid" string, Value true bool, Value true bool}
[__2] (FieldObject FieldType) Key "addressid" string
[___3] (BasicObject BasicType) "addressid" string
[__2] (FieldObject FieldType) Value true bool
[___3] (BasicObject BasicType) true bool

[0] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = users, collection = users}
[_1] (ArrayObject ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string}

[0] (InterfaceObject UserType) _ .error

