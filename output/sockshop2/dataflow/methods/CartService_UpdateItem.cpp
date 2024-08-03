[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (11) (InterfaceVariable UserType) ctx context.Context 
[_] (11) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (13) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (0) (StructVariable UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[_] (14) (Reference UserType) ref <cart.Item struct{ID string, Quantity 1 int, UnitPrice float32}> @ FrontendService 
[__] (15) (FieldVariable FieldType) Quantity int 
[___] (16) (BasicVariable BasicType) quantity int 
[__] (17) (FieldVariable FieldType) UnitPrice float32 
[___] (18) (BasicVariable BasicType) Price float32 
[__] (19) (FieldVariable FieldType) ID string 
[___] (20) (BasicVariable BasicType) ID string 

[] (-1) (PointerVariable PointerType) cart (*cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[___] (0) (ArrayVariable ArrayType) []cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[____] (0) (StructVariable UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[_____] (14) (Reference UserType) ref <cart.Item struct{ID string, Quantity 1 int, UnitPrice float32}> @ FrontendService 
[______] (17) (FieldVariable FieldType) UnitPrice float32 
[_______] (18) (BasicVariable BasicType) Price float32 
[______] (19) (FieldVariable FieldType) ID string 
[_______] (20) (BasicVariable BasicType) ID string 
[______] (15) (FieldVariable FieldType) Quantity int 
[_______] (16) (BasicVariable BasicType) quantity int 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (13) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (-1) (InterfaceVariable UserType) _ .error 

