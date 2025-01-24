[0] (PointerObject PointerType) p (*socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64})
[_1] (StructObject UserType) socialnetwork.PostStorageServiceImpl struct{postStorageCache Cache, postStorageDB NoSQLDatabase, CacheHits int64, NumReqs int64, CacheMiss int64}
[__2] (FieldObject FieldType) CacheMiss int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) NumReqs int64
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) postStorageCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageCache Cache
[__2] (FieldObject FieldType) postStorageDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) postStorageDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(post_db.Post) {1}
[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
     --> w-tainted: write(post_db.Post) {1}
[_1] (Reference UserType) ref <post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}> @ ComposePostService
      --> w-tainted: write(post_db.Post.Creator) {1}
[__2] (FieldObject FieldType) Creator socialnetwork.Creator struct{UserID int64, Username string}
       --> w-tainted: write(post_db.Post.Creator) {1}
[___3] (StructObject UserType) creator socialnetwork.Creator struct{UserID int64, Username string}
      --> w-tainted: write(post_db.Post.Medias) {1}
[__2] (FieldObject FieldType) Medias []socialnetwork.Media struct{MediaID int64, MediaType string}
       --> w-tainted: write(post_db.Post.Medias) {1}
[___3] (ArrayObject SliceType) medias []socialnetwork.Media struct{MediaID int64, MediaType string}
      --> w-tainted: write(post_db.Post.PostID) {1}
[__2] (FieldObject FieldType) PostID int64
       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}             --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[___3] (BasicObject BasicType) uniqueID int64
      --> w-tainted: write(post_db.Post.PostType) {1}
[__2] (FieldObject FieldType) PostType int64
       --> w-tainted: write(post_db.Post.PostType) {1}
[___3] (BasicObject BasicType) postType int64
        --> w-tainted: write(post_db.Post.PostType) {1}
[____4] (Reference BasicType) ref <post_type int64> @ Wrk2APIService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (FieldObject FieldType) ReqID int64
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (BasicObject BasicType) reqID int64
        --> w-tainted: write(post_db.Post.ReqID) {1}
[____4] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
      --> w-tainted: write(post_db.Post.Text) {1}
[__2] (FieldObject FieldType) Text string
       --> w-tainted: write(post_db.Post.Text) {1}
[___3] (BasicObject BasicType) up_text string
      --> w-tainted: write(post_db.Post.Urls) {1}
[__2] (FieldObject FieldType) Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
       --> w-tainted: write(post_db.Post.Urls) {1}
[___3] (ArrayObject SliceType) urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
      --> w-tainted: write(post_db.Post.UserMentions) {1}
[__2] (FieldObject FieldType) UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}
       --> w-tainted: write(post_db.Post.UserMentions) {1}
[___3] (ArrayObject SliceType) usermentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = post, collection = post}

[0] (InterfaceObject UserType) err .error

