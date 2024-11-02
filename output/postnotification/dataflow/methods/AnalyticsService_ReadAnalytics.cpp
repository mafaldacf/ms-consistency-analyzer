[] (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int})
[_] (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}
[__] (FieldVariable FieldType) analyticsDb NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsDb NoSQLDatabase
[__] (FieldVariable FieldType) analyticsQueue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue
[__] (FieldVariable FieldType) numWorkers 4 int
[___] (BasicVariable BasicType) 4 int

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ StorageService
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService
[___] (Reference UserType) ref <ctx context.Context> @ NotifyService

    --> r-tainted: read(analytics_db.Analytics.PostID) {1}
[] (BasicVariable BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_] (Reference BasicType) ref <postID int64> @ StorageService
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (Reference BasicType) ref <postID int64> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (BasicVariable BasicType) PostID string
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (Reference FieldType) ref <PostID string> @ NotifyService
         --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_____] (BasicVariable BasicType) PostID string
          --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}                   --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[______] (InterfaceVariable InterfaceType) PostID interface{}

    --> r-tainted: read(analytics_db.Analytics) {1}
[] (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64}

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analyticsDb, collection = analytics_collection}

[] (InterfaceVariable UserType) err .error

[] (SliceVariable UserType) query primitive.D
[_] (StructVariable StructType) struct{Key "postid" string, Value int64}
[__] (FieldVariable FieldType) Key "postid" string
[___] (BasicVariable BasicType) "postid" string
[__] (FieldVariable FieldType) Value int64
       --> r-tainted: read(analytics_db.Analytics.PostID) {1}
[___] (BasicVariable BasicType) postID int64
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (Reference BasicType) ref <postID int64> @ StorageService
         --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_____] (Reference BasicType) ref <postID int64> @ NotifyService
          --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[______] (BasicVariable BasicType) PostID string
           --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_______] (Reference FieldType) ref <PostID string> @ NotifyService
            --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[________] (BasicVariable BasicType) PostID string
             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}                         --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_________] (InterfaceVariable InterfaceType) PostID interface{}

    --> r-tainted: read(analytics_db.Analytics) {1}
[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = analyticsDb, collection = analytics_collection}
     --> r-tainted: read(analytics_db.Analytics) {1}
[_] (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64}

[] (InterfaceVariable UserType) err .error

[] (BasicVariable BasicType) res bool

[] (InterfaceVariable UserType) err .error

