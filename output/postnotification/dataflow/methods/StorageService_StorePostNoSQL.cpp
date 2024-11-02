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
[_] (Reference UserType) ref <ctx context.Context> @ UploadService

[] (BasicVariable BasicType) reqID int64
     --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}         --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (Reference BasicType) ref <reqID int64> @ UploadService
      --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

    --> w-tainted: write(posts_db.Post) {1}
[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}
     --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post) {3}
[_] (Reference UserType) ref <post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}> @ UploadService
      --> w-tainted: write(posts_db.Post.Creator, posts_cache.key, posts_cache.value) {3}
[__] (FieldVariable FieldType) Creator postnotification.Creator struct{Username "some username" string}
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Creator) {3}
[___] (StructVariable UserType) postnotification.Creator struct{Username "some username" string}
        --> w-tainted: write(posts_db.Post.Creator.Username, posts_cache.key, posts_cache.value) {3}
[____] (FieldVariable FieldType) Username "some username" string
         --> w-tainted: write(posts_db.Post.Creator.Username, posts_cache.key, posts_cache.value) {3}
[_____] (BasicVariable BasicType) "some username" string
      --> w-tainted: write(posts_db.Post.Mentions, posts_cache.key, posts_cache.value) {3}
[__] (FieldVariable FieldType) Mentions []string
       --> w-tainted: write(posts_db.Post.Mentions, posts_cache.key, posts_cache.value) {3}
[___] (ArrayVariable ArrayType) mentions []string
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[____] (BasicVariable BasicType) "alice" string
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[____] (BasicVariable BasicType) "bob" string
      --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5}           --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[__] (FieldVariable FieldType) PostID int64
       --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[___] (BasicVariable BasicType) postID int64
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
      --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value) {3}
[__] (FieldVariable FieldType) ReqID int64
       --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (BasicVariable BasicType) reqID int64
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}               --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
      --> w-tainted: write(posts_db.Post.Text, posts_cache.key, posts_cache.value) {3}
[__] (FieldVariable FieldType) Text string
       --> w-tainted: write(posts_db.Post.Text, posts_cache.key, posts_cache.value) {3}
[___] (BasicVariable BasicType) text string
      --> w-tainted: write(posts_db.Post.Timestamp, posts_cache.key, posts_cache.value) {3}
[__] (FieldVariable FieldType) Timestamp int64
       --> w-tainted: write(posts_db.Post.Timestamp, posts_cache.key, posts_cache.value) {3}
[___] (BasicVariable BasicType) timestamp int64
[_] (FieldVariable FieldType) PostID int64
      --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5}           --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[__] (Reference FieldType) ref <PostID int64> @ UploadService
       --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[___] (BasicVariable BasicType) postID int64
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
      --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}           --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[__] (BasicVariable BasicType) PostID int64
       --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5}             --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[___] (Reference FieldType) ref <PostID int64> @ UploadService
        --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[____] (BasicVariable BasicType) postID int64
         --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}                 --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[] (InterfaceVariable UserType) err .error

[] (InterfaceVariable UserType) err .error

    --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage) {1}       --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage) {1} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage) {1}
[] (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string}
     --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}         --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_] (FieldVariable FieldType) PostID string
      --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}           --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[__] (BasicVariable BasicType) string
       --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}             --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[___] (BasicVariable BasicType) PostID int64
        --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5}               --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[____] (Reference FieldType) ref <PostID int64> @ UploadService
         --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}                 --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[_____] (BasicVariable BasicType) postID int64
          --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}                   --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

[] (BasicVariable BasicType) _ bool

[] (InterfaceVariable UserType) err .error

