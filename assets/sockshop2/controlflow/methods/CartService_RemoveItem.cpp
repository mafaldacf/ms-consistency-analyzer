[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (5) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (6) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (-1) (BasicVariable BasicType) itemID string 
[_] (7) (Reference BasicType) ref <itemID string> @ FrontendService 

[] (-1) (AddressVariable AddressType) cart (&cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (6) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (-1) (InterfaceVariable UserType) _ .error 

