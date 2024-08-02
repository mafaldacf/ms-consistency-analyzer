[] (-1) (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, media_service postnotification.MediaService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, media_service postnotification.MediaService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (ServiceVariable ServiceType) analytics_service postnotification.AnalyticsService 
[__] (-1) (ServiceVariable ServiceType) media_service postnotification.MediaService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_db NoSQLDatabase 

[] (56) (InterfaceVariable UserType) ctx context.Context 
[_] (-1) (Reference UserType) ref <ctx context.Context> @ NotifyService 
[__] (45) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (41) (Reference BasicType) ref <reqID int64> @ NotifyService 
[__] (0) (BasicVariable BasicType) ReqID string 
[___] (47) (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (48) (BasicVariable BasicType) ReqID string 
[_____] (49) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (57) (BasicVariable BasicType) postID int64 
[_] (43) (Reference BasicType) ref <postID int64> @ NotifyService 
[__] (58) (BasicVariable BasicType) PostID string 
[___] (50) (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (51) (BasicVariable BasicType) PostID string 
[_____] (52) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "postid" string, Value int64} 
[__] (0) (FieldVariable FieldType) Value int64 
[___] (57) (BasicVariable BasicType) postID int64 
[____] (43) (Reference BasicType) ref <postID int64> @ NotifyService 
[_____] (58) (BasicVariable BasicType) PostID string 
[______] (50) (Reference FieldType) ref <PostID string> @ NotifyService 
[_______] (51) (BasicVariable BasicType) PostID string 
[________] (52) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (0) (FieldVariable FieldType) Key "postid" string 
[___] (0) (BasicVariable BasicType) "postid" string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) res bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (InterfaceVariable UserType) err .error 

