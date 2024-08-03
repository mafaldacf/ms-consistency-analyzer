[] (-1) (PointerVariable PointerType) u (*postnotification_simple.UploadServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue}) 
[_] (0) (StructVariable UserType) postnotification_simple.UploadServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue} 
[__] (0) (FieldVariable FieldType) storageService postnotification_simple.StorageService 
[___] (-1) (ServiceVariable ServiceType) storageService postnotification_simple.StorageService 
[__] (0) (FieldVariable FieldType) notificationsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 

[] (1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) username string 

[] (8) (BasicVariable BasicType) text string // write(posts_db), 

[] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[_] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 

[] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[_] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 

[] (14) (BasicVariable BasicType) timestamp int64 // write(posts_db), 

[] (10) (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[_] (11) (BasicVariable BasicType) "alice" string // write(posts_db), 
[_] (12) (BasicVariable BasicType) "bob" string // write(posts_db), 

[] (3) (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}} // write(posts_db), 
[_] (4) (FieldVariable FieldType) ReqID int64 // write(posts_db), 
[__] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[___] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[_] (5) (FieldVariable FieldType) PostID int64 // write(posts_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[___] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[_] (7) (FieldVariable FieldType) Text string // write(posts_db), 
[__] (8) (BasicVariable BasicType) text string // write(posts_db), 
[_] (9) (FieldVariable FieldType) Mentions []string // write(posts_db), 
[__] (10) (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[___] (11) (BasicVariable BasicType) "alice" string // write(posts_db), 
[___] (12) (BasicVariable BasicType) "bob" string // write(posts_db), 
[_] (13) (FieldVariable FieldType) Timestamp int64 // write(posts_db), 
[__] (14) (BasicVariable BasicType) timestamp int64 // write(posts_db), 
[_] (15) (FieldVariable FieldType) Creator postnotification_simple.Creator struct{Username "some username" string} // write(posts_db), 
[__] (16) (StructVariable UserType) postnotification_simple.Creator struct{Username "some username" string} // write(posts_db), 
[___] (17) (FieldVariable FieldType) Username "some username" string // write(posts_db), 
[____] (18) (BasicVariable BasicType) "some username" string // write(posts_db), 

[] (19) (StructVariable UserType) message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string} // write(notifications_queue), 
[_] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), 
[__] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[___] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), 
[____] (33) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[_] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), 
[__] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), 
[___] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(notifications_queue), 
[____] (36) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

