[] (PointerVariable PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase}) 
[_] (StructVariable UserType) user.UserServiceImpl struct{userDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) userDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) user user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string} 
[_] (FieldVariable FieldType) UserID string 
[__] (BasicVariable BasicType) UserID string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = user, collection = user} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "userid" string, UserID string} 
[__] (FieldVariable FieldType) "userid" string 
[___] (BasicVariable BasicType) "userid" string 
[__] (FieldVariable FieldType) UserID string 
[___] (BasicVariable BasicType) UserID string 

