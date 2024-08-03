[] (-1) (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue} 
[__] (0) (FieldVariable FieldType) mediaService postnotification.MediaService 
[___] (-1) (ServiceVariable ServiceType) mediaService postnotification.MediaService 
[__] (0) (FieldVariable FieldType) posts_cache Cache 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (0) (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 
[__] (0) (FieldVariable FieldType) analyticsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (0) (FieldVariable FieldType) analyticsService postnotification.AnalyticsService 
[___] (-1) (ServiceVariable ServiceType) analyticsService postnotification.AnalyticsService 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) reqID int64 

[] (-1) (BasicVariable BasicType) postID int64 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} 

[] (-1) (BasicVariable BasicType) postIDStr string 
[_] (-1) (BasicVariable BasicType) postID int64 
[_] (0) (BasicVariable BasicType) 10 int 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

