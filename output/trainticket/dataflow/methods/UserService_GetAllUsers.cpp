[] (PointerObject PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase})
[_] (StructObject UserType) user.UserServiceImpl struct{userDB NoSQLDatabase}
[__] (FieldObject FieldType) userDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = user, collection = user}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(user_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = user, collection = user}
     --> r-tainted: read(user_db.[]user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string}) {1}
[_] (ArrayObject ArrayType) users []user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(user_db.[]user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string}) {1}
[] (ArrayObject ArrayType) users []user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string}

[] (InterfaceObject UserType) err .error

