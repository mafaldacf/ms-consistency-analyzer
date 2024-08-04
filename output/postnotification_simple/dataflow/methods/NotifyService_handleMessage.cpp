[] (PointerVariable PointerType) n (*postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int}) 
[_] (StructVariable UserType) postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int} 
[__] (FieldVariable FieldType) notificationsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 
[__] (FieldVariable FieldType) num_workers 4 int 
[___] (BasicVariable BasicType) 4 int 
[__] (FieldVariable FieldType) storageService postnotification_simple.StorageService 
[___] (ServiceVariable ServiceType) storageService postnotification_simple.StorageService 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (StructVariable UserType) message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (Reference UserType) ref <workerMessage postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService 
[__] (FieldVariable FieldType) PostID string 
[___] (BasicVariable BasicType) PostID string 
[____] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[__] (FieldVariable FieldType) ReqID string 
[___] (BasicVariable BasicType) ReqID string 
[____] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[__] (FieldVariable FieldType) Timestamp string 
[___] (BasicVariable BasicType) Timestamp string 
[____] (InterfaceVariable InterfaceType) Timestamp interface{} 
[_] (FieldVariable FieldType) PostID string 
[__] (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (BasicVariable BasicType) PostID string 
[____] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[__] (BasicVariable BasicType) PostID string 
[___] (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (BasicVariable BasicType) PostID string 
[_____] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[_] (FieldVariable FieldType) ReqID string 
[__] (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (BasicVariable BasicType) ReqID string 
[____] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[__] (BasicVariable BasicType) ReqID string 
[___] (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (BasicVariable BasicType) ReqID string 
[_____] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (BasicVariable BasicType) reqID int64 
[_] (BasicVariable BasicType) ReqID string 
[__] (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (BasicVariable BasicType) ReqID string 
[____] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (InterfaceVariable UserType) err .error 
[_] (BasicVariable BasicType) ReqID string 
[__] (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (BasicVariable BasicType) ReqID string 
[____] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (BasicVariable BasicType) postID int64 
[_] (BasicVariable BasicType) PostID string 
[__] (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (BasicVariable BasicType) PostID string 
[____] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (InterfaceVariable UserType) err .error 
[_] (BasicVariable BasicType) PostID string 
[__] (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (BasicVariable BasicType) PostID string 
[____] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (StructVariable UserType) _ postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}} 

[] (InterfaceVariable UserType) err .error 

