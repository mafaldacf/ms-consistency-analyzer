[] (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue}) 
[_] (StructVariable UserType) postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue} 
[__] (FieldVariable FieldType) analyticsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (FieldVariable FieldType) analyticsService postnotification.AnalyticsService 
[___] (ServiceVariable ServiceType) analyticsService postnotification.AnalyticsService 
[__] (FieldVariable FieldType) mediaService postnotification.MediaService 
[___] (ServiceVariable ServiceType) mediaService postnotification.MediaService 
[__] (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 
[__] (FieldVariable FieldType) posts_cache Cache 
[___] (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService 
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (BasicVariable BasicType) reqID int64 
[_] (Reference BasicType) ref <reqID int64> @ NotifyService 
[__] (BasicVariable BasicType) ReqID string 
[___] (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (BasicVariable BasicType) ReqID string 
[_____] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) postID int64 
[_] (Reference BasicType) ref <postID int64> @ NotifyService 
[__] (BasicVariable BasicType) PostID string 
[___] (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (BasicVariable BasicType) PostID string 
[_____] (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} 

[] (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "postid" string, Value int64} 
[__] (FieldVariable FieldType) Key "postid" string 
[___] (BasicVariable BasicType) "postid" string 
[__] (FieldVariable FieldType) Value int64 
[___] (BasicVariable BasicType) postID int64 
[____] (Reference BasicType) ref <postID int64> @ NotifyService 
[_____] (BasicVariable BasicType) PostID string 
[______] (Reference FieldType) ref <PostID string> @ NotifyService 
[_______] (BasicVariable BasicType) PostID string 
[________] (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post} 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) res bool 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (InterfaceVariable UserType) err .error 

