[] (-1) (PointerVariable PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.UserServiceImpl struct{userDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) userDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) user user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string} // write(user_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = user, collection = user} 

[] (-1) (InterfaceVariable UserType) err .error 

