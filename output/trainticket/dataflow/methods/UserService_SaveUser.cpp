[] (PointerObject PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase})
[_] (StructObject UserType) user.UserServiceImpl struct{userDB NoSQLDatabase}
[__] (FieldObject FieldType) userDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(user_db.User) {1}
[] (StructObject UserType) user user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string}

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = user, collection = user}

[] (InterfaceObject UserType) err .error

