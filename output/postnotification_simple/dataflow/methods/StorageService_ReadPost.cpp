[0] (PointerObject PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase})
[_1] (StructObject UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}
[__2] (FieldObject FieldType) postsDb NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postsDb NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ NotifyService

    --> w-tainted: write(notifications_queue.Message.ReqID) {1}       --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(notifications_queue.Message.ReqID) {1}         --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_1] (Reference BasicType) ref <ReqID int64> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.ReqID) {1}           --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__2] (Reference FieldType) ref <ReqID int64> @ NotifyService
       --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2}             --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___3] (BasicObject BasicType) reqID int64

    --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}       --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}
[0] (BasicObject BasicType) postID int64
     --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}         --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[_1] (Reference BasicType) ref <PostID_MESSAGE int64> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}           --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[__2] (Reference FieldType) ref <PostID_MESSAGE int64> @ NotifyService
       --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}             --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[___3] (BasicObject BasicType) postID_UploadSVC int64
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[____4] (Reference BasicType) ref <postID_STORAGE_SVC int64> @ StorageService

    --> r-tainted: read(posts_db.Post) {1}
[0] (StructObject UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username string}}

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[0] (InterfaceObject UserType) err .error

[0] (SliceObject UserType) query primitive.D
[_1] (StructObject StructType) struct{Key "postid" string, Key "postid" string, Value int64, Value int64}
[__2] (FieldObject FieldType) Key "postid" string
[___3] (BasicObject BasicType) "postid" string
[__2] (FieldObject FieldType) Value int64
       --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}             --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}
[___3] (BasicObject BasicType) postID int64
        --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}               --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[____4] (Reference BasicType) ref <PostID_MESSAGE int64> @ NotifyService
         --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}                 --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[_____5] (Reference FieldType) ref <PostID_MESSAGE int64> @ NotifyService
          --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}                   --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[______6] (BasicObject BasicType) postID_UploadSVC int64
           --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}                     --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[_______7] (Reference BasicType) ref <postID_STORAGE_SVC int64> @ StorageService

    --> r-tainted: read(posts_db.Post) {1}
[0] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = post, collection = post}
     --> r-tainted: read(posts_db.Post) {1}
[_1] (StructObject UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, MediaID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username string}}

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) res bool

[0] (InterfaceObject UserType) err .error

