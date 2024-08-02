[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (22) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (17) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (59) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (23) (Reference BasicType) ref <cartID string> @ OrderService 
[__] (21) (Reference BasicType) ref <cartID string> @ FrontendService 
[_] (60) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (-1) (AddressVariable AddressType) cart (&cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (23) (Reference BasicType) ref <cartID string> @ OrderService 
[_____] (21) (Reference BasicType) ref <cartID string> @ FrontendService 
[____] (60) (Reference BasicType) ref <sessionID string> @ FrontendService 

