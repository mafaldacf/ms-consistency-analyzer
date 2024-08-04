[] (PointerVariable PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase}) 
[_] (StructVariable UserType) user.UserServiceImpl struct{userDB NoSQLDatabase} 
[__] (FieldVariable FieldType) userDB NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) userID string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = user, collection = user} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "userid" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) userID string 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = user, collection = user} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) user user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

