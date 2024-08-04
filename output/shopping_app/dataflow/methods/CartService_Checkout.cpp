[] (PointerVariable PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}) 
[_] (StructVariable UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase} 
[__] (FieldVariable FieldType) cart_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase 
[__] (FieldVariable FieldType) order_service shopping_app.OrderService 
[___] (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (FieldVariable FieldType) product_service shopping_app.ProductService 
[___] (ServiceVariable ServiceType) product_service shopping_app.ProductService 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) cartID string 

[] (StructVariable UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string} 
[_] (FieldVariable FieldType) PricePerUnit int 
[__] (BasicVariable BasicType) PricePerUnit int 
[_] (FieldVariable FieldType) ProductID string 
[__] (BasicVariable BasicType) ProductID string 
[_] (FieldVariable FieldType) Quantity int 
[__] (BasicVariable BasicType) Quantity int 
[_] (FieldVariable FieldType) UserID string 
[__] (BasicVariable BasicType) UserID string 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (FieldVariable FieldType) Key "cartID" string 
[___] (BasicVariable BasicType) "cartID" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) cartID string 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) filter primitive.D 
[_] (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (FieldVariable FieldType) Key "cartID" string 
[___] (BasicVariable BasicType) "cartID" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) cartID string 

[] (SliceVariable UserType) update primitive.D 
[_] (StructVariable StructType) struct{Key "status" string, Value "completed" string} 
[__] (FieldVariable FieldType) Key "status" string 
[___] (BasicVariable BasicType) "status" string 
[__] (FieldVariable FieldType) Value "completed" string 
[___] (BasicVariable BasicType) "completed" string 

