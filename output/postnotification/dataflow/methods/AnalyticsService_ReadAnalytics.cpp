[] (-1) (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int} 
[__] (0) (FieldVariable FieldType) analyticsDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsDb NoSQLDatabase 
[__] (0) (FieldVariable FieldType) analyticsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (0) (FieldVariable FieldType) numWorkers 4 int 
[___] (0) (BasicVariable BasicType) 4 int 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (50) (Reference UserType) ref <ctx context.Context> @ StorageService 
[__] (-1) (Reference UserType) ref <ctx context.Context> @ NotifyService 
[___] (39) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (BasicVariable BasicType) postID int64 
[_] (51) (Reference BasicType) ref <postID int64> @ StorageService 
[__] (37) (Reference BasicType) ref <postID int64> @ NotifyService 
[___] (52) (BasicVariable BasicType) PostID string 
[____] (44) (Reference FieldType) ref <PostID string> @ NotifyService 
[_____] (45) (BasicVariable BasicType) PostID string 
[______] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analyticsDb, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "postid" string, Value int64} 
[__] (0) (FieldVariable FieldType) Key "postid" string 
[___] (0) (BasicVariable BasicType) "postid" string 
[__] (0) (FieldVariable FieldType) Value int64 
[___] (-1) (BasicVariable BasicType) postID int64 
[____] (51) (Reference BasicType) ref <postID int64> @ StorageService 
[_____] (37) (Reference BasicType) ref <postID int64> @ NotifyService 
[______] (52) (BasicVariable BasicType) PostID string 
[_______] (44) (Reference FieldType) ref <PostID string> @ NotifyService 
[________] (45) (BasicVariable BasicType) PostID string 
[_________] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = analyticsDb, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) res bool 

[] (-1) (InterfaceVariable UserType) err .error 

