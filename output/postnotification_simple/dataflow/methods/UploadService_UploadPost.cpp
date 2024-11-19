[] (PointerVariable PointerType) u (*postnotification_simple.UploadServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue})
[_] (StructVariable UserType) postnotification_simple.UploadServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue}
[__] (FieldVariable FieldType) notificationsQueue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue
[__] (FieldVariable FieldType) storageService postnotification_simple.StorageService
[___] (ServiceVariable ServiceType) storageService postnotification_simple.StorageService

[] (InterfaceVariable UserType) ctx context.Context

[] (BasicVariable BasicType) username string

    --> w-tainted: write(posts_db.Post.Text) {1}
[] (BasicVariable BasicType) text string

    --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[] (BasicVariable BasicType) reqID int64
     --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}         --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

    --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[] (BasicVariable BasicType) postID int64
     --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}         --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[_] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

    --> w-tainted: write(posts_db.Post.Timestamp) {1}
[] (BasicVariable BasicType) timestamp int64

    --> w-tainted: write(posts_db.Post.Mentions) {1}
[] (ArrayVariable ArrayType) mentions []string
     --> w-tainted: write(posts_db.Post.Mentions) {1}
[_] (BasicVariable BasicType) "alice" string
     --> w-tainted: write(posts_db.Post.Mentions) {1}
[_] (BasicVariable BasicType) "bob" string

    --> w-tainted: write(posts_db.Post) {1}
[] (StructVariable UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}
     --> w-tainted: write(posts_db.Post.Creator) {1}
[_] (FieldVariable FieldType) Creator postnotification_simple.Creator struct{Username "some username" string}
      --> w-tainted: write(posts_db.Post.Creator) {1}
[__] (StructVariable UserType) postnotification_simple.Creator struct{Username "some username" string}
       --> w-tainted: write(posts_db.Post.Creator.Username) {1}
[___] (FieldVariable FieldType) Username "some username" string
        --> w-tainted: write(posts_db.Post.Creator.Username) {1}
[____] (BasicVariable BasicType) "some username" string
     --> w-tainted: write(posts_db.Post.Mentions) {1}
[_] (FieldVariable FieldType) Mentions []string
      --> w-tainted: write(posts_db.Post.Mentions) {1}
[__] (ArrayVariable ArrayType) mentions []string
       --> w-tainted: write(posts_db.Post.Mentions) {1}
[___] (BasicVariable BasicType) "alice" string
       --> w-tainted: write(posts_db.Post.Mentions) {1}
[___] (BasicVariable BasicType) "bob" string
     --> w-tainted: write(posts_db.Post.PostID) {1}
[_] (FieldVariable FieldType) PostID int64
      --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}           --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[__] (BasicVariable BasicType) postID int64
       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}             --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(posts_db.Post.ReqID) {1}
[_] (FieldVariable FieldType) ReqID int64
      --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}           --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicVariable BasicType) reqID int64
       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}             --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
     --> w-tainted: write(posts_db.Post.Text) {1}
[_] (FieldVariable FieldType) Text string
      --> w-tainted: write(posts_db.Post.Text) {1}
[__] (BasicVariable BasicType) text string
     --> w-tainted: write(posts_db.Post.Timestamp) {1}
[_] (FieldVariable FieldType) Timestamp int64
      --> w-tainted: write(posts_db.Post.Timestamp) {1}
[__] (BasicVariable BasicType) timestamp int64

    --> w-tainted: write(notifications_queue.message) {1}       --> w-tainted: write(notifications_queue.message) {1} --> r-tainted: read(notifications_queue.message) {1}
[] (StructVariable UserType) message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}
     --> w-tainted: write(notifications_queue.Message.PostID) {1}         --> w-tainted: write(notifications_queue.Message.PostID) {1} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[_] (FieldVariable FieldType) PostID string
      --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}           --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[__] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.PostID) {1}           --> w-tainted: write(notifications_queue.Message.PostID) {1} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[__] (BasicVariable BasicType) string
       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}             --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}             --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[___] (BasicVariable BasicType) postID int64
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(notifications_queue.Message.ReqID) {1}         --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (FieldVariable FieldType) ReqID string
      --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}           --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.ReqID) {1}           --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicVariable BasicType) string
       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}             --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}             --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (BasicVariable BasicType) reqID int64
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

[] (BasicVariable BasicType) _ bool

[] (InterfaceVariable UserType) err .error

