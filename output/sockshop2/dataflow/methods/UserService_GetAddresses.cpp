[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (40) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (35) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (85) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) addressid string 
[_] (43) (Reference BasicType) ref <addressID string> @ OrderService 
[__] (37) (Reference BasicType) ref <addressID string> @ FrontendService 
[_] (86) (Reference BasicType) ref <addressID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) addressid string 
[____] (43) (Reference BasicType) ref <addressID string> @ OrderService 
[_____] (37) (Reference BasicType) ref <addressID string> @ FrontendService 
[____] (86) (Reference BasicType) ref <addressID string> @ FrontendService 

[] (-1) (SliceVariable UserType) projection primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value true bool} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value true bool 
[___] (0) (BasicVariable BasicType) true bool 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

