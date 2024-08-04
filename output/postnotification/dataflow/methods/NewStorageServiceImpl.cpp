[] (InterfaceVariable UserType) ctx context.Context 

[] (ServiceVariable ServiceType) analyticsService postnotification.AnalyticsService 

[] (ServiceVariable ServiceType) mediaService postnotification.MediaService 

[] (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 

[] (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase 

[] (BlueprintBackendVariable BlueprintBackendType) analyticsQueue Queue 

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

