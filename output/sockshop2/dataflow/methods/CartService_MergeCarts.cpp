[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (75) (InterfaceVariable UserType) ctx context.Context 
[_] (70) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (75) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (73) (Reference BasicType) ref <UserID string> @ FrontendService 
[_] (81) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (BasicVariable BasicType) sessionID string 
[_] (74) (Reference BasicType) ref <sessionID string> @ FrontendService 
[_] (82) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (-1) (PointerVariable PointerType) cart (*cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (73) (Reference BasicType) ref <UserID string> @ FrontendService 
[____] (81) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (-1) (InterfaceVariable UserType) _ .error 

