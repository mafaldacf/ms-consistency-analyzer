[] (-1) (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue} 
[__] (-1) (ServiceVariable ServiceType) analytics_service postnotification.AnalyticsService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (1) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (-1) (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[__] (38) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} // write(posts_db), 
[_] (3) (Reference UserType) ref <post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}}> @ UploadService // write(posts_db), 
[__] (5) (FieldVariable FieldType) PostID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[____] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[__] (7) (FieldVariable FieldType) Text string // write(posts_db), 
[___] (8) (BasicVariable BasicType) text string // write(posts_db), 
[__] (9) (FieldVariable FieldType) Mentions []string // write(posts_db), 
[___] (10) (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[____] (11) (BasicVariable BasicType) "alice" string // write(posts_db), 
[____] (12) (BasicVariable BasicType) "bob" string // write(posts_db), 
[__] (13) (FieldVariable FieldType) Timestamp int64 // write(posts_db), 
[___] (14) (BasicVariable BasicType) timestamp int64 // write(posts_db), 
[__] (15) (FieldVariable FieldType) Creator postnotification.Creator struct{Username string} // write(posts_db), 
[___] (16) (StructVariable UserType) postnotification.Creator struct{Username string} // write(posts_db), 
[____] (17) (FieldVariable FieldType) Username "some username" string // write(posts_db), 
[_____] (18) (BasicVariable BasicType) "some username" string // write(posts_db), 
[__] (4) (FieldVariable FieldType) ReqID int64 // write(posts_db), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), 
[____] (38) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[_] (0) (FieldVariable FieldType) PostID int64 
[__] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[____] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[__] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_____] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (InterfaceVariable UserType) err .error 

[] (19) (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string} // write(analytics_queue), read(analytics_queue), 
[_] (20) (FieldVariable FieldType) PostID string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[__] (21) (BasicVariable BasicType) string // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[___] (22) (BasicVariable BasicType) PostID int64 // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[____] (5) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_____] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[______] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

