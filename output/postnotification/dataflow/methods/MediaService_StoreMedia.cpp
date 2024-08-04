[] (PointerVariable PointerType) s (*postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase}) 
[_] (StructVariable UserType) postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase} 
[__] (FieldVariable FieldType) mediaDb NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) mediaDb NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string} // write(media_db), 
[_] (Reference UserType) ref <media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}> @ UploadService // write(media_db), 
[__] (FieldVariable FieldType) Content "HELLO WORLD!" untyped string // write(media_db), 
[___] (BasicVariable BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string // write(media_db), 
[__] (FieldVariable FieldType) MediaID int64 // write(media_db), 
[___] (BasicVariable BasicType) mediaID int64 // write(media_db), 
[__] (FieldVariable FieldType) PostID int64 // write(media_db), 
[___] (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = media, collection = media} 

[] (InterfaceVariable UserType) err .error 

