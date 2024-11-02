[] (PointerVariable PointerType) u (*postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache})
[_] (StructVariable UserType) postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache}
[__] (FieldVariable FieldType) mediaService postnotification.MediaService
[___] (ServiceVariable ServiceType) mediaService postnotification.MediaService
[__] (FieldVariable FieldType) notificationsQueue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue
[__] (FieldVariable FieldType) storageService postnotification.StorageService
[___] (ServiceVariable ServiceType) storageService postnotification.StorageService
[__] (FieldVariable FieldType) timelineCache Cache
[___] (BlueprintBackendVariable BlueprintBackendType) timelineCache Cache

[] (InterfaceVariable UserType) ctx context.Context

[] (BasicVariable BasicType) username string

    --> w-tainted: write(posts_db.Post.Text, posts_cache.key, posts_cache.value) {3}
[] (BasicVariable BasicType) text string

    --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}       --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[] (BasicVariable BasicType) reqID int64
     --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}         --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

    --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}       --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[] (BasicVariable BasicType) postID int64
     --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}         --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

    --> w-tainted: write(media_db.Media.MediaID) {1}
[] (BasicVariable BasicType) mediaID int64

    --> w-tainted: write(media_db.Media) {1}
[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}
     --> w-tainted: write(media_db.Media.Content) {1}
[_] (FieldVariable FieldType) Content "HELLO WORLD!" untyped string
      --> w-tainted: write(media_db.Media.Content) {1}
[__] (BasicVariable BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string
     --> w-tainted: write(media_db.Media.MediaID) {1}
[_] (FieldVariable FieldType) MediaID int64
      --> w-tainted: write(media_db.Media.MediaID) {1}
[__] (BasicVariable BasicType) mediaID int64
     --> w-tainted: write(media_db.Media.PostID) {1}
[_] (FieldVariable FieldType) PostID int64
      --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}           --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[__] (BasicVariable BasicType) postID int64
       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

    --> w-tainted: write(posts_db.Post.Timestamp, posts_cache.key, posts_cache.value) {3}
[] (BasicVariable BasicType) timestamp int64

    --> w-tainted: write(posts_db.Post.Mentions, posts_cache.key, posts_cache.value) {3}
[] (ArrayVariable ArrayType) mentions []string
     --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[_] (BasicVariable BasicType) "alice" string
     --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[_] (BasicVariable BasicType) "bob" string

    --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post) {3}
[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}
     --> w-tainted: write(posts_db.Post.Creator, posts_cache.key, posts_cache.value) {3}
[_] (FieldVariable FieldType) Creator postnotification.Creator struct{Username "some username" string}
      --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Creator) {3}
[__] (StructVariable UserType) postnotification.Creator struct{Username "some username" string}
       --> w-tainted: write(posts_db.Post.Creator.Username, posts_cache.key, posts_cache.value) {3}
[___] (FieldVariable FieldType) Username "some username" string
        --> w-tainted: write(posts_db.Post.Creator.Username, posts_cache.key, posts_cache.value) {3}
[____] (BasicVariable BasicType) "some username" string
     --> w-tainted: write(posts_db.Post.Mentions, posts_cache.key, posts_cache.value) {3}
[_] (FieldVariable FieldType) Mentions []string
      --> w-tainted: write(posts_db.Post.Mentions, posts_cache.key, posts_cache.value) {3}
[__] (ArrayVariable ArrayType) mentions []string
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[___] (BasicVariable BasicType) "alice" string
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[___] (BasicVariable BasicType) "bob" string
     --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5}         --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_] (FieldVariable FieldType) PostID int64
      --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}           --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[__] (BasicVariable BasicType) postID int64
       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value) {3}
[_] (FieldVariable FieldType) ReqID int64
      --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicVariable BasicType) reqID int64
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
     --> w-tainted: write(posts_db.Post.Text, posts_cache.key, posts_cache.value) {3}
[_] (FieldVariable FieldType) Text string
      --> w-tainted: write(posts_db.Post.Text, posts_cache.key, posts_cache.value) {3}
[__] (BasicVariable BasicType) text string
     --> w-tainted: write(posts_db.Post.Timestamp, posts_cache.key, posts_cache.value) {3}
[_] (FieldVariable FieldType) Timestamp int64
      --> w-tainted: write(posts_db.Post.Timestamp, posts_cache.key, posts_cache.value) {3}
[__] (BasicVariable BasicType) timestamp int64

    --> w-tainted: write(notifications_queue.message) {1}       --> w-tainted: write(notifications_queue.message) {1} --> r-tainted: read(notifications_queue.message) {1}
[] (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string}
     --> w-tainted: write(notifications_queue.Message.PostID) {1}         --> w-tainted: write(notifications_queue.Message.PostID) {1} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[_] (FieldVariable FieldType) PostID string
      --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}           --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[__] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.PostID) {1}           --> w-tainted: write(notifications_queue.Message.PostID) {1} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[__] (BasicVariable BasicType) string
       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
       --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[___] (BasicVariable BasicType) postID int64
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(notifications_queue.Message.ReqID) {1}         --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (FieldVariable FieldType) ReqID string
      --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.ReqID) {1}           --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicVariable BasicType) string
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
       --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (BasicVariable BasicType) reqID int64
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}               --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

[] (BasicVariable BasicType) _ bool

[] (InterfaceVariable UserType) err .error

[] (BasicVariable BasicType) reqIDStr string
     --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}         --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (BasicVariable BasicType) reqID int64
      --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
[_] (BasicVariable BasicType) 10 int

    --> w-tainted: write(timeline_cache.key, timeline_cache.value) {2}
[] (StructVariable UserType) timeline postnotification.Timeline struct{ReqID int64, PostID int64}
     --> w-tainted: write(timeline_cache.key, timeline_cache.value) {2}
[_] (FieldVariable FieldType) PostID int64
      --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}           --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[__] (BasicVariable BasicType) postID int64
       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(timeline_cache.key, timeline_cache.value) {2}
[_] (FieldVariable FieldType) ReqID int64
      --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicVariable BasicType) reqID int64
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

