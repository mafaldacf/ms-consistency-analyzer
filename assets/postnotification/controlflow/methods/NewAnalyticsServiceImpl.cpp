[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 

[] (-1) (AddressVariable AddressType) n (&postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.AnalyticsServiceImpl struct{analytics_queue Queue, analytics_db NoSQLDatabase, num_workers int} 
[__] (0) (FieldVariable FieldType) analytics_db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (0) (FieldVariable FieldType) analytics_queue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (0) (FieldVariable FieldType) num_workers 4 int 
[___] (0) (BasicVariable BasicType) 4 int 

