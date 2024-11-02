[] (PointerVariable PointerType) u (*postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache})
[_] (StructVariable UserType) postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache}
[__] (FieldVariable FieldType) mediaService postnotification.MediaService
[___] (ServiceVariable ServiceType) mediaService postnotification.MediaService
[__] (FieldVariable FieldType) notificationsQueue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue
[__] (FieldVariable FieldType) storageService postnotification.StorageService
[___] (ServiceVariable ServiceType) storageService postnotification.StorageService
[__] (FieldVariable FieldType) timelineCache Cache
[___] (BlueprintBackendVariable BlueprintBackendType) timelineCache Cache

[] (InterfaceVariable UserType) ctx context.Context

[] (BasicVariable BasicType) reqID int64

    --> r-tainted: read(posts_cache.int64) {1}
[] (BasicVariable BasicType) postID int64

[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}

[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}

[] (InterfaceVariable UserType) _ .error

