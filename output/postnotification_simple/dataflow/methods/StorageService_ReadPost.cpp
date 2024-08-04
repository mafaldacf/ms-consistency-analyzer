[] (PointerVariable PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}) 
[_] (StructVariable UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase} 
[__] (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService 
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (BasicVariable BasicType) reqID int64 
[_] (Reference BasicType) ref <reqID int64> @ NotifyService 
[__] (BasicVariable BasicType) ReqID string 
[___] (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (BasicVariable BasicType) ReqID string 
[_____] (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (BasicVariable BasicType) postID int64 
[_] (Reference BasicType) ref <postID int64> @ NotifyService 
[__] (BasicVariable BasicType) PostID string 
[___] (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (BasicVariable BasicType) PostID string 
[_____] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "postid" string, Value int64} 
[__] (FieldVariable FieldType) Key "postid" string 
[___] (BasicVariable BasicType) "postid" string 
[__] (FieldVariable FieldType) Value int64 
[___] (BasicVariable BasicType) postID int64 
[____] (Reference BasicType) ref <postID int64> @ NotifyService 
[_____] (BasicVariable BasicType) PostID string 
[______] (Reference FieldType) ref <PostID string> @ NotifyService 
[_______] (BasicVariable BasicType) PostID string 
[________] (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post} 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) res bool 

[] (InterfaceVariable UserType) err .error 

