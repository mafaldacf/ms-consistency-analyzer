[0] (PointerObject PointerType) u (*socialnetwork.UserTimelineServiceImpl struct{userTimelineCache Cache, userTimelineDB NoSQLDatabase, postStorageService socialnetwork.PostStorageService, CacheHits int64, CacheMiss int64, NumRequests int64})
[_1] (StructObject UserType) socialnetwork.UserTimelineServiceImpl struct{userTimelineCache Cache, userTimelineDB NoSQLDatabase, postStorageService socialnetwork.PostStorageService, CacheHits int64, CacheMiss int64, NumRequests int64}
[__2] (FieldObject FieldType) CacheHits int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumRequests int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) userTimelineCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userTimelineCache Cache
[__2] (FieldObject FieldType) userTimelineDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userTimelineDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[0] (BasicObject BasicType) postID int64
     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <uniqueID int64> @ ComposePostService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userID int64> @ ComposePostService
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[0] (BasicObject BasicType) timestamp int64
     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <timestamp int64> @ ComposePostService

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = usertimeline, collection = usertimeline}

[0] (InterfaceObject UserType) err .error

[0] (SliceObject UserType) query primitive.D
[_1] (StructObject StructType) struct{ int64,  "userid" string,  int64}

    --> r-tainted: read(usertimeline_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) results NoSQLCursor {database = usertimeline, collection = usertimeline}
     --> r-tainted: read(usertimeline_db.[]socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}) {1}
[_1] (ArrayObject ArrayType) userPosts []socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(usertimeline_db.[]socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}) {1}
[0] (ArrayObject ArrayType) userPosts []socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}

    --> w-tainted: write(usertimeline_db.UserPosts) {1}
[0] (StructObject UserType) userPosts socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}
     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}
[_1] (FieldObject FieldType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
      --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}
[__2] (ArrayObject ArrayType) []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}
[___3] (StructObject UserType) socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}
[____4] (FieldObject FieldType) PostID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) postID int64
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[______6] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}
[____4] (FieldObject FieldType) Timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) timestamp int64
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[______6] (Reference BasicType) ref <timestamp int64> @ ComposePostService
     --> w-tainted: write(usertimeline_db.UserPosts.UserID) {1}
[_1] (FieldObject FieldType) UserID int64
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (BasicObject BasicType) userID int64
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userID int64> @ ComposePostService
        --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}               --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(usertimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) postInfo []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
     --> r-tainted: read(usertimeline_cache.PostInfo) {1}
[_1] (StructObject UserType) socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
      --> r-tainted: read(usertimeline_cache.PostID) {1}
[__2] (FieldObject FieldType) PostID int64
       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}             --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) postID int64
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
      --> r-tainted: read(usertimeline_cache.Timestamp) {1}
[__2] (FieldObject FieldType) Timestamp int64
       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}             --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) timestamp int64
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <timestamp int64> @ ComposePostService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.key, usertimeline_cache.string, usertimeline_cache.int64, usertimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userID int64> @ ComposePostService
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userID int64> @ ComposePostService
       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}             --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[___3] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

[0] (BasicObject BasicType) _ bool

[0] (InterfaceObject UserType) err .error

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postInfo []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (StructObject UserType) socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (FieldObject FieldType) PostID int64
       --> w-tainted: write(usertimeline_cache.value) {1}
[___3] (BasicObject BasicType) postID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (FieldObject FieldType) Timestamp int64
       --> w-tainted: write(usertimeline_cache.value) {1}
[___3] (BasicObject BasicType) timestamp int64

