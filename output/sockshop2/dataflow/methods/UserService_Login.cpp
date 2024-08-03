[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (70) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) username string 
[_] (71) (Reference BasicType) ref <username string> @ FrontendService 

[] (-1) (BasicVariable BasicType) password string 
[_] (72) (Reference BasicType) ref <password string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "username" string, Value string} 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) username string 
[____] (71) (Reference BasicType) ref <username string> @ FrontendService 
[__] (0) (FieldVariable FieldType) Key "username" string 
[___] (0) (BasicVariable BasicType) "username" string 

[] (-1) (SliceVariable UserType) projection primitive.D 
[_] (0) (StructVariable StructType) struct{Key "password" string, Value true bool} 
[__] (0) (FieldVariable FieldType) Key "password" string 
[___] (0) (BasicVariable BasicType) "password" string 
[__] (0) (FieldVariable FieldType) Value true bool 
[___] (0) (BasicVariable BasicType) true bool 

[] (-1) (StructVariable UserType) user user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

