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

    --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[] (BasicObject BasicType) reqID int64
     --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}         --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

    --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[] (BasicObject BasicType) postID int64
     --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}         --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[_] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

    --> w-tainted: write(posts_db.Post.Timestamp) {1}
[] (BasicObject BasicType) timestamp int64

    --> w-tainted: write(posts_db.Post.Mentions) {1}
[] (ArrayObject ArrayType) mentions []string
     --> w-tainted: write(posts_db.Post.Mentions) {1}
[_] (BasicObject BasicType) "alice" string
     --> w-tainted: write(posts_db.Post.Mentions) {1}
[_] (BasicObject BasicType) "bob" string

    --> w-tainted: write(posts_db.Post) {1}
[] (StructObject UserType) post postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}
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
      --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}           --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[__] (BasicObject BasicType) postID int64
       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}             --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(posts_db.Post.ReqID) {1}
[_] (FieldObject FieldType) ReqID int64
      --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}           --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicObject BasicType) reqID int64
       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}             --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
     --> w-tainted: write(posts_db.Post.Text) {1}
[_] (FieldObject FieldType) Text string
      --> w-tainted: write(posts_db.Post.Text) {1}
[__] (BasicObject BasicType) text string
     --> w-tainted: write(posts_db.Post.Timestamp) {1}
[_] (FieldObject FieldType) Timestamp int64
      --> w-tainted: write(posts_db.Post.Timestamp) {1}
[__] (BasicObject BasicType) timestamp int64

    --> w-tainted: write(notifications_queue.message) {1}       --> w-tainted: write(notifications_queue.message) {1} --> r-tainted: read(notifications_queue.message) {1}
[] (StructObject UserType) message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}
     --> w-tainted: write(notifications_queue.Message.PostID) {1}         --> w-tainted: write(notifications_queue.Message.PostID) {1} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[_] (FieldObject FieldType) PostID string
      --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}           --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[__] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.PostID) {1}           --> w-tainted: write(notifications_queue.Message.PostID) {1} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[__] (BasicObject BasicType) string
       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}             --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[___] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
       --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}             --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID) {1}
[___] (BasicObject BasicType) postID int64
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(notifications_queue.Message.ReqID) {1}         --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_] (FieldObject FieldType) ReqID string
      --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}           --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
      --> w-tainted: write(notifications_queue.Message.ReqID) {1}           --> w-tainted: write(notifications_queue.Message.ReqID) {1} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[__] (BasicObject BasicType) string
       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}             --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService
       --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}             --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[___] (BasicObject BasicType) reqID int64
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (Reference InterfaceType) ref <ReqID interface{}> @ NotifyService

[] (BasicObject BasicType) _ bool

[] (InterfaceObject UserType) err .error

