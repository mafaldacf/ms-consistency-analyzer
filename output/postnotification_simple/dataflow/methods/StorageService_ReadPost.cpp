[] (PointerObject PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase})
[_] (StructObject UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}
[__] (FieldObject FieldType) postsDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) postsDb NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService

[] (BasicObject BasicType) reqID int64
[_] (Reference BasicType) ref <reqID int64> @ NotifyService
[__] (BasicObject BasicType) ReqID string
[___] (Reference FieldType) ref <ReqID string> @ NotifyService
[____] (BasicObject BasicType) ReqID string
         --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}                 --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_____] (InterfaceObject InterfaceType) ReqID interface{}

    --> r-tainted: read(posts_db.Post.PostID) {1}
[] (BasicObject BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID) {1}
[_] (Reference BasicType) ref <postID int64> @ NotifyService
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (BasicObject BasicType) PostID string
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (Reference FieldType) ref <PostID string> @ NotifyService
        --> r-tainted: read(posts_db.Post.PostID) {1}
[____] (BasicObject BasicType) PostID string
         --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}                 --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[_____] (InterfaceObject InterfaceType) PostID interface{}

    --> r-tainted: read(posts_db.Post) {1}
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
        --> r-tainted: read(posts_db.Post.PostID) {1}
[____] (Reference BasicType) ref <postID int64> @ NotifyService
         --> r-tainted: read(posts_db.Post.PostID) {1}
[_____] (BasicObject BasicType) PostID string
          --> r-tainted: read(posts_db.Post.PostID) {1}
[______] (Reference FieldType) ref <PostID string> @ NotifyService
           --> r-tainted: read(posts_db.Post.PostID) {1}
[_______] (BasicObject BasicType) PostID string
            --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}                       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[________] (InterfaceObject InterfaceType) PostID interface{}

    --> r-tainted: read(posts_db.Post) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = post, collection = post}
     --> r-tainted: read(posts_db.Post) {1}
[_] (StructObject UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) res bool

[] (InterfaceObject UserType) err .error

