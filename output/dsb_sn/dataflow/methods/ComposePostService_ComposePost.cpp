[0] (PointerObject PointerType) c (*socialnetwork.ComposePostServiceImpl struct{postStorageService socialnetwork.PostStorageService, userTimelineService socialnetwork.UserTimelineService, userService socialnetwork.UserService, uniqueIDService socialnetwork.UniqueIdService, mediaService socialnetwork.MediaService, textService socialnetwork.TextService, homeTimelineService socialnetwork.HomeTimelineService})
[_1] (StructObject UserType) socialnetwork.ComposePostServiceImpl struct{postStorageService socialnetwork.PostStorageService, userTimelineService socialnetwork.UserTimelineService, userService socialnetwork.UserService, uniqueIDService socialnetwork.UniqueIdService, mediaService socialnetwork.MediaService, textService socialnetwork.TextService, homeTimelineService socialnetwork.HomeTimelineService}
[__2] (FieldObject FieldType) homeTimelineService socialnetwork.HomeTimelineService
[___3] (ServiceObject ServiceType) homeTimelineService socialnetwork.HomeTimelineService
[__2] (FieldObject FieldType) mediaService socialnetwork.MediaService
[___3] (ServiceObject ServiceType) mediaService socialnetwork.MediaService
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) textService socialnetwork.TextService
[___3] (ServiceObject ServiceType) textService socialnetwork.TextService
[__2] (FieldObject FieldType) uniqueIDService socialnetwork.UniqueIdService
[___3] (ServiceObject ServiceType) uniqueIDService socialnetwork.UniqueIdService
[__2] (FieldObject FieldType) userService socialnetwork.UserService
[___3] (ServiceObject ServiceType) userService socialnetwork.UserService
[__2] (FieldObject FieldType) userTimelineService socialnetwork.UserTimelineService
[___3] (ServiceObject ServiceType) userTimelineService socialnetwork.UserTimelineService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (BasicObject BasicType) username string
[_1] (Reference BasicType) ref <username string> @ Wrk2APIService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) text string
[_1] (Reference BasicType) ref <text string> @ Wrk2APIService

[0] (ArrayObject ArrayType) mediaIDs []int64
[_1] (Reference ArrayType) ref <media_ids []int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) mediaTypes []string
[_1] (Reference ArrayType) ref <media_types []string> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.PostType) {1}
[0] (BasicObject BasicType) postType int64
     --> w-tainted: write(post_db.Post.PostType) {1}
[_1] (Reference BasicType) ref <post_type int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[0] (BasicObject BasicType) timestamp int64

[0] (BasicObject BasicType) err1 error

[0] (BasicObject BasicType) err2 error

[0] (BasicObject BasicType) err3 error

[0] (BasicObject BasicType) err4 error

    --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[0] (BasicObject BasicType) uniqueID int64

    --> w-tainted: write(post_db.Post.Creator) {1}
[0] (StructObject UserType) creator socialnetwork.Creator struct{UserID int64, Username string}

    --> w-tainted: write(post_db.Post.Text) {1}
[0] (BasicObject BasicType) up_text string

    --> w-tainted: write(post_db.Post.Medias) {1}
[0] (ArrayObject SliceType) medias []socialnetwork.Media struct{MediaID int64, MediaType string}

    --> w-tainted: write(post_db.Post.Urls) {1}
[0] (ArrayObject SliceType) urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}

    --> w-tainted: write(post_db.Post.UserMentions) {1}
[0] (ArrayObject SliceType) usermentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (StructObject UserType) wg sync.WaitGroup

    --> w-tainted: write(post_db.Post) {1}
[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
     --> w-tainted: write(post_db.Post.Creator) {1}
[_1] (FieldObject FieldType) Creator socialnetwork.Creator struct{UserID int64, Username string}
      --> w-tainted: write(post_db.Post.Creator) {1}
[__2] (StructObject UserType) creator socialnetwork.Creator struct{UserID int64, Username string}
     --> w-tainted: write(post_db.Post.Medias) {1}
[_1] (FieldObject FieldType) Medias []socialnetwork.Media struct{MediaID int64, MediaType string}
      --> w-tainted: write(post_db.Post.Medias) {1}
[__2] (ArrayObject SliceType) medias []socialnetwork.Media struct{MediaID int64, MediaType string}
     --> w-tainted: write(post_db.Post.PostID) {1}
[_1] (FieldObject FieldType) PostID int64
      --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[__2] (BasicObject BasicType) uniqueID int64
     --> w-tainted: write(post_db.Post.PostType) {1}
[_1] (FieldObject FieldType) PostType int64
      --> w-tainted: write(post_db.Post.PostType) {1}
[__2] (BasicObject BasicType) postType int64
       --> w-tainted: write(post_db.Post.PostType) {1}
[___3] (Reference BasicType) ref <post_type int64> @ Wrk2APIService
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (FieldObject FieldType) ReqID int64
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (BasicObject BasicType) reqID int64
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
     --> w-tainted: write(post_db.Post.Text) {1}
[_1] (FieldObject FieldType) Text string
      --> w-tainted: write(post_db.Post.Text) {1}
[__2] (BasicObject BasicType) up_text string
     --> w-tainted: write(post_db.Post.Urls) {1}
[_1] (FieldObject FieldType) Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
      --> w-tainted: write(post_db.Post.Urls) {1}
[__2] (ArrayObject SliceType) urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
     --> w-tainted: write(post_db.Post.UserMentions) {1}
[_1] (FieldObject FieldType) UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}
      --> w-tainted: write(post_db.Post.UserMentions) {1}
[__2] (ArrayObject SliceType) usermentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (ArrayObject ArrayType) usermentionIds []int64
[_1] (BasicObject BasicType) UserID int64

[0] (StructObject UserType) um socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (FieldObject FieldType) UserID int64
[__2] (BasicObject BasicType) UserID int64

[0] (ArrayObject ArrayType) usermentionIds []int64
[_1] (BasicObject BasicType) UserID int64

[0] (PointerObject PointerType) c (*socialnetwork.ComposePostServiceImpl struct{postStorageService socialnetwork.PostStorageService, userTimelineService socialnetwork.UserTimelineService, userService socialnetwork.UserService, uniqueIDService socialnetwork.UniqueIdService, mediaService socialnetwork.MediaService, textService socialnetwork.TextService, homeTimelineService socialnetwork.HomeTimelineService})
[_1] (StructObject UserType) socialnetwork.ComposePostServiceImpl struct{postStorageService socialnetwork.PostStorageService, userTimelineService socialnetwork.UserTimelineService, userService socialnetwork.UserService, uniqueIDService socialnetwork.UniqueIdService, mediaService socialnetwork.MediaService, textService socialnetwork.TextService, homeTimelineService socialnetwork.HomeTimelineService}
[__2] (FieldObject FieldType) homeTimelineService socialnetwork.HomeTimelineService
[___3] (ServiceObject ServiceType) homeTimelineService socialnetwork.HomeTimelineService
[__2] (FieldObject FieldType) mediaService socialnetwork.MediaService
[___3] (ServiceObject ServiceType) mediaService socialnetwork.MediaService
[__2] (FieldObject FieldType) postStorageService socialnetwork.PostStorageService
[___3] (ServiceObject ServiceType) postStorageService socialnetwork.PostStorageService
[__2] (FieldObject FieldType) textService socialnetwork.TextService
[___3] (ServiceObject ServiceType) textService socialnetwork.TextService
[__2] (FieldObject FieldType) uniqueIDService socialnetwork.UniqueIdService
[___3] (ServiceObject ServiceType) uniqueIDService socialnetwork.UniqueIdService
[__2] (FieldObject FieldType) userService socialnetwork.UserService
[___3] (ServiceObject ServiceType) userService socialnetwork.UserService
[__2] (FieldObject FieldType) userTimelineService socialnetwork.UserTimelineService
[___3] (ServiceObject ServiceType) userTimelineService socialnetwork.UserTimelineService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (BasicObject BasicType) username string
[_1] (Reference BasicType) ref <username string> @ Wrk2APIService

    --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}       --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3}         --> w-tainted: write(usertimeline_db.UserPosts.UserID, usertimeline_cache.key, social_cache.key) {3} --> r-tainted: read(usertimeline_db._.userid, usertimeline_cache.int64, social_cache.int64) {3}
[_1] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BasicObject BasicType) text string
[_1] (Reference BasicType) ref <text string> @ Wrk2APIService

[0] (ArrayObject ArrayType) mediaIDs []int64
[_1] (Reference ArrayType) ref <media_ids []int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) mediaTypes []string
[_1] (Reference ArrayType) ref <media_types []string> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.PostType) {1}
[0] (BasicObject BasicType) postType int64
     --> w-tainted: write(post_db.Post.PostType) {1}
[_1] (Reference BasicType) ref <post_type int64> @ Wrk2APIService

    --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1}       --> w-tainted: write(usertimeline_db.UserPosts.Posts) {1} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[0] (BasicObject BasicType) timestamp int64

[0] (BasicObject BasicType) err1 error

[0] (BasicObject BasicType) err2 error

[0] (BasicObject BasicType) err3 error

[0] (BasicObject BasicType) err4 error

    --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}       --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[0] (BasicObject BasicType) uniqueID int64

    --> w-tainted: write(post_db.Post.Creator) {1}
[0] (StructObject UserType) creator socialnetwork.Creator struct{UserID int64, Username string}

    --> w-tainted: write(post_db.Post.Text) {1}
[0] (BasicObject BasicType) up_text string

    --> w-tainted: write(post_db.Post.Medias) {1}
[0] (ArrayObject SliceType) medias []socialnetwork.Media struct{MediaID int64, MediaType string}

    --> w-tainted: write(post_db.Post.Urls) {1}
[0] (ArrayObject SliceType) urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}

    --> w-tainted: write(post_db.Post.UserMentions) {1}
[0] (ArrayObject SliceType) usermentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (StructObject UserType) wg sync.WaitGroup

    --> w-tainted: write(post_db.Post) {1}
[0] (StructObject UserType) post socialnetwork.Post struct{PostID int64, Creator socialnetwork.Creator struct{UserID int64, Username string}, ReqID int64, Text string, UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}, Medias []socialnetwork.Media struct{MediaID int64, MediaType string}, Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}, Timestamp int64, PostType int64}
     --> w-tainted: write(post_db.Post.Creator) {1}
[_1] (FieldObject FieldType) Creator socialnetwork.Creator struct{UserID int64, Username string}
      --> w-tainted: write(post_db.Post.Creator) {1}
[__2] (StructObject UserType) creator socialnetwork.Creator struct{UserID int64, Username string}
     --> w-tainted: write(post_db.Post.Medias) {1}
[_1] (FieldObject FieldType) Medias []socialnetwork.Media struct{MediaID int64, MediaType string}
      --> w-tainted: write(post_db.Post.Medias) {1}
[__2] (ArrayObject SliceType) medias []socialnetwork.Media struct{MediaID int64, MediaType string}
     --> w-tainted: write(post_db.Post.PostID) {1}
[_1] (FieldObject FieldType) PostID int64
      --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2}           --> w-tainted: write(post_db.Post.PostID, usertimeline_db.UserPosts.Posts) {2} --> r-tainted: read(usertimeline_cache.int64, hometimeline_cache.int64) {2}
[__2] (BasicObject BasicType) uniqueID int64
     --> w-tainted: write(post_db.Post.PostType) {1}
[_1] (FieldObject FieldType) PostType int64
      --> w-tainted: write(post_db.Post.PostType) {1}
[__2] (BasicObject BasicType) postType int64
       --> w-tainted: write(post_db.Post.PostType) {1}
[___3] (Reference BasicType) ref <post_type int64> @ Wrk2APIService
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (FieldObject FieldType) ReqID int64
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (BasicObject BasicType) reqID int64
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService
     --> w-tainted: write(post_db.Post.Text) {1}
[_1] (FieldObject FieldType) Text string
      --> w-tainted: write(post_db.Post.Text) {1}
[__2] (BasicObject BasicType) up_text string
     --> w-tainted: write(post_db.Post.Urls) {1}
[_1] (FieldObject FieldType) Urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
      --> w-tainted: write(post_db.Post.Urls) {1}
[__2] (ArrayObject SliceType) urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
     --> w-tainted: write(post_db.Post.UserMentions) {1}
[_1] (FieldObject FieldType) UserMentions []socialnetwork.UserMention struct{UserID int64, Username string}
      --> w-tainted: write(post_db.Post.UserMentions) {1}
[__2] (ArrayObject SliceType) usermentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (ArrayObject ArrayType) usermentionIds []int64
[_1] (BasicObject BasicType) UserID int64

[0] (StructObject UserType) um socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (FieldObject FieldType) UserID int64
[__2] (BasicObject BasicType) UserID int64

[0] (StructObject UserType) wg2 sync.WaitGroup

