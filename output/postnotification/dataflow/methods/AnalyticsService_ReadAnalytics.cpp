[] (PointerObject PointerType) a (*postnotification.AnalyticsServiceImpl struct{analyticsQueue Queue, analyticsDb NoSQLDatabase, numWorkers int})
[_] (StructObject UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}
[__] (FieldObject FieldType) analyticsDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) analyticsDb NoSQLDatabase
[__] (FieldObject FieldType) analyticsQueue Queue
[___] (BlueprintBackendObject BlueprintBackendType) analyticsQueue Queue
[__] (FieldObject FieldType) numWorkers 4 int
[___] (BasicObject BasicType) 4 int

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ StorageService
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService
[___] (Reference UserType) ref <ctx context.Context> @ NotifyService

    --> r-tainted: read(analytics_db.Analytics.PostID) {1}
[] (BasicObject BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_] (Reference BasicType) ref <postID int64> @ StorageService
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (Reference BasicType) ref <postID int64> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (BasicObject BasicType) PostID string
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (Reference FieldType) ref <PostID string> @ NotifyService
         --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_____] (BasicObject BasicType) PostID string
          --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                   --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[______] (InterfaceObject InterfaceType) PostID interface{}

    --> r-tainted: read(analytics_db.Analytics) {1}
[] (StructObject UserType) analytics postnotification.Analytics struct{PostID int64}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = analyticsDb, collection = analytics_collection}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "postid" string, Value int64}
[__] (FieldObject FieldType) Key "postid" string
[___] (BasicObject BasicType) "postid" string
[__] (FieldObject FieldType) Value int64
       --> r-tainted: read(analytics_db.Analytics.PostID) {1}
[___] (BasicObject BasicType) postID int64
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (Reference BasicType) ref <postID int64> @ StorageService
         --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_____] (Reference BasicType) ref <postID int64> @ NotifyService
          --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[______] (BasicObject BasicType) PostID string
           --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_______] (Reference FieldType) ref <PostID string> @ NotifyService
            --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[________] (BasicObject BasicType) PostID string
             --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_________] (InterfaceObject InterfaceType) PostID interface{}

    --> r-tainted: read(analytics_db.Analytics) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = analyticsDb, collection = analytics_collection}
     --> r-tainted: read(analytics_db.Analytics) {1}
[_] (StructObject UserType) analytics postnotification.Analytics struct{PostID int64}

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) res bool

[] (InterfaceObject UserType) err .error

