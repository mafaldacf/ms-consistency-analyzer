[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (10) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (30) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (25) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (11) (Reference BasicType) ref <sessionID string> @ FrontendService 
[_] (31) (Reference BasicType) ref <cartID string> @ OrderService 
[__] (29) (Reference BasicType) ref <cartID string> @ FrontendService 

[] (-1) (AddressVariable AddressType) cart (&cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (11) (Reference BasicType) ref <sessionID string> @ FrontendService 
[____] (31) (Reference BasicType) ref <cartID string> @ OrderService 
[_____] (29) (Reference BasicType) ref <cartID string> @ FrontendService 

