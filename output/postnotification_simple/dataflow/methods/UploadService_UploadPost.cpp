[] (PointerVariable PointerType) u (*postnotification_simple.UploadServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue}) 
[_] (StructVariable UserType) postnotification_simple.UploadServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue} 
[__] (FieldVariable FieldType) notificationsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 
[__] (FieldVariable FieldType) storageService postnotification_simple.StorageService 
[___] (ServiceVariable ServiceType) storageService postnotification_simple.StorageService 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) username string 

[] (BasicVariable BasicType) text string // write(posts_db), 

[] (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[_] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 

[] (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[_] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 

[] (BasicVariable BasicType) timestamp int64 // write(posts_db), 

[] (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[_] (BasicVariable BasicType) "alice" string // write(posts_db), 
[_] (BasicVariable BasicType) "bob" string // write(posts_db), 

[] (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}} // write(posts_db), 
[_] (FieldVariable FieldType) Creator postnotification_simple.Creator struct{Username "some username" string} // write(posts_db), 
[__] (StructVariable UserType) postnotification_simple.Creator struct{Username "some username" string} // write(posts_db), 
[___] (FieldVariable FieldType) Username "some username" string // write(posts_db), 
[____] (BasicVariable BasicType) "some username" string // write(posts_db), 
[_] (FieldVariable FieldType) Mentions []string // write(posts_db), 
[__] (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[___] (BasicVariable BasicType) "alice" string // write(posts_db), 
[___] (BasicVariable BasicType) "bob" string // write(posts_db), 
[_] (FieldVariable FieldType) PostID int64 // write(posts_db), 
[__] (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[_] (FieldVariable FieldType) ReqID int64 // write(posts_db), 
[__] (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[_] (FieldVariable FieldType) Text string // write(posts_db), 
[__] (BasicVariable BasicType) text string // write(posts_db), 
[_] (FieldVariable FieldType) Timestamp int64 // write(posts_db), 
[__] (BasicVariable BasicType) timestamp int64 // write(posts_db), 

[] (StructVariable UserType) message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string} // write(notifications_queue), 
[_] (FieldVariable FieldType) PostID string // write(notifications_queue), 
[__] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (BasicVariable BasicType) string // write(notifications_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[___] (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[_] (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (BasicVariable BasicType) string // write(notifications_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[___] (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 

[] (BasicVariable BasicType) _ bool 

[] (InterfaceVariable UserType) err .error 

