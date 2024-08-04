[] (PointerVariable PointerType) n (*postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}) 
[_] (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int} 
[__] (FieldVariable FieldType) analyticsDb NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsDb NoSQLDatabase 
[__] (FieldVariable FieldType) analyticsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (FieldVariable FieldType) numWorkers 4 int 
[___] (BasicVariable BasicType) 4 int 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ChanVariable ChanType) forever chan struct{} 

[] (StructVariable UserType) event postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[__] (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

