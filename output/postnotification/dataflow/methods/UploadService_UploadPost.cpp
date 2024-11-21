[] (PointerObject PointerType) u (*postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache})
[_] (StructObject UserType) postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache}
[__] (FieldObject FieldType) mediaService postnotification.MediaService
[___] (ServiceObject ServiceType) mediaService postnotification.MediaService
[__] (FieldObject FieldType) notificationsQueue Queue
[___] (BlueprintBackendObject BlueprintBackendType) notificationsQueue Queue
[__] (FieldObject FieldType) storageService postnotification.StorageService
[___] (ServiceObject ServiceType) storageService postnotification.StorageService
[__] (FieldObject FieldType) timelineCache Cache
[___] (BlueprintBackendObject BlueprintBackendType) timelineCache Cache

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) username string

    --> w-tainted: write(posts_db.Post.Text, posts_cache.key, posts_cache.value) {3}
[] (BasicObject BasicType) text string

    --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}       --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[] (BasicObject BasicType) reqID int64
     --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}         --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

    --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}       --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[] (BasicObject BasicType) postID int64
     --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}         --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

    --> w-tainted: write(media_db.Media.MediaID) {1}
[] (BasicObject BasicType) mediaID int64

    --> w-tainted: write(media_db.Media) {1}
[] (StructObject UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}
     --> w-tainted: write(media_db.Media.Content) {1}
[_] (FieldObject FieldType) Content "HELLO WORLD!" untyped string
      --> w-tainted: write(media_db.Media.Content) {1}
[__] (BasicObject BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string
     --> w-tainted: write(media_db.Media.MediaID) {1}
[_] (FieldObject FieldType) MediaID int64
      --> w-tainted: write(media_db.Media.MediaID) {1}
[__] (BasicObject BasicType) mediaID int64
     --> w-tainted: write(media_db.Media.PostID) {1}
[_] (FieldObject FieldType) PostID int64
      --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}           --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[__] (BasicObject BasicType) postID int64
       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

    --> w-tainted: write(posts_db.Post.Timestamp, posts_cache.key, posts_cache.value) {3}
[] (BasicObject BasicType) timestamp int64

    --> w-tainted: write(posts_db.Post.Mentions, posts_cache.key, posts_cache.value) {3}
[] (ArrayObject ArrayType) mentions []string
     --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[_] (BasicObject BasicType) "alice" string
     --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[_] (BasicObject BasicType) "bob" string

    --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post) {3}
[] (StructObject UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}
     --> w-tainted: write(posts_db.Post.Creator, posts_cache.key, posts_cache.value) {3}
[_] (FieldObject FieldType) Creator postnotification.Creator struct{Username "some username" string}
      --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Creator) {3}
[__] (StructObject UserType) postnotification.Creator struct{Username "some username" string}
       --> w-tainted: write(posts_db.Post.Creator.Username, posts_cache.key, posts_cache.value) {3}
[___] (FieldObject FieldType) Username "some username" string
        --> w-tainted: write(posts_db.Post.Creator.Username, posts_cache.key, posts_cache.value) {3}
[____] (BasicObject BasicType) "some username" string
     --> w-tainted: write(posts_db.Post.Mentions, posts_cache.key, posts_cache.value) {3}
[_] (FieldObject FieldType) Mentions []string
      --> w-tainted: write(posts_db.Post.Mentions, posts_cache.key, posts_cache.value) {3}
[__] (ArrayObject ArrayType) mentions []string
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[___] (BasicObject BasicType) "alice" string
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.Mentions) {3}
[___] (BasicObject BasicType) "bob" string
     --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5}         --> w-tainted: write(posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {5} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_] (FieldObject FieldType) PostID int64
      --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}           --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[__] (BasicObject BasicType) postID int64
       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value) {3}
[_] (FieldObject FieldType) ReqID int64
      --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicObject BasicType) reqID int64
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
     --> w-tainted: write(posts_db.Post.Text, posts_cache.key, posts_cache.value) {3}
[_] (FieldObject FieldType) Text string
      --> w-tainted: write(posts_db.Post.Text, posts_cache.key, posts_cache.value) {3}
[__] (BasicObject BasicType) text string
     --> w-tainted: write(posts_db.Post.Timestamp, posts_cache.key, posts_cache.value) {3}
[_] (FieldObject FieldType) Timestamp int64
      --> w-tainted: write(posts_db.Post.Timestamp, posts_cache.key, posts_cache.value) {3}
[__] (BasicObject BasicType) timestamp int64

    --> w-tainted: write(notifications_queue.Message) {1}       --> w-tainted: write(notifications_queue.Message) {1} --> r-tainted: read(notifications_queue.Message) {1}
[] (StructObject UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string}
     --> w-tainted: write(notifications_queue.Message.PostID) {1}         --> w-tainted: write(notifications_queue.Message.PostID) {1} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[_] (FieldObject FieldType) PostID string
      --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}           --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[__] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.PostID) {1}           --> w-tainted: write(notifications_queue.Message.PostID) {1} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[__] (BasicObject BasicType) string
       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
       --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[___] (BasicObject BasicType) postID int64
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(notifications_queue.Message.ReqID) {1}         --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (FieldObject FieldType) ReqID string
      --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.ReqID) {1}           --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicObject BasicType) string
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
       --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (BasicObject BasicType) reqID int64
        --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}               --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

[] (BasicObject BasicType) _ bool

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) reqIDStr string
     --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}         --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (BasicObject BasicType) reqID int64
      --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
[_] (BasicObject BasicType) 10 int

    --> w-tainted: write(timeline_cache.key, timeline_cache.value) {2}
[] (StructObject UserType) timeline postnotification.Timeline struct{ReqID int64, PostID int64}
     --> w-tainted: write(timeline_cache.key, timeline_cache.value) {2}
[_] (FieldObject FieldType) PostID int64
      --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}           --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[__] (BasicObject BasicType) postID int64
       --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(timeline_cache.key, timeline_cache.value) {2}
[_] (FieldObject FieldType) ReqID int64
      --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}           --> w-tainted: write(posts_db.Post.ReqID, posts_cache.key, posts_cache.value, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicObject BasicType) reqID int64
       --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6}             --> w-tainted: write(posts_cache.key, posts_cache.value, posts_db.Post.ReqID, notifications_queue.Message.ReqID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

