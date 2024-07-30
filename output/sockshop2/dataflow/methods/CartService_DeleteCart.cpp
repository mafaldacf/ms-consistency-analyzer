[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (30) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (25) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (64) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) customerID string 
[_] (32) (Reference BasicType) ref <customerID string> @ OrderService // write(shipqueue), write(shipdb), write(order_db), 
[__] (26) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (65) (Reference BasicType) ref <sessionID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (-1) (InterfaceVariable UserType) _ .error 

