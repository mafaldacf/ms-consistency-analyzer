[] (-1) (PointerVariable PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase} 
[__] (-1) (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (-1) (ServiceVariable ServiceType) product_service shopping_app.ProductService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) cartID string 

[] (-1) (StructVariable UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string} 
[_] (-1) (FieldVariable FieldType) PricePerUnit int 
[__] (-1) (BasicVariable BasicType) PricePerUnit int 
[_] (-1) (FieldVariable FieldType) UserID string 
[__] (-1) (BasicVariable BasicType) UserID string 
[_] (-1) (FieldVariable FieldType) ProductID string 
[__] (-1) (BasicVariable BasicType) ProductID string 
[_] (-1) (FieldVariable FieldType) Quantity int 
[__] (-1) (BasicVariable BasicType) Quantity int 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "cartID" string 
[___] (0) (BasicVariable BasicType) "cartID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) cartID string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "cartID" string 
[___] (0) (BasicVariable BasicType) "cartID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) cartID string 

[] (-1) (SliceVariable UserType) update primitive.D 
[_] (0) (StructVariable StructType) struct{Key "status" string, Value "completed" string} 
[__] (0) (FieldVariable FieldType) Key "status" string 
[___] (0) (BasicVariable BasicType) "status" string 
[__] (0) (FieldVariable FieldType) Value "completed" string 
[___] (0) (BasicVariable BasicType) "completed" string 

