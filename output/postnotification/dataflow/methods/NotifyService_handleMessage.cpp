[] (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, notificationsQueue Queue, num_workers 4 int})
[_] (StructVariable UserType) postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, notificationsQueue Queue, num_workers 4 int}
[__] (FieldVariable FieldType) notificationsQueue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue
[__] (FieldVariable FieldType) num_workers 4 int
[___] (BasicVariable BasicType) 4 int
[__] (FieldVariable FieldType) storageService postnotification.StorageService
[___] (ServiceVariable ServiceType) storageService postnotification.StorageService

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService

[] (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string}
[_] (Reference UserType) ref <workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (FieldVariable FieldType) PostID string
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (BasicVariable BasicType) PostID string
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (InterfaceVariable InterfaceType) PostID interface{}
[__] (FieldVariable FieldType) ReqID string
[___] (BasicVariable BasicType) ReqID string
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}               --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceVariable InterfaceType) ReqID interface{}
[__] (FieldVariable FieldType) Timestamp string
[___] (BasicVariable BasicType) Timestamp string
        --> r-tainted: read(notifications_queue.message) {1}
[____] (InterfaceVariable InterfaceType) Timestamp interface{}
[_] (FieldVariable FieldType) PostID string
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (BasicVariable BasicType) PostID string
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (InterfaceVariable InterfaceType) PostID interface{}
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (BasicVariable BasicType) PostID string
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (Reference FieldType) ref <PostID string> @ NotifyService
        --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[____] (BasicVariable BasicType) PostID string
         --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}                 --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_____] (InterfaceVariable InterfaceType) PostID interface{}
[_] (FieldVariable FieldType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicVariable BasicType) ReqID string
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}               --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceVariable InterfaceType) ReqID interface{}
[__] (BasicVariable BasicType) ReqID string
[___] (Reference FieldType) ref <ReqID string> @ NotifyService
[____] (BasicVariable BasicType) ReqID string
         --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}                 --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_____] (InterfaceVariable InterfaceType) ReqID interface{}

[] (BasicVariable BasicType) reqID int64
[_] (BasicVariable BasicType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicVariable BasicType) ReqID string
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}               --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceVariable InterfaceType) ReqID interface{}

[] (InterfaceVariable UserType) err .error
[_] (BasicVariable BasicType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicVariable BasicType) ReqID string
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}               --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceVariable InterfaceType) ReqID interface{}

    --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[] (BasicVariable BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_] (BasicVariable BasicType) PostID string
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (BasicVariable BasicType) PostID string
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (InterfaceVariable InterfaceType) PostID interface{}

[] (InterfaceVariable UserType) err .error
     --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[_] (BasicVariable BasicType) PostID string
      --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID, analytics_db.Analytics.PostID) {2}
[___] (BasicVariable BasicType) PostID string
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (InterfaceVariable InterfaceType) PostID interface{}

[] (StructVariable UserType) _ postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}

[] (StructVariable UserType) _ postnotification.Analytics struct{PostID int64}

[] (InterfaceVariable UserType) err .error

