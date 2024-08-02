[] (-1) (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers 4 int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers 4 int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (34) (Reference UserType) ref <ctx context.Context> @ AnalyticsService 

[] (31) (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string} 
[_] (31) (Reference UserType) ref <event postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService 
[__] (31) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[___] (32) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[____] (33) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[_____] (24) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[______] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[________] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (31) (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService // write(analytics_queue), 
[__] (32) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[___] (33) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (24) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (32) (FieldVariable FieldType) PostID string 
[__] (32) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (33) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (24) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (32) (BasicVariable BasicType) PostID string // write(analytics_db), 
[___] (32) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[____] (33) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[_____] (24) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[______] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[________] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[_] (32) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (32) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (33) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (24) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (32) (BasicVariable BasicType) PostID string // write(analytics_db), 
[__] (32) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (33) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[____] (24) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_____] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[______] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_______] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analytics_db, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} // write(analytics_db), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(analytics_db), 
[___] (32) (BasicVariable BasicType) PostID string // write(analytics_db), 
[____] (32) (Reference FieldType) ref <PostID string> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[_____] (33) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[______] (24) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[_______] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[________] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_________] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

