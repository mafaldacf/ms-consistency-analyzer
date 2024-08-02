[] (-1) (PointerVariable PointerType) s (*postnotification.MediaServiceImpl struct{media_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) postnotification.MediaServiceImpl struct{media_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) media_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (4) (Reference UserType) ref <ctx context.Context> @ StorageService 
[__] (1) (Reference UserType) ref <ctx context.Context> @ UploadService 

[] (-1) (BasicVariable BasicType) mediaID int64 
[_] (5) (Reference FieldType) ref <mediaID int64> @ StorageService 
[__] (6) (BasicVariable BasicType) PostID int64 

[] (-1) (StructVariable UserType) media postnotification.Media struct{MediaID int64, PostID int64, Content string} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = media, collection = media} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "mediaid" string, Value int64} 
[__] (0) (FieldVariable FieldType) Key "mediaid" string 
[___] (0) (BasicVariable BasicType) "mediaid" string 
[__] (0) (FieldVariable FieldType) Value int64 
[___] (-1) (BasicVariable BasicType) mediaID int64 
[____] (5) (Reference FieldType) ref <mediaID int64> @ StorageService 
[_____] (6) (BasicVariable BasicType) PostID int64 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = media, collection = media} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

