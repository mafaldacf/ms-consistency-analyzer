[] (-1) (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (ServiceVariable ServiceType) analytics_service postnotification.AnalyticsService 

[] (45) (InterfaceVariable UserType) ctx context.Context 
[_] (-1) (Reference UserType) ref <ctx context.Context> @ NotifyService 
[__] (34) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (30) (Reference BasicType) ref <reqID int64> @ NotifyService 
[__] (0) (BasicVariable BasicType) ReqID string 
[___] (36) (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (37) (BasicVariable BasicType) ReqID string 
[_____] (38) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 

[] (46) (BasicVariable BasicType) postID int64 // read(posts_db), read(analytics_db), 
[_] (32) (Reference BasicType) ref <postID int64> @ NotifyService // read(posts_db), read(analytics_db), 
[__] (47) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[___] (39) (Reference FieldType) ref <PostID string> @ NotifyService // read(posts_db), read(analytics_db), 
[____] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[_____] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(posts_db), 
[_] (0) (StructVariable StructType) struct{Key "postid" string, Value int64} // read(posts_db), 
[__] (0) (FieldVariable FieldType) Key "postid" string // read(posts_db), 
[___] (0) (BasicVariable BasicType) "postid" string // read(posts_db), 
[__] (0) (FieldVariable FieldType) Value int64 // read(posts_db), 
[___] (46) (BasicVariable BasicType) postID int64 // read(posts_db), read(analytics_db), 
[____] (32) (Reference BasicType) ref <postID int64> @ NotifyService // read(posts_db), read(analytics_db), 
[_____] (47) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[______] (39) (Reference FieldType) ref <PostID string> @ NotifyService // read(posts_db), read(analytics_db), 
[_______] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[________] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post} // read(posts_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) res bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (InterfaceVariable UserType) err .error 

