[] (-1) (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, media_service postnotification.MediaService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, media_service postnotification.MediaService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue} 
[__] (-1) (ServiceVariable ServiceType) analytics_service postnotification.AnalyticsService 
[__] (-1) (ServiceVariable ServiceType) media_service postnotification.MediaService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 

[] (56) (InterfaceVariable UserType) ctx context.Context 
[_] (53) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (-1) (BasicVariable BasicType) reqID int64 
[_] (54) (Reference BasicType) ref <reqID int64> @ UploadService 

[] (-1) (BasicVariable BasicType) postID int64 
[_] (55) (Reference BasicType) ref <postID int64> @ UploadService 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 
[_] (-1) (FieldVariable FieldType) PostID int64 
[__] (-1) (BasicVariable BasicType) PostID int64 

[] (-1) (BasicVariable BasicType) postIDStr string 
[_] (-1) (BasicVariable BasicType) postID int64 
[__] (55) (Reference BasicType) ref <postID int64> @ UploadService 
[_] (0) (BasicVariable BasicType) 10 int 

[] (-1) (StructVariable UserType) media postnotification.Media struct{MediaID int64, PostID int64, Content string} 

[] (57) (FieldVariable FieldType) mediaID int64 
[_] (58) (BasicVariable BasicType) PostID int64 

[] (-1) (StructVariable UserType) media postnotification.Media struct{MediaID int64, PostID int64, Content string} 

[] (-1) (InterfaceVariable UserType) _ .error 

