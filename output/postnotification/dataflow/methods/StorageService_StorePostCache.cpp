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
[_] (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (BasicVariable BasicType) reqID int64 
[_] (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} // write(posts_cache), 
[_] (Reference UserType) ref <post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}> @ UploadService // write(posts_cache), write(posts_db), 
[__] (FieldVariable FieldType) Creator postnotification.Creator struct{Username "some username" string} // write(posts_db), write(posts_cache), 
[___] (StructVariable UserType) postnotification.Creator struct{Username "some username" string} // write(posts_cache), write(posts_db), 
[____] (FieldVariable FieldType) Username "some username" string // write(posts_db), write(posts_cache), 
[_____] (BasicVariable BasicType) "some username" string // write(posts_db), write(posts_cache), 
[__] (FieldVariable FieldType) Mentions []string // write(posts_db), write(posts_cache), 
[___] (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[____] (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[____] (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 
[__] (FieldVariable FieldType) PostID int64 // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (FieldVariable FieldType) ReqID int64 // write(posts_db), write(posts_cache), 
[___] (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (FieldVariable FieldType) Text string // write(posts_db), write(posts_cache), 
[___] (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 
[__] (FieldVariable FieldType) Timestamp int64 // write(posts_db), write(posts_cache), 
[___] (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 
[_] (FieldVariable FieldType) PostID int64 // write(posts_cache), 
[__] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (BasicVariable BasicType) PostID int64 // write(posts_cache), 
[___] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[____] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) postIDStr string 
[_] (BasicVariable BasicType) PostID int64 // write(posts_cache), 
[__] (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (BasicVariable BasicType) 10 int 

