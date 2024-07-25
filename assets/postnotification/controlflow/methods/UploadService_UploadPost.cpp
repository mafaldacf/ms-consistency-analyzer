[] (PointerVariable PointerType) u (*postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, queue Queue}) 
[_] (StructVariable UserType) postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, queue Queue} 
[__] (ServiceVariable ServiceType) storageService postnotification.StorageService 
[__] (BlueprintBackendVariable BlueprintBackendType) queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) username string 

[] (BasicVariable BasicType) text string // write(post_nosql), 

[] (BasicVariable BasicType) reqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[_] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 

[] (BasicVariable BasicType) postID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[_] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (BasicVariable BasicType) timestamp int64 // write(post_nosql), 

[] (ArrayVariable ArrayType) mentions []string // write(post_nosql), 
[_] (BasicVariable BasicType) "alice" string // write(post_nosql), 
[_] (BasicVariable BasicType) "bob" string // write(post_nosql), 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} // write(post_nosql), 
[_] (FieldVariable FieldType) ReqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (BasicVariable BasicType) reqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[_] (FieldVariable FieldType) PostID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[__] (BasicVariable BasicType) postID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[_] (FieldVariable FieldType) Text string // write(post_nosql), 
[__] (BasicVariable BasicType) text string // write(post_nosql), 
[_] (FieldVariable FieldType) Mentions []string // write(post_nosql), 
[__] (ArrayVariable ArrayType) mentions []string // write(post_nosql), 
[___] (BasicVariable BasicType) "alice" string // write(post_nosql), 
[___] (BasicVariable BasicType) "bob" string // write(post_nosql), 
[_] (FieldVariable FieldType) Timestamp int64 // write(post_nosql), 
[__] (BasicVariable BasicType) timestamp int64 // write(post_nosql), 
[_] (FieldVariable FieldType) Creator postnotification.Creator struct{Username string} // write(post_nosql), 
[__] (StructVariable UserType) postnotification.Creator struct{Username string} // write(post_nosql), 
[___] (FieldVariable FieldType) Username "some username" string // write(post_nosql), 
[____] (BasicVariable BasicType) "some username" string // write(post_nosql), 

[] (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} // write(notif_queue), read(notif_queue), 
[_] (FieldVariable FieldType) ReqID string // write(notif_queue), read(notif_queue), 
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (BasicVariable BasicType) string // write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (FieldVariable FieldType) ReqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[____] (BasicVariable BasicType) reqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[_____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[_] (FieldVariable FieldType) PostID string // write(notif_queue), read(notif_queue), 
[__] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[__] (BasicVariable BasicType) string // write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[___] (FieldVariable FieldType) PostID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[____] (BasicVariable BasicType) postID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[_____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (BasicVariable BasicType) _ bool 

[] (InterfaceVariable UserType) err .error 

