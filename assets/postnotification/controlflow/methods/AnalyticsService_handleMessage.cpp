[] (-1) (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int} 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (28) (Reference UserType) ref <ctx context.Context> @ AnalyticsService 

[] (24) (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (24) (Reference UserType) ref <event postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // read(analytics_queue), 
[__] (24) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), read(analytics_queue), 
[___] (25) (FieldVariable FieldType) PostID string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (26) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (27) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[________] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[_] (24) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), read(analytics_queue), 
[__] (25) (FieldVariable FieldType) PostID string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (26) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (27) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[_] (25) (FieldVariable FieldType) PostID string 
[__] (25) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (26) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (27) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[__] (25) (BasicVariable BasicType) PostID string // write(analytics_db), 
[___] (25) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (26) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (27) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[________] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[_] (25) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (25) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (26) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (27) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (25) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (25) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (26) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (27) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analytics_db, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} // write(analytics_db), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[___] (25) (BasicVariable BasicType) PostID string // write(analytics_db), 
[____] (25) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (26) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[______] (27) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_______] (16) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[________] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_________] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

