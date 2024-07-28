[] (-1) (PointerVariable PointerType) c (*threechain2.CartServiceImpl struct{order_service threechain2.OrderService, cart_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) threechain2.CartServiceImpl struct{order_service threechain2.OrderService, cart_db NoSQLDatabase} 
[__] (-1) (ServiceVariable ServiceType) order_service threechain2.OrderService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase 

[] (1) (InterfaceVariable UserType) ctx context.Context 

[] (2) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 

[] (-1) (StructVariable UserType) cart threechain2.Cart struct{CartID string, Username string, ProductID string, Quantity int, PricePerUnit int, Status string} 
[_] (-1) (FieldVariable FieldType) Username string 
[__] (3) (BasicVariable BasicType) Username string // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), 
[_] (-1) (FieldVariable FieldType) ProductID string 
[__] (4) (BasicVariable BasicType) ProductID string // write(order_db), write(stock_db), write(billing_db), 
[_] (-1) (FieldVariable FieldType) Quantity int 
[__] (5) (BasicVariable BasicType) Quantity int // write(order_db), write(stock_db), write(billing_db), 
[_] (-1) (FieldVariable FieldType) PricePerUnit int 
[__] (6) (BasicVariable BasicType) PricePerUnit int // write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "cartID" string 
[___] (0) (BasicVariable BasicType) "cartID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (2) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{Key "cartID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "cartID" string 
[___] (0) (BasicVariable BasicType) "cartID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (2) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 

[] (-1) (SliceVariable UserType) update primitive.D 
[_] (0) (StructVariable StructType) struct{Key "status" string, Value "completed" string} 
[__] (0) (FieldVariable FieldType) Key "status" string 
[___] (0) (BasicVariable BasicType) "status" string 
[__] (0) (FieldVariable FieldType) Value "completed" string 
[___] (0) (BasicVariable BasicType) "completed" string 

