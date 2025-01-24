[0] (PointerObject PointerType) s (*socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService})
[_1] (StructObject UserType) socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService}
[__2] (FieldObject FieldType) socialGraphCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphCache Cache
[__2] (FieldObject FieldType) socialGraphDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphDB NoSQLDatabase
[__2] (FieldObject FieldType) userIDService socialnetwork.UserIDService
[___3] (ServiceObject ServiceType) userIDService socialnetwork.UserIDService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ SocialGraphService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ SocialGraphService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(social_cache.key) {1}       --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[_1] (Reference BasicType) ref <id int64> @ SocialGraphService

    --> r-tainted: read(social_cache.int64) {1}
[0] (BasicObject BasicType) followeeID int64
     --> r-tainted: read(social_cache.int64) {1}
[_1] (Reference BasicType) ref <followeeID int64> @ Wrk2APIService
     --> r-tainted: read(social_cache.int64) {1}
[_1] (Reference BasicType) ref <followee_id int64> @ SocialGraphService

    --> r-tainted: read(social_cache.int64) {1}
[0] (BasicObject BasicType) now int64

[0] (BasicObject BasicType) timestamp string
     --> r-tainted: read(social_cache.int64) {1}
[_1] (BasicObject BasicType) now int64
[_1] (BasicObject BasicType) 10 int
     --> r-tainted: read(social_cache.int64) {1}
[_1] (BasicObject BasicType) now int64
[_1] (BasicObject BasicType) 10 int

    --> w-tainted: write(social_cache.key) {1}       --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.string) {1}
[0] (BasicObject BasicType) userIDstr string
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(social_cache.key) {1}           --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
      --> w-tainted: write(social_cache.key) {1}           --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[__2] (Reference BasicType) ref <id int64> @ SocialGraphService
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(social_cache.key) {1}           --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
      --> w-tainted: write(social_cache.key) {1}           --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[__2] (Reference BasicType) ref <id int64> @ SocialGraphService
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

    --> r-tainted: read(social_cache.string) {1}
[0] (BasicObject BasicType) followeeIDstr string
     --> r-tainted: read(social_cache.int64) {1}
[_1] (BasicObject BasicType) followeeID int64
      --> r-tainted: read(social_cache.int64) {1}
[__2] (Reference BasicType) ref <followeeID int64> @ Wrk2APIService
      --> r-tainted: read(social_cache.int64) {1}
[__2] (Reference BasicType) ref <followee_id int64> @ SocialGraphService
     --> r-tainted: read(social_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> r-tainted: read(social_cache.int64) {1}
[_1] (BasicObject BasicType) followeeID int64
      --> r-tainted: read(social_cache.int64) {1}
[__2] (Reference BasicType) ref <followeeID int64> @ Wrk2APIService
      --> r-tainted: read(social_cache.int64) {1}
[__2] (Reference BasicType) ref <followee_id int64> @ SocialGraphService
     --> r-tainted: read(social_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

[0] (BasicObject BasicType) err1 error

[0] (BasicObject BasicType) err2 error

[0] (BasicObject BasicType) err3 error

[0] (StructObject UserType) wg sync.WaitGroup

    --> r-tainted: read(social_cache.[]socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) followees []socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}
     --> r-tainted: read(social_cache.FolloweeInfo) {1}
[_1] (StructObject UserType) socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}
      --> r-tainted: read(social_cache.FolloweeID) {1}
[__2] (FieldObject FieldType) FolloweeID int64
       --> r-tainted: read(social_cache.int64) {1}
[___3] (BasicObject BasicType) followeeID int64
        --> r-tainted: read(social_cache.int64) {1}
[____4] (Reference BasicType) ref <followeeID int64> @ Wrk2APIService
        --> r-tainted: read(social_cache.int64) {1}
[____4] (Reference BasicType) ref <followee_id int64> @ SocialGraphService
      --> r-tainted: read(social_cache.Timestamp) {1}
[__2] (FieldObject FieldType) Timestamp int64
       --> r-tainted: read(social_cache.int64) {1}
[___3] (BasicObject BasicType) now int64

    --> r-tainted: read(social_cache.[]socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) followers []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}
     --> r-tainted: read(social_cache.FollowerInfo) {1}
[_1] (StructObject UserType) socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}
      --> r-tainted: read(social_cache.FollowerID) {1}
[__2] (FieldObject FieldType) FollowerID int64
       --> w-tainted: write(social_cache.key) {1}             --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(social_cache.key) {1}               --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
        --> w-tainted: write(social_cache.key) {1}               --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[____4] (Reference BasicType) ref <id int64> @ SocialGraphService
      --> r-tainted: read(social_cache.Timestamp) {1}
[__2] (FieldObject FieldType) Timestamp int64
       --> r-tainted: read(social_cache.int64) {1}
[___3] (BasicObject BasicType) now int64

