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

    --> w-tainted: write(user_cache.key) {1}       --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[0] (BasicObject BasicType) username string

    --> w-tainted: write(user_cache.key) {1}       --> w-tainted: write(user_cache.key) {1} --> r-tainted: read(user_cache.string, user_db._.username) {2}
[0] (BasicObject BasicType) followeeName string

    --> r-tainted: read(social_cache.int64) {1}
[0] (BasicObject BasicType) userId int64

    --> r-tainted: read(social_cache.int64) {1}
[0] (BasicObject BasicType) followeeID int64

[0] (BasicObject BasicType) reqID int64

