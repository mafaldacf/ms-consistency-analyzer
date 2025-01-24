[0] (PointerObject PointerType) h (*socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) homeTimelineCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) homeTimelineCache Cache
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> r-tainted: read(hometimeline_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) start int64
[_1] (Reference BasicType) ref <start int64> @ Wrk2APIService

[0] (BasicObject BasicType) stop int64
[_1] (Reference BasicType) ref <stop int64> @ Wrk2APIService

    --> r-tainted: read(hometimeline_cache.key, hometimeline_cache.string, hometimeline_cache.int64, hometimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> r-tainted: read(hometimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> r-tainted: read(hometimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> r-tainted: read(hometimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> r-tainted: read(hometimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> r-tainted: read(hometimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> r-tainted: read(hometimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

[0] (ArrayObject ArrayType) postIDs []int64
[_1] (BasicObject BasicType) PostID int64

    --> r-tainted: read(hometimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) postInfos []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) _ bool

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) pinfo socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (ArrayObject ArrayType) postIDs []int64
[_1] (BasicObject BasicType) PostID int64

[0] (PointerObject PointerType) h (*socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.HomeTimelineServiceImpl struct{homeTimelineCache Cache, postStorageService socialnetwork.PostStorageService, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) homeTimelineCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) homeTimelineCache Cache
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> r-tainted: read(hometimeline_cache.int64) {1}
[0] (BasicObject BasicType) userID int64
     --> r-tainted: read(hometimeline_cache.int64) {1}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) start int64
[_1] (Reference BasicType) ref <start int64> @ Wrk2APIService

[0] (BasicObject BasicType) stop int64
[_1] (Reference BasicType) ref <stop int64> @ Wrk2APIService

    --> r-tainted: read(hometimeline_cache.key, hometimeline_cache.string, hometimeline_cache.int64, hometimeline_cache.int) {4}
[0] (BasicObject BasicType) userIDStr string
     --> r-tainted: read(hometimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> r-tainted: read(hometimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> r-tainted: read(hometimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int
     --> r-tainted: read(hometimeline_cache.int64) {1}
[_1] (BasicObject BasicType) userID int64
      --> r-tainted: read(hometimeline_cache.int64) {1}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService
     --> r-tainted: read(hometimeline_cache.int) {1}
[_1] (BasicObject BasicType) 10 int

[0] (ArrayObject ArrayType) postIDs []int64
[_1] (BasicObject BasicType) PostID int64

    --> r-tainted: read(hometimeline_cache.[]socialnetwork.PostInfo struct{PostID int64, Timestamp int64}) {1}
[0] (ArrayObject ArrayType) postInfos []socialnetwork.PostInfo struct{PostID int64, Timestamp int64}

[0] (BasicObject BasicType) _ bool

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) pinfo socialnetwork.PostInfo struct{PostID int64, Timestamp int64}
[_1] (FieldObject FieldType) PostID int64
[__2] (BasicObject BasicType) PostID int64

[0] (BasicObject BasicType) minstop int64

[0] (BasicObject BasicType) minstop len(postIDs []int64) int64

[0] (ArrayObject ArrayType) postIDs []int64
[_1] (BasicObject BasicType) PostID int64

[0] (SliceObject SliceType) _ []socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}

[0] (InterfaceObject UserType) err .error

