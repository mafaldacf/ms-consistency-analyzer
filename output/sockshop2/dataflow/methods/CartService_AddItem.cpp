[] (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) customerID string 
[_] (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (StructVariable UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[_] (Reference UserType) ref <cart.Item struct{ID string, Quantity int, UnitPrice float32}> @ FrontendService 
[__] (FieldVariable FieldType) ID string 
[___] (BasicVariable BasicType) ID string 
[__] (FieldVariable FieldType) Quantity 1 int 
[___] (BasicVariable BasicType) 1 int 
[__] (FieldVariable FieldType) UnitPrice float32 
[___] (BasicVariable BasicType) Price float32 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (InterfaceVariable UserType) _ .error 

[] (PointerVariable PointerType) cart (*cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (FieldVariable FieldType) ID string 
[___] (BasicVariable BasicType) customerID string 
[____] (Reference BasicType) ref <sessionID string> @ FrontendService 

