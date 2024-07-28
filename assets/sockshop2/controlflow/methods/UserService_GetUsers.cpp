[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (16) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (11) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (41) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) userid string // read(user_db), 
[_] (18) (Reference BasicType) ref <customerID string> @ OrderService // write(shipqueue), write(shipdb), write(order_db), read(user_db), 
[__] (12) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), read(user_db), 
[_] (42) (Reference BasicType) ref <userID string> @ FrontendService // read(user_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) users []user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} 

[] (-1) (SliceVariable UserType) filter primitive.D // read(user_db), 
[_] (0) (StructVariable StructType) struct{Key "userid" string, Value string} // read(user_db), 
[__] (0) (FieldVariable FieldType) Key "userid" string // read(user_db), 
[___] (0) (BasicVariable BasicType) "userid" string // read(user_db), 
[__] (0) (FieldVariable FieldType) Value string // read(user_db), 
[___] (-1) (BasicVariable BasicType) userid string // read(user_db), 
[____] (18) (Reference BasicType) ref <customerID string> @ OrderService // write(shipqueue), write(shipdb), write(order_db), read(user_db), 
[_____] (12) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), read(user_db), 
[____] (42) (Reference BasicType) ref <userID string> @ FrontendService // read(user_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = users, collection = users} // read(user_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

