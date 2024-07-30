[] (-1) (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (28) (Reference UserType) ref <ctx context.Context> @ AnalyticsService 

[] (25) (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (25) (Reference UserType) ref <event postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService 
[__] (25) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[___] (26) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[____] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[_____] (16) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[______] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[________] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (25) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[__] (26) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (16) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (26) (FieldVariable FieldType) PostID string 
[__] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (16) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (26) (BasicVariable BasicType) PostID string // write(analytics_db), 
[___] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[____] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[_____] (16) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[______] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[________] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[_] (26) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (16) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (26) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (16) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analytics_db, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} // write(analytics_db), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[___] (26) (BasicVariable BasicType) PostID string // write(analytics_db), 
[____] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[_____] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[______] (16) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_______] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[________] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_________] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

