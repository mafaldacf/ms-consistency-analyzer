[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (30) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (25) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (79) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) userid string 
[_] (32) (Reference BasicType) ref <customerID string> @ OrderService // write(shipqueue), write(shipdb), write(order_db), 
[__] (26) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (80) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) users []user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "userid" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "userid" string 
[___] (0) (BasicVariable BasicType) "userid" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) userid string 
[____] (32) (Reference BasicType) ref <customerID string> @ OrderService // write(shipqueue), write(shipdb), write(order_db), 
[_____] (26) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[____] (80) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

