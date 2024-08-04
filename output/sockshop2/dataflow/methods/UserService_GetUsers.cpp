[] (PointerVariable PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}) 
[_] (StructVariable UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) userid string 
[_] (Reference BasicType) ref <customerID string> @ OrderService // write(shipqueue), write(shipdb), write(order_db), 
[__] (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (Reference BasicType) ref <userID string> @ FrontendService 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (InterfaceVariable UserType) _ .error 

[] (ArrayVariable ArrayType) users []user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} 

[] (SliceVariable UserType) filter primitive.D 
[_] (StructVariable StructType) struct{Key "userid" string, Value string} 
[__] (FieldVariable FieldType) Key "userid" string 
[___] (BasicVariable BasicType) "userid" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) userid string 
[____] (Reference BasicType) ref <customerID string> @ OrderService // write(shipqueue), write(shipdb), write(order_db), 
[_____] (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[____] (Reference BasicType) ref <userID string> @ FrontendService 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (InterfaceVariable UserType) _ .error 

