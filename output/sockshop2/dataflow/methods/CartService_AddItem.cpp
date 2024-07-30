[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (15) (InterfaceVariable UserType) ctx context.Context 
[_] (15) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (17) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (0) (StructVariable UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[_] (18) (Reference UserType) ref <cart.Item struct{ID string, Quantity int, UnitPrice float32}> @ FrontendService 
[__] (23) (FieldVariable FieldType) Quantity 1 int 
[___] (24) (BasicVariable BasicType) 1 int 
[__] (19) (FieldVariable FieldType) UnitPrice float32 
[___] (20) (BasicVariable BasicType) Price float32 
[__] (21) (FieldVariable FieldType) ID string 
[___] (22) (BasicVariable BasicType) ID string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (AddressVariable AddressType) cart (&cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (17) (Reference BasicType) ref <sessionID string> @ FrontendService 

