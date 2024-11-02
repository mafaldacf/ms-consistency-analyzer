[] (PointerVariable PointerType) s (*postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase})
[_] (StructVariable UserType) postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase}
[__] (FieldVariable FieldType) mediaDb NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) mediaDb NoSQLDatabase

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ StorageService
[__] (Reference UserType) ref <ctx context.Context> @ UploadService

    --> r-tainted: read(media_db.Media.MediaID) {1}
[] (BasicVariable BasicType) mediaID int64
     --> r-tainted: read(media_db.Media.MediaID) {1}
[_] (Reference FieldType) ref <mediaID int64> @ StorageService
      --> r-tainted: read(media_db.Media.MediaID) {1}
[__] (BasicVariable BasicType) PostID int64

    --> r-tainted: read(media_db.Media) {1}
[] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = media, collection = media}

[] (InterfaceVariable UserType) err .error

[] (SliceVariable UserType) query primitive.D
[_] (StructVariable StructType) struct{Key "mediaid" string, Value int64}
[__] (FieldVariable FieldType) Key "mediaid" string
[___] (BasicVariable BasicType) "mediaid" string
[__] (FieldVariable FieldType) Value int64
       --> r-tainted: read(media_db.Media.MediaID) {1}
[___] (BasicVariable BasicType) mediaID int64
        --> r-tainted: read(media_db.Media.MediaID) {1}
[____] (Reference FieldType) ref <mediaID int64> @ StorageService
         --> r-tainted: read(media_db.Media.MediaID) {1}
[_____] (BasicVariable BasicType) PostID int64

    --> r-tainted: read(media_db.Media) {1}
[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = media, collection = media}
     --> r-tainted: read(media_db.Media) {1}
[_] (StructVariable UserType) media postnotification.Media struct{PostID int64, MediaID int64, Content "HELLO WORLD!" untyped string}

[] (InterfaceVariable UserType) err .error

[] (BasicVariable BasicType) _ bool

[] (InterfaceVariable UserType) err .error

