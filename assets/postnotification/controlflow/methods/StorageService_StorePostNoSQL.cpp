[] (PointerVariable PointerType) p (*postnotification.StorageServiceImpl struct{cache Cache, db NoSQLDatabase}) 
[_] (StructVariable UserType) postnotification.StorageServiceImpl struct{cache Cache, db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) cache Cache 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (BasicVariable BasicType) reqID int64 
[_] (Reference FieldType) ref <ReqID int64> @ UploadService // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (BasicVariable BasicType) reqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} // write(post_nosql), 
[_] (Reference UserType) ref <post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}}> @ UploadService // write(post_nosql), 
[__] (FieldVariable FieldType) ReqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (BasicVariable BasicType) reqID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), 
[__] (FieldVariable FieldType) PostID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[___] (BasicVariable BasicType) postID int64 // write(post_nosql), write(notif_queue), read(notif_queue), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[__] (FieldVariable FieldType) Text string // write(post_nosql), 
[___] (BasicVariable BasicType) text string // write(post_nosql), 
[__] (FieldVariable FieldType) Mentions []string // write(post_nosql), 
[___] (ArrayVariable ArrayType) mentions []string // write(post_nosql), 
[____] (BasicVariable BasicType) "alice" string // write(post_nosql), 
[____] (BasicVariable BasicType) "bob" string // write(post_nosql), 
[__] (FieldVariable FieldType) Timestamp int64 // write(post_nosql), 
[___] (BasicVariable BasicType) timestamp int64 // write(post_nosql), 
[__] (FieldVariable FieldType) Creator postnotification.Creator struct{Username string} // write(post_nosql), 
[___] (StructVariable UserType) postnotification.Creator struct{Username string} // write(post_nosql), 
[____] (FieldVariable FieldType) Username "some username" string // write(post_nosql), 
[_____] (BasicVariable BasicType) "some username" string // write(post_nosql), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (InterfaceVariable UserType) err .error 

