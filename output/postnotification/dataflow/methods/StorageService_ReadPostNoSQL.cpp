[] (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue})
[_] (StructVariable UserType) postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue}
[__] (FieldVariable FieldType) analyticsQueue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue
[__] (FieldVariable FieldType) analyticsService postnotification.AnalyticsService
[___] (ServiceVariable ServiceType) analyticsService postnotification.AnalyticsService
[__] (FieldVariable FieldType) mediaService postnotification.MediaService
[___] (ServiceVariable ServiceType) mediaService postnotification.MediaService
[__] (FieldVariable FieldType) postsDb NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase
[__] (FieldVariable FieldType) posts_cache Cache
[___] (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService

[] (BasicVariable BasicType) reqID int64
[_] (Reference BasicType) ref <reqID int64> @ NotifyService
[__] (BasicVariable BasicType) ReqID string
[___] (Reference FieldType) ref <ReqID string> @ NotifyService
[____] (BasicVariable BasicType) ReqID string
         --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}                 --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_____] (InterfaceVariable InterfaceType) ReqID interface{}

    --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[] (BasicVariable BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_] (Reference BasicType) ref <postID int64> @ NotifyService
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (BasicVariable BasicType) PostID string
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (Reference FieldType) ref <PostID string> @ NotifyService
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (BasicVariable BasicType) PostID string
         --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}                 --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_____] (InterfaceVariable InterfaceType) PostID interface{}

    --> r-tainted: read(posts_db.Post) {1}
[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}

[] (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64}

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[] (InterfaceVariable UserType) err .error

[] (SliceVariable UserType) query primitive.D
[_] (StructVariable StructType) struct{Key "postid" string, Value int64}
[__] (FieldVariable FieldType) Key "postid" string
[___] (BasicVariable BasicType) "postid" string
[__] (FieldVariable FieldType) Value int64
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (BasicVariable BasicType) postID int64
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (Reference BasicType) ref <postID int64> @ NotifyService
         --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_____] (BasicVariable BasicType) PostID string
          --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[______] (Reference FieldType) ref <PostID string> @ NotifyService
           --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_______] (BasicVariable BasicType) PostID string
            --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}                       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[________] (InterfaceVariable InterfaceType) PostID interface{}

    --> r-tainted: read(posts_db.Post) {1}
[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post}
     --> r-tainted: read(posts_db.Post) {1}
[_] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}

[] (InterfaceVariable UserType) err .error

[] (BasicVariable BasicType) res bool

[] (InterfaceVariable UserType) err .error

[] (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64}

[] (InterfaceVariable UserType) err .error

