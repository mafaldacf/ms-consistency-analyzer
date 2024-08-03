[] (-1) (PointerVariable PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}) 
[_] (0) (StructVariable UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (-1) (Reference UserType) ref <ctx context.Context> @ NotifyService 
[__] (29) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (25) (Reference BasicType) ref <reqID int64> @ NotifyService 
[__] (0) (BasicVariable BasicType) ReqID string 
[___] (31) (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (32) (BasicVariable BasicType) ReqID string 
[_____] (33) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_db), write(notifications_queue), 

[] (-1) (BasicVariable BasicType) postID int64 
[_] (27) (Reference BasicType) ref <postID int64> @ NotifyService 
[__] (0) (BasicVariable BasicType) PostID string 
[___] (34) (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (35) (BasicVariable BasicType) PostID string 
[_____] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (-1) (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "postid" string, Value int64} 
[__] (0) (FieldVariable FieldType) Key "postid" string 
[___] (0) (BasicVariable BasicType) "postid" string 
[__] (0) (FieldVariable FieldType) Value int64 
[___] (-1) (BasicVariable BasicType) postID int64 
[____] (27) (Reference BasicType) ref <postID int64> @ NotifyService 
[_____] (0) (BasicVariable BasicType) PostID string 
[______] (34) (Reference FieldType) ref <PostID string> @ NotifyService 
[_______] (35) (BasicVariable BasicType) PostID string 
[________] (36) (InterfaceVariable InterfaceType) PostID interface{} // write(posts_db), write(notifications_queue), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) res bool 

[] (-1) (InterfaceVariable UserType) err .error 

