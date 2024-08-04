[] (PointerVariable PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}) 
[_] (StructVariable UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase} 
[__] (FieldVariable FieldType) cart_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase 
[__] (FieldVariable FieldType) order_service shopping_app.OrderService 
[___] (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (FieldVariable FieldType) product_service shopping_app.ProductService 
[___] (ServiceVariable ServiceType) product_service shopping_app.ProductService 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) cartID string 
[_] (Reference BasicType) ref <cartID string> @ Frontend 

[] (BasicVariable BasicType) productID string 
[_] (Reference BasicType) ref <productID string> @ Frontend 

[] (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 
[_] (FieldVariable FieldType) PricePerUnit int 
[__] (BasicVariable BasicType) PricePerUnit int // write(cart_db), 
[_] (FieldVariable FieldType) ProductID string 
[__] (BasicVariable BasicType) ProductID string // write(cart_db), 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string} // write(cart_db), 
[_] (FieldVariable FieldType) PricePerUnit int // write(cart_db), 
[__] (BasicVariable BasicType) PricePerUnit int // write(cart_db), 
[_] (FieldVariable FieldType) ProductID string // write(cart_db), 
[__] (BasicVariable BasicType) ProductID string // write(cart_db), 
[_] (FieldVariable FieldType) Quantity int // write(cart_db), 
[__] (BasicVariable BasicType) 1 int // write(cart_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (FieldVariable FieldType) Key "cartID" string 
[___] (BasicVariable BasicType) "cartID" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) cartID string 
[____] (Reference BasicType) ref <cartID string> @ Frontend 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (PointerVariable PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}) 
[_] (StructVariable UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase} 
[__] (FieldVariable FieldType) cart_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase 
[__] (FieldVariable FieldType) order_service shopping_app.OrderService 
[___] (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (FieldVariable FieldType) product_service shopping_app.ProductService 
[___] (ServiceVariable ServiceType) product_service shopping_app.ProductService 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) cartID string 
[_] (Reference BasicType) ref <cartID string> @ Frontend 

[] (BasicVariable BasicType) productID string 
[_] (Reference BasicType) ref <productID string> @ Frontend 

[] (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 
[_] (FieldVariable FieldType) PricePerUnit int 
[__] (BasicVariable BasicType) PricePerUnit int // write(cart_db), 
[_] (FieldVariable FieldType) ProductID string 
[__] (BasicVariable BasicType) ProductID string // write(cart_db), 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string} // write(cart_db), 
[_] (FieldVariable FieldType) PricePerUnit int // write(cart_db), 
[__] (BasicVariable BasicType) PricePerUnit int // write(cart_db), 
[_] (FieldVariable FieldType) ProductID string // write(cart_db), 
[__] (BasicVariable BasicType) ProductID string // write(cart_db), 
[_] (FieldVariable FieldType) Quantity int // write(cart_db), 
[__] (BasicVariable BasicType) 1 int // write(cart_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (FieldVariable FieldType) Key "cartID" string 
[___] (BasicVariable BasicType) "cartID" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) cartID string 
[____] (Reference BasicType) ref <cartID string> @ Frontend 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection} 

[] (InterfaceVariable UserType) _ .error 

