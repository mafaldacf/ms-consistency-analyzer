[] (-1) (PointerVariable PointerType) n (*postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (23) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (19) (StructVariable UserType) event postnotification.TriggerAnalyticsMessage struct{PostID string} // read(analytics_queue), 
[_] (19) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), read(analytics_queue), 
[__] (20) (FieldVariable FieldType) PostID string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (4) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_______] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

