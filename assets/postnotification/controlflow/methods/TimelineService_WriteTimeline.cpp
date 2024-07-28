[] (-1) (PointerVariable PointerType) s (*postnotification.TimelineServiceImpl struct{storage_service postnotification.StorageService, timeline_cache Cache}) 
[_] (0) (StructVariable UserType) postnotification.TimelineServiceImpl struct{storage_service postnotification.StorageService, timeline_cache Cache} 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) timeline_cache Cache 

[] (6) (InterfaceVariable UserType) ctx context.Context 
[_] (6) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (7) (BasicVariable BasicType) reqID int64 // write(timeline_cache), 
[_] (-1) (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(timeline_cache), write(notifications_queue), read(notifications_queue), 
[__] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(timeline_cache), write(posts_db), write(notifications_queue), read(notifications_queue), 

[] (23) (BasicVariable BasicType) postID int64 // write(timeline_cache), 
[_] (-1) (Reference BasicType) ref <postID int64> @ UploadService // write(posts_db), write(timeline_cache), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[__] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(timeline_cache), write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (BasicVariable BasicType) reqIDStr string 
[_] (7) (BasicVariable BasicType) reqID int64 // write(timeline_cache), 
[__] (-1) (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(timeline_cache), write(notifications_queue), read(notifications_queue), 
[___] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(timeline_cache), write(posts_db), write(notifications_queue), read(notifications_queue), 
[_] (0) (BasicVariable BasicType) 10 int 

[] (-1) (StructVariable UserType) timeline postnotification.Timeline struct{ReqID int64, PostID int64} // write(timeline_cache), 
[_] (0) (FieldVariable FieldType) PostID int64 // write(timeline_cache), 
[__] (23) (BasicVariable BasicType) postID int64 // write(timeline_cache), 
[___] (-1) (Reference BasicType) ref <postID int64> @ UploadService // write(posts_db), write(timeline_cache), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(timeline_cache), write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[_] (0) (FieldVariable FieldType) ReqID int64 // write(timeline_cache), 
[__] (7) (BasicVariable BasicType) reqID int64 // write(timeline_cache), 
[___] (-1) (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(timeline_cache), write(notifications_queue), read(notifications_queue), 
[____] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(timeline_cache), write(posts_db), write(notifications_queue), read(notifications_queue), 

