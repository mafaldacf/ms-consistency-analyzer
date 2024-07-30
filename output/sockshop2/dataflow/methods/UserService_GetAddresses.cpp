[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (30) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (25) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (60) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) addressid string 
[_] (33) (Reference BasicType) ref <addressID string> @ OrderService 
[__] (27) (Reference BasicType) ref <addressID string> @ FrontendService 
[_] (61) (Reference BasicType) ref <addressID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) addressid string 
[____] (33) (Reference BasicType) ref <addressID string> @ OrderService 
[_____] (27) (Reference BasicType) ref <addressID string> @ FrontendService 
[____] (61) (Reference BasicType) ref <addressID string> @ FrontendService 

[] (-1) (SliceVariable UserType) projection primitive.D 
[_] (0) (StructVariable StructType) struct{Key "addressid" string, Value true bool} 
[__] (0) (FieldVariable FieldType) Key "addressid" string 
[___] (0) (BasicVariable BasicType) "addressid" string 
[__] (0) (FieldVariable FieldType) Value true bool 
[___] (0) (BasicVariable BasicType) true bool 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

