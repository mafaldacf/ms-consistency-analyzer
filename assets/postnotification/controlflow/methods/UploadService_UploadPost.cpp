[] (-1) (PointerVariable PointerType) u (*postnotification.UploadServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue}) 
[_] (0) (StructVariable UserType) postnotification.UploadServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue} 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 

[] (1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) username string 

[] (12) (BasicVariable BasicType) text string // write(posts_db), 

[] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), 
[_] (38) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 

[] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[_] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (18) (BasicVariable BasicType) timestamp int64 // write(posts_db), 

[] (14) (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[_] (15) (BasicVariable BasicType) "alice" string // write(posts_db), 
[_] (16) (BasicVariable BasicType) "bob" string // write(posts_db), 

[] (3) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} // write(posts_db), 
[_] (8) (FieldVariable FieldType) ReqID int64 // write(posts_db), 
[__] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), 
[___] (38) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[_] (9) (FieldVariable FieldType) PostID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), 
[__] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[___] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[_] (11) (FieldVariable FieldType) Text string // write(posts_db), 
[__] (12) (BasicVariable BasicType) text string // write(posts_db), 
[_] (13) (FieldVariable FieldType) Mentions []string // write(posts_db), 
[__] (14) (ArrayVariable ArrayType) mentions []string // write(posts_db), 
[___] (15) (BasicVariable BasicType) "alice" string // write(posts_db), 
[___] (16) (BasicVariable BasicType) "bob" string // write(posts_db), 
[_] (17) (FieldVariable FieldType) Timestamp int64 // write(posts_db), 
[__] (18) (BasicVariable BasicType) timestamp int64 // write(posts_db), 
[_] (4) (FieldVariable FieldType) Creator postnotification.Creator struct{Username string} // write(posts_db), 
[__] (5) (StructVariable UserType) postnotification.Creator struct{Username string} // write(posts_db), 
[___] (6) (FieldVariable FieldType) Username "some username" string // write(posts_db), 
[____] (7) (BasicVariable BasicType) "some username" string // write(posts_db), 

[] (24) (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} // write(notifications_queue), read(notifications_queue), 
[_] (-1) (FieldVariable FieldType) ReqID string // write(notifications_queue), read(notifications_queue), 
[__] (38) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), read(notifications_queue), 
[___] (38) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[___] (-1) (BasicVariable BasicType) reqID int64 // write(posts_db), write(notifications_queue), read(notifications_queue), 
[____] (38) (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService // write(posts_db), write(notifications_queue), read(notifications_queue), 
[_] (-1) (FieldVariable FieldType) PostID string // write(notifications_queue), read(notifications_queue), 
[__] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[__] (-1) (BasicVariable BasicType) string // write(notifications_queue), read(notifications_queue), 
[___] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), 
[____] (41) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(posts_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(notifications_queue), read(notifications_queue), read(posts_db), read(analytics_db), 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

