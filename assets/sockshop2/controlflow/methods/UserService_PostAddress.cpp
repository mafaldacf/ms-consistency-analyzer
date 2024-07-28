[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (81) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) userid string 
[_] (82) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (StructVariable UserType) address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} 
[_] (83) (Reference UserType) ref <address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "userid" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "userid" string 
[___] (0) (BasicVariable BasicType) "userid" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) userid string 
[____] (82) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (SliceVariable UserType) update primitive.D 
[_] (0) (StructVariable StructType) struct{Key "address" string, Value user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}} 
[__] (0) (FieldVariable FieldType) Key "address" string 
[___] (0) (BasicVariable BasicType) "address" string 
[__] (0) (FieldVariable FieldType) Value user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} 
[___] (-1) (StructVariable UserType) address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} 
[____] (83) (Reference UserType) ref <address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}> @ FrontendService 

