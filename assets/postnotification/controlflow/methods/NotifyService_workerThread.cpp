[] (-1) (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int} 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 

[] (39) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) workerID int 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (29) (MapVariable MapType) event map[string]interface{} // read(notifications_queue), 
[_] (29) (Reference UserType) ref <message postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService // write(notifications_queue), read(notifications_queue), 
[__] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), read(notifications_queue), 
[___] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) string // write(notifications_queue), read(notifications_queue), 
[____] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[____] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_____] (43) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[__] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), read(notifications_queue), 
[___] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[___] (-1) (BasicVariable BasicType) string // write(notifications_queue), read(notifications_queue), 
[____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[____] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[_] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[_] (49) (InterfaceVariable InterfaceType) Timestamp interface{} // read(notifications_queue), 

[] (42) (BasicVariable BasicType) ReqID string 
[_] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 

[] (45) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[_] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 

[] (48) (BasicVariable BasicType) Timestamp string 
[_] (49) (InterfaceVariable InterfaceType) Timestamp interface{} // read(notifications_queue), 

[] (40) (StructVariable UserType) workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (41) (FieldVariable FieldType) ReqID string 
[__] (42) (BasicVariable BasicType) ReqID string 
[___] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), write(timeline_cache), 
[_] (44) (FieldVariable FieldType) PostID string // read(posts_db), read(analytics_db), 
[__] (45) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[___] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), write(timeline_cache), 
[_] (47) (FieldVariable FieldType) Timestamp string 
[__] (48) (BasicVariable BasicType) Timestamp string 
[___] (49) (InterfaceVariable InterfaceType) Timestamp interface{} // read(notifications_queue), 

