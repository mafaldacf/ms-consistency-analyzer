[] (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) customerID string 
[_] (Reference BasicType) ref <sessionID string> @ FrontendService 
[_] (Reference BasicType) ref <cartID string> @ OrderService 
[__] (Reference BasicType) ref <cartID string> @ FrontendService 

[] (PointerVariable PointerType) cart (*cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (FieldVariable FieldType) ID string 
[___] (BasicVariable BasicType) customerID string 
[____] (Reference BasicType) ref <sessionID string> @ FrontendService 
[____] (Reference BasicType) ref <cartID string> @ OrderService 
[_____] (Reference BasicType) ref <cartID string> @ FrontendService 
[__] (FieldVariable FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[___] (ArrayVariable ArrayType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} 

