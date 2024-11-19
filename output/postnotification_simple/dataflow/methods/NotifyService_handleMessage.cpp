[] (PointerObject PointerType) n (*postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int})
[_] (StructObject UserType) postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int}
[__] (FieldObject FieldType) notificationsQueue Queue
[___] (BlueprintBackendObject BlueprintBackendType) notificationsQueue Queue
[__] (FieldObject FieldType) num_workers 4 int
[___] (BasicObject BasicType) 4 int
[__] (FieldObject FieldType) storageService postnotification_simple.StorageService
[___] (ServiceObject ServiceType) storageService postnotification_simple.StorageService

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService

[] (StructObject UserType) message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}
[_] (Reference UserType) ref <workerMessage postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (FieldObject FieldType) PostID string
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicObject BasicType) PostID string
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (InterfaceObject InterfaceType) PostID interface{}
[__] (FieldObject FieldType) ReqID string
[___] (BasicObject BasicType) ReqID string
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceObject InterfaceType) ReqID interface{}
[__] (FieldObject FieldType) Timestamp string
[___] (BasicObject BasicType) Timestamp string
        --> r-tainted: read(notifications_queue.message) {1}
[____] (InterfaceObject InterfaceType) Timestamp interface{}
[_] (FieldObject FieldType) PostID string
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicObject BasicType) PostID string
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (InterfaceObject InterfaceType) PostID interface{}
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (BasicObject BasicType) PostID string
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (Reference FieldType) ref <PostID string> @ NotifyService
        --> r-tainted: read(posts_db.Post.PostID) {1}
[____] (BasicObject BasicType) PostID string
         --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}                 --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[_____] (InterfaceObject InterfaceType) PostID interface{}
[_] (FieldObject FieldType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicObject BasicType) ReqID string
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceObject InterfaceType) ReqID interface{}
[__] (BasicObject BasicType) ReqID string
[___] (Reference FieldType) ref <ReqID string> @ NotifyService
[____] (BasicObject BasicType) ReqID string
         --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}                 --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_____] (InterfaceObject InterfaceType) ReqID interface{}

[] (BasicObject BasicType) reqID int64
[_] (BasicObject BasicType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicObject BasicType) ReqID string
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceObject InterfaceType) ReqID interface{}

[] (InterfaceObject UserType) err .error
[_] (BasicObject BasicType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicObject BasicType) ReqID string
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceObject InterfaceType) ReqID interface{}

    --> r-tainted: read(posts_db.Post.PostID) {1}
[] (BasicObject BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID) {1}
[_] (BasicObject BasicType) PostID string
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicObject BasicType) PostID string
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (InterfaceObject InterfaceType) PostID interface{}

[] (InterfaceObject UserType) err .error
     --> r-tainted: read(posts_db.Post.PostID) {1}
[_] (BasicObject BasicType) PostID string
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicObject BasicType) PostID string
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (InterfaceObject InterfaceType) PostID interface{}

[] (StructObject UserType) _ postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}

[] (InterfaceObject UserType) err .error

