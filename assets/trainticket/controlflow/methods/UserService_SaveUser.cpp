[] (PointerVariable PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase}) 
[_] (StructVariable UserType) user.UserServiceImpl struct{userDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) userDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) user user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string} // write(user_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = user, collection = user} 

[] (InterfaceVariable UserType) err .error 

