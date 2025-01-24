[0] (PointerObject PointerType) w (*socialnetwork.Wrk2APIServiceImpl struct{userService socialnetwork.UserService, composePostService socialnetwork.ComposePostService, userTimelineService socialnetwork.UserTimelineService, homeTimelineService socialnetwork.HomeTimelineService, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.Wrk2APIServiceImpl struct{userService socialnetwork.UserService, composePostService socialnetwork.ComposePostService, userTimelineService socialnetwork.UserTimelineService, homeTimelineService socialnetwork.HomeTimelineService, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) composePostService socialnetwork.ComposePostService
[___3] (ServiceObject ServiceType) composePostService socialnetwork.ComposePostService
[__2] (FieldObject FieldType) homeTimelineService socialnetwork.HomeTimelineService
[___3] (ServiceObject ServiceType) homeTimelineService socialnetwork.HomeTimelineService
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService
[__2] (FieldObject FieldType) userService socialnetwork.UserService
[___3] (ServiceObject ServiceType) userService socialnetwork.UserService
[__2] (FieldObject FieldType) userTimelineService socialnetwork.UserTimelineService
[___3] (ServiceObject ServiceType) userTimelineService socialnetwork.UserTimelineService

[0] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userId int64

[0] (BasicObject BasicType) username string

    --> w-tainted: write(post_db.Post.PostType) {1}
[0] (BasicObject BasicType) post_type int64

[0] (BasicObject BasicType) text string

[0] (ArrayObject ArrayType) media_types []string

[0] (ArrayObject ArrayType) media_ids []int64

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64

