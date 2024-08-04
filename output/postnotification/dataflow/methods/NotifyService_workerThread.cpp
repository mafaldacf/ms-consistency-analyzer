[] (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, notificationsQueue Queue, num_workers 4 int}) 
[_] (StructVariable UserType) postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, notificationsQueue Queue, num_workers 4 int} 
[__] (FieldVariable FieldType) notificationsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 
[__] (FieldVariable FieldType) num_workers 4 int 
[___] (BasicVariable BasicType) 4 int 
[__] (FieldVariable FieldType) storageService postnotification.StorageService 
[___] (ServiceVariable ServiceType) storageService postnotification.StorageService 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) workerID int 

[] (ChanVariable ChanType) forever chan struct{} 

[] (MapVariable MapType) event map[string]interface{} 
[_] (Reference UserType) ref <message postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService // write(notifications_queue), 
[__] (FieldVariable FieldType) PostID string // write(notifications_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (BasicVariable BasicType) string // write(notifications_queue), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[___] (BasicVariable BasicType) string // write(notifications_queue), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[____] (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[_____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (InterfaceVariable InterfaceType) Timestamp interface{} 

[] (BasicVariable BasicType) ReqID string 
[_] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) PostID string 
[_] (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BasicVariable BasicType) Timestamp string 
[_] (InterfaceVariable InterfaceType) Timestamp interface{} 

[] (StructVariable UserType) workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (FieldVariable FieldType) PostID string 
[__] (BasicVariable BasicType) PostID string 
[___] (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (FieldVariable FieldType) ReqID string 
[__] (BasicVariable BasicType) ReqID string 
[___] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (FieldVariable FieldType) Timestamp string 
[__] (BasicVariable BasicType) Timestamp string 
[___] (InterfaceVariable InterfaceType) Timestamp interface{} 

