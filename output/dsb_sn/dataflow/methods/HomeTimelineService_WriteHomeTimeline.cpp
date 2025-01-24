[0] (PointerObject PointerType) h (*socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) homeTimelineCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) homeTimelineCache Cache
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.PostID) {1}       --> w-tainted: write(post_db.Post.PostID) {1} --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) postID int64
     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <uniqueID int64> @ ComposePostService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userID int64> @ ComposePostService
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

    --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) timestamp int64
     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <timestamp int64> @ ComposePostService

[0] (ArrayObject ArrayType) userMentionIDs []int64
[_1] (Reference ArrayType) ref <usermentionIds []int64> @ ComposePostService
[__2] (BasicObject BasicType) UserID int64

[0] (SliceObject SliceType) followers []int64

[0] (InterfaceObject UserType) err .error

[0] (MapObject MapType) followers_set map[int64]bool
[_1] (BasicObject BasicType) true bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) follower int64

[0] (PointerObject PointerType) h (*socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) homeTimelineCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) homeTimelineCache Cache
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.PostID) {1}       --> w-tainted: write(post_db.Post.PostID) {1} --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) postID int64
     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <uniqueID int64> @ ComposePostService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userID int64> @ ComposePostService
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

    --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) timestamp int64
     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <timestamp int64> @ ComposePostService

[0] (ArrayObject ArrayType) userMentionIDs []int64
[_1] (Reference ArrayType) ref <usermentionIds []int64> @ ComposePostService
[__2] (BasicObject BasicType) UserID int64

[0] (SliceObject SliceType) followers []int64

[0] (InterfaceObject UserType) err .error

[0] (MapObject MapType) followers_set map[int64]bool
[_1] (BasicObject BasicType) true bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) follower int64

[0] (BasicObject BasicType) um int64

[0] (PointerObject PointerType) h (*socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) homeTimelineCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) homeTimelineCache Cache
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.PostID) {1}       --> w-tainted: write(post_db.Post.PostID) {1} --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) postID int64
     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <uniqueID int64> @ ComposePostService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userID int64> @ ComposePostService
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

    --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) timestamp int64
     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <timestamp int64> @ ComposePostService

[0] (ArrayObject ArrayType) userMentionIDs []int64
[_1] (Reference ArrayType) ref <usermentionIds []int64> @ ComposePostService
[__2] (BasicObject BasicType) UserID int64

[0] (SliceObject SliceType) followers []int64

[0] (InterfaceObject UserType) err .error

[0] (MapObject MapType) followers_set map[int64]bool
[_1] (BasicObject BasicType) true bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) follower int64

[0] (PointerObject PointerType) h (*socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) homeTimelineCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) homeTimelineCache Cache
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.PostID) {1}       --> w-tainted: write(post_db.Post.PostID) {1} --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) postID int64
     --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}         --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <uniqueID int64> @ ComposePostService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userID int64> @ ComposePostService
      --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}           --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

    --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) timestamp int64
     --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}         --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[_1] (Reference BasicType) ref <timestamp int64> @ ComposePostService

[0] (ArrayObject ArrayType) userMentionIDs []int64
[_1] (Reference ArrayType) ref <usermentionIds []int64> @ ComposePostService
[__2] (BasicObject BasicType) UserID int64

[0] (SliceObject SliceType) followers []int64

[0] (InterfaceObject UserType) err .error

[0] (MapObject MapType) followers_set map[int64]bool
[_1] (BasicObject BasicType) true bool
[_1] (BasicObject BasicType) true bool

[0] (BasicObject BasicType) follower int64

[0] (BasicObject BasicType) um int64

    --> w-tainted: write(hometimeline_cache.key) {1}       --> w-tainted: write(hometimeline_cache.key) {1} --> r-tainted: read(hometimeline_cache.bool) {1}
[0] (BasicObject BasicType) id bool

    --> w-tainted: write(hometimeline_cache.key) {1}       --> w-tainted: write(hometimeline_cache.key) {1} --> r-tainted: read(hometimeline_cache.key, hometimeline_cache.string, hometimeline_cache.bool, hometimeline_cache.int) {4}
[0] (BasicObject BasicType) id_str string
     --> w-tainted: write(hometimeline_cache.key) {1}         --> w-tainted: write(hometimeline_cache.key) {1} --> r-tainted: read(hometimeline_cache.bool) {1}
[_1] (BasicObject BasicType) id bool
     --> w-tainted: write(hometimeline_cache.key) {1}         --> w-tainted: write(hometimeline_cache.key) {1} --> r-tainted: read(hometimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> w-tainted: write(hometimeline_cache.key) {1}         --> w-tainted: write(hometimeline_cache.key) {1} --> r-tainted: read(hometimeline_cache.bool) {1}
[_1] (BasicObject BasicType) id bool
     --> w-tainted: write(hometimeline_cache.key) {1}         --> w-tainted: write(hometimeline_cache.key) {1} --> r-tainted: read(hometimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

    --> r-tainted: read(hometimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
     --> r-tainted: read(hometimeline_cache.PostInfo) {1}
[_1] (StructObject UserType) socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
      --> r-tainted: read(hometimeline_cache.PostID) {1}
[__2] (FieldObject FieldType) PostID int64
       --> w-tainted: write(post_db.Post.PostID) {1}             --> w-tainted: write(post_db.Post.PostID) {1} --> r-tainted: read(hometimeline_cache.int64) {1}
[___3] (BasicObject BasicType) postID int64
        --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}               --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <uniqueID int64> @ ComposePostService
      --> r-tainted: read(hometimeline_cache.Timestamp) {1}
[__2] (FieldObject FieldType) Timestamp int64
       --> r-tainted: read(hometimeline_cache.int64) {1}
[___3] (BasicObject BasicType) timestamp int64
        --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}               --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[____4] (Reference BasicType) ref <timestamp int64> @ ComposePostService

[0] (BasicObject BasicType) _ bool

[0] (InterfaceObject UserType) err .error

    --> w-tainted: write(hometimeline_cache.value) {1}
[0] (ArrayObject ArrayType) posts []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
     --> w-tainted: write(hometimeline_cache.value) {1}
[_1] (StructObject UserType) socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
      --> w-tainted: write(hometimeline_cache.value) {1}
[__2] (FieldObject FieldType) PostID int64
       --> w-tainted: write(hometimeline_cache.value) {1}
[___3] (BasicObject BasicType) postID int64
      --> w-tainted: write(hometimeline_cache.value) {1}
[__2] (FieldObject FieldType) Timestamp int64
       --> w-tainted: write(hometimeline_cache.value) {1}
[___3] (BasicObject BasicType) timestamp int64

[0] (InterfaceObject UserType) err .error

