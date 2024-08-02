[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase} 
[__] (-1) (ServiceVariable ServiceType) UserService user.UserService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (45) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) userid string 
[_] (46) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (StructVariable UserType) card user.Card struct{LongNum string, Expires string, CCV string, ID string} 
[_] (47) (Reference UserType) ref <card user.Card struct{LongNum string, Expires string, CCV string, ID string}> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "userid" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "userid" string 
[___] (0) (BasicVariable BasicType) "userid" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) userid string 
[____] (46) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (SliceVariable UserType) update primitive.D 
[_] (0) (StructVariable StructType) struct{Key "card" string, Value user.Card struct{LongNum string, Expires string, CCV string, ID string}} 
[__] (0) (FieldVariable FieldType) Key "card" string 
[___] (0) (BasicVariable BasicType) "card" string 
[__] (0) (FieldVariable FieldType) Value user.Card struct{LongNum string, Expires string, CCV string, ID string} 
[___] (-1) (StructVariable UserType) card user.Card struct{LongNum string, Expires string, CCV string, ID string} 
[____] (47) (Reference UserType) ref <card user.Card struct{LongNum string, Expires string, CCV string, ID string}> @ FrontendService 

