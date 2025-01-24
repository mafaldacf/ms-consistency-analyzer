[0] (BasicObject BasicType) query string
[_1] (Reference BasicType) ref <query string> @ UserMentionService
[_1] (Reference BasicType) ref <update string> @ UserTimelineService
[__2] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[__2] (BasicObject BasicType) postIDstr string
       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}             --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) postID int64
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[___3] (BasicObject BasicType) 10 int
       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}             --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) postID int64
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[___3] (BasicObject BasicType) 10 int
[__2] (BasicObject BasicType) timestampstr string
       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}             --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) timestamp int64
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[___3] (BasicObject BasicType) 10 int
       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}             --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) timestamp int64
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[___3] (BasicObject BasicType) 10 int
[__2] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[__2] (BasicObject BasicType) postIDstr string
       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}             --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) postID int64
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[___3] (BasicObject BasicType) 10 int
       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}             --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) postID int64
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[___3] (BasicObject BasicType) 10 int
[__2] (BasicObject BasicType) timestampstr string
       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}             --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) timestamp int64
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[___3] (BasicObject BasicType) 10 int
       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}             --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) timestamp int64
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[___3] (BasicObject BasicType) 10 int
[_1] (Reference BasicType) ref <query string> @ SocialGraphService
[_1] (Reference BasicType) ref <query string> @ PostStorageService
[_1] (Reference BasicType) ref <query string> @ UserTimelineService
[__2] (BasicObject BasicType) `{"UserID": %[1]d}` string
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (BasicObject BasicType) userID int64
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[__2] (BasicObject BasicType) `{"UserID": %[1]d}` string
      --> w-tainted: write(usertimeline_cache.key) {1}           --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[__2] (BasicObject BasicType) userID int64
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <projection string> @ UserTimelineService
[__2] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[__2] (BasicObject BasicType) stop int64
[___3] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[__2] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[__2] (BasicObject BasicType) stop int64
[___3] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_1] (Reference BasicType) ref <query string> @ PostStorageService

