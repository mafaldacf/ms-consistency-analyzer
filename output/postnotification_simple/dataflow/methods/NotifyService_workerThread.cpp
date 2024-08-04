[] (PointerVariable PointerType) n (*postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int}) 
[_] (StructVariable UserType) postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int} 
[__] (FieldVariable FieldType) notificationsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 
[__] (FieldVariable FieldType) num_workers 4 int 
[___] (BasicVariable BasicType) 4 int 
[__] (FieldVariable FieldType) storageService postnotification_simple.StorageService 
[___] (ServiceVariable ServiceType) storageService postnotification_simple.StorageService 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) workerID int 

[] (ChanVariable ChanType) forever chan struct{} 

[] (MapVariable MapType) event map[string]interface{} 
[_] (Reference UserType) ref <message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService // write(notifications_queue), 
[__] (FieldVariable FieldType) PostID string // write(notifications_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[___] (BasicVariable BasicType) string // write(notifications_queue), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[____] (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[_____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[___] (BasicVariable BasicType) string // write(notifications_queue), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[____] (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[_____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[_] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[_] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[_] (InterfaceVariable InterfaceType) Timestamp interface{} 

[] (BasicVariable BasicType) ReqID string 
[_] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (BasicVariable BasicType) PostID string 
[_] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (BasicVariable BasicType) Timestamp string 
[_] (InterfaceVariable InterfaceType) Timestamp interface{} 

[] (StructVariable UserType) workerMessage postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (FieldVariable FieldType) PostID string 
[__] (BasicVariable BasicType) PostID string 
[___] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[_] (FieldVariable FieldType) ReqID string 
[__] (BasicVariable BasicType) ReqID string 
[___] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[_] (FieldVariable FieldType) Timestamp string 
[__] (BasicVariable BasicType) Timestamp string 
[___] (InterfaceVariable InterfaceType) Timestamp interface{} 

