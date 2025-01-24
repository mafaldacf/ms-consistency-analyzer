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

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(user_cache.key) {1}       --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[0] (BasicObject BasicType) username string
     --> w-tainted: write(user_cache.key) {1}         --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[_1] (Reference BasicType) ref <username string> @ Wrk2APIService

    --> w-tainted: write(user_cache.key) {1}       --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[0] (BasicObject BasicType) followee_name string
     --> w-tainted: write(user_cache.key) {1}         --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[_1] (Reference BasicType) ref <followeeName string> @ Wrk2APIService

    --> w-tainted: write(social_cache.key) {1}       --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int64) {1}
[0] (BasicObject BasicType) id int64

    --> r-tainted: read(social_cache.int64) {1}
[0] (BasicObject BasicType) followee_id int64

[0] (BasicObject BasicType) err1 error

[0] (BasicObject BasicType) err2 error

[0] (StructObject UserType) wg sync.WaitGroup

