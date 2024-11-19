[] (PointerObject PointerType) u (*postnotification_simple.UploadServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue})
[_] (StructObject UserType) postnotification_simple.UploadServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue}
[__] (FieldObject FieldType) notificationsQueue Queue
[___] (BlueprintBackendObject BlueprintBackendType) notificationsQueue Queue
[__] (FieldObject FieldType) storageService postnotification_simple.StorageService
[___] (ServiceObject ServiceType) storageService postnotification_simple.StorageService

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) username string

    --> w-tainted: write(posts_db.Post.Text) {1}
[] (BasicObject BasicType) text string

    --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2}       --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[] (BasicObject BasicType) reqID int64

    --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}       --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[] (BasicObject BasicType) postID_UploadSVC int64
     --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}         --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[_] (Reference BasicType) ref <postID_STORAGE_SVC int64> @ StorageService

[] (InterfaceObject UserType) _ .error
[_] (Reference UserType) ref <err .error> @ StorageService

    --> w-tainted: write(notifications_queue.message) {1}       --> w-tainted: write(notifications_queue.message) {1} --> r-tainted: read(notifications_queue.message) {1}
[] (StructObject UserType) message postnotification_simple.Message struct{ReqID int64, PostID_MESSAGE int64, Timestamp int64}
     --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}         --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[_] (FieldObject FieldType) PostID_MESSAGE int64
      --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}           --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[__] (BasicObject BasicType) postID_UploadSVC int64
       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}             --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[___] (Reference BasicType) ref <postID_STORAGE_SVC int64> @ StorageService
     --> w-tainted: write(notifications_queue.Message.ReqID) {1}         --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (FieldObject FieldType) ReqID int64
      --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2}           --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicObject BasicType) reqID int64

[] (BasicObject BasicType) _ bool

[] (InterfaceObject UserType) err .error

