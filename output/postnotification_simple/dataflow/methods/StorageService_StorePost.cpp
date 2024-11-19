[] (PointerVariable PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase})
[_] (StructVariable UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}
[__] (FieldVariable FieldType) postsDb NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) postsDb NoSQLDatabase

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ UploadService

[] (BasicVariable BasicType) reqID int64
     --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}         --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (Reference BasicType) ref <reqID int64> @ UploadService
      --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}           --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

    --> w-tainted: write(posts_db.Post) {1}
[] (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}
     --> w-tainted: write(posts_db.Post) {1}
[_] (Reference UserType) ref <post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}> @ UploadService
      --> w-tainted: write(posts_db.Post.Creator) {1}
[__] (FieldVariable FieldType) Creator postnotification_simple.Creator struct{Username "some username" string}
       --> w-tainted: write(posts_db.Post.Creator) {1}
[___] (StructVariable UserType) postnotification_simple.Creator struct{Username "some username" string}
        --> w-tainted: write(posts_db.Post.Creator.Username) {1}
[____] (FieldVariable FieldType) Username "some username" string
         --> w-tainted: write(posts_db.Post.Creator.Username) {1}
[_____] (BasicVariable BasicType) "some username" string
      --> w-tainted: write(posts_db.Post.Mentions) {1}
[__] (FieldVariable FieldType) Mentions []string
       --> w-tainted: write(posts_db.Post.Mentions) {1}
[___] (ArrayVariable ArrayType) mentions []string
        --> w-tainted: write(posts_db.Post.Mentions) {1}
[____] (BasicVariable BasicType) "alice" string
        --> w-tainted: write(posts_db.Post.Mentions) {1}
[____] (BasicVariable BasicType) "bob" string
      --> w-tainted: write(posts_db.Post.PostID) {1}
[__] (FieldVariable FieldType) PostID int64
       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}             --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[___] (BasicVariable BasicType) postID int64
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
      --> w-tainted: write(posts_db.Post.ReqID) {1}
[__] (FieldVariable FieldType) ReqID int64
       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}             --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (BasicVariable BasicType) reqID int64
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
      --> w-tainted: write(posts_db.Post.Text) {1}
[__] (FieldVariable FieldType) Text string
       --> w-tainted: write(posts_db.Post.Text) {1}
[___] (BasicVariable BasicType) text string
      --> w-tainted: write(posts_db.Post.Timestamp) {1}
[__] (FieldVariable FieldType) Timestamp int64
       --> w-tainted: write(posts_db.Post.Timestamp) {1}
[___] (BasicVariable BasicType) timestamp int64

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[] (InterfaceVariable UserType) err .error

[] (InterfaceVariable UserType) err .error

