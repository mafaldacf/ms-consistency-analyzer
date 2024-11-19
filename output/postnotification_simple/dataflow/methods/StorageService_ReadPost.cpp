[] (PointerObject PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase})
[_] (StructObject UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}
[__] (FieldObject FieldType) postsDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) postsDb NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService

[] (BasicObject BasicType) reqID int64
     --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (Reference BasicType) ref <ReqID int64> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.ReqID) {1}           --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference FieldType) ref <ReqID int64> @ NotifyService
       --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2}             --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (BasicObject BasicType) reqID int64

    --> r-tainted: read(posts_db.Post.PostID) {1}
[] (BasicObject BasicType) postID int64
     --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[_] (Reference BasicType) ref <PostID_MESSAGE int64> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}           --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[__] (Reference FieldType) ref <PostID_MESSAGE int64> @ NotifyService
       --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}             --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[___] (BasicObject BasicType) postID_UploadSVC int64
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[____] (Reference BasicType) ref <postID_STORAGE_SVC int64> @ StorageService

[] (StructObject UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "postid" string, Value int64}
[__] (FieldObject FieldType) Key "postid" string
[___] (BasicObject BasicType) "postid" string
[__] (FieldObject FieldType) Value int64
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicObject BasicType) postID int64
        --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[____] (Reference BasicType) ref <PostID_MESSAGE int64> @ NotifyService
         --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}                 --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[_____] (Reference FieldType) ref <PostID_MESSAGE int64> @ NotifyService
          --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1}                   --> w-tainted: write(notifications_queue.Message.PostID_MESSAGE) {1} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[______] (BasicObject BasicType) postID_UploadSVC int64
           --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}                     --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[_______] (Reference BasicType) ref <postID_STORAGE_SVC int64> @ StorageService

[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = post, collection = post}
[_] (StructObject UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) res bool

[] (InterfaceObject UserType) err .error

