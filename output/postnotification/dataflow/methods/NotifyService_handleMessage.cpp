[] (-1) (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, notificationsQueue Queue, num_workers 4 int}) 
[_] (0) (StructVariable UserType) postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, notificationsQueue Queue, num_workers 4 int} 
[__] (0) (FieldVariable FieldType) num_workers 4 int 
[___] (0) (BasicVariable BasicType) 4 int 
[__] (0) (FieldVariable FieldType) storageService postnotification.StorageService 
[___] (-1) (ServiceVariable ServiceType) storageService postnotification.StorageService 
[__] (0) (FieldVariable FieldType) notificationsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (39) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (40) (Reference UserType) ref <workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService 
[__] (44) (FieldVariable FieldType) PostID string 
[___] (45) (BasicVariable BasicType) PostID string 
[____] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (47) (FieldVariable FieldType) Timestamp string 
[___] (48) (BasicVariable BasicType) Timestamp string 
[____] (49) (InterfaceVariable InterfaceType) Timestamp interface{} 
[__] (41) (FieldVariable FieldType) ReqID string 
[___] (42) (BasicVariable BasicType) ReqID string 
[____] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (0) (FieldVariable FieldType) ReqID string 
[__] (41) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (42) (BasicVariable BasicType) ReqID string 
[____] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (0) (BasicVariable BasicType) ReqID string 
[___] (41) (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (42) (BasicVariable BasicType) ReqID string 
[_____] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (0) (FieldVariable FieldType) PostID string 
[__] (44) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (45) (BasicVariable BasicType) PostID string 
[____] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (52) (BasicVariable BasicType) PostID string 
[___] (44) (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (45) (BasicVariable BasicType) PostID string 
[_____] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (35) (BasicVariable BasicType) reqID int64 
[_] (0) (BasicVariable BasicType) ReqID string 
[__] (41) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (42) (BasicVariable BasicType) ReqID string 
[____] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (0) (BasicVariable BasicType) ReqID string 
[__] (41) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (42) (BasicVariable BasicType) ReqID string 
[____] (43) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (37) (BasicVariable BasicType) postID int64 
[_] (52) (BasicVariable BasicType) PostID string 
[__] (44) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (45) (BasicVariable BasicType) PostID string 
[____] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (52) (BasicVariable BasicType) PostID string 
[__] (44) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (45) (BasicVariable BasicType) PostID string 
[____] (46) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (StructVariable UserType) _ postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} 

[] (-1) (StructVariable UserType) _ postnotification.Analytics struct{PostID int64} 

[] (-1) (InterfaceVariable UserType) err .error 

