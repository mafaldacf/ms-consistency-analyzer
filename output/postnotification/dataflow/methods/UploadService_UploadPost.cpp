[] (-1) (PointerVariable PointerType) u (*postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache}) 
[_] (0) (StructVariable UserType) postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache} 
[__] (0) (FieldVariable FieldType) storageService postnotification.StorageService 
[___] (-1) (ServiceVariable ServiceType) storageService postnotification.StorageService 
[__] (0) (FieldVariable FieldType) mediaService postnotification.MediaService 
[___] (-1) (ServiceVariable ServiceType) mediaService postnotification.MediaService 
[__] (0) (FieldVariable FieldType) notificationsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 
[__] (0) (FieldVariable FieldType) timelineCache Cache 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) timelineCache Cache 

[] (1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) username string 

[] (13) (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 

[] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[_] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (6) (BasicVariable BasicType) mediaID int64 // write(media_db), 

[] (2) (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string} // write(media_db), 
[_] (3) (FieldVariable FieldType) PostID int64 // write(media_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (5) (FieldVariable FieldType) MediaID int64 // write(media_db), 
[__] (6) (BasicVariable BasicType) mediaID int64 // write(media_db), 
[_] (7) (FieldVariable FieldType) Content "HELLO WORLD!" untyped string // write(media_db), 
[__] (8) (BasicVariable BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string // write(media_db), 

[] (19) (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 

[] (15) (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[_] (16) (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[_] (17) (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 

[] (10) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} // write(posts_cache), write(posts_db), 
[_] (24) (FieldVariable FieldType) ReqID int64 // write(posts_db), write(posts_cache), 
[__] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[___] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (11) (FieldVariable FieldType) PostID int64 // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (12) (FieldVariable FieldType) Text string // write(posts_db), write(posts_cache), 
[__] (13) (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 
[_] (14) (FieldVariable FieldType) Mentions []string // write(posts_db), write(posts_cache), 
[__] (15) (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[___] (16) (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[___] (17) (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 
[_] (18) (FieldVariable FieldType) Timestamp int64 // write(posts_db), write(posts_cache), 
[__] (19) (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 
[_] (20) (FieldVariable FieldType) Creator postnotification.Creator struct{Username "some username" string} // write(posts_db), write(posts_cache), 
[__] (21) (StructVariable UserType) postnotification.Creator struct{Username "some username" string} // write(posts_cache), write(posts_db), 
[___] (22) (FieldVariable FieldType) Username "some username" string // write(posts_db), write(posts_cache), 
[____] (23) (BasicVariable BasicType) "some username" string // write(posts_db), write(posts_cache), 

[] (29) (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} // write(notifications_queue), 
[_] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[__] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[___] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[____] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), 
[__] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[___] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) reqIDStr string 
[_] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[__] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (0) (BasicVariable BasicType) 10 int 

[] (-1) (StructVariable UserType) timeline postnotification.Timeline struct{ReqID int64, PostID int64} // write(timeline_cache), 
[_] (0) (FieldVariable FieldType) ReqID int64 // write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[___] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

