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
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userID int64> @ ComposePostService
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) username string
[_1] (Reference BasicType) ref <username string> @ ComposePostService
[__2] (Reference BasicType) ref <username string> @ Wrk2APIService

