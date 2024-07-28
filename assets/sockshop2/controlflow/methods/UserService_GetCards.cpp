[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (16) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (11) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (43) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) cardid string // read(user_db), 
[_] (20) (Reference BasicType) ref <cardID string> @ OrderService // read(user_db), 
[__] (14) (Reference BasicType) ref <cardID string> @ FrontendService // read(user_db), 
[_] (44) (Reference BasicType) ref <cardID string> @ FrontendService // read(user_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} 

[] (-1) (SliceVariable UserType) filter primitive.D // read(user_db), 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value string} // read(user_db), 
[__] (0) (FieldVariable FieldType) Key "addressid" string // read(user_db), 
[___] (0) (BasicVariable BasicType) "addressid" string // read(user_db), 
[__] (0) (FieldVariable FieldType) Value string // read(user_db), 
[___] (-1) (BasicVariable BasicType) cardid string // read(user_db), 
[____] (20) (Reference BasicType) ref <cardID string> @ OrderService // read(user_db), 
[_____] (14) (Reference BasicType) ref <cardID string> @ FrontendService // read(user_db), 
[____] (44) (Reference BasicType) ref <cardID string> @ FrontendService // read(user_db), 

[] (-1) (SliceVariable UserType) projection primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value true bool} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value true bool 
[___] (0) (BasicVariable BasicType) true bool 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} // read(user_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

