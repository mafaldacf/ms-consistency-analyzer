[] (PointerVariable PointerType) s (*shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int}) 
[_] (StructVariable UserType) shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int} 
[__] (FieldVariable FieldType) cart_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase 
[__] (FieldVariable FieldType) num_workers 4 int 
[___] (BasicVariable BasicType) 4 int 
[__] (FieldVariable FieldType) product_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue 
[__] (FieldVariable FieldType) product_service shopping_simple.ProductService 
[___] (ServiceVariable ServiceType) product_service shopping_simple.ProductService 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) cartID string // write(cart_db), 
[_] (Reference BasicType) ref <cartID string> @ Frontend // write(cart_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_database} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) cart shopping_simple.Cart struct{CartID string, TotalQuantity 1 int, LastProductID string, Products []string} // write(cart_db), 
[_] (FieldVariable FieldType) CartID string // write(cart_db), 
[__] (BasicVariable BasicType) cartID string // write(cart_db), 
[___] (Reference BasicType) ref <cartID string> @ Frontend // write(cart_db), 

[] (InterfaceVariable UserType) err .error 

