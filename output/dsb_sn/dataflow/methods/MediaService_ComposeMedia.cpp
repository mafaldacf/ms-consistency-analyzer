[0] (PointerObject PointerType) m (*socialnetwork.MediaServiceImpl struct{})
[_1] (StructObject UserType) socialnetwork.MediaServiceImpl struct{}

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) mediaTypes []string
[_1] (Reference ArrayType) ref <mediaTypes []string> @ ComposePostService
[__2] (Reference ArrayType) ref <media_types []string> @ Wrk2APIService

[0] (ArrayObject ArrayType) mediaIds []int64
[_1] (Reference ArrayType) ref <mediaIDs []int64> @ ComposePostService
[__2] (Reference ArrayType) ref <media_ids []int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) medias []socialnetwork.Media struct{MediaID int64, MediaType string}
[_1] (StructObject UserType) media socialnetwork.Media struct{MediaID 0 int, MediaType string}
[__2] (FieldObject FieldType) MediaID 0 int
[___3] (BasicObject BasicType) mediaId 0 int
[__2] (FieldObject FieldType) MediaType string
[___3] (BasicObject BasicType) * string

[0] (BasicObject BasicType) idx int64

[0] (BasicObject BasicType) mediaId 0 int

[0] (StructObject UserType) media socialnetwork.Media struct{MediaID 0 int, MediaType string}
[_1] (FieldObject FieldType) MediaID 0 int
[__2] (BasicObject BasicType) mediaId 0 int
[_1] (FieldObject FieldType) MediaType string
[__2] (BasicObject BasicType) * string

[0] (ArrayObject ArrayType) medias []socialnetwork.Media struct{MediaID int64, MediaType string}
[_1] (StructObject UserType) media socialnetwork.Media struct{MediaID 0 int, MediaType string}
[__2] (FieldObject FieldType) MediaID 0 int
[___3] (BasicObject BasicType) mediaId 0 int
[__2] (FieldObject FieldType) MediaType string
[___3] (BasicObject BasicType) * string

[0] (PointerObject PointerType) m (*socialnetwork.MediaServiceImpl struct{})
[_1] (StructObject UserType) socialnetwork.MediaServiceImpl struct{}

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) mediaTypes []string
[_1] (Reference ArrayType) ref <mediaTypes []string> @ ComposePostService
[__2] (Reference ArrayType) ref <media_types []string> @ Wrk2APIService

[0] (ArrayObject ArrayType) mediaIds []int64
[_1] (Reference ArrayType) ref <mediaIDs []int64> @ ComposePostService
[__2] (Reference ArrayType) ref <media_ids []int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) medias []socialnetwork.Media struct{MediaID int64, MediaType string}
[_1] (StructObject UserType) media socialnetwork.Media struct{MediaID 0 int, MediaType string}
[__2] (FieldObject FieldType) MediaID 0 int
[___3] (BasicObject BasicType) mediaId 0 int
[__2] (FieldObject FieldType) MediaType string
[___3] (BasicObject BasicType) * string

[0] (BasicObject BasicType) idx int64

[0] (BasicObject BasicType) mediaId 0 int

