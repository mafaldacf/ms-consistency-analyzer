[] (-1) (PointerVariable PointerType) a (*postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (45) (Reference UserType) ref <ctx context.Context> @ StorageService 
[__] (-1) (Reference UserType) ref <ctx context.Context> @ NotifyService 
[___] (34) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (BasicVariable BasicType) postID int64 // read(analytics_db), 
[_] (46) (Reference BasicType) ref <postID int64> @ StorageService // read(posts_db), read(analytics_db), 
[__] (32) (Reference BasicType) ref <postID int64> @ NotifyService // read(posts_db), read(analytics_db), 
[___] (47) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[____] (39) (Reference FieldType) ref <PostID string> @ NotifyService // read(posts_db), read(analytics_db), 
[_____] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[______] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analytics_db, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(analytics_db), 
[_] (0) (StructVariable StructType) struct{Key "postid" string, Value int64} // read(analytics_db), 
[__] (0) (FieldVariable FieldType) Key "postid" string // read(analytics_db), 
[___] (0) (BasicVariable BasicType) "postid" string // read(analytics_db), 
[__] (0) (FieldVariable FieldType) Value int64 // read(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // read(analytics_db), 
[____] (46) (Reference BasicType) ref <postID int64> @ StorageService // read(posts_db), read(analytics_db), 
[_____] (32) (Reference BasicType) ref <postID int64> @ NotifyService // read(posts_db), read(analytics_db), 
[______] (47) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[_______] (39) (Reference FieldType) ref <PostID string> @ NotifyService // read(posts_db), read(analytics_db), 
[________] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[_________] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = analytics_db, collection = analytics_collection} // read(analytics_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) res bool 

[] (-1) (InterfaceVariable UserType) err .error 

