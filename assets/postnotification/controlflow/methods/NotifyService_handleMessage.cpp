[] (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, queue Queue, numWorkers int}) 
[_] (StructVariable UserType) postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, queue Queue, numWorkers int} 
[__] (ServiceVariable ServiceType) storageService postnotification.StorageService 
[__] (BlueprintBackendVariable BlueprintBackendType) queue Queue 
[__] (BasicVariable BasicType) numWorkers 4 int 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (Reference UserType) ref <workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService 
[__] (FieldVariable FieldType) PostID string // read(post_nosql), 
[___] (BasicVariable BasicType) PostID string // read(post_nosql), 
[____] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[__] (FieldVariable FieldType) Timestamp string 
[___] (BasicVariable BasicType) Timestamp string 
[____] (InterfaceVariable InterfaceType) Timestamp interface{} // read(notif_queue), 
[__] (FieldVariable FieldType) ReqID string 
[___] (BasicVariable BasicType) ReqID string 
[____] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 
[_] (FieldVariable FieldType) ReqID string 
[__] (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (BasicVariable BasicType) ReqID string 
[____] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (BasicVariable BasicType) ReqID string 
[___] (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (BasicVariable BasicType) ReqID string 
[_____] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 
[_] (FieldVariable FieldType) PostID string 
[__] (Reference FieldType) ref <PostID string> @ NotifyService // read(post_nosql), 
[___] (BasicVariable BasicType) PostID string // read(post_nosql), 
[____] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[__] (BasicVariable BasicType) PostID string // read(post_nosql), 
[___] (Reference FieldType) ref <PostID string> @ NotifyService // read(post_nosql), 
[____] (BasicVariable BasicType) PostID string // read(post_nosql), 
[_____] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (BasicVariable BasicType) reqID int64 
[_] (BasicVariable BasicType) ReqID string 
[__] (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (BasicVariable BasicType) ReqID string 
[____] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 

[] (InterfaceVariable UserType) err .error 
[_] (BasicVariable BasicType) ReqID string 
[__] (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (BasicVariable BasicType) ReqID string 
[____] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 

[] (BasicVariable BasicType) postID int64 // read(post_nosql), 
[_] (BasicVariable BasicType) PostID string // read(post_nosql), 
[__] (Reference FieldType) ref <PostID string> @ NotifyService // read(post_nosql), 
[___] (BasicVariable BasicType) PostID string // read(post_nosql), 
[____] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (InterfaceVariable UserType) err .error 
[_] (BasicVariable BasicType) PostID string // read(post_nosql), 
[__] (Reference FieldType) ref <PostID string> @ NotifyService // read(post_nosql), 
[___] (BasicVariable BasicType) PostID string // read(post_nosql), 
[____] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (StructVariable UserType) _ postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 

[] (InterfaceVariable UserType) err .error 

