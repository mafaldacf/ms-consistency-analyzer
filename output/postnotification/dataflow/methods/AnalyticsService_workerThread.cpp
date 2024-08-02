[] (-1) (PointerVariable PointerType) n (*postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers 4 int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers 4 int} 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 

[] (34) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (31) (StructVariable UserType) event postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (31) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[__] (32) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[___] (33) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (24) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

