[] (-1) (PointerVariable PointerType) u (*postnotification.UploadServiceImpl struct{storage_service postnotification.StorageService, media_service postnotification.MediaService, notifications_queue Queue, timeline_cache Cache}) 
[_] (0) (StructVariable UserType) postnotification.UploadServiceImpl struct{storage_service postnotification.StorageService, media_service postnotification.MediaService, notifications_queue Queue, timeline_cache Cache} 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (-1) (ServiceVariable ServiceType) media_service postnotification.MediaService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) timeline_cache Cache 

[] (1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) username string 

[] (18) (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 

[] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[_] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (8) (BasicVariable BasicType) mediaID int64 // write(media_db), 

[] (2) (StructVariable UserType) media postnotification.Media struct{MediaID int64, PostID int64, Content string} // write(media_db), 
[_] (5) (FieldVariable FieldType) PostID int64 // write(media_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (7) (FieldVariable FieldType) MediaID int64 // write(media_db), 
[__] (8) (BasicVariable BasicType) mediaID int64 // write(media_db), 
[_] (3) (FieldVariable FieldType) Content "a nice content" string // write(media_db), 
[__] (4) (BasicVariable BasicType) "a nice content" string // write(media_db), 

[] (24) (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 

[] (20) (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[_] (21) (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[_] (22) (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 

[] (10) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} // write(posts_cache), write(posts_db), 
[_] (11) (FieldVariable FieldType) Creator postnotification.Creator struct{Username string} // write(posts_db), write(posts_cache), 
[__] (12) (StructVariable UserType) postnotification.Creator struct{Username string} // write(posts_cache), write(posts_db), 
[___] (13) (FieldVariable FieldType) Username "some username" string // write(posts_db), write(posts_cache), 
[____] (14) (BasicVariable BasicType) "some username" string // write(posts_db), write(posts_cache), 
[_] (15) (FieldVariable FieldType) ReqID int64 // write(posts_db), write(posts_cache), 
[__] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[___] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (16) (FieldVariable FieldType) PostID int64 // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (17) (FieldVariable FieldType) Text string // write(posts_db), write(posts_cache), 
[__] (18) (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 
[_] (19) (FieldVariable FieldType) Mentions []string // write(posts_db), write(posts_cache), 
[__] (20) (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[___] (21) (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[___] (22) (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 
[_] (23) (FieldVariable FieldType) Timestamp int64 // write(posts_db), write(posts_cache), 
[__] (24) (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 

[] (29) (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} // write(notifications_queue), 
[_] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[__] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[___] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[____] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), 
[__] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[___] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) reqIDStr string 
[_] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[__] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (0) (BasicVariable BasicType) 10 int 

[] (-1) (StructVariable UserType) timeline postnotification.Timeline struct{ReqID int64, PostID int64} // write(timeline_cache), 
[_] (0) (FieldVariable FieldType) ReqID int64 // write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[___] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

