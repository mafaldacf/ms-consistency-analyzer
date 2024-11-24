[] (PointerObject PointerType) a (*postnotification.AnalyticsServiceImpl struct{analyticsQueue Queue, analyticsDb NoSQLDatabase, numWorkers int})
[_] (StructObject UserType) postnotification.AnalyticsServiceImpl struct{analyticsDb NoSQLDatabase, analyticsQueue Queue, numWorkers 4 int}
[__] (FieldObject FieldType) analyticsDb NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) analyticsDb NoSQLDatabase
[__] (FieldObject FieldType) analyticsQueue Queue
[___] (BlueprintBackendObject BlueprintBackendType) analyticsQueue Queue
[__] (FieldObject FieldType) numWorkers 4 int
[___] (BasicObject BasicType) 4 int

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ AnalyticsService

[] (StructObject UserType) message postnotification.TriggerAnalyticsMessage struct{PostID string}
     --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage) {1}
[_] (Reference UserType) ref <event postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService
      --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage) {1}           --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage) {1} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage) {1}
[__] (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService
       --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}             --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[___] (FieldObject FieldType) PostID string
        --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}               --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[____] (BasicObject BasicType) string
         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                 --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_____] (BasicObject BasicType) postID int64
          --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                   --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[______] (Reference FieldType) ref <PostID int64> @ UploadService
           --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                     --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[_______] (BasicObject BasicType) postID int64
            --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                       --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[________] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
     --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage) {1}         --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage) {1} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage) {1}
[_] (Reference UserType) ref <message postnotification.TriggerAnalyticsMessage struct{PostID string}> @ AnalyticsService
      --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}           --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[__] (FieldObject FieldType) PostID string
       --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}             --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[___] (BasicObject BasicType) string
        --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}               --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[____] (BasicObject BasicType) postID int64
         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                 --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_____] (Reference FieldType) ref <PostID int64> @ UploadService
          --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                   --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[______] (BasicObject BasicType) postID int64
           --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                     --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
[_] (FieldObject FieldType) PostID string
      --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}           --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ AnalyticsService
       --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}             --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[___] (BasicObject BasicType) string
        --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}               --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[____] (BasicObject BasicType) postID int64
         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                 --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_____] (Reference FieldType) ref <PostID int64> @ UploadService
          --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                   --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[______] (BasicObject BasicType) postID int64
           --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                     --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService
      --> w-tainted: write(analytics_db.Analytics.PostID) {1}
[__] (BasicObject BasicType) PostID string
       --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}             --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[___] (Reference FieldType) ref <PostID string> @ AnalyticsService
        --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}               --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[____] (BasicObject BasicType) string
         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                 --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_____] (BasicObject BasicType) postID int64
          --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                   --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[______] (Reference FieldType) ref <PostID int64> @ UploadService
           --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                     --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[_______] (BasicObject BasicType) postID int64
            --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                       --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[________] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

    --> w-tainted: write(analytics_db.Analytics.PostID) {1}
[] (BasicObject BasicType) postID int64
     --> w-tainted: write(analytics_db.Analytics.PostID) {1}
[_] (BasicObject BasicType) PostID string
      --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}           --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ AnalyticsService
       --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}             --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[___] (BasicObject BasicType) string
        --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}               --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[____] (BasicObject BasicType) postID int64
         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                 --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_____] (Reference FieldType) ref <PostID int64> @ UploadService
          --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                   --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[______] (BasicObject BasicType) postID int64
           --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                     --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

[] (InterfaceObject UserType) err .error
     --> w-tainted: write(analytics_db.Analytics.PostID) {1}
[_] (BasicObject BasicType) PostID string
      --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}           --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[__] (Reference FieldType) ref <PostID string> @ AnalyticsService
       --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}             --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[___] (BasicObject BasicType) string
        --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}               --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[____] (BasicObject BasicType) postID int64
         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                 --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_____] (Reference FieldType) ref <PostID int64> @ UploadService
          --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                   --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[______] (BasicObject BasicType) postID int64
           --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                     --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_______] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = analyticsDb, collection = analytics_collection}

[] (InterfaceObject UserType) err .error

    --> w-tainted: write(analytics_db.Analytics) {1}
[] (StructObject UserType) analytics postnotification.Analytics struct{PostID int64}
     --> w-tainted: write(analytics_db.Analytics.PostID) {1}
[_] (FieldObject FieldType) PostID int64
      --> w-tainted: write(analytics_db.Analytics.PostID) {1}
[__] (BasicObject BasicType) postID int64
       --> w-tainted: write(analytics_db.Analytics.PostID) {1}
[___] (BasicObject BasicType) PostID string
        --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}               --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[____] (Reference FieldType) ref <PostID string> @ AnalyticsService
         --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2}                 --> w-tainted: write(analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {2} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_____] (BasicObject BasicType) string
          --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                   --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[______] (BasicObject BasicType) postID int64
           --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3}                     --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID) {3} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID) {1}
[_______] (Reference FieldType) ref <PostID int64> @ UploadService
            --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                       --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID) {2}
[________] (BasicObject BasicType) postID int64
             --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6}                         --> w-tainted: write(posts_db.Post.PostID, analytics_queue.TriggerAnalyticsMessage.PostID, analytics_db.Analytics.PostID, notifications_queue.Message.PostID, timeline_cache.key, timeline_cache.value) {6} --> r-tainted: read(analytics_queue.TriggerAnalyticsMessage.PostID, notifications_queue.Message.PostID, posts_db.Post.PostID, analytics_db.Analytics.PostID) {4}
[_________] (Reference InterfaceType) ref <PostID interface{}> @ NotifyService

