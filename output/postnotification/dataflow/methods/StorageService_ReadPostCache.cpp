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

[] (BasicVariable BasicType) reqID int64

[] (BasicVariable BasicType) postID int64

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username "some username" string}, Creator postnotification.Creator struct{Username "some username" string}}

[] (BasicVariable BasicType) postIDStr string
[_] (BasicVariable BasicType) postID int64
[_] (BasicVariable BasicType) 10 int

[] (BasicVariable BasicType) _ bool

[] (InterfaceVariable UserType) err .error

