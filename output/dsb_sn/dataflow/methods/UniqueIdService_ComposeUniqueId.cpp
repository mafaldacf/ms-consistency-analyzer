[0] (PointerObject PointerType) u (*socialnetwork.UniqueIdServiceImpl struct{counter int64, current_timestamp int64, machine_id string})
[_1] (StructObject UserType) socialnetwork.UniqueIdServiceImpl struct{counter 0 int, current_timestamp int64, machine_id string}
[__2] (FieldObject FieldType) counter 0 int
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) current_timestamp int64
[___3] (BasicObject BasicType) timestamp int64
[____4] (Reference BasicType) ref <timestamp int64> @ UniqueIdService
[__2] (FieldObject FieldType) machine_id string
[___3] (BasicObject BasicType) string

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.PostType) {1}
[0] (BasicObject BasicType) postType int64
     --> w-tainted: write(post_db.Post.PostType) {1}
[_1] (Reference BasicType) ref <postType int64> @ ComposePostService
      --> w-tainted: write(post_db.Post.PostType) {1}
[__2] (Reference BasicType) ref <post_type int64> @ Wrk2APIService

[0] (BasicObject BasicType) timestamp int64

[0] (BasicObject BasicType) idx int64
[_1] (Reference BasicType) ref <0 int> @ getCounter

[0] (BasicObject BasicType) timestamp_hex string
[_1] (BasicObject BasicType) timestamp int64
[_1] (BasicObject BasicType) 16 int
[_1] (BasicObject BasicType) timestamp int64
[_1] (BasicObject BasicType) 16 int

[0] (BasicObject BasicType) timestamp_hex string

[0] (BasicObject BasicType) counter_hex string
[_1] (BasicObject BasicType) idx int64
[__2] (Reference BasicType) ref <0 int> @ getCounter
[_1] (BasicObject BasicType) 16 int
[_1] (BasicObject BasicType) idx int64
[__2] (Reference BasicType) ref <0 int> @ getCounter
[_1] (BasicObject BasicType) 16 int

[0] (BasicObject BasicType) counter_hex string

[0] (BasicObject BasicType) post_id_str string

[0] (BasicObject BasicType) post_id int64
[_1] (BasicObject BasicType) post_id_str string
[_1] (BasicObject BasicType) 16 int
[_1] (BasicObject BasicType) 64 int
[_1] (BasicObject BasicType) post_id_str string
[_1] (BasicObject BasicType) 16 int
[_1] (BasicObject BasicType) 64 int

[0] (InterfaceObject UserType) err .error
[_1] (BasicObject BasicType) post_id_str string
[_1] (BasicObject BasicType) 16 int
[_1] (BasicObject BasicType) 64 int

[0] (BasicObject BasicType) post_id 0x7FFFFFFFFFFFFFFF 
[_1] (BasicObject BasicType) post_id int64
[__2] (BasicObject BasicType) post_id_str string
[__2] (BasicObject BasicType) 16 int
[__2] (BasicObject BasicType) 64 int
[__2] (BasicObject BasicType) post_id_str string
[__2] (BasicObject BasicType) 16 int
[__2] (BasicObject BasicType) 64 int
[_1] (BasicObject BasicType) 0x7FFFFFFFFFFFFFFF int

