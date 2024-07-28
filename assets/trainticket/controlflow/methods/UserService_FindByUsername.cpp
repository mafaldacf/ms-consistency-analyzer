[] (-1) (PointerVariable PointerType) u (*user.UserServiceImpl struct{userDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.UserServiceImpl struct{userDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) userDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) username string // read(user_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = user, collection = user} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(user_db), 
[_] (0) (StructVariable StructType) struct{ "username" string,  string} // read(user_db), 
[__] (0) (FieldVariable FieldType) string // read(user_db), 
[___] (-1) (BasicVariable BasicType) username string // read(user_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = user, collection = user} // read(user_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) user user.User struct{UserID string, Username string, Password string, Gender int64, DocumentType int64, DocumentNum string, Email string} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

