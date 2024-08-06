[] (PointerVariable PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}) 
[_] (StructVariable UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) cardid string 
[_] (Reference BasicType) ref <cardID string> @ FrontendService 
[_] (Reference BasicType) ref <cardID string> @ OrderService 
[__] (Reference BasicType) ref <cardID string> @ FrontendService 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (InterfaceVariable UserType) _ .error 

[] (ArrayVariable ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} 

[] (SliceVariable UserType) filter primitive.D 
[_] (StructVariable StructType) struct{Key "addressid" string, Value string} 
[__] (FieldVariable FieldType) Key "addressid" string 
[___] (BasicVariable BasicType) "addressid" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) cardid string 
[____] (Reference BasicType) ref <cardID string> @ FrontendService 
[____] (Reference BasicType) ref <cardID string> @ OrderService 
[_____] (Reference BasicType) ref <cardID string> @ FrontendService 

[] (SliceVariable UserType) projection primitive.D 
[_] (StructVariable StructType) struct{Key "addressid" string, Value true bool} 
[__] (FieldVariable FieldType) Key "addressid" string 
[___] (BasicVariable BasicType) "addressid" string 
[__] (FieldVariable FieldType) Value true bool 
[___] (BasicVariable BasicType) true bool 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (InterfaceVariable UserType) _ .error 

