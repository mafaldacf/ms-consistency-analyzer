[] (PointerVariable PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase})
[_] (StructVariable UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}
[__] (FieldVariable FieldType) postsDb NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService
[__] (Reference UserType) ref <ctx context.Context> @ NotifyService

[] (BasicVariable BasicType) reqID int64
[_] (Reference BasicType) ref <reqID int64> @ NotifyService
[__] (BasicVariable BasicType) ReqID string
[___] (Reference FieldType) ref <ReqID string> @ NotifyService
[____] (BasicVariable BasicType) ReqID string
         --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}                 --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_____] (InterfaceVariable InterfaceType) ReqID interface{}

    --> r-tainted: read(posts_db.Post.PostID) {1}
[] (BasicVariable BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID) {1}
[_] (Reference BasicType) ref <postID int64> @ NotifyService
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (BasicVariable BasicType) PostID string
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (Reference FieldType) ref <PostID string> @ NotifyService
        --> r-tainted: read(posts_db.Post.PostID) {1}
[____] (BasicVariable BasicType) PostID string
         --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}                 --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[_____] (InterfaceVariable InterfaceType) PostID interface{}

    --> r-tainted: read(posts_db.Post) {1}
[] (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[] (InterfaceVariable UserType) err .error

[] (SliceVariable UserType) query primitive.D
[_] (StructVariable StructType) struct{Key "postid" string, Value int64}
[__] (FieldVariable FieldType) Key "postid" string
[___] (BasicVariable BasicType) "postid" string
[__] (FieldVariable FieldType) Value int64
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicVariable BasicType) postID int64
        --> r-tainted: read(posts_db.Post.PostID) {1}
[____] (Reference BasicType) ref <postID int64> @ NotifyService
         --> r-tainted: read(posts_db.Post.PostID) {1}
[_____] (BasicVariable BasicType) PostID string
          --> r-tainted: read(posts_db.Post.PostID) {1}
[______] (Reference FieldType) ref <PostID string> @ NotifyService
           --> r-tainted: read(posts_db.Post.PostID) {1}
[_______] (BasicVariable BasicType) PostID string
            --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}                       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[________] (InterfaceVariable InterfaceType) PostID interface{}

    --> r-tainted: read(posts_db.Post) {1}
[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = post, collection = post}
     --> r-tainted: read(posts_db.Post) {1}
[_] (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}

[] (InterfaceVariable UserType) err .error

[] (BasicVariable BasicType) res bool

[] (InterfaceVariable UserType) err .error

