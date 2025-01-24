[0] (PointerObject PointerType) u (*socialnetwork.UserServiceImpl struct{machine_id string, counter int64, current_timestamp int64, secret string, userCache Cache, userDB NoSQLDatabase, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.UserServiceImpl struct{machine_id string, counter 0 int, current_timestamp int64, secret string, userCache Cache, userDB NoSQLDatabase, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) counter 0 int
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) current_timestamp int64
[___3] (BasicObject BasicType) timestamp int64
[__2] (FieldObject FieldType) machine_id string
[___3] (BasicObject BasicType) string
[__2] (FieldObject FieldType) secret string
[___3] (BasicObject BasicType) secret string
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(user_db.User.FirstName) {1}
[0] (BasicObject BasicType) firstName string
     --> w-tainted: write(user_db.User.FirstName) {1}
[_1] (Reference BasicType) ref <firstName string> @ Wrk2APIService

    --> w-tainted: write(user_db.User.LastName) {1}
[0] (BasicObject BasicType) lastName string
     --> w-tainted: write(user_db.User.LastName) {1}
[_1] (Reference BasicType) ref <lastName string> @ Wrk2APIService

    --> w-tainted: write(user_db.User.Username) {1}       --> w-tainted: write(user_db.User.Username) {1} --> r-tainted: read(user_db._.username) {1}
[0] (BasicObject BasicType) username string
     --> w-tainted: write(user_db.User.Username) {1}         --> w-tainted: write(user_db.User.Username) {1} --> r-tainted: read(user_db._.username) {1}
[_1] (Reference BasicType) ref <username string> @ Wrk2APIService

[0] (BasicObject BasicType) password string
[_1] (Reference BasicType) ref <password string> @ Wrk2APIService

    --> w-tainted: write(user_db.User.UserID, social_db.UserInfo.UserID) {2}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(user_db.User.UserID, social_db.UserInfo.UserID) {2}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = user, collection = user}

[0] (InterfaceObject UserType) err .error

[0] (SliceObject UserType) query primitive.D
[_1] (StructObject StructType) struct{ string,  "username" string,  string}

    --> r-tainted: read(user_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = user, collection = user}
     --> r-tainted: read(user_db.User) {1}
[_1] (StructObject UserType) user socialnetwork.User struct{UserID int64, FirstName string, LastName string, Username string, PwdHashed string, Salt string}

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(user_db.User) {1}
[0] (StructObject UserType) user socialnetwork.User struct{UserID int64, FirstName string, LastName string, Username string, PwdHashed string, Salt string}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

    --> w-tainted: write(user_db.User.Salt) {1}
[0] (BasicObject BasicType) salt string
     --> w-tainted: write(user_db.User.Salt) {1}
[_1] (Reference BasicType) ref <string> @ genRandomStr
      --> w-tainted: write(user_db.User.Salt) {1}
[__2] (ArrayObject ArrayType) b []rune
       --> w-tainted: write(user_db.User.Salt) {1}
[___3] (SliceObject SliceType) github.com/blueprint-uservices/blueprint/examples/dsb_sn/workflow/socialnetwork.letterRunes []rune

    --> w-tainted: write(user_db.User.PwdHashed) {1}
[0] (BasicObject BasicType) hashed_pwd string
     --> w-tainted: write(user_db.User.PwdHashed) {1}
[_1] (Reference BasicType) ref <string> @ hashPwd
      --> w-tainted: write(user_db.User.PwdHashed) {1}
[__2] (SliceObject SliceType) []byte
       --> w-tainted: write(user_db.User.PwdHashed) {1}
[___3] (BasicObject BasicType) nil
       --> w-tainted: write(user_db.User.PwdHashed) {1}
[___3] (BasicObject BasicType) nil
      --> w-tainted: write(user_db.User.PwdHashed) {1}
[__2] (SliceObject SliceType) []byte
       --> w-tainted: write(user_db.User.PwdHashed) {1}
[___3] (BasicObject BasicType) nil
       --> w-tainted: write(user_db.User.PwdHashed) {1}
[___3] (BasicObject BasicType) nil

    --> w-tainted: write(user_db.User) {1}
[0] (StructObject UserType) user socialnetwork.User struct{UserID int64, FirstName string, LastName string, Username string, PwdHashed string, Salt string}
     --> w-tainted: write(user_db.User.FirstName) {1}
[_1] (FieldObject FieldType) FirstName string
      --> w-tainted: write(user_db.User.FirstName) {1}
[__2] (BasicObject BasicType) firstName string
       --> w-tainted: write(user_db.User.FirstName) {1}
[___3] (Reference BasicType) ref <firstName string> @ Wrk2APIService
     --> w-tainted: write(user_db.User.LastName) {1}
[_1] (FieldObject FieldType) LastName string
      --> w-tainted: write(user_db.User.LastName) {1}
[__2] (BasicObject BasicType) lastName string
       --> w-tainted: write(user_db.User.LastName) {1}
[___3] (Reference BasicType) ref <lastName string> @ Wrk2APIService
     --> w-tainted: write(user_db.User.PwdHashed) {1}
[_1] (FieldObject FieldType) PwdHashed string
      --> w-tainted: write(user_db.User.PwdHashed) {1}
[__2] (BasicObject BasicType) hashed_pwd string
       --> w-tainted: write(user_db.User.PwdHashed) {1}
[___3] (Reference BasicType) ref <string> @ hashPwd
        --> w-tainted: write(user_db.User.PwdHashed) {1}
[____4] (SliceObject SliceType) []byte
         --> w-tainted: write(user_db.User.PwdHashed) {1}
[_____5] (BasicObject BasicType) nil
         --> w-tainted: write(user_db.User.PwdHashed) {1}
[_____5] (BasicObject BasicType) nil
        --> w-tainted: write(user_db.User.PwdHashed) {1}
[____4] (SliceObject SliceType) []byte
         --> w-tainted: write(user_db.User.PwdHashed) {1}
[_____5] (BasicObject BasicType) nil
         --> w-tainted: write(user_db.User.PwdHashed) {1}
[_____5] (BasicObject BasicType) nil
     --> w-tainted: write(user_db.User.Salt) {1}
[_1] (FieldObject FieldType) Salt string
      --> w-tainted: write(user_db.User.Salt) {1}
[__2] (BasicObject BasicType) salt string
       --> w-tainted: write(user_db.User.Salt) {1}
[___3] (Reference BasicType) ref <string> @ genRandomStr
        --> w-tainted: write(user_db.User.Salt) {1}
[____4] (ArrayObject ArrayType) b []rune
         --> w-tainted: write(user_db.User.Salt) {1}
[_____5] (SliceObject SliceType) github.com/blueprint-uservices/blueprint/examples/dsb_sn/workflow/socialnetwork.letterRunes []rune
     --> w-tainted: write(user_db.User.UserID) {1}
[_1] (FieldObject FieldType) UserID int64
      --> w-tainted: write(user_db.User.UserID, social_db.UserInfo.UserID) {2}
[__2] (BasicObject BasicType) userID int64
       --> w-tainted: write(user_db.User.UserID, social_db.UserInfo.UserID) {2}
[___3] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(user_db.User.Username) {1}
[_1] (FieldObject FieldType) Username string
      --> w-tainted: write(user_db.User.Username) {1}           --> w-tainted: write(user_db.User.Username) {1} --> r-tainted: read(user_db._.username) {1}
[__2] (BasicObject BasicType) username string
       --> w-tainted: write(user_db.User.Username) {1}             --> w-tainted: write(user_db.User.Username) {1} --> r-tainted: read(user_db._.username) {1}
[___3] (Reference BasicType) ref <username string> @ Wrk2APIService

[0] (InterfaceObject UserType) err .error

