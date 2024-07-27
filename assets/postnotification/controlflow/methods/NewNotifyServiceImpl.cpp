[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 

[] (-1) (AddressVariable AddressType) n (&postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) postnotification.NotifyServiceImpl struct{storage_service postnotification.StorageService, notifications_queue Queue, num_workers int} 
[__] (0) (FieldVariable FieldType) num_workers 4 int 
[___] (0) (BasicVariable BasicType) 4 int 
[__] (0) (FieldVariable FieldType) storage_service postnotification.StorageService 
[___] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (0) (FieldVariable FieldType) notifications_queue Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) notifications_queue Queue 

