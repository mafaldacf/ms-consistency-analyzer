[] (-1) (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analyticsService postnotification.AnalyticsService, mediaService postnotification.MediaService, posts_cache Cache, postsDb NoSQLDatabase, analyticsQueue Queue} 
[__] (0) (FieldVariable FieldType) analyticsService postnotification.AnalyticsService 
[___] (-1) (ServiceVariable ServiceType) analyticsService postnotification.AnalyticsService 
[__] (0) (FieldVariable FieldType) mediaService postnotification.MediaService 
[___] (-1) (ServiceVariable ServiceType) mediaService postnotification.MediaService 
[__] (0) (FieldVariable FieldType) posts_cache Cache 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (0) (FieldVariable FieldType) postsDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 
[__] (0) (FieldVariable FieldType) analyticsQueue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 

[] (56) (InterfaceVariable UserType) ctx context.Context 
[_] (53) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (54) (Reference BasicType) ref <reqID int64> @ UploadService 

[] (-1) (BasicVariable BasicType) postID int64 
[_] (55) (Reference BasicType) ref <postID int64> @ UploadService 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}} 
[_] (-1) (FieldVariable FieldType) PostID int64 
[__] (-1) (BasicVariable BasicType) PostID int64 

[] (-1) (BasicVariable BasicType) postIDStr string 
[_] (-1) (BasicVariable BasicType) postID int64 
[__] (55) (Reference BasicType) ref <postID int64> @ UploadService 
[_] (0) (BasicVariable BasicType) 10 int 

[] (-1) (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string} 

[] (57) (FieldVariable FieldType) mediaID int64 
[_] (58) (BasicVariable BasicType) PostID int64 

[] (-1) (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string} 

[] (-1) (InterfaceVariable UserType) _ .error 

