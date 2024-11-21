[] (PointerObject PointerType) u (*postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache})
[_] (StructObject UserType) postnotification.UploadServiceImpl struct{storageService postnotification.StorageService, mediaService postnotification.MediaService, notificationsQueue Queue, timelineCache Cache}
[__] (FieldObject FieldType) mediaService postnotification.MediaService
[___] (ServiceObject ServiceType) mediaService postnotification.MediaService
[__] (FieldObject FieldType) notificationsQueue Queue
[___] (BlueprintBackendObject BlueprintBackendType) notificationsQueue Queue
[__] (FieldObject FieldType) storageService postnotification.StorageService
[___] (ServiceObject ServiceType) storageService postnotification.StorageService
[__] (FieldObject FieldType) timelineCache Cache
[___] (BlueprintBackendObject BlueprintBackendType) timelineCache Cache

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) reqID int64

    --> r-tainted: read(posts_cache.int64) {1}
[] (BasicObject BasicType) postID int64

[] (StructObject UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}

[] (StructObject UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}
[_] (Reference UserType) ref <media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}> @ StorageService
      --> r-tainted: read(media_db.Media) {1}
[__] (Reference UserType) ref <media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}> @ MediaService

[] (InterfaceObject UserType) _ .error
[_] (Reference BasicType) ref <nil> @ StorageService

