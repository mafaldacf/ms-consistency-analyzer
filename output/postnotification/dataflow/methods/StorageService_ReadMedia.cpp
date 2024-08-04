[] (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue}) 
[_] (StructVariable UserType) postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue} 
[__] (FieldVariable FieldType) analyticsQueue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 
[__] (FieldVariable FieldType) analyticsService postnotification.AnalyticsService 
[___] (ServiceVariable ServiceType) analyticsService postnotification.AnalyticsService 
[__] (FieldVariable FieldType) mediaService postnotification.MediaService 
[___] (ServiceVariable ServiceType) mediaService postnotification.MediaService 
[__] (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 
[__] (FieldVariable FieldType) posts_cache Cache 
[___] (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (BasicVariable BasicType) reqID int64 
[_] (Reference BasicType) ref <reqID int64> @ UploadService 

[] (BasicVariable BasicType) postID int64 
[_] (Reference BasicType) ref <postID int64> @ UploadService 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} 
[_] (FieldVariable FieldType) PostID int64 
[__] (BasicVariable BasicType) PostID int64 

[] (BasicVariable BasicType) postIDStr string 
[_] (BasicVariable BasicType) postID int64 
[__] (Reference BasicType) ref <postID int64> @ UploadService 
[_] (BasicVariable BasicType) 10 int 

[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string} 

[] (FieldVariable FieldType) mediaID int64 
[_] (BasicVariable BasicType) PostID int64 

[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string} 

[] (InterfaceVariable UserType) _ .error 

