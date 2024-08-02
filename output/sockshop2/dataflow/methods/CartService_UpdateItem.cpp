[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (63) (InterfaceVariable UserType) ctx context.Context 
[_] (63) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (65) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (0) (StructVariable UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[_] (66) (Reference UserType) ref <cart.Item struct{ID string, Quantity int, UnitPrice float32}> @ FrontendService 
[__] (67) (FieldVariable FieldType) ID string 
[___] (68) (BasicVariable BasicType) ID string 
[__] (69) (FieldVariable FieldType) Quantity int 
[___] (70) (BasicVariable BasicType) quantity int 
[__] (71) (FieldVariable FieldType) UnitPrice float32 
[___] (72) (BasicVariable BasicType) Price float32 

[] (-1) (AddressVariable AddressType) cart (&cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}) 
[_] (0) (StructVariable UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}} 
[__] (0) (FieldVariable FieldType) ID string 
[___] (-1) (BasicVariable BasicType) customerID string 
[____] (65) (Reference BasicType) ref <sessionID string> @ FrontendService 
[__] (0) (FieldVariable FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[___] (0) (ArrayVariable ArrayType) []cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[____] (0) (StructVariable UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32} 
[_____] (66) (Reference UserType) ref <cart.Item struct{ID string, Quantity int, UnitPrice float32}> @ FrontendService 
[______] (67) (FieldVariable FieldType) ID string 
[_______] (68) (BasicVariable BasicType) ID string 
[______] (69) (FieldVariable FieldType) Quantity int 
[_______] (70) (BasicVariable BasicType) quantity int 
[______] (71) (FieldVariable FieldType) UnitPrice float32 
[_______] (72) (BasicVariable BasicType) Price float32 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (-1) (InterfaceVariable UserType) _ .error 

