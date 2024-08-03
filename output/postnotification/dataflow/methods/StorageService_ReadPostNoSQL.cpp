[] (-1) (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue} 
[__] (0) (FieldVariable FieldType) analyticsService postnotification.AnalyticsService 
[___] (-1) (ServiceVariable ServiceType) analyticsService postnotification.AnalyticsService 
[__] (0) (FieldVariable FieldType) mediaService postnotification.MediaService 
[___] (-1) (ServiceVariable ServiceType) mediaService postnotification.MediaService 
[__] (0) (FieldVariable FieldType) posts_cache Cache 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (0) (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 
[__] (0) (FieldVariable FieldType) analyticsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 

[] (50) (InterfaceVariable UserType) ctx context.Context 
[_] (-1) (Reference UserType) ref <ctx context.Context> @ NotifyService 
[__] (39) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (35) (Reference BasicType) ref <reqID int64> @ NotifyService 
[__] (0) (BasicVariable BasicType) ReqID string 
[___] (41) (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (42) (BasicVariable BasicType) ReqID string 
[_____] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (51) (BasicVariable BasicType) postID int64 
[_] (37) (Reference BasicType) ref <postID int64> @ NotifyService 
[__] (52) (BasicVariable BasicType) PostID string 
[___] (44) (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (45) (BasicVariable BasicType) PostID string 
[_____] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "postid" string, Value int64} 
[__] (0) (FieldVariable FieldType) Key "postid" string 
[___] (0) (BasicVariable BasicType) "postid" string 
[__] (0) (FieldVariable FieldType) Value int64 
[___] (51) (BasicVariable BasicType) postID int64 
[____] (37) (Reference BasicType) ref <postID int64> @ NotifyService 
[_____] (52) (BasicVariable BasicType) PostID string 
[______] (44) (Reference FieldType) ref <PostID string> @ NotifyService 
[_______] (45) (BasicVariable BasicType) PostID string 
[________] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) res bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (InterfaceVariable UserType) err .error 

