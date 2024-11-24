[] (PointerObject PointerType) s (*postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase})
[_] (StructObject UserType) postnotification.MediaServiceImpl struct{mediaDb NoSQLDatabase}
[__] (FieldObject FieldType) mediaDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) mediaDb NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ UploadService

    --> w-tainted: write(media_db.Media) {1}
[] (StructObject UserType) media postnotification.Media struct{MediaID int64, Content string}
     --> w-tainted: write(media_db.Media) {1}
[_] (Reference UserType) ref <media postnotification.Media struct{Content "HELLO WORLD!" untyped string, Content string}> @ UploadService
      --> w-tainted: write(media_db.Media.Content) {1}
[__] (FieldObject FieldType) Content "HELLO WORLD!" untyped string
       --> w-tainted: write(media_db.Media.Content) {1}
[___] (BasicObject BasicType) HELLO_WORLD_CONST "HELLO WORLD!" untyped string
     --> w-tainted: write(media_db.Media.MediaID) {1}
[_] (FieldObject FieldType) MediaID int64
      --> w-tainted: write(media_db.Media.MediaID) {1}
[__] (BasicObject BasicType) mediaID int64

    --> w-tainted: write(media_db.Media.MediaID) {1}
[] (BasicObject BasicType) mediaID int64

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = media, collection = media}

[] (InterfaceObject UserType) err .error

