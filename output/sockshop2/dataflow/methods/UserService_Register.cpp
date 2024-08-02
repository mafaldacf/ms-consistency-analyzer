[] (-1) (PointerVariable PointerType) s (*user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) user.userServiceImpl struct{UserService user.UserService, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 
[__] (-1) (ServiceVariable ServiceType) UserService user.UserService 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (34) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) username string // write(user_db), 
[_] (35) (Reference BasicType) ref <username string> @ FrontendService // write(user_db), 

[] (-1) (BasicVariable BasicType) password string // write(user_db), 
[_] (36) (Reference BasicType) ref <password string> @ FrontendService // write(user_db), 

[] (-1) (BasicVariable BasicType) email string // write(user_db), 
[_] (37) (Reference BasicType) ref <email string> @ FrontendService // write(user_db), 

[] (-1) (BasicVariable BasicType) first string // write(user_db), 
[_] (38) (Reference BasicType) ref <first string> @ FrontendService // write(user_db), 

[] (-1) (BasicVariable BasicType) last string // write(user_db), 
[_] (39) (Reference BasicType) ref <last string> @ FrontendService // write(user_db), 

[] (-1) (StructVariable UserType) u user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} // write(user_db), 
[_] (-1) (FieldVariable FieldType) Cards user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(user_db), 
[__] (0) (StructVariable UserType) user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(user_db), 
[_] (-1) (FieldVariable FieldType) Username string // write(user_db), 
[__] (-1) (BasicVariable BasicType) username string // write(user_db), 
[___] (35) (Reference BasicType) ref <username string> @ FrontendService // write(user_db), 
[_] (-1) (FieldVariable FieldType) Password string // write(user_db), 
[__] (-1) (BasicVariable BasicType) password string // write(user_db), 
[___] (36) (Reference BasicType) ref <password string> @ FrontendService // write(user_db), 
[_] (-1) (FieldVariable FieldType) Email string // write(user_db), 
[__] (-1) (BasicVariable BasicType) email string // write(user_db), 
[___] (37) (Reference BasicType) ref <email string> @ FrontendService // write(user_db), 
[_] (-1) (FieldVariable FieldType) FirstName string // write(user_db), 
[__] (-1) (BasicVariable BasicType) first string // write(user_db), 
[___] (38) (Reference BasicType) ref <first string> @ FrontendService // write(user_db), 
[_] (-1) (FieldVariable FieldType) LastName string // write(user_db), 
[__] (-1) (BasicVariable BasicType) last string // write(user_db), 
[___] (39) (Reference BasicType) ref <last string> @ FrontendService // write(user_db), 
[_] (-1) (FieldVariable FieldType) Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(user_db), 
[__] (0) (StructVariable UserType) user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(user_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = users, collection = users} 

[] (-1) (InterfaceVariable UserType) _ .error 

