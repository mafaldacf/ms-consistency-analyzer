[0] (PointerObject PointerType) u (*socialnetwork.UserIDServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserIDServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ SocialGraphService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ SocialGraphService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ SocialGraphService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ SocialGraphService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ SocialGraphService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ SocialGraphService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ SocialGraphService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ SocialGraphService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(user_cache.key) {1}       --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_db._.username, user_cache.string) {2}
[0] (BasicObject BasicType) username string
     --> w-tainted: write(user_cache.key) {1}         --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[_1] (Reference BasicType) ref <username string> @ SocialGraphService
      --> w-tainted: write(user_cache.key) {1}           --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[__2] (Reference BasicType) ref <username string> @ Wrk2APIService
     --> w-tainted: write(user_cache.key) {1}         --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[_1] (Reference BasicType) ref <followee_name string> @ SocialGraphService
      --> w-tainted: write(user_cache.key) {1}           --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[__2] (Reference BasicType) ref <followeeName string> @ Wrk2APIService
     --> w-tainted: write(user_cache.key) {1}         --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[_1] (Reference BasicType) ref <username string> @ SocialGraphService
      --> w-tainted: write(user_cache.key) {1}           --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[__2] (Reference BasicType) ref <username string> @ Wrk2APIService
     --> w-tainted: write(user_cache.key) {1}         --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[_1] (Reference BasicType) ref <followee_name string> @ SocialGraphService
      --> w-tainted: write(user_cache.key) {1}           --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[__2] (Reference BasicType) ref <followeeName string> @ Wrk2APIService

    --> r-tainted: read(user_cache.int64) {1}
[0] (BasicObject BasicType) user_id int64
     --> r-tainted: read(user_cache.int64) {1}
[_1] (BasicObject BasicType) int64

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(user_db.User, user_db.User.UserID) {2}
[0] (StructObject UserType) user socialnetwork.User struct{UserID int64, FirstName string, LastName string, Username string, PwdHashed string, Salt string}
     --> r-tainted: read(user_db.User.UserID) {1}
[_1] (FieldObject FieldType) UserID int64
      --> r-tainted: read(user_db.User.UserID) {1}
[__2] (BasicObject BasicType) UserID int64

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = user, collection = user}

[0] (InterfaceObject UserType) err .error

[0] (SliceObject UserType) query primitive.D
[_1] (StructObject StructType) struct{ string,  "username" string,  string}

    --> r-tainted: read(user_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = user, collection = user}
     --> r-tainted: read(user_db.User, user_db.User.UserID) {2}
[_1] (StructObject UserType) user socialnetwork.User struct{UserID int64, FirstName string, LastName string, Username string, PwdHashed string, Salt string}
      --> r-tainted: read(user_db.User.UserID) {1}
[__2] (FieldObject FieldType) UserID int64
       --> r-tainted: read(user_db.User.UserID) {1}
[___3] (BasicObject BasicType) UserID int64

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) result bool

[0] (InterfaceObject UserType) err .error

    --> w-tainted: write(user_cache.value) {1}
[0] (FieldObject FieldType) user_id int64
     --> w-tainted: write(user_cache.value) {1}
[_1] (BasicObject BasicType) UserID int64

[0] (InterfaceObject UserType) err .error

