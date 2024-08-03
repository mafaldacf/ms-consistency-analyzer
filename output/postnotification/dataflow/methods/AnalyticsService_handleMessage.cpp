[] (-1) (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int} 
[__] (0) (FieldVariable FieldType) analyticsDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsDb NoSQLDatabase 
[__] (0) (FieldVariable FieldType) analyticsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (0) (FieldVariable FieldType) numWorkers 4 int 
[___] (0) (BasicVariable BasicType) 4 int 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (28) (Reference UserType) ref <ctx context.Context> @ AnalyticsService 

[] (25) (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (25) (Reference UserType) ref <event postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService 
[__] (25) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[___] (26) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[____] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[_____] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[______] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[________] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (25) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[__] (26) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (26) (FieldVariable FieldType) PostID string 
[__] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (26) (BasicVariable BasicType) PostID string // write(analytics_db), 
[___] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[____] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[_____] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[______] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[________] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[_] (26) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (26) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analyticsDb, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} // write(analytics_db), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[___] (26) (BasicVariable BasicType) PostID string // write(analytics_db), 
[____] (26) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[_____] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[______] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_______] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[________] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_________] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

