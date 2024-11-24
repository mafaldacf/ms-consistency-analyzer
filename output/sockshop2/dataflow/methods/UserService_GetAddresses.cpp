[] (PointerObject PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase})
[_] (StructObject UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) addressid string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = users, collection = users}

[] (InterfaceObject UserType) _ .error

[] (ArrayObject ArrayType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{Key "addressid" string, Value string}
[__] (FieldObject FieldType) Key "addressid" string
[___] (BasicObject BasicType) "addressid" string
[__] (FieldObject FieldType) Value string
[___] (BasicObject BasicType) addressid string

[] (SliceObject UserType) projection primitive.D
[_] (StructObject StructType) struct{Key "addressid" string, Value true bool}
[__] (FieldObject FieldType) Key "addressid" string
[___] (BasicObject BasicType) "addressid" string
[__] (FieldObject FieldType) Value true bool
[___] (BasicObject BasicType) true bool

[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = users, collection = users}
[_] (ArrayObject ArrayType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}

[] (InterfaceObject UserType) _ .error

