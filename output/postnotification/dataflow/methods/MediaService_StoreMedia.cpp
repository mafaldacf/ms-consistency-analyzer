[] (PointerVariable PointerType) s (*postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase})
[_] (StructVariable UserType) postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase}
[__] (FieldVariable FieldType) mediaDb NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) mediaDb NoSQLDatabase

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ UploadService

    --> w-tainted: write(media_db.Media) {1}
[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}
     --> w-tainted: write(media_db.Media) {1}
[_] (Reference UserType) ref <media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}> @ UploadService
      --> w-tainted: write(media_db.Media.Content) {1}
[__] (FieldVariable FieldType) Content "HELLO WORLD!" untyped string
       --> w-tainted: write(media_db.Media.Content) {1}
[___] (BasicVariable BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string
      --> w-tainted: write(media_db.Media.MediaID) {1}
[__] (FieldVariable FieldType) MediaID int64
       --> w-tainted: write(media_db.Media.MediaID) {1}
[___] (BasicVariable BasicType) mediaID int64
      --> w-tainted: write(media_db.Media.PostID) {1}
[__] (FieldVariable FieldType) PostID int64
       --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[___] (BasicVariable BasicType) postID int64
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = media, collection = media}

[] (InterfaceVariable UserType) err .error

