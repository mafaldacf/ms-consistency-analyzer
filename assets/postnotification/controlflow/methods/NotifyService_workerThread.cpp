[] (-1) (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int} 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 

[] (34) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) workerID int 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (24) (MapVariable MapType) event map[string]interface{} // read(notifications_queue), 
[_] (24) (Reference UserType) ref <message postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService // write(notifications_queue), read(notifications_queue), 
[__] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), read(notifications_queue), 
[___] (44) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[___] (-1) (BasicVariable BasicType) string // write(notifications_queue), read(notifications_queue), 
[____] (44) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[____] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), 
[_____] (44) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[__] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), read(notifications_queue), 
[___] (38) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[___] (-1) (BasicVariable BasicType) string // write(notifications_queue), read(notifications_queue), 
[____] (38) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[____] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_____] (38) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[_] (44) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 
[_] (38) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[_] (41) (InterfaceVariable InterfaceType) Timestamp interface{} // read(notifications_queue), 

[] (43) (BasicVariable BasicType) ReqID string 
[_] (44) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 

[] (37) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[_] (38) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (40) (BasicVariable BasicType) Timestamp string 
[_] (41) (InterfaceVariable InterfaceType) Timestamp interface{} // read(notifications_queue), 

[] (35) (StructVariable UserType) workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (42) (FieldVariable FieldType) ReqID string 
[__] (43) (BasicVariable BasicType) ReqID string 
[___] (44) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 
[_] (36) (FieldVariable FieldType) PostID string // read(posts_db), read(analytics_db), 
[__] (37) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[___] (38) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[_] (39) (FieldVariable FieldType) Timestamp string 
[__] (40) (BasicVariable BasicType) Timestamp string 
[___] (41) (InterfaceVariable InterfaceType) Timestamp interface{} // read(notifications_queue), 

