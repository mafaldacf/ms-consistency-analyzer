[] (-1) (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int} 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 

[] (39) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) workerID int 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (29) (MapVariable MapType) event map[string]interface{} 
[_] (29) (Reference UserType) ref <message postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService // write(notifications_queue), 
[__] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[___] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[____] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[____] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(posts_cache), write(notifications_queue), write(timeline_cache), 
[_____] (46) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), 
[___] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[____] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_____] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (46) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (49) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (43) (InterfaceVariable InterfaceType) Timestamp interface{} 

[] (45) (BasicVariable BasicType) ReqID string 
[_] (46) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (48) (BasicVariable BasicType) PostID string 
[_] (49) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (42) (BasicVariable BasicType) Timestamp string 
[_] (43) (InterfaceVariable InterfaceType) Timestamp interface{} 

[] (40) (StructVariable UserType) workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (44) (FieldVariable FieldType) ReqID string 
[__] (45) (BasicVariable BasicType) ReqID string 
[___] (46) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (47) (FieldVariable FieldType) PostID string 
[__] (48) (BasicVariable BasicType) PostID string 
[___] (49) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[_] (41) (FieldVariable FieldType) Timestamp string 
[__] (42) (BasicVariable BasicType) Timestamp string 
[___] (43) (InterfaceVariable InterfaceType) Timestamp interface{} 

