[] (PointerObject PointerType) s (*postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase})
[_] (StructObject UserType) postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase}
[__] (FieldObject FieldType) mediaDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) mediaDb NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ UploadService

    --> w-tainted: write(media_db.Media) {1}
[] (StructObject UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}
     --> w-tainted: write(media_db.Media) {1}
[_] (Reference UserType) ref <media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}> @ UploadService
      --> w-tainted: write(media_db.Media.Content) {1}
[__] (FieldObject FieldType) Content "HELLO WORLD!" untyped string
       --> w-tainted: write(media_db.Media.Content) {1}
[___] (BasicObject BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string
      --> w-tainted: write(media_db.Media.MediaID) {1}
[__] (FieldObject FieldType) MediaID int64
       --> w-tainted: write(media_db.Media.MediaID) {1}
[___] (BasicObject BasicType) mediaID int64
      --> w-tainted: write(media_db.Media.PostID) {1}
[__] (FieldObject FieldType) PostID int64
       --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}             --> w-tainted: write(media_db.Media.PostID, posts_db.Post.PostID, posts_cache.key, posts_cache.value, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[___] (BasicObject BasicType) postID int64
        --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9}               --> w-tainted: write(media_db.Media.PostID, posts_cache.key, posts_cache.value, posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {9} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = media, collection = media}

[] (InterfaceObject UserType) err .error

