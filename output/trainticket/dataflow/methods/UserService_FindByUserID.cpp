[] (PointerObject PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase})
[_] (StructObject UserType) user.UserServiceImpl struct{userDB NoSQLDatabase}
[__] (FieldObject FieldType) userDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(user_db._.userid) {1}
[] (BasicObject BasicType) userID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = user, collection = user}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "userid" string,  string}

    --> r-tainted: read(user_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = user, collection = user}
     --> r-tainted: read(user_db.User) {1}
[_] (StructObject UserType) user user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(user_db.User) {1}
[] (StructObject UserType) user user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

