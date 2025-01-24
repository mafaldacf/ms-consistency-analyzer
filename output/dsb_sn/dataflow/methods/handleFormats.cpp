[0] (BasicObject BasicType) jsonQuery string
[_1] (Reference BasicType) ref <query string> @ MediaService
[__2] (Reference BasicType) ref <query string> @ UserMentionService
[__2] (Reference BasicType) ref <update string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[__2] (Reference BasicType) ref <query string> @ SocialGraphService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[__2] (Reference BasicType) ref <query string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <projection string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[_1] (Reference BasicType) ref <query string> @ MediaService
[__2] (Reference BasicType) ref <query string> @ UserMentionService
[__2] (Reference BasicType) ref <update string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[__2] (Reference BasicType) ref <query string> @ SocialGraphService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[__2] (Reference BasicType) ref <query string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <projection string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[_1] (Reference BasicType) ref <query string> @ MediaService
[__2] (Reference BasicType) ref <query string> @ UserMentionService
[__2] (Reference BasicType) ref <update string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[__2] (Reference BasicType) ref <query string> @ SocialGraphService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[__2] (Reference BasicType) ref <query string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <projection string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[_1] (Reference BasicType) ref <query string> @ MediaService
[__2] (Reference BasicType) ref <query string> @ UserMentionService
[__2] (Reference BasicType) ref <update string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[__2] (Reference BasicType) ref <query string> @ SocialGraphService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[__2] (Reference BasicType) ref <query string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <projection string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[_1] (Reference BasicType) ref <query string> @ MediaService
[__2] (Reference BasicType) ref <query string> @ UserMentionService
[__2] (Reference BasicType) ref <update string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[__2] (Reference BasicType) ref <query string> @ SocialGraphService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[__2] (Reference BasicType) ref <query string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <projection string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[_1] (Reference BasicType) ref <query string> @ MediaService
[__2] (Reference BasicType) ref <query string> @ UserMentionService
[__2] (Reference BasicType) ref <update string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[__2] (Reference BasicType) ref <query string> @ SocialGraphService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[__2] (Reference BasicType) ref <query string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <projection string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[_1] (Reference BasicType) ref <query string> @ MediaService
[__2] (Reference BasicType) ref <query string> @ UserMentionService
[__2] (Reference BasicType) ref <update string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[___3] (BasicObject BasicType) postIDstr string
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) postID int64
         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                 --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[___3] (BasicObject BasicType) timestampstr string
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (BasicObject BasicType) timestamp int64
         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                 --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_____5] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[____4] (BasicObject BasicType) 10 int
[__2] (Reference BasicType) ref <query string> @ SocialGraphService
[__2] (Reference BasicType) ref <query string> @ PostStorageService
[__2] (Reference BasicType) ref <query string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"UserID": %[1]d}` string
       --> w-tainted: write(usertimeline_cache.key) {1}             --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[___3] (BasicObject BasicType) userID int64
        --> w-tainted: write(usertimeline_cache.key) {1}               --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <projection string> @ UserTimelineService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[___3] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[___3] (BasicObject BasicType) stop int64
[____4] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[__2] (Reference BasicType) ref <query string> @ PostStorageService

[0] (SliceObject UserType) bdoc primitive.D

[0] (BasicObject BasicType) err error

[0] (InterfaceObject InterfaceType) f interface{}

[0] (InterfaceObject UserType) err .error
[_1] (BasicObject BasicType) byte
[__2] (BasicObject BasicType) jsonQuery string
[___3] (Reference BasicType) ref <query string> @ MediaService
[____4] (Reference BasicType) ref <query string> @ UserMentionService
[____4] (Reference BasicType) ref <update string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[____4] (Reference BasicType) ref <query string> @ SocialGraphService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[____4] (Reference BasicType) ref <query string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <projection string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[___3] (Reference BasicType) ref <query string> @ MediaService
[____4] (Reference BasicType) ref <query string> @ UserMentionService
[____4] (Reference BasicType) ref <update string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[____4] (Reference BasicType) ref <query string> @ SocialGraphService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[____4] (Reference BasicType) ref <query string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <projection string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[___3] (Reference BasicType) ref <query string> @ MediaService
[____4] (Reference BasicType) ref <query string> @ UserMentionService
[____4] (Reference BasicType) ref <update string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[____4] (Reference BasicType) ref <query string> @ SocialGraphService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[____4] (Reference BasicType) ref <query string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <projection string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[___3] (Reference BasicType) ref <query string> @ MediaService
[____4] (Reference BasicType) ref <query string> @ UserMentionService
[____4] (Reference BasicType) ref <update string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[____4] (Reference BasicType) ref <query string> @ SocialGraphService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[____4] (Reference BasicType) ref <query string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <projection string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[___3] (Reference BasicType) ref <query string> @ MediaService
[____4] (Reference BasicType) ref <query string> @ UserMentionService
[____4] (Reference BasicType) ref <update string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[____4] (Reference BasicType) ref <query string> @ SocialGraphService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[____4] (Reference BasicType) ref <query string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <projection string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[___3] (Reference BasicType) ref <query string> @ MediaService
[____4] (Reference BasicType) ref <query string> @ UserMentionService
[____4] (Reference BasicType) ref <update string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[____4] (Reference BasicType) ref <query string> @ SocialGraphService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[____4] (Reference BasicType) ref <query string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <projection string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[___3] (Reference BasicType) ref <query string> @ MediaService
[____4] (Reference BasicType) ref <query string> @ UserMentionService
[____4] (Reference BasicType) ref <update string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) `{"$push": {"Posts": {"$each": [{"PostID": %s, "Timestamp": %s}], "$position": 0}}}` string
[_____5] (BasicObject BasicType) postIDstr string
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                   --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) postID int64
           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}                     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[_____5] (BasicObject BasicType) timestampstr string
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
          --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                   --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (BasicObject BasicType) timestamp int64
           --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}                     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_______7] (Reference BasicType) ref <timestamp int64> @ ComposePostService
[______6] (BasicObject BasicType) 10 int
[____4] (Reference BasicType) ref <query string> @ SocialGraphService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[____4] (Reference BasicType) ref <query string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"UserID": %[1]d}` string
         --> w-tainted: write(usertimeline_cache.key) {1}                 --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[_____5] (BasicObject BasicType) userID int64
          --> w-tainted: write(usertimeline_cache.key) {1}                   --> w-tainted: write(usertimeline_cache.key) {1} --> r-tainted: read(usertimeline_cache.int64) {1}
[______6] (Reference BasicType) ref <userId int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <projection string> @ UserTimelineService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[_____5] (BasicObject BasicType) `{"posts": {"$slice": [0, %[1]d]}}` string
[_____5] (BasicObject BasicType) stop int64
[______6] (Reference BasicType) ref <stop int64> @ Wrk2APIService
[____4] (Reference BasicType) ref <query string> @ PostStorageService
[_1] (PointerObject PointerType) f (*interface{})
[__2] (InterfaceObject InterfaceType) f interface{}

[0] (SliceObject SliceType) lowerQuery []byte
[_1] (InterfaceObject InterfaceType) f interface{}
[_1] (InterfaceObject InterfaceType) f interface{}

[0] (InterfaceObject UserType) err .error
[_1] (InterfaceObject InterfaceType) f interface{}

[0] (InterfaceObject UserType) err .error
[_1] (SliceObject SliceType) lowerQuery []byte
[__2] (InterfaceObject InterfaceType) f interface{}
[__2] (InterfaceObject InterfaceType) f interface{}
[_1] (BasicObject BasicType) true bool
[_1] (PointerObject PointerType) bdoc (*primitive.D)
[__2] (SliceObject UserType) bdoc primitive.D

