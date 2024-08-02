[] (-1) (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, media_service postnotification.MediaService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, media_service postnotification.MediaService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (ServiceVariable ServiceType) analytics_service postnotification.AnalyticsService 
[__] (-1) (ServiceVariable ServiceType) media_service postnotification.MediaService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_db NoSQLDatabase 

[] (7) (InterfaceVariable UserType) ctx context.Context 
[_] (7) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (-1) (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[__] (49) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} // write(posts_cache), 
[_] (16) (Reference UserType) ref <post postnotification.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}}> @ UploadService // write(posts_cache), write(posts_db), 
[__] (23) (FieldVariable FieldType) ReqID int64 // write(posts_db), write(posts_cache), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[____] (49) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (24) (FieldVariable FieldType) PostID int64 // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (25) (FieldVariable FieldType) Text string // write(posts_db), write(posts_cache), 
[___] (26) (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 
[__] (27) (FieldVariable FieldType) Mentions []string // write(posts_db), write(posts_cache), 
[___] (28) (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[____] (29) (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[____] (30) (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 
[__] (17) (FieldVariable FieldType) Timestamp int64 // write(posts_db), write(posts_cache), 
[___] (18) (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 
[__] (19) (FieldVariable FieldType) Creator postnotification.Creator struct{Username string} // write(posts_db), write(posts_cache), 
[___] (20) (StructVariable UserType) postnotification.Creator struct{Username string} // write(posts_cache), write(posts_db), 
[____] (21) (FieldVariable FieldType) Username "some username" string // write(posts_db), write(posts_cache), 
[_____] (22) (BasicVariable BasicType) "some username" string // write(posts_db), write(posts_cache), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(posts_cache), 
[__] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (0) (BasicVariable BasicType) PostID int64 // write(posts_cache), 
[___] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[____] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_____] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) postIDStr string 
[_] (0) (BasicVariable BasicType) PostID int64 // write(posts_cache), 
[__] (24) (Reference FieldType) ref <PostID int64> @ UploadService // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (52) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (0) (BasicVariable BasicType) 10 int 

