[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ServiceVariable ServiceType) analytics_service postnotification.AnalyticsService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_db NoSQLDatabase 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 

[] (-1) (AddressVariable AddressType) s (&postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue}) 
[_] (0) (StructVariable UserType) postnotification.StorageServiceImpl struct{analytics_service postnotification.AnalyticsService, posts_cache Cache, posts_db NoSQLDatabase, analytics_queue Queue} 
[__] (0) (FieldVariable FieldType) posts_cache Cache 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_cache Cache 
[__] (0) (FieldVariable FieldType) posts_db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) posts_db NoSQLDatabase 
[__] (0) (FieldVariable FieldType) analytics_queue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (0) (FieldVariable FieldType) analytics_service postnotification.AnalyticsService 
[___] (-1) (ServiceVariable ServiceType) analytics_service postnotification.AnalyticsService 

