[] (PointerObject PointerType) s (*postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase})
[_] (StructObject UserType) postnotification_simple.StorageServiceImpl struct{postsDb NoSQLDatabase}
[__] (FieldObject FieldType) postsDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) postsDb NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ UploadService

    --> w-tainted: write(posts_db.Post.ReqID) {1}
[] (BasicObject BasicType) reqID int64
     --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2}         --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (Reference BasicType) ref <reqID int64> @ UploadService

    --> w-tainted: write(posts_db.Post.Text) {1}
[] (BasicObject BasicType) text string
     --> w-tainted: write(posts_db.Post.Text) {1}
[_] (Reference BasicType) ref <text string> @ UploadService

    --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[] (BasicObject BasicType) postID_STORAGE_SVC int64

    --> w-tainted: write(posts_db.Post.Timestamp) {1}
[] (BasicObject BasicType) timestamp int64

    --> w-tainted: write(posts_db.Post.Mentions) {1}
[] (ArrayObject ArrayType) mentions []string
     --> w-tainted: write(posts_db.Post.Mentions) {1}
[_] (BasicObject BasicType) "alice" string
     --> w-tainted: write(posts_db.Post.Mentions) {1}
[_] (BasicObject BasicType) "bob" string

    --> w-tainted: write(posts_db.Post) {1}
[] (StructObject UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username string}}
     --> w-tainted: write(posts_db.Post.Creator) {1}
[_] (FieldObject FieldType) Creator postnotification_simple.Creator struct{Username "some username" string}
      --> w-tainted: write(posts_db.Post.Creator) {1}
[__] (StructObject UserType) postnotification_simple.Creator struct{Username "some username" string}
       --> w-tainted: write(posts_db.Post.Creator.Username) {1}
[___] (FieldObject FieldType) Username "some username" string
        --> w-tainted: write(posts_db.Post.Creator.Username) {1}
[____] (BasicObject BasicType) "some username" string
     --> w-tainted: write(posts_db.Post.Mentions) {1}
[_] (FieldObject FieldType) Mentions []string
      --> w-tainted: write(posts_db.Post.Mentions) {1}
[__] (ArrayObject ArrayType) mentions []string
       --> w-tainted: write(posts_db.Post.Mentions) {1}
[___] (BasicObject BasicType) "alice" string
       --> w-tainted: write(posts_db.Post.Mentions) {1}
[___] (BasicObject BasicType) "bob" string
     --> w-tainted: write(posts_db.Post.PostID) {1}
[_] (FieldObject FieldType) PostID int64
      --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2}           --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID_MESSAGE) {2} --> r-tainted: read(notifications_queue.Message.PostID_MESSAGE, posts_db.Post.PostID) {2}
[__] (BasicObject BasicType) postID_STORAGE_SVC int64
     --> w-tainted: write(posts_db.Post.ReqID) {1}
[_] (FieldObject FieldType) ReqID int64
      --> w-tainted: write(posts_db.Post.ReqID) {1}
[__] (BasicObject BasicType) reqID int64
       --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2}             --> w-tainted: write(notifications_queue.Message.ReqID, posts_db.Post.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference BasicType) ref <reqID int64> @ UploadService
     --> w-tainted: write(posts_db.Post.Text) {1}
[_] (FieldObject FieldType) Text string
      --> w-tainted: write(posts_db.Post.Text) {1}
[__] (BasicObject BasicType) text string
       --> w-tainted: write(posts_db.Post.Text) {1}
[___] (Reference BasicType) ref <text string> @ UploadService
     --> w-tainted: write(posts_db.Post.Timestamp) {1}
[_] (FieldObject FieldType) Timestamp int64
      --> w-tainted: write(posts_db.Post.Timestamp) {1}
[__] (BasicObject BasicType) timestamp int64

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[] (InterfaceObject UserType) err .error

[] (InterfaceObject UserType) err .error

