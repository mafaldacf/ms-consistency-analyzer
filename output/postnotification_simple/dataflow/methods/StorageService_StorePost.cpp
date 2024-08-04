[] (PointerVariable PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}) 
[_] (StructVariable UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase} 
[__] (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (BasicVariable BasicType) reqID int64 
[_] (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(notifications_queue), 
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 

[] (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}} // write(posts_db), 
[_] (Reference UserType) ref <post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}> @ UploadService // write(posts_db), 
[__] (FieldVariable FieldType) Creator postnotification_simple.Creator struct{Username "some username" string} // write(posts_db), 
[___] (StructVariable UserType) postnotification_simple.Creator struct{Username "some username" string} // write(posts_db), 
[____] (FieldVariable FieldType) Username "some username" string // write(posts_db), 
[_____] (BasicVariable BasicType) "some username" string // write(posts_db), 
[__] (FieldVariable FieldType) Mentions []string // write(posts_db), 
[___] (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[____] (BasicVariable BasicType) "alice" string // write(posts_db), 
[____] (BasicVariable BasicType) "bob" string // write(posts_db), 
[__] (FieldVariable FieldType) PostID int64 // write(posts_db), 
[___] (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (FieldVariable FieldType) ReqID int64 // write(posts_db), 
[___] (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (FieldVariable FieldType) Text string // write(posts_db), 
[___] (BasicVariable BasicType) text string // write(posts_db), 
[__] (FieldVariable FieldType) Timestamp int64 // write(posts_db), 
[___] (BasicVariable BasicType) timestamp int64 // write(posts_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (InterfaceVariable UserType) err .error 

[] (InterfaceVariable UserType) err .error 

