[] (-1) (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (50) (Reference UserType) ref <ctx context.Context> @ StorageService 
[__] (-1) (Reference UserType) ref <ctx context.Context> @ NotifyService 
[___] (39) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (BasicVariable BasicType) postID int64 
[_] (51) (Reference BasicType) ref <postID int64> @ StorageService 
[__] (37) (Reference BasicType) ref <postID int64> @ NotifyService 
[___] (52) (BasicVariable BasicType) PostID string 
[____] (47) (Reference FieldType) ref <PostID string> @ NotifyService 
[_____] (48) (BasicVariable BasicType) PostID string 
[______] (49) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analytics_db, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "postid" string, Value int64} 
[__] (0) (FieldVariable FieldType) Value int64 
[___] (-1) (BasicVariable BasicType) postID int64 
[____] (51) (Reference BasicType) ref <postID int64> @ StorageService 
[_____] (37) (Reference BasicType) ref <postID int64> @ NotifyService 
[______] (52) (BasicVariable BasicType) PostID string 
[_______] (47) (Reference FieldType) ref <PostID string> @ NotifyService 
[________] (48) (BasicVariable BasicType) PostID string 
[_________] (49) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (0) (FieldVariable FieldType) Key "postid" string 
[___] (0) (BasicVariable BasicType) "postid" string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = analytics_db, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) res bool 

[] (-1) (InterfaceVariable UserType) err .error 

