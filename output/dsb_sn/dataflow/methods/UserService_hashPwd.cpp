[0] (PointerObject PointerType) u (*socialnetwork.UserServiceImpl struct{machine_id string, counter int64, current_timestamp int64, secret string, userCache Cache, userDB NoSQLDatabase, socialGraphService socialnetwork.SocialGraphService})
[_1] (StructObject UserType) socialnetwork.UserServiceImpl struct{machine_id string, counter 0 int, current_timestamp int64, secret string, userCache Cache, userDB NoSQLDatabase, socialGraphService socialnetwork.SocialGraphService}
[__2] (FieldObject FieldType) counter 0 int
[___3] (BasicObject BasicType) 1 int
[__2] (FieldObject FieldType) current_timestamp int64
[___3] (BasicObject BasicType) timestamp int64
[__2] (FieldObject FieldType) machine_id string
[___3] (BasicObject BasicType) string
[__2] (FieldObject FieldType) secret string
[___3] (BasicObject BasicType) secret string
[__2] (FieldObject FieldType) socialGraphService socialnetwork.SocialGraphService
[___3] (ServiceObject ServiceType) socialGraphService socialnetwork.SocialGraphService
[__2] (FieldObject FieldType) userCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) userCache Cache
[__2] (FieldObject FieldType) userDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) userDB NoSQLDatabase

[0] (ArrayObject ArrayType) pwd []byte
[_1] (Reference BasicType) ref <byte> @ UserService
[__2] (BasicObject BasicType) 
[___3] (BasicObject BasicType) password string
[____4] (Reference BasicType) ref <password string> @ Wrk2APIService
       --> w-tainted: write(user_db.User.Salt) {1}
[___3] (BasicObject BasicType) salt string
        --> w-tainted: write(user_db.User.Salt) {1}
[____4] (Reference BasicType) ref <string> @ genRandomStr
         --> w-tainted: write(user_db.User.Salt) {1}
[_____5] (ArrayObject ArrayType) b []rune
          --> w-tainted: write(user_db.User.Salt) {1}
[______6] (SliceObject SliceType) github.com/blueprint-uservices/blueprint/examples/dsb_sn/workflow/socialnetwork.letterRunes []rune

[0] (InterfaceObject UserType) hasher hash.Hash interface{ interface{BlockSize() int; Reset(); Size() int; Sum(b []byte) []byte; io.Writer} }

