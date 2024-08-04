[] (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}) 
[_] (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int} 
[__] (FieldVariable FieldType) analyticsDb NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsDb NoSQLDatabase 
[__] (FieldVariable FieldType) analyticsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (FieldVariable FieldType) numWorkers 4 int 
[___] (BasicVariable BasicType) 4 int 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ StorageService 
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService 
[___] (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (BasicVariable BasicType) postID int64 
[_] (Reference BasicType) ref <postID int64> @ StorageService 
[__] (Reference BasicType) ref <postID int64> @ NotifyService 
[___] (BasicVariable BasicType) PostID string 
[____] (Reference FieldType) ref <PostID string> @ NotifyService 
[_____] (BasicVariable BasicType) PostID string 
[______] (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analyticsDb, collection = analytics_collection} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "postid" string, Value int64} 
[__] (FieldVariable FieldType) Key "postid" string 
[___] (BasicVariable BasicType) "postid" string 
[__] (FieldVariable FieldType) Value int64 
[___] (BasicVariable BasicType) postID int64 
[____] (Reference BasicType) ref <postID int64> @ StorageService 
[_____] (Reference BasicType) ref <postID int64> @ NotifyService 
[______] (BasicVariable BasicType) PostID string 
[_______] (Reference FieldType) ref <PostID string> @ NotifyService 
[________] (BasicVariable BasicType) PostID string 
[_________] (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = analyticsDb, collection = analytics_collection} 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) res bool 

[] (InterfaceVariable UserType) err .error 

