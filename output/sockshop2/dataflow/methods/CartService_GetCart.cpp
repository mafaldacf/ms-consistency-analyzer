[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (32) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (40) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (35) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (33) (Reference BasicType) ref <sessionID string> @ FrontendService 
[_] (41) (Reference BasicType) ref <cartID string> @ OrderService 
[__] (39) (Reference BasicType) ref <cartID string> @ FrontendService 

[] (-1) (PointerVariable PointerType) cart (*cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (33) (Reference BasicType) ref <sessionID string> @ FrontendService 
[____] (41) (Reference BasicType) ref <cartID string> @ OrderService 
[_____] (39) (Reference BasicType) ref <cartID string> @ FrontendService 
[__] (-1) (FieldVariable FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[___] (-1) (ArrayVariable ArrayType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} 

