[] (PointerVariable PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase}) 
[_] (StructVariable UserType) user.UserServiceImpl struct{userDB NoSQLDatabase} 
[__] (FieldVariable FieldType) userDB NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = user, collection = user} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = user, collection = user} 

[] (InterfaceVariable UserType) err .error 

[] (ArrayVariable ArrayType) users []user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string} 

[] (InterfaceVariable UserType) err .error 

