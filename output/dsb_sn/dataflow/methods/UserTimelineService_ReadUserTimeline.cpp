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
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) start int64
[_1] (Reference BasicType) ref <start int64> @ Wrk2APIService

[0] (BasicObject BasicType) stop int64
[_1] (Reference BasicType) ref <stop int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.key, usertimeline_cache.string, usertimeline_cache.int64, usertimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

    --> r-tainted: read(usertimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) post_infos []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) seen_posts map[int64]bool

[0] (StructObject UserType) post_info socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

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
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) start int64
[_1] (Reference BasicType) ref <start int64> @ Wrk2APIService

[0] (BasicObject BasicType) stop int64
[_1] (Reference BasicType) ref <stop int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.key, usertimeline_cache.string, usertimeline_cache.int64, usertimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

    --> r-tainted: read(usertimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) post_infos []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) seen_posts map[int64]bool

[0] (StructObject UserType) post_info socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (BasicObject BasicType) db_start len(post_ids []int64) 
[_1] (BasicObject BasicType) start int64
[__2] (Reference BasicType) ref <start int64> @ Wrk2APIService
[_1] (BasicObject BasicType) len(post_ids []int64) int64

[0] (ArrayObject ArrayType) new_post_ids []int64
[_1] (BasicObject BasicType) PostID int64
[_1] (BasicObject BasicType) PostID int64

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = usertimeline, collection = usertimeline}

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) query string
[_1] (BasicObject BasicType) `{"UserID": %[1]d}` string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_1] (BasicObject BasicType) `{"UserID": %[1]d}` string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) projection string
[_1] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_1] (BasicObject BasicType) stop int64
[__2] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_1] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_1] (BasicObject BasicType) stop int64
[__2] (Reference BasicType) ref <stop int64> @ Wrk2APIService

[0] (SliceObject UserType) query_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

[0] (SliceObject UserType) projection_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

    --> r-tainted: read(usertimeline_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) post_db_val NoSQLCursor {database = usertimeline, collection = usertimeline}
     --> r-tainted: read(usertimeline_db.UserPosts, usertimeline_db.UserPosts.Posts) {2}
[_1] (StructObject UserType) user_posts socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}
      --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[__2] (FieldObject FieldType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
       --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[___3] (SliceObject SliceType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(usertimeline_db.UserPosts, usertimeline_db.UserPosts.Posts) {2}
[0] (StructObject UserType) user_posts socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}
     --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[_1] (FieldObject FieldType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
      --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[__2] (SliceObject SliceType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) post socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (BasicObject BasicType) _ bool

[0] (ArrayObject ArrayType) new_post_ids []int64
[_1] (BasicObject BasicType) PostID int64

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
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) start int64
[_1] (Reference BasicType) ref <start int64> @ Wrk2APIService

[0] (BasicObject BasicType) stop int64
[_1] (Reference BasicType) ref <stop int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.key, usertimeline_cache.string, usertimeline_cache.int64, usertimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

    --> r-tainted: read(usertimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) post_infos []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) seen_posts map[int64]bool

[0] (StructObject UserType) post_info socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

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
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) start int64
[_1] (Reference BasicType) ref <start int64> @ Wrk2APIService

[0] (BasicObject BasicType) stop int64
[_1] (Reference BasicType) ref <stop int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.key, usertimeline_cache.string, usertimeline_cache.int64, usertimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

    --> r-tainted: read(usertimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) post_infos []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) seen_posts map[int64]bool

[0] (StructObject UserType) post_info socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (BasicObject BasicType) db_start len(post_ids []int64) 
[_1] (BasicObject BasicType) start int64
[__2] (Reference BasicType) ref <start int64> @ Wrk2APIService
[_1] (BasicObject BasicType) len(post_ids []int64) int64

[0] (ArrayObject ArrayType) new_post_ids []int64
[_1] (BasicObject BasicType) PostID int64
[_1] (BasicObject BasicType) PostID int64

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = usertimeline, collection = usertimeline}

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) query string
[_1] (BasicObject BasicType) `{"UserID": %[1]d}` string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_1] (BasicObject BasicType) `{"UserID": %[1]d}` string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) projection string
[_1] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_1] (BasicObject BasicType) stop int64
[__2] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_1] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_1] (BasicObject BasicType) stop int64
[__2] (Reference BasicType) ref <stop int64> @ Wrk2APIService

[0] (SliceObject UserType) query_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

[0] (SliceObject UserType) projection_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

    --> r-tainted: read(usertimeline_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) post_db_val NoSQLCursor {database = usertimeline, collection = usertimeline}
     --> r-tainted: read(usertimeline_db.UserPosts, usertimeline_db.UserPosts.Posts) {2}
[_1] (StructObject UserType) user_posts socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}
      --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[__2] (FieldObject FieldType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
       --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[___3] (SliceObject SliceType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(usertimeline_db.UserPosts, usertimeline_db.UserPosts.Posts) {2}
[0] (StructObject UserType) user_posts socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}
     --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[_1] (FieldObject FieldType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
      --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[__2] (SliceObject SliceType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) post socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (BasicObject BasicType) _ bool

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
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) start int64
[_1] (Reference BasicType) ref <start int64> @ Wrk2APIService

[0] (BasicObject BasicType) stop int64
[_1] (Reference BasicType) ref <stop int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.key, usertimeline_cache.string, usertimeline_cache.int64, usertimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

    --> r-tainted: read(usertimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) post_infos []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) seen_posts map[int64]bool

[0] (StructObject UserType) post_info socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

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
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) start int64
[_1] (Reference BasicType) ref <start int64> @ Wrk2APIService

[0] (BasicObject BasicType) stop int64
[_1] (Reference BasicType) ref <stop int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.key) {1}       --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.key, usertimeline_cache.string, usertimeline_cache.int64, usertimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

    --> r-tainted: read(usertimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) post_infos []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) post_ids []int64
[_1] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) seen_posts map[int64]bool

[0] (StructObject UserType) post_info socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (BasicObject BasicType) db_start len(post_ids []int64) 
[_1] (BasicObject BasicType) start int64
[__2] (Reference BasicType) ref <start int64> @ Wrk2APIService
[_1] (BasicObject BasicType) len(post_ids []int64) int64

[0] (ArrayObject ArrayType) new_post_ids []int64
[_1] (BasicObject BasicType) PostID int64
[_1] (BasicObject BasicType) PostID int64

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = usertimeline, collection = usertimeline}

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) query string
[_1] (BasicObject BasicType) `{"UserID": %[1]d}` string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_1] (BasicObject BasicType) `{"UserID": %[1]d}` string
     --> w-tainted: write(usertimeline_cache.key) {1}         --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) projection string
[_1] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_1] (BasicObject BasicType) stop int64
[__2] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_1] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_1] (BasicObject BasicType) stop int64
[__2] (Reference BasicType) ref <stop int64> @ Wrk2APIService

[0] (SliceObject UserType) query_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

[0] (SliceObject UserType) projection_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

    --> r-tainted: read(usertimeline_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) post_db_val NoSQLCursor {database = usertimeline, collection = usertimeline}
     --> r-tainted: read(usertimeline_db.UserPosts, usertimeline_db.UserPosts.Posts) {2}
[_1] (StructObject UserType) user_posts socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}
      --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[__2] (FieldObject FieldType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
       --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[___3] (SliceObject SliceType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(usertimeline_db.UserPosts, usertimeline_db.UserPosts.Posts) {2}
[0] (StructObject UserType) user_posts socialnetwork.UserPosts struct{UserID int64, Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}}
     --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[_1] (FieldObject FieldType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
      --> r-tainted: read(usertimeline_db.UserPosts.Posts) {1}
[__2] (SliceObject SliceType) Posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) post socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) post_ids []int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (BasicObject BasicType) PostID int64

[0] (BasicObject BasicType) post_channel bool

[0] (BasicObject BasicType) err_post_channel error

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) err error

