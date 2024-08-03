[] (-1) (PointerVariable PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}) 
[_] (0) (StructVariable UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (1) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (-1) (Reference BasicType) ref <reqID int64> @ UploadService // write(posts_db), write(notifications_queue), 
[__] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 

[] (-1) (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}} // write(posts_db), 
[_] (3) (Reference UserType) ref <post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}> @ UploadService // write(posts_db), 
[__] (13) (FieldVariable FieldType) Timestamp int64 // write(posts_db), 
[___] (14) (BasicVariable BasicType) timestamp int64 // write(posts_db), 
[__] (15) (FieldVariable FieldType) Creator postnotification_simple.Creator struct{Username "some username" string} // write(posts_db), 
[___] (16) (StructVariable UserType) postnotification_simple.Creator struct{Username "some username" string} // write(posts_db), 
[____] (17) (FieldVariable FieldType) Username "some username" string // write(posts_db), 
[_____] (18) (BasicVariable BasicType) "some username" string // write(posts_db), 
[__] (4) (FieldVariable FieldType) ReqID int64 // write(posts_db), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[____] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (5) (FieldVariable FieldType) PostID int64 // write(posts_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[____] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (7) (FieldVariable FieldType) Text string // write(posts_db), 
[___] (8) (BasicVariable BasicType) text string // write(posts_db), 
[__] (9) (FieldVariable FieldType) Mentions []string // write(posts_db), 
[___] (10) (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[____] (11) (BasicVariable BasicType) "alice" string // write(posts_db), 
[____] (12) (BasicVariable BasicType) "bob" string // write(posts_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (InterfaceVariable UserType) err .error 

