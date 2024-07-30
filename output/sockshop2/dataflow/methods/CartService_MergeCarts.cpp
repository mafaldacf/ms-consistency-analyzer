[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (71) (InterfaceVariable UserType) ctx context.Context 
[_] (44) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (71) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (47) (Reference BasicType) ref <UserID string> @ FrontendService 
[_] (77) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (BasicVariable BasicType) sessionID string 
[_] (48) (Reference BasicType) ref <sessionID string> @ FrontendService 
[_] (78) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (-1) (AddressVariable AddressType) cart (&cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (47) (Reference BasicType) ref <UserID string> @ FrontendService 
[____] (77) (Reference BasicType) ref <userID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (-1) (InterfaceVariable UserType) _ .error 

