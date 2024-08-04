[] (PointerVariable PointerType) s (*user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase}) 
[_] (StructVariable UserType) user.userServiceImpl struct{db NoSQLDatabase, db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) username string // write(user_db), 
[_] (Reference BasicType) ref <username string> @ FrontendService // write(user_db), 

[] (BasicVariable BasicType) password string // write(user_db), 
[_] (Reference BasicType) ref <password string> @ FrontendService // write(user_db), 

[] (BasicVariable BasicType) email string // write(user_db), 
[_] (Reference BasicType) ref <email string> @ FrontendService // write(user_db), 

[] (BasicVariable BasicType) first string // write(user_db), 
[_] (Reference BasicType) ref <first string> @ FrontendService // write(user_db), 

[] (BasicVariable BasicType) last string // write(user_db), 
[_] (Reference BasicType) ref <last string> @ FrontendService // write(user_db), 

[] (StructVariable UserType) u user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} // write(user_db), 
[_] (FieldVariable FieldType) Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(user_db), 
[__] (StructVariable UserType) user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(user_db), 
[_] (FieldVariable FieldType) Cards user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(user_db), 
[__] (StructVariable UserType) user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(user_db), 
[_] (FieldVariable FieldType) Email string // write(user_db), 
[__] (BasicVariable BasicType) email string // write(user_db), 
[___] (Reference BasicType) ref <email string> @ FrontendService // write(user_db), 
[_] (FieldVariable FieldType) FirstName string // write(user_db), 
[__] (BasicVariable BasicType) first string // write(user_db), 
[___] (Reference BasicType) ref <first string> @ FrontendService // write(user_db), 
[_] (FieldVariable FieldType) LastName string // write(user_db), 
[__] (BasicVariable BasicType) last string // write(user_db), 
[___] (Reference BasicType) ref <last string> @ FrontendService // write(user_db), 
[_] (FieldVariable FieldType) Password string // write(user_db), 
[__] (BasicVariable BasicType) password string // write(user_db), 
[___] (Reference BasicType) ref <password string> @ FrontendService // write(user_db), 
[_] (FieldVariable FieldType) UserID string 
[__] (BasicVariable BasicType) UserID string 
[_] (FieldVariable FieldType) Username string // write(user_db), 
[__] (BasicVariable BasicType) username string // write(user_db), 
[___] (Reference BasicType) ref <username string> @ FrontendService // write(user_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (InterfaceVariable UserType) _ .error 

