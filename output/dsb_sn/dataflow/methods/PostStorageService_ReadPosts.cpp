[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

    --> r-tainted: read(post_db.[]socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}) {1}
[0] (ArrayObject ArrayType) new_posts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) unique_pids []int64
[_1] (BasicObject BasicType) k bool

[0] (BasicObject BasicType) k bool

[0] (ArrayObject ArrayType) unique_pids []int64
[_1] (BasicObject BasicType) k bool

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

    --> r-tainted: read(post_db.[]socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}) {1}
[0] (ArrayObject ArrayType) new_posts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) unique_pids []int64
[_1] (BasicObject BasicType) k bool

[0] (BasicObject BasicType) k bool

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) id_str string
[_1] (SliceObject SliceType) []string
[__2] (BasicObject BasicType) string
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[__2] (BasicObject BasicType) string
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[_1] (BasicObject BasicType) "," string
[_1] (SliceObject SliceType) []string
[__2] (BasicObject BasicType) string
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[__2] (BasicObject BasicType) string
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[_1] (BasicObject BasicType) "," string

[0] (BasicObject BasicType) query string

[0] (SliceObject UserType) query_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

    --> r-tainted: read(post_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) vals NoSQLCursor {database = post, collection = post}
     --> r-tainted: read(post_db.[]socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}) {1}
[_1] (ArrayObject ArrayType) new_posts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (InterfaceObject UserType) err .error

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) wg sync.WaitGroup

[0] (StructObject UserType) new_post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

    --> r-tainted: read(post_db.[]socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}) {1}
[0] (ArrayObject ArrayType) new_posts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) unique_pids []int64
[_1] (BasicObject BasicType) k bool

[0] (BasicObject BasicType) k bool

[0] (ArrayObject ArrayType) unique_pids []int64
[_1] (BasicObject BasicType) k bool

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ HomeTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService
[_1] (Reference UserType) ref <ctx context.Context> @ UserTimelineService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ HomeTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <reqID int64> @ UserTimelineService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_cache.value) {1}
[0] (ArrayObject ArrayType) postIDs []int64
[_1] (Reference ArrayType) ref <postIDs []int64> @ HomeTimelineService
[__2] (BasicObject BasicType) PostID int64
     --> w-tainted: write(usertimeline_cache.value) {1}
[_1] (Reference ArrayType) ref <post_ids []int64> @ UserTimelineService
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64
      --> w-tainted: write(usertimeline_cache.value) {1}
[__2] (BasicObject BasicType) PostID int64

[0] (MapObject MapType) unique_post_ids map[int64]bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) pid int64

    --> r-tainted: read(post_cache.key, post_cache.[]string, post_cache.string, post_cache.int64, post_cache.int) {5}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(post_cache.string) {1}
[_1] (BasicObject BasicType) string
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int
      --> r-tainted: read(post_cache.int64) {1}
[__2] (BasicObject BasicType) pid int64
      --> r-tainted: read(post_cache.int) {1}
[__2] (BasicObject BasicType) 10 int

    --> r-tainted: read(post_cache.int64) {1}
[0] (BasicObject BasicType) pid int64

[0] (ArrayObject ArrayType) values []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

    --> r-tainted: read(post_cache.value, post_cache.[]interface{}, post_cache.(*Post), post_cache.Post) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(post_cache.(*Post)) {1}
[_1] (PointerObject PointerType) * (*socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64})
      --> r-tainted: read(post_cache.Post) {1}
[__2] (StructObject UserType) * socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (StructObject UserType) idx socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

    --> r-tainted: read(post_db.[]socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}) {1}
[0] (ArrayObject ArrayType) new_posts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (ArrayObject ArrayType) unique_pids []int64
[_1] (BasicObject BasicType) k bool

[0] (BasicObject BasicType) k bool

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) id_str string
[_1] (SliceObject SliceType) []string
[__2] (BasicObject BasicType) string
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[__2] (BasicObject BasicType) string
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[_1] (BasicObject BasicType) "," string
[_1] (SliceObject SliceType) []string
[__2] (BasicObject BasicType) string
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[__2] (BasicObject BasicType) string
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[___3] (ArrayObject ArrayType) unique_pids []int64
[____4] (BasicObject BasicType) k bool
[_1] (BasicObject BasicType) "," string

[0] (BasicObject BasicType) query string

[0] (SliceObject UserType) query_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

    --> r-tainted: read(post_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) vals NoSQLCursor {database = post, collection = post}
     --> r-tainted: read(post_db.[]socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}) {1}
[_1] (ArrayObject ArrayType) new_posts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (InterfaceObject UserType) err .error

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) retposts []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[_1] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
[__2] (FieldObject FieldType) PostID int64
[___3] (BasicObject BasicType) PostID int64

[0] (StructObject UserType) wg sync.WaitGroup

[0] (StructObject UserType) new_post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

