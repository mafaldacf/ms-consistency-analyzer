[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (30) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (25) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (62) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) cardid string 
[_] (34) (Reference BasicType) ref <cardID string> @ OrderService 
[__] (28) (Reference BasicType) ref <cardID string> @ FrontendService 
[_] (63) (Reference BasicType) ref <cardID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) cardid string 
[____] (34) (Reference BasicType) ref <cardID string> @ OrderService 
[_____] (28) (Reference BasicType) ref <cardID string> @ FrontendService 
[____] (63) (Reference BasicType) ref <cardID string> @ FrontendService 

[] (-1) (SliceVariable UserType) projection primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value true bool} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value true bool 
[___] (0) (BasicVariable BasicType) true bool 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

