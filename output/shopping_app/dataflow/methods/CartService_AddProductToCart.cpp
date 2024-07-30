[] (-1) (PointerVariable PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase} 
[__] (-1) (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (-1) (ServiceVariable ServiceType) product_service shopping_app.ProductService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase 

[] (6) (InterfaceVariable UserType) ctx context.Context 
[_] (3) (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (-1) (BasicVariable BasicType) cartID string 
[_] (4) (Reference BasicType) ref <cartID string> @ Frontend 

[] (7) (BasicVariable BasicType) productID string 
[_] (5) (Reference BasicType) ref <productID string> @ Frontend 

[] (-1) (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (-1) (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 
[_] (-1) (FieldVariable FieldType) PricePerUnit int 
[__] (-1) (BasicVariable BasicType) PricePerUnit int // write(cart_db), 
[_] (-1) (FieldVariable FieldType) ProductID string 
[__] (-1) (BasicVariable BasicType) ProductID string // write(cart_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string} // write(cart_db), 
[_] (-1) (FieldVariable FieldType) Quantity int // write(cart_db), 
[__] (0) (BasicVariable BasicType) 1 int // write(cart_db), 
[_] (-1) (FieldVariable FieldType) PricePerUnit int // write(cart_db), 
[__] (-1) (BasicVariable BasicType) PricePerUnit int // write(cart_db), 
[_] (-1) (FieldVariable FieldType) ProductID string // write(cart_db), 
[__] (-1) (BasicVariable BasicType) ProductID string // write(cart_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "cartID" string 
[___] (0) (BasicVariable BasicType) "cartID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) cartID string 
[____] (4) (Reference BasicType) ref <cartID string> @ Frontend 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (PointerVariable PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase 
[__] (-1) (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (-1) (ServiceVariable ServiceType) product_service shopping_app.ProductService 

[] (6) (InterfaceVariable UserType) ctx context.Context 
[_] (3) (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (-1) (BasicVariable BasicType) cartID string 
[_] (4) (Reference BasicType) ref <cartID string> @ Frontend 

[] (7) (BasicVariable BasicType) productID string 
[_] (5) (Reference BasicType) ref <productID string> @ Frontend 

[] (-1) (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (-1) (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 
[_] (-1) (FieldVariable FieldType) ProductID string 
[__] (-1) (BasicVariable BasicType) ProductID string // write(cart_db), 
[_] (-1) (FieldVariable FieldType) PricePerUnit int 
[__] (-1) (BasicVariable BasicType) PricePerUnit int // write(cart_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string} // write(cart_db), 
[_] (-1) (FieldVariable FieldType) ProductID string // write(cart_db), 
[__] (-1) (BasicVariable BasicType) ProductID string // write(cart_db), 
[_] (-1) (FieldVariable FieldType) Quantity int // write(cart_db), 
[__] (0) (BasicVariable BasicType) 1 int // write(cart_db), 
[_] (-1) (FieldVariable FieldType) PricePerUnit int // write(cart_db), 
[__] (-1) (BasicVariable BasicType) PricePerUnit int // write(cart_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) cartID string 
[____] (4) (Reference BasicType) ref <cartID string> @ Frontend 
[__] (0) (FieldVariable FieldType) Key "cartID" string 
[___] (0) (BasicVariable BasicType) "cartID" string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

