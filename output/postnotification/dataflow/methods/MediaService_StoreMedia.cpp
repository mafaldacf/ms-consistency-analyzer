[] (-1) (PointerVariable PointerType) s (*postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase}) 
[_] (0) (StructVariable UserType) postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) mediaDb NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) mediaDb NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (1) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (-1) (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string} // write(media_db), 
[_] (2) (Reference UserType) ref <media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}> @ UploadService // write(media_db), 
[__] (3) (FieldVariable FieldType) PostID int64 // write(media_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (46) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (5) (FieldVariable FieldType) MediaID int64 // write(media_db), 
[___] (6) (BasicVariable BasicType) mediaID int64 // write(media_db), 
[__] (7) (FieldVariable FieldType) Content "HELLO WORLD!" untyped string // write(media_db), 
[___] (8) (BasicVariable BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string // write(media_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = media, collection = media} 

[] (-1) (InterfaceVariable UserType) err .error 

