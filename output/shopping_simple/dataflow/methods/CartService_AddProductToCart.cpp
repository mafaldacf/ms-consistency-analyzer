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

[] (BasicVariable BasicType) productID string // write(cart_db), 
[_] (Reference BasicType) ref <productID string> @ Frontend // write(cart_db), 

[] (StructVariable UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (StructVariable UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 
[_] (FieldVariable FieldType) PricePerUnit int 
[__] (BasicVariable BasicType) PricePerUnit int 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) cart shopping_simple.Cart struct{CartID string, TotalQuantity 1 int, LastProductID string, Products []string} 

[] (StructVariable UserType) cartProduct shopping_simple.CartProduct struct{CartID string, ProductID string, PricePerUnit int, Quantity 1 int} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) filter primitive.D 
[_] (StructVariable StructType) struct{Key "cartid" string, Value string} 
[__] (FieldVariable FieldType) Key "cartid" string 
[___] (BasicVariable BasicType) "cartid" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) cartID string // write(cart_db), 
[____] (Reference BasicType) ref <cartID string> @ Frontend // write(cart_db), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) cartProduct shopping_simple.CartProduct struct{CartID string, ProductID string, PricePerUnit int, Quantity 1 int} 
[_] (FieldVariable FieldType) CartID string 
[__] (BasicVariable BasicType) cartID string // write(cart_db), 
[___] (Reference BasicType) ref <cartID string> @ Frontend // write(cart_db), 
[_] (FieldVariable FieldType) PricePerUnit int 
[__] (BasicVariable BasicType) PricePerUnit int 
[_] (FieldVariable FieldType) ProductID string 
[__] (BasicVariable BasicType) productID string // write(cart_db), 
[___] (Reference BasicType) ref <productID string> @ Frontend // write(cart_db), 
[_] (FieldVariable FieldType) Quantity 1 int 
[__] (BasicVariable BasicType) 1 int 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) _ .error 

