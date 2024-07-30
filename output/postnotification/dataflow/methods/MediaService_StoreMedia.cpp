[] (-1) (PointerVariable PointerType) s (*postnotification.MediaServiceImpl struct{media_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) postnotification.MediaServiceImpl struct{media_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) media_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (1) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (-1) (StructVariable UserType) media postnotification.Media struct{MediaID int64, PostID int64, Content string} // write(media_db), 
[_] (2) (Reference UserType) ref <media postnotification.Media struct{MediaID int64, PostID int64, Content string}> @ UploadService // write(media_db), 
[__] (3) (FieldVariable FieldType) Content "a nice content" string // write(media_db), 
[___] (4) (BasicVariable BasicType) "a nice content" string // write(media_db), 
[__] (5) (FieldVariable FieldType) PostID int64 // write(media_db), 
[___] (-1) (BasicVariable BasicType) postID int64 // write(media_db), write(posts_db), write(posts_cache), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[____] (49) (Reference InterfaceType) ref <PostID interface{}> @ NotifyService // write(media_db), write(posts_cache), write(posts_db), write(analytics_queue), write(analytics_db), write(notifications_queue), write(timeline_cache), 
[__] (7) (FieldVariable FieldType) MediaID int64 // write(media_db), 
[___] (8) (BasicVariable BasicType) mediaID int64 // write(media_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = media, collection = media} 

[] (-1) (InterfaceVariable UserType) err .error 

