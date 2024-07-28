[] (-1) (PointerVariable PointerType) u (*postnotification.UploadServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, timeline_cache Cache}) 
[_] (0) (StructVariable UserType) postnotification.UploadServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, timeline_cache Cache} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) timeline_cache Cache 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 

[] (6) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) username string 

[] (13) (BasicVariable BasicType) text string // write(posts_db), 

[] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

[] (19) (BasicVariable BasicType) timestamp int64 // write(posts_db), 

[] (15) (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[_] (16) (BasicVariable BasicType) "alice" string // write(posts_db), 
[_] (17) (BasicVariable BasicType) "bob" string // write(posts_db), 

[] (8) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} // write(posts_db), 
[_] (12) (FieldVariable FieldType) Text string // write(posts_db), 
[__] (13) (BasicVariable BasicType) text string // write(posts_db), 
[_] (14) (FieldVariable FieldType) Mentions []string // write(posts_db), 
[__] (15) (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[___] (16) (BasicVariable BasicType) "alice" string // write(posts_db), 
[___] (17) (BasicVariable BasicType) "bob" string // write(posts_db), 
[_] (18) (FieldVariable FieldType) Timestamp int64 // write(posts_db), 
[__] (19) (BasicVariable BasicType) timestamp int64 // write(posts_db), 
[_] (20) (FieldVariable FieldType) Creator postnotification.Creator struct{Username string} // write(posts_db), 
[__] (21) (StructVariable UserType) postnotification.Creator struct{Username string} // write(posts_db), 
[___] (22) (FieldVariable FieldType) Username "some username" string // write(posts_db), 
[____] (23) (BasicVariable BasicType) "some username" string // write(posts_db), 
[_] (9) (FieldVariable FieldType) ReqID int64 // write(posts_db), 
[__] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[___] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_] (10) (FieldVariable FieldType) PostID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[___] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

[] (29) (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} // write(notifications_queue), read(notifications_queue), 
[_] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), read(notifications_queue), 
[__] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), read(notifications_queue), 
[___] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[____] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), read(notifications_queue), 
[__] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), read(notifications_queue), 
[___] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) reqIDStr string 
[_] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[__] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_] (0) (BasicVariable BasicType) 10 int 

[] (-1) (StructVariable UserType) timeline postnotification.Timeline struct{ReqID int64, PostID int64} // write(timeline_cache), 
[_] (0) (FieldVariable FieldType) ReqID int64 // write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[___] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(timeline_cache), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[___] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

