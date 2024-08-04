[] (PointerVariable PointerType) u (*postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache}) 
[_] (StructVariable UserType) postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache} 
[__] (FieldVariable FieldType) mediaService postnotification.MediaService 
[___] (ServiceVariable ServiceType) mediaService postnotification.MediaService 
[__] (FieldVariable FieldType) notificationsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 
[__] (FieldVariable FieldType) storageService postnotification.StorageService 
[___] (ServiceVariable ServiceType) storageService postnotification.StorageService 
[__] (FieldVariable FieldType) timelineCache Cache 
[___] (BlueprintBackendVariable BlueprintBackendType) timelineCache Cache 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) username string 

[] (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 

[] (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[_] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) mediaID int64 // write(media_db), 

[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string} // write(media_db), 
[_] (FieldVariable FieldType) Content "HELLO WORLD!" untyped string // write(media_db), 
[__] (BasicVariable BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string // write(media_db), 
[_] (FieldVariable FieldType) MediaID int64 // write(media_db), 
[__] (BasicVariable BasicType) mediaID int64 // write(media_db), 
[_] (FieldVariable FieldType) PostID int64 // write(media_db), 
[__] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 

[] (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[_] (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[_] (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} // write(posts_cache), write(posts_db), 
[_] (FieldVariable FieldType) Creator postnotification.Creator struct{Username "some username" string} // write(posts_db), write(posts_cache), 
[__] (StructVariable UserType) postnotification.Creator struct{Username "some username" string} // write(posts_cache), write(posts_db), 
[___] (FieldVariable FieldType) Username "some username" string // write(posts_db), write(posts_cache), 
[____] (BasicVariable BasicType) "some username" string // write(posts_db), write(posts_cache), 
[_] (FieldVariable FieldType) Mentions []string // write(posts_db), write(posts_cache), 
[__] (ArrayVariable ArrayType) mentions []string // write(posts_db), write(posts_cache), 
[___] (BasicVariable BasicType) "alice" string // write(posts_cache), write(posts_db), 
[___] (BasicVariable BasicType) "bob" string // write(posts_cache), write(posts_db), 
[_] (FieldVariable FieldType) PostID int64 // write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), 
[__] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (FieldVariable FieldType) ReqID int64 // write(posts_db), write(posts_cache), 
[__] (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (FieldVariable FieldType) Text string // write(posts_db), write(posts_cache), 
[__] (BasicVariable BasicType) text string // write(posts_db), write(posts_cache), 
[_] (FieldVariable FieldType) Timestamp int64 // write(posts_db), write(posts_cache), 
[__] (BasicVariable BasicType) timestamp int64 // write(posts_db), write(posts_cache), 

[] (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} // write(notifications_queue), 
[_] (FieldVariable FieldType) PostID string // write(notifications_queue), 
[__] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (BasicVariable BasicType) string // write(notifications_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (BasicVariable BasicType) string // write(notifications_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[___] (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) _ bool 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) reqIDStr string 
[_] (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (BasicVariable BasicType) 10 int 

[] (StructVariable UserType) timeline postnotification.Timeline struct{ReqID int64, PostID int64} // write(timeline_cache), 
[_] (FieldVariable FieldType) PostID int64 // write(timeline_cache), 
[__] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (FieldVariable FieldType) ReqID int64 // write(timeline_cache), 
[__] (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

