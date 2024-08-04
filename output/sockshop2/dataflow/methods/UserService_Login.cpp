[] (PointerVariable PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}) 
[_] (StructVariable UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) username string 
[_] (Reference BasicType) ref <username string> @ FrontendService 

[] (BasicVariable BasicType) password string 
[_] (Reference BasicType) ref <password string> @ FrontendService 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "username" string, Value string} 
[__] (FieldVariable FieldType) Key "username" string 
[___] (BasicVariable BasicType) "username" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) username string 
[____] (Reference BasicType) ref <username string> @ FrontendService 

[] (SliceVariable UserType) projection primitive.D 
[_] (StructVariable StructType) struct{Key "password" string, Value true bool} 
[__] (FieldVariable FieldType) Key "password" string 
[___] (BasicVariable BasicType) "password" string 
[__] (FieldVariable FieldType) Value true bool 
[___] (BasicVariable BasicType) true bool 

[] (StructVariable UserType) user user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (InterfaceVariable UserType) _ .error 

