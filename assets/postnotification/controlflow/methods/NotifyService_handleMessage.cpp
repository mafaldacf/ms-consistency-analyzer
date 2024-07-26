[] (-1) (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int} 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (34) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (35) (Reference UserType) ref <workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService 
[__] (42) (FieldVariable FieldType) Timestamp string 
[___] (43) (BasicVariable BasicType) Timestamp string 
[____] (44) (InterfaceVariable InterfaceType) Timestamp interface{} // read(notifications_queue), 
[__] (36) (FieldVariable FieldType) ReqID string 
[___] (37) (BasicVariable BasicType) ReqID string 
[____] (38) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 
[__] (39) (FieldVariable FieldType) PostID string // read(posts_db), read(analytics_db), 
[___] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[____] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[_] (0) (FieldVariable FieldType) ReqID string 
[__] (36) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (37) (BasicVariable BasicType) ReqID string 
[____] (38) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 
[__] (0) (BasicVariable BasicType) ReqID string 
[___] (36) (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (37) (BasicVariable BasicType) ReqID string 
[_____] (38) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 
[_] (0) (FieldVariable FieldType) PostID string 
[__] (39) (Reference FieldType) ref <PostID string> @ NotifyService // read(posts_db), read(analytics_db), 
[___] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[____] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[__] (47) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[___] (39) (Reference FieldType) ref <PostID string> @ NotifyService // read(posts_db), read(analytics_db), 
[____] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[_____] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (30) (BasicVariable BasicType) reqID int64 
[_] (0) (BasicVariable BasicType) ReqID string 
[__] (36) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (37) (BasicVariable BasicType) ReqID string 
[____] (38) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (0) (BasicVariable BasicType) ReqID string 
[__] (36) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (37) (BasicVariable BasicType) ReqID string 
[____] (38) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), read(notifications_queue), 

[] (32) (BasicVariable BasicType) postID int64 // read(posts_db), read(analytics_db), 
[_] (47) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[__] (39) (Reference FieldType) ref <PostID string> @ NotifyService // read(posts_db), read(analytics_db), 
[___] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[____] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (47) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[__] (39) (Reference FieldType) ref <PostID string> @ NotifyService // read(posts_db), read(analytics_db), 
[___] (40) (BasicVariable BasicType) PostID string // read(posts_db), read(analytics_db), 
[____] (41) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (StructVariable UserType) _ postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 

[] (-1) (StructVariable UserType) _ postnotification.Analytics struct{PostID int64} 

[] (-1) (InterfaceVariable UserType) err .error 

