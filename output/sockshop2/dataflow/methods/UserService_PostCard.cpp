[] (PointerVariable PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}) 
[_] (StructVariable UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) userid string 
[_] (Reference BasicType) ref <userID string> @ FrontendService 

[] (StructVariable UserType) card user.Card struct{LongNum string, Expires string, CCV string, ID string} 
[_] (Reference UserType) ref <card user.Card struct{LongNum string, Expires string, CCV string, ID string}> @ FrontendService 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) filter primitive.D 
[_] (StructVariable StructType) struct{Key "userid" string, Value string} 
[__] (FieldVariable FieldType) Key "userid" string 
[___] (BasicVariable BasicType) "userid" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) userid string 
[____] (Reference BasicType) ref <userID string> @ FrontendService 

[] (SliceVariable UserType) update primitive.D 
[_] (StructVariable StructType) struct{Key "card" string, Value user.Card struct{LongNum string, Expires string, CCV string, ID string}} 
[__] (FieldVariable FieldType) Key "card" string 
[___] (BasicVariable BasicType) "card" string 
[__] (FieldVariable FieldType) Value user.Card struct{LongNum string, Expires string, CCV string, ID string} 
[___] (StructVariable UserType) card user.Card struct{LongNum string, Expires string, CCV string, ID string} 
[____] (Reference UserType) ref <card user.Card struct{LongNum string, Expires string, CCV string, ID string}> @ FrontendService 

