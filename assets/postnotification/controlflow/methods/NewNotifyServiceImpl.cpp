[] (InterfaceVariable UserType) ctx context.Context 

[] (ServiceVariable ServiceType) storageService postnotification.StorageService 

[] (BlueprintBackendVariable BlueprintBackendType) queue Queue 

[] (AddressVariable AddressType) n (&postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, queue Queue, numWorkers int}) 
[_] (StructVariable UserType) postnotification.NotifyServiceImpl struct{storageService postnotification.StorageService, queue Queue, numWorkers int} 
[__] (FieldVariable FieldType) numWorkers 4 int 
[___] (BasicVariable BasicType) 4 int 
[__] (FieldVariable FieldType) storageService postnotification.StorageService 
[___] (ServiceVariable ServiceType) storageService postnotification.StorageService 
[__] (FieldVariable FieldType) queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) queue Queue 

