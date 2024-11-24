[] (PointerObject PointerType) s (*postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase})
[_] (StructObject UserType) postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase}
[__] (FieldObject FieldType) mediaDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) mediaDb NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ StorageService
[__] (Reference UserType) ref <ctx context.Context> @ UploadService

    --> r-tainted: read(media_db._.mediaid) {1}
[] (BasicObject BasicType) mediaID int64
     --> r-tainted: read(media_db._.mediaid) {1}
[_] (Reference FieldType) ref <mediaID int64> @ StorageService
      --> r-tainted: read(media_db._.mediaid) {1}
[__] (BasicObject BasicType) PostID int64

    --> r-tainted: read(media_db.Media) {1}
[] (StructObject UserType) media postnotification.Media struct{MediaID int64, Content string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = media, collection = media}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "mediaid" string, Value int64}
[__] (FieldObject FieldType) Key "mediaid" string
[___] (BasicObject BasicType) "mediaid" string
[__] (FieldObject FieldType) Value int64
       --> r-tainted: read(media_db._.mediaid) {1}
[___] (BasicObject BasicType) mediaID int64
        --> r-tainted: read(media_db._.mediaid) {1}
[____] (Reference FieldType) ref <mediaID int64> @ StorageService
         --> r-tainted: read(media_db._.mediaid) {1}
[_____] (BasicObject BasicType) PostID int64

    --> r-tainted: read(media_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = media, collection = media}
     --> r-tainted: read(media_db.Media) {1}
[_] (StructObject UserType) media postnotification.Media struct{MediaID int64, Content string}

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) _ bool

[] (InterfaceObject UserType) err .error

