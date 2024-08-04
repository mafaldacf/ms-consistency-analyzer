[] (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}) 
[_] (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int} 
[__] (FieldVariable FieldType) analyticsDb NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsDb NoSQLDatabase 
[__] (FieldVariable FieldType) analyticsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (FieldVariable FieldType) numWorkers 4 int 
[___] (BasicVariable BasicType) 4 int 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ AnalyticsService 

[] (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (Reference UserType) ref <event postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService 
[__] (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[___] (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[____] (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[_____] (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[______] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_______] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[________] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[__] (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (FieldVariable FieldType) PostID string 
[__] (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (BasicVariable BasicType) PostID string // write(analytics_db), 
[___] (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[____] (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[_____] (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[______] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_______] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[________] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) postID int64 // write(analytics_db), 
[_] (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (InterfaceVariable UserType) err .error 
[_] (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analyticsDb, collection = analytics_collection} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} // write(analytics_db), 
[_] (FieldVariable FieldType) PostID int64 // write(analytics_db), 
[__] (BasicVariable BasicType) postID int64 // write(analytics_db), 
[___] (BasicVariable BasicType) PostID string // write(analytics_db), 
[____] (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[_____] (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[______] (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_______] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[________] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_________] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

