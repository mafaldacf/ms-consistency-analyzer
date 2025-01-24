[0] (PointerObject PointerType) s (*socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService})
[_1] (StructObject UserType) socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService}
[__2] (FieldObject FieldType) socialGraphCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphCache Cache
[__2] (FieldObject FieldType) socialGraphDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphDB NoSQLDatabase
[__2] (FieldObject FieldType) userIDService socialnetwork.UserIDService
[___3] (ServiceObject ServiceType) userIDService socialnetwork.UserIDService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userID int64> @ HomeTimelineService
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userID int64> @ ComposePostService
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) followers []int64
[_1] (BasicObject BasicType) FollowerID int64
[_1] (BasicObject BasicType) FollowerID int64

    --> r-tainted: read(social_cache.[]socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) followerInfos []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}

    --> w-tainted: write(social_cache.key) {1}       --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.string) {1}
[0] (BasicObject BasicType) userIDstr string
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userID int64> @ HomeTimelineService
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userID int64> @ ComposePostService
        --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}               --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userID int64> @ HomeTimelineService
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userID int64> @ ComposePostService
        --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}               --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) f socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}
[_1] (FieldObject FieldType) FollowerID int64
[__2] (BasicObject BasicType) FollowerID int64

[0] (ArrayObject ArrayType) followers []int64
[_1] (BasicObject BasicType) FollowerID int64
[_1] (BasicObject BasicType) FollowerID int64

[0] (PointerObject PointerType) s (*socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService})
[_1] (StructObject UserType) socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService}
[__2] (FieldObject FieldType) socialGraphCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphCache Cache
[__2] (FieldObject FieldType) socialGraphDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphDB NoSQLDatabase
[__2] (FieldObject FieldType) userIDService socialnetwork.UserIDService
[___3] (ServiceObject ServiceType) userIDService socialnetwork.UserIDService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userID int64> @ HomeTimelineService
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userID int64> @ ComposePostService
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) followers []int64
[_1] (BasicObject BasicType) FollowerID int64
[_1] (BasicObject BasicType) FollowerID int64

    --> r-tainted: read(social_cache.[]socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) followerInfos []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}

    --> w-tainted: write(social_cache.key) {1}       --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.string) {1}
[0] (BasicObject BasicType) userIDstr string
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userID int64> @ HomeTimelineService
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userID int64> @ ComposePostService
        --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}               --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userID int64> @ HomeTimelineService
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userID int64> @ ComposePostService
        --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}               --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(social_cache.key) {1}         --> w-tainted: write(social_cache.key) {1} --> r-tainted: read(social_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) f socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}
[_1] (FieldObject FieldType) FollowerID int64
[__2] (BasicObject BasicType) FollowerID int64

