[0] (PointerObject PointerType) s (*socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService})
[_1] (StructObject UserType) socialnetwork.SocialGraphServiceImpl struct{socialGraphCache Cache, socialGraphDB NoSQLDatabase, userIDService socialnetwork.UserIDService}
[__2] (FieldObject FieldType) socialGraphCache Cache
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphCache Cache
[__2] (FieldObject FieldType) socialGraphDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) socialGraphDB NoSQLDatabase
[__2] (FieldObject FieldType) userIDService socialnetwork.UserIDService
[___3] (ServiceObject ServiceType) userIDService socialnetwork.UserIDService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ UserService
[__2] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

[0] (BasicObject BasicType) reqID int64
[_1] (Reference BasicType) ref <reqID int64> @ UserService
[__2] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

    --> w-tainted: write(social_db.UserInfo.UserID, user_db.User.UserID) {2}
[0] (BasicObject BasicType) userID int64
     --> w-tainted: write(user_db.User.UserID, social_db.UserInfo.UserID) {2}
[_1] (Reference BasicType) ref <userID int64> @ UserService
      --> w-tainted: write(user_db.User.UserID, social_db.UserInfo.UserID) {2}
[__2] (Reference BasicType) ref <userId int64> @ Wrk2APIService

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = social-graph, collection = social-graph}

[0] (InterfaceObject UserType) err .error

    --> w-tainted: write(social_db.UserInfo) {1}
[0] (StructObject UserType) user socialnetwork.UserInfo struct{UserID int64, Followers []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}, Followees []socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}}
     --> w-tainted: write(social_db.UserInfo.Followees) {1}
[_1] (FieldObject FieldType) Followees []socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}
      --> w-tainted: write(social_db.UserInfo.Followees) {1}
[__2] (ArrayObject ArrayType) []socialnetwork.FolloweeInfo struct{FolloweeID int64, Timestamp int64}
     --> w-tainted: write(social_db.UserInfo.Followers) {1}
[_1] (FieldObject FieldType) Followers []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}
      --> w-tainted: write(social_db.UserInfo.Followers) {1}
[__2] (ArrayObject ArrayType) []socialnetwork.FollowerInfo struct{FollowerID int64, Timestamp int64}
     --> w-tainted: write(social_db.UserInfo.UserID) {1}
[_1] (FieldObject FieldType) UserID int64
      --> w-tainted: write(social_db.UserInfo.UserID, user_db.User.UserID) {2}
[__2] (BasicObject BasicType) userID int64
       --> w-tainted: write(user_db.User.UserID, social_db.UserInfo.UserID) {2}
[___3] (Reference BasicType) ref <userID int64> @ UserService
        --> w-tainted: write(user_db.User.UserID, social_db.UserInfo.UserID) {2}
[____4] (Reference BasicType) ref <userId int64> @ Wrk2APIService

