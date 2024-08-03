[] (-1) (PointerVariable PointerType) n (*postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int}) 
[_] (0) (StructVariable UserType) postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int} 
[__] (0) (FieldVariable FieldType) num_workers 4 int 
[___] (0) (BasicVariable BasicType) 4 int 
[__] (0) (FieldVariable FieldType) storageService postnotification_simple.StorageService 
[___] (-1) (ServiceVariable ServiceType) storageService postnotification_simple.StorageService 
[__] (0) (FieldVariable FieldType) notificationsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (29) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (StructVariable UserType) message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (30) (Reference UserType) ref <workerMessage postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService 
[__] (31) (FieldVariable FieldType) ReqID string 
[___] (32) (BasicVariable BasicType) ReqID string 
[____] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[__] (34) (FieldVariable FieldType) PostID string 
[___] (35) (BasicVariable BasicType) PostID string 
[____] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[__] (37) (FieldVariable FieldType) Timestamp string 
[___] (38) (BasicVariable BasicType) Timestamp string 
[____] (39) (InterfaceVariable InterfaceType) Timestamp interface{} 
[_] (0) (FieldVariable FieldType) ReqID string 
[__] (31) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (32) (BasicVariable BasicType) ReqID string 
[____] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[__] (0) (BasicVariable BasicType) ReqID string 
[___] (31) (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (32) (BasicVariable BasicType) ReqID string 
[_____] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 
[_] (0) (FieldVariable FieldType) PostID string 
[__] (34) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (35) (BasicVariable BasicType) PostID string 
[____] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 
[__] (0) (BasicVariable BasicType) PostID string 
[___] (34) (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (35) (BasicVariable BasicType) PostID string 
[_____] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (25) (BasicVariable BasicType) reqID int64 
[_] (0) (BasicVariable BasicType) ReqID string 
[__] (31) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (32) (BasicVariable BasicType) ReqID string 
[____] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (0) (BasicVariable BasicType) ReqID string 
[__] (31) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (32) (BasicVariable BasicType) ReqID string 
[____] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (27) (BasicVariable BasicType) postID int64 
[_] (0) (BasicVariable BasicType) PostID string 
[__] (34) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (35) (BasicVariable BasicType) PostID string 
[____] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (0) (BasicVariable BasicType) PostID string 
[__] (34) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (35) (BasicVariable BasicType) PostID string 
[____] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (-1) (StructVariable UserType) _ postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}} 

[] (-1) (InterfaceVariable UserType) err .error 

