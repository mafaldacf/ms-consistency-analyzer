[] (PointerObject PointerType) s (*postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue})
[_] (StructObject UserType) postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue}
[__] (FieldObject FieldType) analyticsQueue Queue
[___] (BlueprintBackendObject BlueprintBackendType) analyticsQueue Queue
[__] (FieldObject FieldType) analyticsService postnotification.AnalyticsService
[___] (ServiceObject ServiceType) analyticsService postnotification.AnalyticsService
[__] (FieldObject FieldType) mediaService postnotification.MediaService
[___] (ServiceObject ServiceType) mediaService postnotification.MediaService
[__] (FieldObject FieldType) postsDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) postsDb NoSQLDatabase
[__] (FieldObject FieldType) posts_cache Cache
[___] (BlueprintBackendObject BlueprintBackendType) posts_cache Cache

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService

[] (BasicObject BasicType) reqID int64
[_] (Reference BasicType) ref <reqID int64> @ NotifyService
[__] (BasicObject BasicType) ReqID string
[___] (Reference FieldType) ref <ReqID string> @ NotifyService
[____] (BasicObject BasicType) ReqID string
         --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {4}                 --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {4} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_____] (InterfaceObject InterfaceType) ReqID interface{}

    --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[] (BasicObject BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_] (Reference BasicType) ref <postID int64> @ NotifyService
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (BasicObject BasicType) PostID string
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (Reference FieldType) ref <PostID string> @ NotifyService
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (BasicObject BasicType) PostID string
         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                 --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_____] (InterfaceObject InterfaceType) PostID interface{}

    --> r-tainted: read(posts_db.Post) {1}
[] (StructObject UserType) post postnotification.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}}

[] (StructObject UserType) analytics postnotification.Analytics struct{PostID int64}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "postid" string, Value int64}
[__] (FieldObject FieldType) Key "postid" string
[___] (BasicObject BasicType) "postid" string
[__] (FieldObject FieldType) Value int64
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (BasicObject BasicType) postID int64
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (Reference BasicType) ref <postID int64> @ NotifyService
         --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_____] (BasicObject BasicType) PostID string
          --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[______] (Reference FieldType) ref <PostID string> @ NotifyService
           --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_______] (BasicObject BasicType) PostID string
            --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                       --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[________] (InterfaceObject InterfaceType) PostID interface{}

    --> r-tainted: read(posts_db.Post) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = post, collection = post}
     --> r-tainted: read(posts_db.Post) {1}
[_] (StructObject UserType) post postnotification.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}}

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) res bool

[] (InterfaceObject UserType) err .error

[] (StructObject UserType) analytics postnotification.Analytics struct{PostID int64}
     --> r-tainted: read(analytics_db.Analytics) {1}
[_] (Reference UserType) ref <analytics postnotification.Analytics struct{PostID int64}> @ AnalyticsService

[] (InterfaceObject UserType) err .error
[_] (Reference BasicType) ref <nil> @ AnalyticsService

