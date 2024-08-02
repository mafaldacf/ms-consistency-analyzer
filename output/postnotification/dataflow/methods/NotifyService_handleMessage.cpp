[] (-1) (PointerVariable PointerType) n (*postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers 4 int}) 
[_] (0) (StructVariable UserType) postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers 4 int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (45) (Reference UserType) ref <ctx context.Context> @ NotifyService 

[] (-1) (StructVariable UserType) message postnotification.Message struct{ReqID string, PostID string, Timestamp string} 
[_] (46) (Reference UserType) ref <workerMessage postnotification.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService 
[__] (47) (FieldVariable FieldType) ReqID string 
[___] (48) (BasicVariable BasicType) ReqID string 
[____] (49) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (50) (FieldVariable FieldType) PostID string 
[___] (51) (BasicVariable BasicType) PostID string 
[____] (52) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (53) (FieldVariable FieldType) Timestamp string 
[___] (54) (BasicVariable BasicType) Timestamp string 
[____] (55) (InterfaceVariable InterfaceType) Timestamp interface{} 
[_] (0) (FieldVariable FieldType) ReqID string 
[__] (47) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (48) (BasicVariable BasicType) ReqID string 
[____] (49) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[__] (0) (BasicVariable BasicType) ReqID string 
[___] (47) (Reference FieldType) ref <ReqID string> @ NotifyService 
[____] (48) (BasicVariable BasicType) ReqID string 
[_____] (49) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 
[_] (0) (FieldVariable FieldType) PostID string 
[__] (50) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (51) (BasicVariable BasicType) PostID string 
[____] (52) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (58) (BasicVariable BasicType) PostID string 
[___] (50) (Reference FieldType) ref <PostID string> @ NotifyService 
[____] (51) (BasicVariable BasicType) PostID string 
[_____] (52) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (41) (BasicVariable BasicType) reqID int64 
[_] (0) (BasicVariable BasicType) ReqID string 
[__] (47) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (48) (BasicVariable BasicType) ReqID string 
[____] (49) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (0) (BasicVariable BasicType) ReqID string 
[__] (47) (Reference FieldType) ref <ReqID string> @ NotifyService 
[___] (48) (BasicVariable BasicType) ReqID string 
[____] (49) (InterfaceVariable InterfaceType) ReqID interface{} // write(posts_cache), write(posts_db), write(notifications_queue), write(timeline_cache), 

[] (43) (BasicVariable BasicType) postID int64 
[_] (58) (BasicVariable BasicType) PostID string 
[__] (50) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (51) (BasicVariable BasicType) PostID string 
[____] (52) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (InterfaceVariable UserType) err .error 
[_] (58) (BasicVariable BasicType) PostID string 
[__] (50) (Reference FieldType) ref <PostID string> @ NotifyService 
[___] (51) (BasicVariable BasicType) PostID string 
[____] (52) (InterfaceVariable InterfaceType) PostID interface{} // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (-1) (StructVariable UserType) _ postnotification.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 

[] (-1) (StructVariable UserType) _ postnotification.Analytics struct{PostID int64} 

[] (-1) (InterfaceVariable UserType) err .error 

