[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) :UserID 
[__2] (BasicObject BasicType) name string
[__2] (BasicObject BasicType) ":UserID" string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) values []int64

    --> r-tainted: read(user_cache.value, user_cache.[]interface{}, user_cache.(*int64), user_cache.int64) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(user_cache.(*int64)) {1}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (BasicObject BasicType) idx int64

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) :UserID 
[__2] (BasicObject BasicType) name string
[__2] (BasicObject BasicType) ":UserID" string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) values []int64

    --> r-tainted: read(user_cache.value, user_cache.[]interface{}, user_cache.(*int64), user_cache.int64) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(user_cache.(*int64)) {1}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (BasicObject BasicType) idx int64

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[__2] (FieldObject FieldType) UserID int64
[___3] (BasicObject BasicType) * int64
[__2] (FieldObject FieldType) Username string
[___3] (BasicObject BasicType) * string

[0] (BasicObject BasicType) idx string

[0] (BasicObject BasicType) key 0 int

[0] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (FieldObject FieldType) UserID int64
[__2] (BasicObject BasicType) * int64
[_1] (FieldObject FieldType) Username string
[__2] (BasicObject BasicType) * string

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[__2] (FieldObject FieldType) UserID int64
[___3] (BasicObject BasicType) * int64
[__2] (FieldObject FieldType) Username string
[___3] (BasicObject BasicType) * string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) :UserID 
[__2] (BasicObject BasicType) name string
[__2] (BasicObject BasicType) ":UserID" string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) values []int64

    --> r-tainted: read(user_cache.value, user_cache.[]interface{}, user_cache.(*int64), user_cache.int64) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(user_cache.(*int64)) {1}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (BasicObject BasicType) idx int64

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) :UserID 
[__2] (BasicObject BasicType) name string
[__2] (BasicObject BasicType) ":UserID" string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) values []int64

    --> r-tainted: read(user_cache.value, user_cache.[]interface{}, user_cache.(*int64), user_cache.int64) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(user_cache.(*int64)) {1}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (BasicObject BasicType) idx int64

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[__2] (FieldObject FieldType) UserID int64
[___3] (BasicObject BasicType) * int64
[__2] (FieldObject FieldType) Username string
[___3] (BasicObject BasicType) * string

[0] (BasicObject BasicType) idx string

[0] (BasicObject BasicType) key 0 int

[0] (ArrayObject ArrayType) names []string
[_1] (BasicObject BasicType) string

[0] (BasicObject BasicType) name bool

[0] (ArrayObject ArrayType) names []string
[_1] (BasicObject BasicType) string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) :UserID 
[__2] (BasicObject BasicType) name string
[__2] (BasicObject BasicType) ":UserID" string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) values []int64

    --> r-tainted: read(user_cache.value, user_cache.[]interface{}, user_cache.(*int64), user_cache.int64) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(user_cache.(*int64)) {1}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (BasicObject BasicType) idx int64

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) :UserID 
[__2] (BasicObject BasicType) name string
[__2] (BasicObject BasicType) ":UserID" string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) values []int64

    --> r-tainted: read(user_cache.value, user_cache.[]interface{}, user_cache.(*int64), user_cache.int64) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(user_cache.(*int64)) {1}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (BasicObject BasicType) idx int64

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[__2] (FieldObject FieldType) UserID int64
[___3] (BasicObject BasicType) * int64
[__2] (FieldObject FieldType) Username string
[___3] (BasicObject BasicType) * string

[0] (BasicObject BasicType) idx string

[0] (BasicObject BasicType) key 0 int

[0] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (FieldObject FieldType) UserID int64
[__2] (BasicObject BasicType) * int64
[_1] (FieldObject FieldType) Username string
[__2] (BasicObject BasicType) * string

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[__2] (FieldObject FieldType) UserID int64
[___3] (BasicObject BasicType) * int64
[__2] (FieldObject FieldType) Username string
[___3] (BasicObject BasicType) * string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) :UserID 
[__2] (BasicObject BasicType) name string
[__2] (BasicObject BasicType) ":UserID" string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) values []int64

    --> r-tainted: read(user_cache.value, user_cache.[]interface{}, user_cache.(*int64), user_cache.int64) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(user_cache.(*int64)) {1}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (BasicObject BasicType) idx int64

[0] (ArrayObject ArrayType) retvals []interface{}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) keys []string
[_1] (BasicObject BasicType) :UserID 
[__2] (BasicObject BasicType) name string
[__2] (BasicObject BasicType) ":UserID" string

[0] (PointerObject PointerType) u (*socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase})
[_1] (StructObject UserType) socialnetwork.UserMentionServiceImpl struct{userCache Cache, userDB NoSQLDatabase}
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) usernames []string
[_1] (Reference ArrayType) ref <usernames []string> @ TextService
[__2] (BasicObject BasicType) m string

[0] (MapObject MapType) usernames_not_cached map[string]bool
[_1] (BasicObject BasicType) true bool

[0] (MapObject MapType) rev_lookup map[string]string
     --> r-tainted: read(user_cache.string) {1}
[_1] (BasicObject BasicType) name string

    --> r-tainted: read(user_cache.key, user_cache.[]string, user_cache., user_cache.string) {4}
[0] (ArrayObject ArrayType) keys []string
     --> r-tainted: read(user_cache.) {1}
[_1] (BasicObject BasicType) :UserID 
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) name string
      --> r-tainted: read(user_cache.string) {1}
[__2] (BasicObject BasicType) ":UserID" string

    --> r-tainted: read(user_cache.string) {1}
[0] (BasicObject BasicType) name string

[0] (ArrayObject ArrayType) values []int64

    --> r-tainted: read(user_cache.value, user_cache.[]interface{}, user_cache.(*int64), user_cache.int64) {4}
[0] (ArrayObject ArrayType) retvals []interface{}
     --> r-tainted: read(user_cache.(*int64)) {1}
[_1] (PointerObject PointerType) * (*int64)
      --> r-tainted: read(user_cache.int64) {1}
[__2] (BasicObject BasicType) * int64

[0] (BasicObject BasicType) idx int64

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[__2] (FieldObject FieldType) UserID int64
[___3] (BasicObject BasicType) * int64
[__2] (FieldObject FieldType) Username string
[___3] (BasicObject BasicType) * string

[0] (BasicObject BasicType) idx string

[0] (BasicObject BasicType) key 0 int

[0] (ArrayObject ArrayType) names []string
[_1] (BasicObject BasicType) string

[0] (BasicObject BasicType) name bool

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = user, collection = user}

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) in_str string
[_1] (ArrayObject ArrayType) names []string
[__2] (BasicObject BasicType) string
[_1] (BasicObject BasicType) "," string
[_1] (ArrayObject ArrayType) names []string
[__2] (BasicObject BasicType) string
[_1] (BasicObject BasicType) "," string

[0] (BasicObject BasicType) query string

[0] (SliceObject UserType) query_d primitive.D
[_1] (Reference UserType) ref <primitive.D> @ parseNoSQLDBQuery

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <.error> @ parseNoSQLDBQuery

    --> r-tainted: read(user_db.User) {1}
[0] (BlueprintBackendObject BlueprintBackendType) vals NoSQLCursor {database = user, collection = user}
     --> r-tainted: read(user_db.[]socialnetwork.UserMention struct{UserID int64, Username string}) {1}
[_1] (ArrayObject ArrayType) new_user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (InterfaceObject UserType) err .error

    --> r-tainted: read(user_db.[]socialnetwork.UserMention struct{UserID int64, Username string}) {1}
[0] (ArrayObject ArrayType) new_user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}

[0] (InterfaceObject UserType) err .error

[0] (ArrayObject ArrayType) user_mentions []socialnetwork.UserMention struct{UserID int64, Username string}
[_1] (StructObject UserType) user_mention socialnetwork.UserMention struct{UserID int64, Username string}
[__2] (FieldObject FieldType) UserID int64
[___3] (BasicObject BasicType) * int64
[__2] (FieldObject FieldType) Username string
[___3] (BasicObject BasicType) * string

