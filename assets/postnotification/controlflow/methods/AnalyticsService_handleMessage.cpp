[] (-1) (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (23) (Reference UserType) ref <ctx context.Context> @ AnalyticsService 

[] (19) (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (19) (Reference UserType) ref <event postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // read(analytics_queue), 
[__] (19) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), read(analytics_queue), 
[___] (20) (FieldVariable FieldType) PostID string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[________] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[_] (19) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), read(analytics_queue), 
[__] (20) (FieldVariable FieldType) PostID string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_______] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[_] (20) (FieldVariable FieldType) PostID string 
[__] (20) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_______] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[__] (20) (BasicVariable BasicType) PostID string // write(analytics_db), 
[___] (20) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[________] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[_] (20) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (20) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_______] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (20) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (20) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_______] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analytics_db, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} // write(analytics_db), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[___] (20) (BasicVariable BasicType) PostID string // write(analytics_db), 
[____] (20) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_______] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[________] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_________] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

