[] (-1) (PointerVariable PointerType) n (*postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int} 
[__] (0) (FieldVariable FieldType) analyticsDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsDb NoSQLDatabase 
[__] (0) (FieldVariable FieldType) analyticsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (0) (FieldVariable FieldType) numWorkers 4 int 
[___] (0) (BasicVariable BasicType) 4 int 

[] (28) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (25) (StructVariable UserType) event postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (25) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[__] (26) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[___] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

