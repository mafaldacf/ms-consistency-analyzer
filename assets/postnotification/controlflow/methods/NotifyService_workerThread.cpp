[] (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, queue Queue, numWorkers int}) 
[_] (StructVariable UserType) postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, queue Queue, numWorkers int} 
[__] (BasicVariable BasicType) numWorkers 4 int 
[__] (ServiceVariable ServiceType) storageService postnotification.StorageService 
[__] (BlueprintBackendVariable BlueprintBackendType) queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) workerID int 

[] (ChanVariable ChanType) forever chan struct{} 

[] (MapVariable MapType) event map[string]interface{} // read(notif_queue), 
[_] (Reference UserType) ref <message postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService // write(notif_queue), read(notif_queue), 
[__] (FieldVariable FieldType) ReqID string // write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (BasicVariable BasicType) string // write(notif_queue), read(notif_queue), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[____] (BasicVariable BasicType) reqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[_____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (FieldVariable FieldType) PostID string // write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[___] (BasicVariable BasicType) string // write(notif_queue), read(notif_queue), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[____] (BasicVariable BasicType) postID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[_____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[_] (InterfaceVariable InterfaceType) Timestamp interface{} // read(notif_queue), 
[_] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 
[_] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (BasicVariable BasicType) ReqID string 
[_] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 

[] (BasicVariable BasicType) PostID string // read(post_nosql), 
[_] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (BasicVariable BasicType) Timestamp string 
[_] (InterfaceVariable InterfaceType) Timestamp interface{} // read(notif_queue), 

[] (StructVariable UserType) workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (FieldVariable FieldType) ReqID string 
[__] (BasicVariable BasicType) ReqID string 
[___] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 
[_] (FieldVariable FieldType) PostID string // read(post_nosql), 
[__] (BasicVariable BasicType) PostID string // read(post_nosql), 
[___] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[_] (FieldVariable FieldType) Timestamp string 
[__] (BasicVariable BasicType) Timestamp string 
[___] (InterfaceVariable InterfaceType) Timestamp interface{} // read(notif_queue), 

