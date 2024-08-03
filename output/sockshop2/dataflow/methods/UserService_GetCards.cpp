[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (40) (InterfaceVariable UserType) ctx context.Context 
[_] (30) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (40) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (35) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) cardid string 
[_] (31) (Reference BasicType) ref <cardID string> @ FrontendService 
[_] (44) (Reference BasicType) ref <cardID string> @ OrderService 
[__] (38) (Reference BasicType) ref <cardID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) cardid string 
[____] (31) (Reference BasicType) ref <cardID string> @ FrontendService 
[____] (44) (Reference BasicType) ref <cardID string> @ OrderService 
[_____] (38) (Reference BasicType) ref <cardID string> @ FrontendService 

[] (-1) (SliceVariable UserType) projection primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value true bool} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value true bool 
[___] (0) (BasicVariable BasicType) true bool 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

