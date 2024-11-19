[] (PointerVariable PointerType) n (*postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int})
[_] (StructVariable UserType) postnotification_simple.NotifyServiceImpl struct{storageService postnotification_simple.StorageService, notificationsQueue Queue, num_workers 4 int}
[__] (FieldVariable FieldType) notificationsQueue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) notificationsQueue Queue
[__] (FieldVariable FieldType) num_workers 4 int
[___] (BasicVariable BasicType) 4 int
[__] (FieldVariable FieldType) storageService postnotification_simple.StorageService
[___] (ServiceVariable ServiceType) storageService postnotification_simple.StorageService

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ NotifyService

[] (StructVariable UserType) message postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}
[_] (Reference UserType) ref <workerMessage postnotification_simple.Message struct{ReqID string, PostID string, Timestamp string}> @ NotifyService
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (FieldVariable FieldType) PostID string
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicVariable BasicType) PostID string
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (InterfaceVariable InterfaceType) PostID interface{}
[__] (FieldVariable FieldType) ReqID string
[___] (BasicVariable BasicType) ReqID string
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceVariable InterfaceType) ReqID interface{}
[__] (FieldVariable FieldType) Timestamp string
[___] (BasicVariable BasicType) Timestamp string
        --> r-tainted: read(notifications_queue.message) {1}
[____] (InterfaceVariable InterfaceType) Timestamp interface{}
[_] (FieldVariable FieldType) PostID string
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicVariable BasicType) PostID string
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (InterfaceVariable InterfaceType) PostID interface{}
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (BasicVariable BasicType) PostID string
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (Reference FieldType) ref <PostID string> @ NotifyService
        --> r-tainted: read(posts_db.Post.PostID) {1}
[____] (BasicVariable BasicType) PostID string
         --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}                 --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[_____] (InterfaceVariable InterfaceType) PostID interface{}
[_] (FieldVariable FieldType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicVariable BasicType) ReqID string
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceVariable InterfaceType) ReqID interface{}
[__] (BasicVariable BasicType) ReqID string
[___] (Reference FieldType) ref <ReqID string> @ NotifyService
[____] (BasicVariable BasicType) ReqID string
         --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}                 --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[_____] (InterfaceVariable InterfaceType) ReqID interface{}

[] (BasicVariable BasicType) reqID int64
[_] (BasicVariable BasicType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicVariable BasicType) ReqID string
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceVariable InterfaceType) ReqID interface{}

[] (InterfaceVariable UserType) err .error
[_] (BasicVariable BasicType) ReqID string
[__] (Reference FieldType) ref <ReqID string> @ NotifyService
[___] (BasicVariable BasicType) ReqID string
        --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2}               --> w-tainted: write(posts_db.Post.ReqID, notifications_queue.Message.ReqID) {2} --> r-tainted: read(notifications_queue.Message.ReqID) {1}
[____] (InterfaceVariable InterfaceType) ReqID interface{}

    --> r-tainted: read(posts_db.Post.PostID) {1}
[] (BasicVariable BasicType) postID int64
     --> r-tainted: read(posts_db.Post.PostID) {1}
[_] (BasicVariable BasicType) PostID string
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicVariable BasicType) PostID string
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (InterfaceVariable InterfaceType) PostID interface{}

[] (InterfaceVariable UserType) err .error
     --> r-tainted: read(posts_db.Post.PostID) {1}
[_] (BasicVariable BasicType) PostID string
      --> r-tainted: read(posts_db.Post.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ NotifyService
       --> r-tainted: read(posts_db.Post.PostID) {1}
[___] (BasicVariable BasicType) PostID string
        --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2}               --> w-tainted: write(posts_db.Post.PostID, notifications_queue.Message.PostID) {2} --> r-tainted: read(notifications_queue.Message.PostID, posts_db.Post.PostID) {2}
[____] (InterfaceVariable InterfaceType) PostID interface{}

[] (StructVariable UserType) _ postnotification_simple.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification_simple.Creator struct{Username "some username" string}, Creator postnotification_simple.Creator struct{Username "some username" string}}

[] (InterfaceVariable UserType) err .error

