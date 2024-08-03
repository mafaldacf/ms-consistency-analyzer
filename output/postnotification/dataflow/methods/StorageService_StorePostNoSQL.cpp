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

[] (1) (InterfaceVariable UserType) ctx context.Context 
[_] (1) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (9) (BasicVariable BasicType) reqID int64 
[_] (-1) (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[__] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (10) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} // write(posts_db), 
[_] (10) (Reference UserType) ref <post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}> @ UploadService // write(posts_cache), write(posts_db), 
[__] (20) (FieldVariable FieldType) Creator postnotification.Creator struct{Username "some username" string} // write(posts_db), write(posts_cache), 
[___] (21) (StructVariable UserType) postnotification.Creator struct{Username "some username" string} // write(posts_cache), write(posts_db), 
[____] (22) (FieldVariable FieldType) Username "some username" string // write(posts_db), write(posts_cache), 
[_____] (23) (BasicVariable BasicType) "some username" string // write(posts_db), write(posts_cache), 
[__] (24) (FieldVariable FieldType) ReqID int64 // write(posts_db), write(posts_cache), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[____] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (11) (FieldVariable FieldType) PostID int64 // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (12) (FieldVariable FieldType) Text string // write(posts_db), write(posts_cache), 
[___] (13) (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 
[__] (14) (FieldVariable FieldType) Mentions []string // write(posts_db), write(posts_cache), 
[___] (15) (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[____] (16) (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[____] (17) (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 
[__] (18) (FieldVariable FieldType) Timestamp int64 // write(posts_db), write(posts_cache), 
[___] (19) (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 
[_] (11) (FieldVariable FieldType) PostID int64 
[__] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[___] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[____] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (InterfaceVariable UserType) err .error 

[] (25) (StructVariable UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string} // write(analytics_queue), 
[_] (26) (FieldVariable FieldType) PostID string // write(analytics_queue), write(analytics_db), 
[__] (27) (BasicVariable BasicType) string // write(analytics_queue), write(analytics_db), 
[___] (11) (BasicVariable BasicType) PostID int64 // write(analytics_queue), write(analytics_db), 
[____] (11) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[_____] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[______] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

