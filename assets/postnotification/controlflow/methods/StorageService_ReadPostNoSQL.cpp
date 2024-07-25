[] (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{cache Cache, db NoSQLDatabase}) 
[_] (StructVariable UserType) postnotification.StorageServiceImpl struct{cache Cache, db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) cache Cache 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService 
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (BasicVariable BasicType) reqID int64 
[_] (Reference BasicType) ref <reqID int64> @ NotifyService 
[__] (FieldVariable FieldType) ReqID string 
[___] (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (BasicVariable BasicType) ReqID string 
[_____] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 
[___] (BasicVariable BasicType) ReqID string 
[____] (Reference FieldType) ref <ReqID string> @ NotifyService 
[_____] (BasicVariable BasicType) ReqID string 
[______] (InterfaceVariable InterfaceType) ReqID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), 

[] (BasicVariable BasicType) postID int64 // read(post_nosql), 
[_] (Reference BasicType) ref <postID int64> @ NotifyService // read(post_nosql), 
[__] (FieldVariable FieldType) PostID string // read(post_nosql), 
[___] (Reference FieldType) ref <PostID string> @ NotifyService // read(post_nosql), 
[____] (BasicVariable BasicType) PostID string // read(post_nosql), 
[_____] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[___] (BasicVariable BasicType) PostID string // read(post_nosql), 
[____] (Reference FieldType) ref <PostID string> @ NotifyService // read(post_nosql), 
[_____] (BasicVariable BasicType) PostID string // read(post_nosql), 
[______] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(post_nosql), 
[_] (StructVariable StructType) struct{Key "postid" string, Value int64} // read(post_nosql), 
[__] (FieldVariable FieldType) Key "postid" string // read(post_nosql), 
[___] (BasicVariable BasicType) "postid" string // read(post_nosql), 
[__] (FieldVariable FieldType) Value int64 // read(post_nosql), 
[___] (BasicVariable BasicType) postID int64 // read(post_nosql), 
[____] (Reference BasicType) ref <postID int64> @ NotifyService // read(post_nosql), 
[_____] (FieldVariable FieldType) PostID string // read(post_nosql), 
[______] (Reference FieldType) ref <PostID string> @ NotifyService // read(post_nosql), 
[_______] (BasicVariable BasicType) PostID string // read(post_nosql), 
[________] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 
[______] (BasicVariable BasicType) PostID string // read(post_nosql), 
[_______] (Reference FieldType) ref <PostID string> @ NotifyService // read(post_nosql), 
[________] (BasicVariable BasicType) PostID string // read(post_nosql), 
[_________] (InterfaceVariable InterfaceType) PostID interface{} // write(post_nosql), write(notif_queue), read(notif_queue), read(post_nosql), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post} // read(post_nosql), 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) res bool 

[] (InterfaceVariable UserType) err .error 

