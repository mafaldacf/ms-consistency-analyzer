[] (-1) (PointerVariable PointerType) s (*cart.cartImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) cart.cartImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (16) (InterfaceVariable UserType) ctx context.Context 
[_] (3) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (16) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (11) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (18) (BasicVariable BasicType) customerID string 
[_] (4) (Reference BasicType) ref <sessionID string> @ FrontendService 
[_] (18) (Reference BasicType) ref <customerID string> @ OrderService // write(shipqueue), write(shipdb), write(order_db), read(user_db), 
[__] (12) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), read(user_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts} 

[] (-1) (InterfaceVariable UserType) _ .error 

