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

[0] (InterfaceObject UserType) ctx context.Context

[0] (BasicObject BasicType) reqID int64

[0] (BasicObject BasicType) username string

[0] (BasicObject BasicType) user_id int64
[_1] (BasicObject BasicType) int64

[0] (StructObject UserType) user socialnetwork.User struct{UserID int64, FirstName string, LastName string, Username string, PwdHashed string, Salt string}
[_1] (FieldObject FieldType) UserID int64
[__2] (BasicObject BasicType) UserID int64

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = user, collection = user}

[0] (InterfaceObject UserType) err .error

[0] (SliceObject UserType) query primitive.D
[_1] (StructObject StructType) struct{ string,  "username" string,  string}

[0] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = user, collection = user}
[_1] (StructObject UserType) user socialnetwork.User struct{UserID int64, FirstName string, LastName string, Username string, PwdHashed string, Salt string}
[__2] (FieldObject FieldType) UserID int64
[___3] (BasicObject BasicType) UserID int64

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) exists bool

[0] (InterfaceObject UserType) err .error

[0] (FieldObject FieldType) user_id int64
[_1] (BasicObject BasicType) UserID int64

[0] (InterfaceObject UserType) err .error

