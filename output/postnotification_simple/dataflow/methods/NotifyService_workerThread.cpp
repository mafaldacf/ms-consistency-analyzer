[] (-1) (PointerVariable PointerType) n (*postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int}) 
[_] (0) (StructVariable UserType) postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int} 
[__] (0) (FieldVariable FieldType) storageService postnotification_simple.StorageService 
[___] (-1) (ServiceVariable ServiceType) storageService postnotification_simple.StorageService 
[__] (0) (FieldVariable FieldType) notificationsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 
[__] (0) (FieldVariable FieldType) num_workers 4 int 
[___] (0) (BasicVariable BasicType) 4 int 

[] (29) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) workerID int 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (19) (MapVariable MapType) event map[string]interface{} 
[_] (19) (Reference UserType) ref <message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService // write(notifications_queue), 
[__] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), 
[___] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[___] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[____] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[____] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[_____] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[___] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[___] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[____] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[____] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[_____] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[_] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[_] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[_] (39) (InterfaceVariable InterfaceType) Timestamp interface{} 

[] (32) (BasicVariable BasicType) ReqID string 
[_] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (35) (BasicVariable BasicType) PostID string 
[_] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (38) (BasicVariable BasicType) Timestamp string 
[_] (39) (InterfaceVariable InterfaceType) Timestamp interface{} 

[] (30) (StructVariable UserType) workerMessage postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (31) (FieldVariable FieldType) ReqID string 
[__] (32) (BasicVariable BasicType) ReqID string 
[___] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[_] (34) (FieldVariable FieldType) PostID string 
[__] (35) (BasicVariable BasicType) PostID string 
[___] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[_] (37) (FieldVariable FieldType) Timestamp string 
[__] (38) (BasicVariable BasicType) Timestamp string 
[___] (39) (InterfaceVariable InterfaceType) Timestamp interface{} 

