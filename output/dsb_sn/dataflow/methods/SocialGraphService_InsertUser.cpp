[0] (PointerObject PointerType) s (*socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService})
[_1] (StructObject UserType) socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService}
[__2] (FieldObject FieldType) socialGraphCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphCache Cache
[__2] (FieldObject FieldType) socialGraphDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphDB NoSQLDatabase
[__2] (FieldObject FieldType) userIDService socialnetwork.UserIDService
[___3] (ServiceObject ServiceType) userIDService socialnetwork.UserIDService

[0] (InterfaceObject UserType) ctx context.Context

[0] (BasicObject BasicType) reqID int64

[0] (BasicObject BasicType) userID int64

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = social-graph, collection = social-graph}

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) user socialnetwork.UserInfo struct{UserID int64, Followers []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}, Followees []socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}}
[_1] (FieldObject FieldType) Followees []socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}
[__2] (ArrayObject ArrayType) []socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}
[_1] (FieldObject FieldType) Followers []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}
[__2] (ArrayObject ArrayType) []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}
[_1] (FieldObject FieldType) UserID int64
[__2] (BasicObject BasicType) userID int64

